#pragma once

#include <furi.h>
#include <furi_hal_bt.h>
#include <furi_hal_usb.h>
#include <furi_hal_usb_hid.h>

#include <extra_profiles/hid_profile.h>

#include <bt/bt_service/bt.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <notification/notification.h>
#include <storage/storage.h>

#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/popup.h>
#include "views/hid_keynote.h"
#include "scenes/hid_scene.h"

#define HID_BT_KEYS_STORAGE_NAME ".bt_hid.keys"

typedef enum {
    HidTransportUsb,
    HidTransportBle,
} HidTransport;

typedef struct Hid Hid;

struct Hid {
    FuriHalBleProfileBase* ble_hid_profile;
    Bt* bt;
    Gui* gui;
    NotificationApp* notifications;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;
    Submenu* device_type_submenu;
    DialogEx* dialog;
    Popup* popup;
    HidKeynote* hid_keynote;

    HidTransport transport;
    uint32_t view_id;
};
void bt_hid_remove_pairing(Hid* app);

void hid_hal_keyboard_press(Hid* instance, uint16_t event);
void hid_hal_keyboard_release(Hid* instance, uint16_t event);
void hid_hal_keyboard_release_all(Hid* instance);

void hid_hal_consumer_key_press(Hid* instance, uint16_t event);
void hid_hal_consumer_key_release(Hid* instance, uint16_t event);
void hid_hal_consumer_key_release_all(Hid* instance);

/*void hid_hal_mouse_move(Hid* instance, int8_t dx, int8_t dy);
void hid_hal_mouse_scroll(Hid* instance, int8_t delta);
void hid_hal_mouse_press(Hid* instance, uint16_t event);
void hid_hal_mouse_release(Hid* instance, uint16_t event);
void hid_hal_mouse_release_all(Hid* instance);*/
