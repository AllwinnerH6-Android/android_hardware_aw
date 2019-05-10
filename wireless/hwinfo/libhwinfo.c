/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <poll.h>
#include <sys/stat.h>
#include <libhwinfo.h>
#define LOG_TAG "WifiHWInfo"
#include <log/log.h>
#include <cutils/properties.h>
#include <pthread.h>

#define ARRAY_SIZE(arr)         (sizeof(arr) / sizeof((arr)[0]))
#define UEVENT_MSG_LEN          1024
#define WIFI_SCAN_DEVICE_PATH   "/sys/devices/virtual/misc/sunxi-wlan/rf-ctrl/scan_device"
#define WIFI_POWER_STATE_PATH   "/sys/devices/virtual/misc/sunxi-wlan/rf-ctrl/power_state"
#define MODULE_WLAN_INFO_PROP   "persist.vendor.overlay.wlan.info"
#define MODULE_WLAN_VENDOR_PROP "persist.vendor.overlay.wlan.vendor"
#define MODULE_BT_SUPPORT_PROP  "persist.vendor.overlay.bluetooth.support"

#define LINE_MAX                1024
#define INFO_CONFIG_FILE        "/vendor/etc/hwinfo.conf"
#define CONFIG_SESSION_KEY      "[module]"

struct wifi_hardware_info {
    unsigned long device_id;
    char *module_name;
    char *driver_name;
    char *driver_module_name;
    char *vendor_name;
    char *fw_path_sta;
    char *fw_path_ap;
    char *fw_path_p2p;
    int  bt_support;
};

struct wl_hwinfo_list {
    struct wifi_hardware_info hwinfo;
    struct wl_hwinfo_list *next;
};

static const char *keytab[] = {
    "device_id",
    "module_name",
    "driver_name",
    "driver_module_name",
    "vendor_name",
    "fw_path_sta",
    "fw_path_ap",
    "fw_path_p2p",
    "bt_support"};

