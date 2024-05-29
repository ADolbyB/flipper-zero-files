#include "../uhf_app_i.h"
#include <dolphin/dolphin.h>

void uhf_read_tag_success_worker_callback(UHFWorkerEvent event, void* ctx) {
    UNUSED(event);
    UNUSED(ctx);
}

void uhf_scene_read_card_success_widget_callback(GuiButtonType result, InputType type, void* ctx) {
    furi_assert(ctx);
    UHFApp* uhf_app = ctx;

    if(type == InputTypeShort) {
        view_dispatcher_send_custom_event(uhf_app->view_dispatcher, result);
    }
}

void uhf_scene_read_tag_success_on_enter(void* ctx) {
    UHFApp* uhf_app = ctx;
    UHFTag* uhf_tag = uhf_app->worker->uhf_tag_wrapper->uhf_tag;
    FuriString* temp_str = furi_string_alloc();

    dolphin_deed(DolphinDeedNfcReadSuccess);

    // Send notification
    notification_message(uhf_app->notifications, &sequence_success);

    widget_add_string_element(
        uhf_app->widget, 32, 5, AlignLeft, AlignCenter, FontPrimary, "Read Success");

    widget_add_string_element(uhf_app->widget, 3, 18, AlignLeft, AlignCenter, FontPrimary, "PC :");

    widget_add_string_element(
        uhf_app->widget, 66, 18, AlignLeft, AlignCenter, FontPrimary, "CRC :");

    widget_add_string_element(
        uhf_app->widget, 3, 32, AlignLeft, AlignCenter, FontPrimary, "EPC :");

    furi_string_cat_printf(temp_str, "%04X", uhf_tag->epc->pc);
    widget_add_string_element(
        uhf_app->widget,
        26,
        19,
        AlignLeft,
        AlignCenter,
        FontKeyboard,
        furi_string_get_cstr(temp_str));
    furi_string_reset(temp_str);
    furi_string_cat_printf(temp_str, "%04X", uhf_tag->epc->crc);
    widget_add_string_element(
        uhf_app->widget,
        96,
        19,
        AlignLeft,
        AlignCenter,
        FontKeyboard,
        furi_string_get_cstr(temp_str));
    char* epc = convertToHexString(uhf_tag->epc->data, uhf_tag->epc->size);
    if(epc != NULL) {
        widget_add_string_multiline_element(
            uhf_app->widget, 34, 29, AlignLeft, AlignTop, FontKeyboard, epc);
    }
    widget_add_button_element(
        uhf_app->widget,
        GuiButtonTypeRight,
        "More",
        uhf_scene_read_card_success_widget_callback,
        uhf_app);
    widget_add_button_element(
        uhf_app->widget,
        GuiButtonTypeLeft,
        "Exit",
        uhf_scene_read_card_success_widget_callback,
        uhf_app);
    view_dispatcher_switch_to_view(uhf_app->view_dispatcher, UHFViewWidget);
    free(epc);
    furi_string_free(temp_str);
}

bool uhf_scene_read_tag_success_on_event(void* ctx, SceneManagerEvent event) {
    UHFApp* uhf_app = ctx;
    bool consumed = false;
    if(event.event == SceneManagerEventTypeBack) {
        uhf_app->worker->state = UHFWorkerStateStop;
    }
    if(event.type == SceneManagerEventTypeCustom) {
        // if 'exit' is pressed go back to home screen
        if(event.event == GuiButtonTypeLeft) {
            consumed = scene_manager_search_and_switch_to_previous_scene(
                uhf_app->scene_manager, UHFSceneStart);
        } else if(event.event == GuiButtonTypeRight) {
            scene_manager_next_scene(uhf_app->scene_manager, UHFSceneTagMenu);
            consumed = true;
        } else if(event.event == GuiButtonTypeCenter) {
            // consumed = scene_manager_search_and_switch_to_another_scene(
            //     picopass->scene_manager, PicopassSceneStart);
        }
    }
    return consumed;
}

void uhf_scene_read_tag_success_on_exit(void* ctx) {
    UHFApp* uhf_app = ctx;

    // // Stop worker
    uhf_worker_stop(uhf_app->worker);
    // Clear view
    popup_reset(uhf_app->popup);
    // clear widget
    widget_reset(uhf_app->widget);
}