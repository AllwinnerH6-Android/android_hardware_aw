-include hardware/aw/wireless/bluetooth/firmware/xradio/xradio-bt.mk
-include hardware/aw/wireless/bluetooth/firmware/realtek/realtek-bt.mk
-include hardware/aw/wireless/bluetooth/firmware/broadcom/broadcom-bt.mk

# initrc for bluetooth
PRODUCT_COPY_FILES += \
    hardware/aw/wireless/bluetooth/config/init.bluetooth.common.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.bluetooth.common.rc

# realtek bluetooth run time config file
PRODUCT_COPY_FILES += \
    device/softwinner/$(basename $(TARGET_DEVICE))/configs/bluetooth/rtkbt.conf:$(TARGET_COPY_OUT_VENDOR)/etc/bluetooth/rtkbt.conf

# broadcom bluetooth run time config file
PRODUCT_COPY_FILES += \
    device/softwinner/$(basename $(TARGET_DEVICE))/configs/bluetooth/bt_vendor.conf:$(TARGET_COPY_OUT_VENDOR)/etc/bluetooth/bt_vendor.conf
