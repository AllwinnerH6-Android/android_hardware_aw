
#include "CameraMetadata.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "format_metadata_factory.h"
#include "metadata/test_common.h"
#include "v4l2_wrapper_mock.h"

using testing::AtLeast;
using testing::Expectation;
using testing::Return;
using testing::SetArgPointee;
using testing::Test;
using testing::_;

namespace v4l2_camera_hal {
  
using ::android::hardware::camera::common::V1_0::helper::CameraMetadata;

class FormatMetadataFactoryTest : public Test {
 protected:
  virtual void SetUp() { mock_device_.reset(new V4L2WrapperMock()); }

  virtual void ExpectMetadataTagCount(const CameraMetadata& metadata,
                                      uint32_t tag,
                                      size_t count) {
    camera_metadata_ro_entry_t entry = metadata.find(tag);
    EXPECT_EQ(entry.count, count);
  }

  std::shared_ptr<V4L2WrapperMock> mock_device_;
};

TEST_F(FormatMetadataFactoryTest, GetFormatMetadata) {
  std::set<uint32_t> formats{V4L2_PIX_FMT_JPEG, V4L2_PIX_FMT_YUV420};
  std::map<uint32_t, std::set<std::array<int32_t, 2>>> sizes{
      {V4L2_PIX_FMT_JPEG, {{{10, 20}}, {{30, 60}}, {{120, 240}}}},
      {V4L2_PIX_FMT_YUV420, {{{1, 2}}, {{3, 6}}, {{12, 24}}}}};
  // These need to be on the correct order of magnitude,
  // as there is a check for min fps > 15.
  std::map<uint32_t, std::map<std::array<int32_t, 2>, std::array<int64_t, 2>>>
      durations{{V4L2_PIX_FMT_JPEG,
                 {{{{10, 20}}, {{100000000, 200000000}}},
                  {{{30, 60}}, {{1000000000, 2000000000}}},
                  {{{120, 240}}, {{700000000, 1200000000}}}}},
                {V4L2_PIX_FMT_YUV420,
                 {{{{1, 2}}, {{10000000000, 20000000000}}},
                  {{{3, 6}}, {{11000000000, 21000000000}}},
                  {{{12, 24}}, {{10500000000, 19000000000}}}}}};

  // Device must support IMPLEMENTATION_DEFINED (as well as JPEG & YUV).
  // Just duplicate the values from another format.
  uint32_t imp_defined_format = StreamFormat::HalToV4L2PixelFormat(
      HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED);
  formats.insert(imp_defined_format);
  sizes[imp_defined_format] = sizes[V4L2_PIX_FMT_YUV420];
  durations[imp_defined_format] = durations[V4L2_PIX_FMT_YUV420];

  EXPECT_CALL(*mock_device_, GetFormats(_))
      .WillOnce(DoAll(SetArgPointee<0>(formats), Return(0)));

  for (auto format : formats) {
    std::set<std::array<int32_t, 2>> format_sizes = sizes[format];
    EXPECT_CALL(*mock_device_, GetFormatFrameSizes(format, _))
        .Times(AtLeast(1))
        .WillRepeatedly(DoAll(SetArgPointee<1>(format_sizes), Return(0)));
    for (auto size : format_sizes) {
      EXPECT_CALL(*mock_device_, GetFormatFrameDurationRange(format, size, _))
          .Times(AtLeast(1))
          .WillRepeatedly(
              DoAll(SetArgPointee<2>(durations[format][size]), Return(0)));
    }
  }

  PartialMetadataSet components;
  ASSERT_EQ(AddFormatComponents(mock_device_,
                                std::inserter(components, components.end())),
            0);

  for (auto& component : components) {
    CameraMetadata metadata;
    component->PopulateStaticFields(&metadata);
    ASSERT_EQ(metadata.entryCount(), 1);
    int32_t tag = component->StaticTags()[0];
    switch (tag) {
      case ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS:  // Fall through.
      case ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS:    // Fall through.
      case ANDROID_SCALER_AVAILABLE_STALL_DURATIONS:        // Fall through.
        // 3 sizes per format, 4 elements per config.
        // # formats + 1 for IMPLEMENTATION_DEFINED.
        ExpectMetadataTagCount(metadata, tag, (formats.size() + 1) * 3 * 4);
        break;
      case ANDROID_SENSOR_INFO_MAX_FRAME_DURATION:
        // The lowest max duration from above.
        ExpectMetadataEq(metadata, tag, 200000000);
        break;
      case ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES:
        // 2 ranges ({min, max} and {max, max}), each with a min and max.
        ExpectMetadataTagCount(metadata, tag, 4);
        break;
      default:
        FAIL() << "Unexpected component created.";
        break;
    }
  }
}

TEST_F(FormatMetadataFactoryTest, GetFormatMetadataMissingJpeg) {
  uint32_t imp_defined_format = StreamFormat::HalToV4L2PixelFormat(
      HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED);
  std::set<uint32_t> formats{V4L2_PIX_FMT_YUV420, imp_defined_format};
  EXPECT_CALL(*mock_device_, GetFormats(_))
      .WillOnce(DoAll(SetArgPointee<0>(formats), Return(0)));
  PartialMetadataSet components;
  ASSERT_EQ(AddFormatComponents(mock_device_,
                                std::inserter(components, components.end())),
            -ENODEV);
}

TEST_F(FormatMetadataFactoryTest, GetFormatMetadataMissingYuv) {
  uint32_t imp_defined_format = StreamFormat::HalToV4L2PixelFormat(
      HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED);
  std::set<uint32_t> formats{V4L2_PIX_FMT_JPEG, imp_defined_format};
  EXPECT_CALL(*mock_device_, GetFormats(_))
      .WillOnce(DoAll(SetArgPointee<0>(formats), Return(0)));
  PartialMetadataSet components;
  ASSERT_EQ(AddFormatComponents(mock_device_,
                                std::inserter(components, components.end())),
            -ENODEV);
}

TEST_F(FormatMetadataFactoryTest,
       GetFormatMetadataMissingImplementationDefined) {
  std::set<uint32_t> formats{V4L2_PIX_FMT_JPEG, V4L2_PIX_FMT_YUV420};
  EXPECT_CALL(*mock_device_, GetFormats(_))
      .WillOnce(DoAll(SetArgPointee<0>(formats), Return(0)));
  PartialMetadataSet components;
  ASSERT_EQ(AddFormatComponents(mock_device_,
                                std::inserter(components, components.end())),
            -ENODEV);
}

}  // namespace v4l2_camera_hal
