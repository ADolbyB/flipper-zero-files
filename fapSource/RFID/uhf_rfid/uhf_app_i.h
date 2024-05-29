#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <notification/notification_messages.h>

#include <gui/modules/submenu.h>
#include <gui/modules/popup.h>
#include <gui/modules/loading.h>
#include <gui/modules/text_input.h>
#include <gui/modules/widget.h>
#include <gui/modules/variable_item_list.h>

#include <input/input.h>

#include "uhf_app.h"
#include "uhf_worker.h"
#include "uhf_device.h"
#include "scenes/uhf_scene.h"

#include <storage/storage.h>
#include <lib/toolbox/path.h>
#include <toolbox/path.h>
#include <flipper_format/flipper_format.h>

#include <uhf_rfid_icons.h>

#define UHF_TEXT_STORE_SIZE 128
// #define UHF_APPS_DATA_FOLDER EXT_PATH("apps_data")
// #define UHF_APPS_STORAGE_FOLDER
//     UHF_APPS_DATA_FOLDER "/"
//                          "uhf_rfid"
// #define UHF_FILE_EXTENSION ".uhf"

enum UHFCustomEvent {
    // Reserve first 100 events for button types and indexes, starting from 0
    UHFCustomEventReserved = 100,

    UHFCustomEventVerifyDone,
    UHFCustomEventViewExit,
    UHFCustomEventWorkerExit,
    UHFCustomEventByteInputDone,
    UHFCustomEventTextInputDone,
    UHFCustomEventSceneSettingLock,
};

typedef enum {
    EventTypeTick,
    EventTypeKey,
} EventType;

struct UHFApp {
    UHFWorker* worker;
    ViewDispatcher* view_dispatcher;
    Gui* gui;
    NotificationApp* notifications;
    SceneManager* scene_manager;
    VariableItemList* variable_item_list;
    // Storage* storage;
    UHFDevice* uhf_device;
    char text_store[UHF_TEXT_STORE_SIZE + 1];
    FuriString* text_box_store;
    // Common Views
    Submenu* submenu;
    Popup* popup;
    Loading* loading;
    TextInput* text_input;
    Widget* widget;
    // view setting
    bool device_verified;
    bool view_device_info;
};

typedef enum {
    UHFViewMenu,
    UHFViewPopup,
    UHFViewLoading,
    UHFViewTextInput,
    UHFViewWidget,
    UHFViewVariableItemList,
} UHFView;

UHFApp* uhf_app_alloc();

void uhf_text_store_set(UHFApp* uhf, const char* text, ...);

void uhf_text_store_clear(UHFApp* uhf);

void uhf_blink_start(UHFApp* uhf);

void uhf_blink_stop(UHFApp* uhf);

void uhf_show_loading_popup(void* context, bool show);

/** Check if memory is set to pattern
 *
 * @warning    zero size will return false
 *
 * @param[in]  data     Pointer to the byte array
 * @param[in]  pattern  The pattern
 * @param[in]  size     The byte array size
 *
 * @return     True if memory is set to pattern, false otherwise
 */
bool uhf_is_memset(const uint8_t* data, const uint8_t pattern, size_t size);

char* convertToHexString(uint8_t* array, size_t length);

// bool uhf_save_read_data(UHFResponseData* uhf_response_data, Storage* storage, const char* filename);