static const struct wifi_hardware_info wifi_list[] = {
    {
        .device_id   = 0x18179,
        .module_name = "rtl8189es",
        .driver_name = "8189es",
        .driver_module_name = "8189es",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
#ifdef WIFI_USE_RTL8723BS_VQ0
    {
        .device_id   = 0x1b723,
        .module_name = "rtl8723bs_vq0",
        .driver_name = "8723bs-vq0",
        .driver_module_name = "8723bs_vq0",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
#else
    {
        .device_id   = 0x1b723,
        .module_name = "rtl8723bs",
        .driver_name = "8723bs",
        .driver_module_name = "8723bs",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
#endif
    {
        .device_id   = 0x1b703,
        .module_name = "rtl8723cs",
        .driver_name = "8723cs",
        .driver_module_name = "8723cs",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x1d723,
        .module_name = "rtl8723ds",
        .driver_name = "8723ds",
        .driver_module_name = "8723ds",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
    {
        .device_id    = 0x08179,
        .module_name  = "rtl8188etv",
        .driver_name  = "8188eu",
        .driver_module_name  = "8188eu",
        .vendor_name  = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
    {
        .device_id    = 0x00179,
        .module_name  = "rtl8188eu",
        .driver_name  = "8188eu",
        .driver_module_name  = "8188eu",
        .vendor_name  = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
    {
        .device_id    = 0x0818b,
        .module_name  = "rtl8192eu",
        .driver_name  = "8192eu",
        .driver_module_name  = "8192eu",
        .vendor_name  = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
    {
        .device_id    = 0x0b720,
        .module_name  = "rtl8723bu",
        .driver_name  = "8723bu",
        .driver_module_name  = "8723bu",
        .vendor_name  = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x1f179,
        .module_name = "rtl8189fs",
        .driver_name = "8189fs",
        .driver_module_name = "8189fs",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
    {
        .device_id   = 0x1B822,
        .module_name = "rtl88x2bs",
        .driver_name = "88x2bs",
        .driver_module_name = "88x2bs",
        .vendor_name = "realtek",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x1a9a6,
        .module_name = "ap6212",
        .driver_name = "bcmdhd",
        .driver_module_name = "bcmdhd",
        .vendor_name = "broadcom",
        .fw_path_sta = "/system/vendor/modules/fw_bcm43438a0.bin",
        .fw_path_ap  = "/system/vendor/modules/fw_bcm43438a0_apsta.bin",
        .fw_path_p2p = "/system/vendor/modules/fw_bcm43438a0_p2p.bin",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x14330,
        .module_name = "ap6330",
        .driver_name = "bcmdhd",
        .driver_module_name = "bcmdhd",
        .vendor_name = "broadcom",
        .fw_path_sta = "/system/vendor/modules/fw_bcm40183b2_ag.bin",
        .fw_path_ap  = "/system/vendor/modules/fw_bcm40183b2_ag_apsta.bin",
        .fw_path_p2p = "/system/vendor/modules/fw_bcm40183b2_ag_p2p.bin",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x14356,
        .module_name = "ap6356s",
        .driver_name = "bcmdhd",
        .driver_module_name = "bcmdhd",
        .vendor_name = "broadcom",
        .fw_path_sta = "/system/vendor/modules/fw_bcm4356a2_ag.bin",
        .fw_path_ap  = "/system/vendor/modules/fw_bcm4356a2_apsta.bin",
        .fw_path_p2p = "/system/vendor/modules/fw_bcm4356a2_ag.bin",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x1a9bf,
        .module_name = "ap6255",
        .driver_name = "bcmdhd",
        .driver_module_name = "bcmdhd",
        .vendor_name = "broadcom",
        .fw_path_sta = "/system/vendor/modules/fw_bcm43455c0_ag.bin",
        .fw_path_ap  = "/system/vendor/modules/fw_bcm43455c0_ag_apsta.bin",
        .fw_path_p2p = "/system/vendor/modules/fw_bcm43455c0_ag.bin",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x12281,
        .module_name = "xr819",
        .driver_name = "xradio_wlan",
        .driver_module_name = "xradio_wlan",
        .vendor_name = "xradio",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    },
    {
        .device_id   = 0x12282,
        .module_name = "xr829",
        .driver_name = "xradio_wlan",
        .driver_module_name = "xradio_wlan",
        .vendor_name = "xradio",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 1,
    },
    {
        .device_id   = 0x1050a,
        .module_name = "qca6174a",
        .driver_name = "qualcomm",
        .driver_module_name = "qualcomm",
        .vendor_name = "atheros",
        .fw_path_sta = "STA",
        .fw_path_ap  = "AP",
        .fw_path_p2p = "P2P",
        .bt_support  = 0,
    }
};
/* default select rtl8189es if get wifi_hardware_info failed */
static struct wifi_hardware_info selected_wifi = {
    0x18179, "rtl8189es", "8189es", "8189es", "realtek", "STA", "AP", "P2P", 0
};

static enum {
    running,
    exiting,
    exited
} thread_state = exited;

static struct wl_hwinfo_list *head = NULL;

static int search_key(const char *str, const char *key)
{
    const char *p = NULL;
    int keysize = 0;
    int bufsize = 0;

    if (str == NULL || key == NULL) return -1;

    keysize = strlen(key);
    bufsize = strlen(str);
    if (bufsize < keysize) return -1;

    p = str;
    while (*p != 0 && *p == ' ') p++;

    if (*p == '#') return -1;

    if (str + bufsize - p < keysize) return -1;

    if (strncmp(p, key, keysize) != 0) return -1;

    p += keysize;

    while (*p != 0 && *p == ' ') p++;

    if (*p != 0 && *p != '\r' && *p != '\n') return -1;

    return 0;
}

static int search_key_val(const char *str, const char *key, char *val)
{
    const char *p = NULL;
    const char *dst = NULL;
    int keysize = 0;
    int bufsize = 0;

    if (str == NULL || key == NULL || val == NULL) return -1;

    keysize = strlen(key);
    bufsize = strlen(str);
    if (bufsize <= keysize) return -1;

    p = str;
    while (*p != 0 && *p == ' ') p++;

    if (*p == '#') return -1;

    if (str + bufsize - p <= keysize) return -1;

    if (strncmp(p, key, keysize) != 0) return -1;

    p += keysize;

    while (*p != 0 && *p == ' ') p++;

    if (*p != '=') return -1;

    p++;
    while (*p != 0 && *p == ' ') p++;

    if (*p == '"') p++;

    dst = p;
    while (*p != 0) p++;

    p--;
    while (*p == ' ') p--;

    if (*p == '"') p--;

    while (*p == '\r' || *p == '\n') p--;

    p++;
    strncpy(val, dst, p -dst);
    val[p - dst] = 0;
    return 0;
}

static struct wl_hwinfo_list *load_config_from_file(const char *filename)
{
    FILE *fp   = NULL;
    char *cstr = NULL;
    uint32_t i = 0;
    uint32_t start = 0;
    char conf[256];
    char buf[LINE_MAX];
    const  char *key = NULL;
    static struct wl_hwinfo_list *head = NULL;
    struct wl_hwinfo_list *new  = NULL;
    struct wl_hwinfo_list *cur  = NULL;

    if ((fp = fopen(filename, "r")) == NULL) {
        ALOGE("Open config file %s error!\n", filename);
        return head;
    }

    while (fgets(buf, LINE_MAX, fp)) {
        if (search_key(buf, CONFIG_SESSION_KEY) == 0) {
            if (start == 0) {
                new = (struct wl_hwinfo_list *)malloc(sizeof(struct wl_hwinfo_list));
                memset(new, 0, sizeof(struct wl_hwinfo_list));
                if (head == NULL) {
                    head = new;
                    cur  = new;
                } else {
                    cur = head;
                    while (cur->next != NULL)
                        cur = cur->next;
                    cur->next = new;
                    cur       = cur->next;
                }
            }
            start = 1;
            continue;
        }

        for (i = 0; i < sizeof(keytab) / sizeof(keytab[0]); i++) {
            key = keytab[i];
            if (search_key_val(buf, key, conf) == 0) {
                switch (i) {
                    case 0:
                        cur->hwinfo.device_id = strtol(conf, NULL, 0);
                        break;
                    case 1:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.module_name = cstr;
                        break;
                    case 2:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.driver_name = cstr;
                        break;
                    case 3:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.driver_module_name = cstr;
                        break;
                    case 4:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.vendor_name = cstr;
                        break;
                    case 5:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.fw_path_sta = cstr;
                        break;
                    case 6:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.fw_path_ap = cstr;
                        break;
                    case 7:
                        cstr = (char *)malloc(strlen(conf) + 1);
                        strcpy(cstr, conf);
                        cur->hwinfo.fw_path_p2p = cstr;
                        break;
                    case 8:
                        cur->hwinfo.bt_support = strtol(conf, NULL, 0);
                        break;
                    default:
                        break;
                }
                start = 0;
            }
        }
    }
    return head;
}

static struct wl_hwinfo_list *load_config_from_local(const struct wifi_hardware_info *list, uint32_t num)
{
    struct wifi_hardware_info *p = (struct wifi_hardware_info *)list;
    static struct wl_hwinfo_list *head = NULL;
    struct wl_hwinfo_list *new  = NULL;
    struct wl_hwinfo_list *cur  = NULL;
    char  *cstr = NULL;

    while (num--) {
        new = (struct wl_hwinfo_list *)malloc(sizeof(struct wl_hwinfo_list));
        memset(new, 0, sizeof(struct wl_hwinfo_list));
        if (head == NULL) {
            head = new;
            cur  = new;
        } else {
            cur = head;
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = new;
            cur       = cur->next;
        }

        cur->hwinfo.device_id = p->device_id;

        cstr = (char *)malloc(strlen(p->module_name) + 1);
        strcpy(cstr, p->module_name);
        cur->hwinfo.module_name = cstr;

        cstr = (char *)malloc(strlen(p->driver_name) + 1);
        strcpy(cstr, p->driver_name);
        cur->hwinfo.driver_name = cstr;

        cstr = (char *)malloc(strlen(p->driver_module_name) + 1);
        strcpy(cstr, p->driver_module_name);
        cur->hwinfo.driver_module_name = cstr;

        cstr = (char *)malloc(strlen(p->vendor_name) + 1);
        strcpy(cstr, p->vendor_name);
        cur->hwinfo.vendor_name = cstr;

        cstr = (char *)malloc(strlen(p->fw_path_sta) + 1);
        strcpy(cstr, p->fw_path_sta);
        cur->hwinfo.fw_path_sta = cstr;

        cstr = (char *)malloc(strlen(p->fw_path_ap) + 1);
        strcpy(cstr, p->fw_path_ap);
        cur->hwinfo.fw_path_ap = cstr;

        cstr = (char *)malloc(strlen(p->fw_path_p2p) + 1);
        strcpy(cstr, p->fw_path_p2p);
        cur->hwinfo.fw_path_p2p = cstr;

        cur->hwinfo.bt_support = p->bt_support;

        p++;
    }
    return head;
}

static struct wl_hwinfo_list *load_merged_config(void)
{
    struct wl_hwinfo_list *h1   = load_config_from_local(wifi_list, sizeof(wifi_list) / sizeof(wifi_list[0]));
    struct wl_hwinfo_list *h2   = load_config_from_file(INFO_CONFIG_FILE);
    struct wl_hwinfo_list *p1   = NULL;
    struct wl_hwinfo_list *p2   = NULL;
    struct wl_hwinfo_list *head = NULL;
    uint32_t delete_node = 0;

    if (h1 == NULL) {
        head = h2;
        goto merge;
    }

    head = h1;
    p1   = head;
    while (p1->next != NULL)
        p1 = p1->next;

    p1->next = h2;

merge:
    p1 = head;
    h1 = head;
    h2 = head;
    while (p1 != NULL && p1->next != NULL) {
        p2 = p1->next;
        while (p2 != NULL) {
            if (p1->hwinfo.device_id == p2->hwinfo.device_id) {
                delete_node = 1;
                p2 = p2->next;
                break;
            }
            p2 = p2->next;
        }

        p1 = p1->next;
        if (delete_node) {
            delete_node = 0;
            if (h2 == head) {
                h1 = p1;
                head = h1;
            } else {
                h1->next = p1;
            }
            free(h2->hwinfo.module_name);
            free(h2->hwinfo.driver_name);
            free(h2->hwinfo.driver_module_name);
            free(h2->hwinfo.vendor_name);
            free(h2->hwinfo.fw_path_sta);
            free(h2->hwinfo.fw_path_ap);
            free(h2->hwinfo.fw_path_p2p);
            free(h2);
        } else {
            h1 = h2;
        }
        h2 = p1;
    }
    return head;
}

static int get_hardware_info_by_module_name(const char *module_name, struct wifi_hardware_info *wifiinfo)
{
    struct wl_hwinfo_list *cur = head;

    if (strcmp(wifiinfo->module_name, module_name) == 0) {
        return 0;
    }

    while (cur != NULL) {
        if (strcmp(cur->hwinfo.module_name, module_name) == 0) {
            *wifiinfo = cur->hwinfo;
            return 0;
        }
        cur = cur->next;
    }
    return -1;
}

static int get_hardware_info_by_device_id(const unsigned long device_id, struct wifi_hardware_info *wifiinfo)
{
    struct wl_hwinfo_list *cur = head;

    if (wifiinfo->device_id == device_id) {
        return 0;
    }

    while (cur != NULL) {
        if (cur->hwinfo.device_id == device_id) {
            *wifiinfo = cur->hwinfo;
            return 0;
        }
        cur = cur->next;
    }
    return -1;
}

static int wifi_power_on(void)
{
    int fd = 0;
    int size = 0;
    char store_state = 0;
    char to_write = '1';

    fd = open(WIFI_POWER_STATE_PATH, O_RDWR);
    if (fd < 0) {
        ALOGE("%s error:%d %s###", __FUNCTION__, errno, strerror(errno));
        return -1;
    }

    size = read(fd, &store_state, sizeof(store_state));
    if (size <= 0) {
        close(fd);
        return -1;
    }

    if ((store_state - '0') > 0)
        return 1;

    size = write(fd, &to_write, sizeof(to_write));
    if (size < 0) {
        close(fd);
        return -1;
    }

    size = read(fd, &store_state, sizeof(store_state));
    if (size <= 0) {
        close(fd);
        return -1;
    }

    close(fd);
    return (store_state - '0');
}

static int wifi_power_off(void)
{
    int fd = 0;
    int size = 0;
    char to_write = '0';

    fd = open(WIFI_POWER_STATE_PATH, O_WRONLY);
    if (fd < 0) {
        return -1;
    }
    size = write(fd, &to_write, sizeof(to_write));
    if (size < 0) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

static int wifi_scan_device(int val)
{
    int fd = 0;
    int size = 0;
    char to_write = val ? '1' : '0';

    fd = open(WIFI_SCAN_DEVICE_PATH, O_WRONLY);
    if (fd < 0) {
        return -1;
    }

    size = write(fd, &to_write, sizeof(to_write));
    if (size < 0) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

static void parse_uevent(char *msg, struct wifi_hardware_info *wifiinfo)
{
    char sdio_device_id[10] = {0};
    char device_type[10] = {0};
    char *subsystem = NULL;
    char *sdio_id = NULL;
    char *usb_product = NULL;
    unsigned long device_id = 0;

    while (*msg) {
        if (!strncmp(msg, "SUBSYSTEM=", 10)) {
            msg += 10;
            subsystem = msg;
        } else if (!strncmp(msg, "SDIO_ID=", 8)) {
            msg += 8;
            sdio_id = msg;
        } else if (!strncmp(msg, "PRODUCT=", 8)) {
            msg += 8;
            usb_product = msg;
        }

        /* advance to after the next \0 */
        while (*msg++) {
            /* do nothing */
        }
    }

    if (!strncmp(subsystem, "sdio", 4)) {
        ALOGI("get uevent, sdio_id = %s", sdio_id);
        strcpy(device_type, "sdio");
        char *subid = strrchr(sdio_id, ':');
        if (subid == NULL) {
            return;
        }
        subid++;
        strcpy(sdio_device_id, subid);
        device_id = strtoul(sdio_device_id, NULL, 16);
        device_id += 0x10000;
    } else if (!strncmp(subsystem, "usb", 3)) {
        strcpy(device_type, "usb");
        char *subid = NULL;

        strtok(usb_product, "/");
        subid = strtok( NULL, "/");
        if (subid == NULL) {
            return;
        }
        device_id = strtoul(subid, NULL, 16);
    } else {
        return;
    }

    ALOGI("parse_uevent(), device_id: 0x%lx", device_id);
    if (!get_hardware_info_by_device_id(device_id, wifiinfo)) {
        char info[PROPERTY_VALUE_MAX] = {0};
        snprintf(info, sizeof(info), "%s:%s", wifiinfo->vendor_name, wifiinfo->module_name);
        ALOGD("setprop %s=%s", MODULE_WLAN_INFO_PROP, info);
        property_set(MODULE_WLAN_INFO_PROP, info);
        thread_state = exiting;
    }
}

static void * ls_device_thread(void *args)
{
    struct wifi_hardware_info *wifiinfo = (struct wifi_hardware_info *)args;
    char buf[UEVENT_MSG_LEN + 2] = {0};
    int count;
    int err;
    int retval;
    struct sockaddr_nl snl;
    int sock;
    struct pollfd fds;
    const int buffersize = 32*1024;

    thread_state = running;
    memset(&snl, 0x0, sizeof(snl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = 0;
    snl.nl_groups = 0xffffffff;
    sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (sock < 0) {
        ALOGE("####socket is failed in %s error:%d %s###", __FUNCTION__, errno, strerror(errno));
        return((void *)-1);
    }
    setsockopt(sock, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
    retval = bind(sock, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (retval < 0) {
        ALOGE("####bind is failed in %s error:%d %s###", __FUNCTION__, errno, strerror(errno));
        close(sock);
       return((void *)-1);
    }

    while (running == thread_state) {
        fds.fd = sock;
        fds.events = POLLIN;
        fds.revents = 0;
        err = poll(&fds, 1, 1000);
        memset(buf, '\0', sizeof(char) * 1024);
        if (err > 0 && (fds.revents & POLLIN)) {
            count = recv(sock, buf, sizeof(char) * 1024,0);
            if (count > 0) {
                parse_uevent(buf, wifiinfo);
            }
        }
    }

    close(sock);
    thread_state = exited;
    return((void *)0);
}

static int do_coldboot(DIR *d, struct wifi_hardware_info *wifiinfo)
{
    struct dirent *de;
    int dfd, dfd2, fd, fd2;

    dfd = dirfd(d);

    while ((de = readdir(d))) {
        DIR *d2;

        if (de->d_name[0] == '.')
            continue;

        fd = openat(dfd, de->d_name, O_RDONLY | O_DIRECTORY);
        if (fd < 0)
            continue;

        d2 = fdopendir(fd);
        if (d2 == 0)
            close(fd);
        else {
            dfd2 = dirfd(d2);
            fd2 = openat(dfd2, "uevent", O_RDONLY);
            if (fd >= 0) {
                char *buf = NULL, *buf_tmp = NULL;
                char sdio_device_id[10] = {0};
                char sdio_id[10] = {0};
                unsigned long device_id = 0;

                buf = buf_tmp = malloc(UEVENT_MSG_LEN + 2);
                memset(buf, 0 , UEVENT_MSG_LEN + 2);

                read(fd2, buf, UEVENT_MSG_LEN);
                while (*buf) {
                    if (!strncmp(buf, "SDIO_ID=", 8)) {
                        buf += 8;
                        strncpy(sdio_id, buf, 9);
                        ALOGE("read from sdio path, sdio_id=%s", sdio_id);
                        char *subid = strrchr(sdio_id, ':');
                        subid++;
                        strcpy(sdio_device_id, subid);
                        device_id = strtoul(sdio_device_id, NULL, 16);
                        device_id += 0x10000;
                        break;
                    }
                    buf++;
                }
                close(fd2);
                free(buf_tmp);
                if (!get_hardware_info_by_device_id(device_id, wifiinfo)) {
                    char info[PROPERTY_VALUE_MAX] = {0};
                    snprintf(info, sizeof(info), "%s:%s", wifiinfo->vendor_name, wifiinfo->module_name);
                    ALOGI("setprop %s=%s", MODULE_WLAN_INFO_PROP, info);
                    property_set(MODULE_WLAN_INFO_PROP, info);
                    closedir(d2);
                    return 0;
               }
            }
            closedir(d2);
        }
    }
    return 1;
}

static int coldboot(const char *path, struct wifi_hardware_info *wifiinfo)
{
    int ret = 1;
    DIR *d = opendir(path);

    if (d) {
        ret = do_coldboot(d, wifiinfo);
        closedir(d);
    }
    return ret;
}

static void get_wifi_hardware_info(struct wifi_hardware_info *wifiinfo)
{
    char info[PROPERTY_VALUE_MAX] = {0};
    int ret = 0;
    pthread_t ls_device_thread_fd;
    int store_power_state = 0;
    static bool initialed = false;
    struct wl_hwinfo_list *cur = NULL;
    int entrynum = 0;

    if (initialed == false) {

        ALOGD("Start to load wireless module hardware info table...");
        head = load_merged_config();
        cur  = head;
        while (cur != NULL) {
            entrynum++;
            ALOGD("Find Entry, ID: 0x%08lX, Name: %s.", cur->hwinfo.device_id, cur->hwinfo.module_name);
            cur = cur->next;
        }
        ALOGD("Load info table done, find %d Entry!", entrynum);
#if defined(WIFI_VENDOR_NAME) && defined(WIFI_MODULE_NAME) && defined(WIFI_DRIVER_NAME) && defined(WIFI_DRIVER_MODULE_NAME)
        wifiinfo->vendor_name = WIFI_VENDOR_NAME;
        wifiinfo->module_name = WIFI_MODULE_NAME;
        wifiinfo->driver_name = WIFI_DRIVER_NAME;
        wifiinfo->driver_module_name = WIFI_DRIVER_MODULE_NAME;
#if defined(WIFI_DRIVER_FW_PATH_STA)
        wifiinfo->fw_path_sta = WIFI_DRIVER_FW_PATH_STA;
#endif

#if defined(WIFI_DRIVER_FW_PATH_AP)
        wifiinfo->fw_path_ap = WIFI_DRIVER_FW_PATH_AP;
#endif

#if defined(WIFI_DRIVER_FW_PATH_P2P)
        wifiinfo->fw_path_p2p = WIFI_DRIVER_FW_PATH_P2P;
#endif
        snprintf(info, sizeof(info), "%s:%s", WIFI_VENDOR_NAME, WIFI_MODULE_NAME);
        property_set(MODULE_WLAN_INFO_PROP, info);
#else

start:
        if (property_get(MODULE_WLAN_INFO_PROP, info, NULL) > 0) {
            char *module_name = strchr(info, ':');
            if (module_name == NULL) {
                property_set(MODULE_WLAN_INFO_PROP, "");
                goto start;
            }

            module_name++;
            if (get_hardware_info_by_module_name(module_name, wifiinfo)) {
                property_set(MODULE_WLAN_INFO_PROP, "");
                goto start;
            }
        } else {
            ALOGD("%s not exist, try to create it!", MODULE_WLAN_INFO_PROP);
            if (!coldboot("/sys/bus/sdio/devices", wifiinfo))
                goto start;

            ret = pthread_create(&ls_device_thread_fd, NULL, ls_device_thread, wifiinfo);
            if (ret) {
                ALOGE("Create ls_device_thread error!\n");
                return;
            }

            int i = 0;
            while ((i++ < 10) && (store_power_state <= 0)) {
                if ((store_power_state = wifi_power_on()) == 1)
                    break;
                usleep(100000);
            }

            if (store_power_state <= 0)
                return;

            wifi_scan_device(1);

            for (i = 0; i < 20; i++) {
                if (exited == thread_state)
                    break;

                if (property_get(MODULE_WLAN_INFO_PROP, info, NULL) > 0)
                    break;
                usleep(100000);
            }

            if (running == thread_state) {
                ALOGE("get uevent timeout!\n");
                thread_state = exiting;
            }

            wifi_power_off();
            wifi_scan_device(0);
        }
#endif
        initialed = true;
        property_set(MODULE_WLAN_VENDOR_PROP, wifiinfo->vendor_name);
        property_set(MODULE_BT_SUPPORT_PROP,  wifiinfo->bt_support ? "1" : "0");
    }
}

const char *get_wifi_vendor_name()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.vendor_name;
}

const char *get_wifi_module_name()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.module_name;
}

const char *get_wifi_driver_name()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.driver_name;
}

const char *get_wifi_driver_module_name()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.driver_module_name;
}

const char *get_fw_path_sta()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.fw_path_sta;
}

const char *get_fw_path_ap()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.fw_path_ap;
}

const char *get_fw_path_p2p()
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.fw_path_p2p;
}

void get_driver_module_arg(char* arg)
{
    char module_arg[256] = {0};

#if defined(WIFI_VENDOR_NAME) && defined(WIFI_MODULE_NAME) && defined(WIFI_DRIVER_NAME) && defined(WIFI_DRIVER_MODULE_NAME)

#ifdef WIFI_DRIVER_MODULE_ARG
    const char *driver_module_arg = WIFI_DRIVER_MODULE_ARG;
    snprintf(module_arg, sizeof(module_arg), "%s", driver_module_arg);
#endif

#else
    const char *vendor_name = get_wifi_vendor_name();
    if(strcmp(vendor_name, "realtek") == 0) {
        const char *driver_module_arg = "ifname=wlan0 if2name=p2p0";
        snprintf(module_arg, sizeof(module_arg), "%s", driver_module_arg);
    } else if(strcmp(vendor_name, "broadcom") == 0) {
        const char *nvram_path = "nvram_path=/system/vendor/modules/nvram";
        const char *config_path = "config_path=/system/vendor/modules/config";
        snprintf(module_arg, sizeof(module_arg), "%s_%s.txt %s_%s.txt",
                nvram_path, get_wifi_module_name(), config_path, get_wifi_module_name());
    }else if(strcmp(get_wifi_vendor_name(), "xradio") == 0) {
        const char *driver_module_arg = "";
        snprintf(module_arg, sizeof(module_arg), "%s", driver_module_arg);
    } else if(strcmp(vendor_name, "atheros") == 0){
            const char *driver_module_arg = "";
            snprintf(module_arg, sizeof(module_arg), "%s", driver_module_arg);
    }
#endif
    strcpy(arg, module_arg);
}

const char *get_wifi_hal_name(const char *vendor_name)
{
    if (strncmp(vendor_name, "realtek", sizeof("realtek")) == 0) {
        return "libwifi-hal-rtk.so";
    } else if (strncmp(vendor_name, "broadcom", sizeof("broadcom")) == 0) {
        return "libwifi-hal-bcm.so";
    } else if (strncmp(vendor_name, "qualcomm", sizeof("qualcomm")) == 0) {
        return "libwifi-hal-qcom.so";
    } else if (strncmp(vendor_name, "xradio", sizeof("xradio")) == 0) {
        return "libwifi-hal-xradio.so";
    }
    return NULL;
}

const char *get_bluetooth_libbt_name(void)
{
    const char *vendor_name = get_wifi_vendor_name();
    if (strncmp(vendor_name, "realtek", sizeof("realtek")) == 0) {
        return "libbt-realtek.so";
    } else if (strncmp(vendor_name, "broadcom", sizeof("broadcom")) == 0) {
        return "libbt-broadcom.so";
    } else if (strncmp(vendor_name, "qualcomm", sizeof("qualcomm")) == 0) {
        return "libbt-qualcomm.so";
    } else if (strncmp(vendor_name, "xradio", sizeof("xradio")) == 0) {
        return "libbt-xradio.so";
    }
    return NULL;
}

int get_bluetooth_is_support(void)
{
    get_wifi_hardware_info(&selected_wifi);
    return selected_wifi.bt_support;
}
