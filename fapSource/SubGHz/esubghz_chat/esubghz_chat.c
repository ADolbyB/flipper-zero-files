#include <furi_hal.h>
#include <gui/elements.h>
#include <gui/gui.h>

#include "helpers/radio_device_loader.h"
#include "esubghz_chat_i.h"

#include "bgloader_api.h"

#define CHAT_LEAVE_DELAY 10
#define TICK_INTERVAL 50
#define MESSAGE_COMPLETION_TIMEOUT 500

#define KBD_UNLOCK_CNT 3
#define KBD_UNLOCK_TIMEOUT 1000

/* Callback for RX events from the Sub-GHz worker. Records the current ticks as
 * the time of the last reception. */
static void have_read_cb(void* context) {
    furi_assert(context);
    ESubGhzChatState* state = context;

    state->last_time_rx_data = furi_get_tick();
}

/* Sets the header for the chat input field depending on whether or not a
 * message preview exists. */
void set_chat_input_header(ESubGhzChatState* state) {
    if(strlen(state->msg_preview) == 0) {
        text_input_set_header_text(state->text_input, "Message");
    } else {
        text_input_set_header_text(state->text_input, state->msg_preview);
    }
}

/* Appends the latest message to the chat box and prepares the message preview.
 */
void append_msg(ESubGhzChatState* state, const char* msg) {
    /* append message to text box */
    furi_string_cat_printf(state->chat_box_store, "\n%s", msg);

    /* prepare message preview */
    strncpy(state->msg_preview, msg, MSG_PREVIEW_SIZE);
    state->msg_preview[MSG_PREVIEW_SIZE] = 0;
    set_chat_input_header(state);

    /* reset text box contents and focus */
    text_box_set_text(state->chat_box, furi_string_get_cstr(state->chat_box_store));
    text_box_set_focus(state->chat_box, TextBoxFocusEnd);
}

/* Decrypts a message for post_rx(). */
static bool post_rx_decrypt(ESubGhzChatState* state, size_t rx_size) {
    bool ret = crypto_ctx_decrypt(
        state->crypto_ctx, state->rx_buffer, rx_size, (uint8_t*)state->rx_str_buffer);

    if(ret) {
        state->rx_str_buffer[rx_size - (MSG_OVERHEAD)] = 0;
    } else {
        state->rx_str_buffer[0] = 0;
    }

    return ret;
}

/* Post RX handler, decrypts received messages and calls append_msg(). */
static void post_rx(ESubGhzChatState* state, size_t rx_size) {
    furi_assert(state);

    if(rx_size == 0) {
        return;
    }

    furi_check(rx_size <= RX_TX_BUFFER_SIZE);

    /* decrypt if necessary */
    if(!state->encrypted) {
        memcpy(state->rx_str_buffer, state->rx_buffer, rx_size);
        state->rx_str_buffer[rx_size] = 0;

        /* remove trailing newline if it is there, for compat with CLI
		 * Sub-GHz chat */
        if(state->rx_str_buffer[rx_size - 1] == '\n') {
            state->rx_str_buffer[rx_size - 1] = 0;
        }
    } else {
        /* if decryption fails output an error message */
        if(!post_rx_decrypt(state, rx_size)) {
            strcpy(state->rx_str_buffer, "ERR: Decryption failed!");
        }
    }

    /* append message to text box and prepare message preview */
    append_msg(state, state->rx_str_buffer);

    /* send notification (make the flipper vibrate) */
    notification_message(state->notification, &sequence_single_vibro);
}

/* Reads the message from msg_input, encrypts it if necessary and then
 * transmits it. */
void tx_msg_input(ESubGhzChatState* state) {
    /* encrypt message if necessary */
    size_t msg_len = strlen(furi_string_get_cstr(state->msg_input));
    size_t tx_size = msg_len;
    if(state->encrypted) {
        tx_size += MSG_OVERHEAD;
        furi_check(tx_size <= sizeof(state->tx_buffer));

        crypto_ctx_encrypt(
            state->crypto_ctx,
            (uint8_t*)furi_string_get_cstr(state->msg_input),
            msg_len,
            state->tx_buffer);
    } else {
        tx_size += 2;
        furi_check(tx_size <= sizeof(state->tx_buffer));
        memcpy(state->tx_buffer, furi_string_get_cstr(state->msg_input), msg_len);

        /* append \r\n for compat with Sub-GHz CLI chat */
        state->tx_buffer[msg_len] = '\r';
        state->tx_buffer[msg_len + 1] = '\n';
    }

    /* transmit */
    subghz_tx_rx_worker_write(state->subghz_worker, state->tx_buffer, tx_size);
}

/* Displays information on frequency, encryption and radio type in the text
 * box. Also clears the text input buffer to remove the password and starts the
 * Sub-GHz worker. After starting the worker a join message is transmitted. */
void enter_chat(ESubGhzChatState* state) {
    furi_string_cat_printf(state->chat_box_store, "Frequency: %lu", state->frequency);

    furi_string_cat_printf(
        state->chat_box_store, "\nEncrypted: %s", (state->encrypted ? "yes" : "no"));

    subghz_tx_rx_worker_start(state->subghz_worker, state->subghz_device, state->frequency);

    if(strcmp(state->subghz_device->name, "cc1101_ext") == 0) {
        furi_string_cat_printf(state->chat_box_store, "\nRadio: External");
    } else {
        furi_string_cat_printf(state->chat_box_store, "\nRadio: Internal");
    }

    /* concatenate the name prefix and join message */
    furi_string_set(state->msg_input, state->name_prefix);
    furi_string_cat_str(state->msg_input, " joined chat.");

    /* encrypt and transmit message */
    tx_msg_input(state);

    /* clear message input buffer */
    furi_string_set_char(state->msg_input, 0, 0);
}

/* Sends a leave message */
void exit_chat(ESubGhzChatState* state) {
    /* concatenate the name prefix and leave message */
    furi_string_set(state->msg_input, state->name_prefix);
    furi_string_cat_str(state->msg_input, " left chat.");

    /* encrypt and transmit message */
    tx_msg_input(state);

    /* clear message input buffer */
    furi_string_set_char(state->msg_input, 0, 0);

    /* wait for leave message to be delivered */
    furi_delay_ms(CHAT_LEAVE_DELAY);
}

/* Whether or not to display the locked message. */
static bool kbd_lock_msg_display(ESubGhzChatState* state) {
    return (state->kbd_lock_msg_ticks != 0);
}

/* Whether or not to hide the locked message again. */
static bool kbd_lock_msg_reset_timeout(ESubGhzChatState* state) {
    if(state->kbd_lock_msg_ticks == 0) {
        return false;
    }

    if(furi_get_tick() - state->kbd_lock_msg_ticks > KBD_UNLOCK_TIMEOUT) {
        return true;
    }

    return false;
}

/* Resets the timeout for the locked message and turns off the backlight if
 * specified. */
static void kbd_lock_msg_reset(ESubGhzChatState* state, bool backlight_off) {
    state->kbd_lock_msg_ticks = 0;
    state->kbd_lock_count = 0;

    if(backlight_off) {
        notification_message(state->notification, &sequence_display_backlight_off);
    }
}

/* Locks the keyboard. */
static void kbd_lock(ESubGhzChatState* state) {
    state->kbd_locked = true;
    kbd_lock_msg_reset(state, true);
}

/* Unlocks the keyboard. */
static void kbd_unlock(ESubGhzChatState* state) {
    state->kbd_locked = false;
    kbd_lock_msg_reset(state, false);
}

/* Custom event callback for view dispatcher. Just calls scene manager. */
static bool esubghz_chat_custom_event_callback(void* context, uint32_t event) {
    FURI_LOG_T(APPLICATION_NAME, "esubghz_chat_custom_event_callback");
    furi_assert(context);
    ESubGhzChatState* state = context;
    return scene_manager_handle_custom_event(state->scene_manager, event);
}

/* Navigation event callback for view dispatcher. Just calls scene manager. */
static bool esubghz_chat_navigation_event_callback(void* context) {
    FURI_LOG_T(APPLICATION_NAME, "esubghz_chat_navigation_event_callback");
    furi_assert(context);
    ESubGhzChatState* state = context;
    return scene_manager_handle_back_event(state->scene_manager);
}

static void esubghz_chat_check_messages(ESubGhzChatState* state) {
    /* if the maximum message size was reached or the
	 * MESSAGE_COMPLETION_TIMEOUT has expired, retrieve a message and call
	 * post_rx() */
    size_t avail = 0;
    while((avail = subghz_tx_rx_worker_available(state->subghz_worker)) > 0) {
        volatile uint32_t since_last_rx = furi_get_tick() - state->last_time_rx_data;
        if(avail < RX_TX_BUFFER_SIZE && since_last_rx < MESSAGE_COMPLETION_TIMEOUT) {
            break;
        }

        size_t rx_size =
            subghz_tx_rx_worker_read(state->subghz_worker, state->rx_buffer, RX_TX_BUFFER_SIZE);
        post_rx(state, rx_size);
    }
}

/* Tick event callback for view dispatcher. Called every TICK_INTERVAL. Resets
 * the locked message if necessary. Retrieves a received message from the
 * Sub-GHz worker and calls post_rx(). Then calls the scene manager. */
static void esubghz_chat_tick_event_callback(void* context) {
    FURI_LOG_T(APPLICATION_NAME, "esubghz_chat_tick_event_callback");

    furi_assert(context);
    ESubGhzChatState* state = context;

    /* reset locked message if necessary */
    if(kbd_lock_msg_reset_timeout(state)) {
        kbd_lock_msg_reset(state, true);
    }

    esubghz_chat_check_messages(state);

    /* call scene manager */
    scene_manager_handle_tick_event(state->scene_manager);
}

/* Hooks into the view port's draw callback to overlay the keyboard locked
 * message. */
static void esubghz_hooked_draw_callback(Canvas* canvas, void* context) {
    FURI_LOG_T(APPLICATION_NAME, "esubghz_hooked_draw_callback");

    furi_assert(canvas);

    furi_assert(context);
    ESubGhzChatState* state = context;

    /* call original callback */
    state->orig_draw_cb(canvas, state->view_dispatcher);

    /* display if the keyboard is locked */
    if(state->kbd_locked) {
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_framed(canvas, 42, 30, "Locked");
    }

    /* display the unlock message if necessary */
    if(kbd_lock_msg_display(state)) {
        canvas_set_font(canvas, FontSecondary);
        elements_bold_rounded_frame(canvas, 14, 8, 99, 48);
        elements_multiline_text(canvas, 65, 26, "To unlock\npress:");
        canvas_draw_icon(canvas, 65, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 80, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 95, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 16, 13, &I_WarningDolphin_45x42);
    }
}

/* Hooks into the view port's input callback to handle the user locking the
 * keyboard. */
static void esubghz_hooked_input_callback(InputEvent* event, void* context) {
    FURI_LOG_T(APPLICATION_NAME, "esubghz_hooked_input_callback");

    furi_assert(event);

    furi_assert(context);
    ESubGhzChatState* state = context;

    /* if the keyboard is locked no key presses are forwarded */
    if(state->kbd_locked) {
        /* key has been pressed, display the unlock message and
		 * initiate the timer */
        if(state->kbd_lock_count == 0) {
            state->kbd_lock_msg_ticks = furi_get_tick();
        }

        /* back button has been pressed, increase the lock counter */
        if(event->key == InputKeyBack && event->type == InputTypeShort) {
            state->kbd_lock_count++;
        }

        /* unlock the keyboard */
        if(state->kbd_lock_count >= KBD_UNLOCK_CNT) {
            kbd_unlock(state);
        }

        /* do not handle the event */
        return;
    }

    /* handle long press of back key to exit for real */
    if(event->key == InputKeyBack) {
        if(state->view_dispatcher->current_view == text_input_get_view(state->text_input)) {
            if(event->type == InputTypeLong) {
                state->exit_for_real = true;
                view_dispatcher_stop(state->view_dispatcher);
                return;
            }
        }
    }

    if(event->key == InputKeyOk) {
        /* if we are in the chat view and no input is ongoing, allow
		 * locking */
        if(state->view_dispatcher->current_view == text_box_get_view(state->chat_box) &&
           !(state->kbd_ok_input_ongoing)) {
            /* lock keyboard upon long press of Ok button */
            if(event->type == InputTypeLong) {
                kbd_lock(state);
            }

            /* do not handle any Ok key events to prevent blocking
			 * of other keys */
            return;
        }

        /* handle ongoing inputs when changing to chat view */
        if(event->type == InputTypePress) {
            state->kbd_ok_input_ongoing = true;
        } else if(event->type == InputTypeRelease) {
            state->kbd_ok_input_ongoing = false;
        }
    }

    if(event->key == InputKeyLeft) {
        /* if we are in the chat view and no input is ongoing, allow
		 * switching to msg input */
        if(state->view_dispatcher->current_view == text_box_get_view(state->chat_box) &&
           !(state->kbd_left_input_ongoing)) {
            /* go to msg input upon short press of Left button */
            if(event->type == InputTypeShort) {
                view_dispatcher_send_custom_event(
                    state->view_dispatcher, ESubGhzChatEvent_GotoMsgInput);
            }

            /* do not handle any Left key events to prevent
			 * blocking of other keys */
            return;
        }

        /* handle ongoing inputs when changing to chat view */
        if(event->type == InputTypePress) {
            state->kbd_left_input_ongoing = true;
        } else if(event->type == InputTypeRelease) {
            state->kbd_left_input_ongoing = false;
        }
    }

    if(event->key == InputKeyRight) {
        /* if we are in the chat view and no input is ongoing, allow
		 * switching to key display */
        if(state->view_dispatcher->current_view == text_box_get_view(state->chat_box) &&
           !(state->kbd_right_input_ongoing)) {
            /* go to key display upon short press of Right button
			 */
            if(event->type == InputTypeShort) {
                view_dispatcher_send_custom_event(
                    state->view_dispatcher, ESubGhzChatEvent_GotoKeyDisplay);
            }

            /* do not handle any Right key events to prevent
			 * blocking of other keys */
            return;
        }

        /* handle ongoing inputs when changing to chat view */
        if(event->type == InputTypePress) {
            state->kbd_right_input_ongoing = true;
        } else if(event->type == InputTypeRelease) {
            state->kbd_right_input_ongoing = false;
        }
    }

    /* call original callback */
    state->orig_input_cb(event, state->view_dispatcher);
}

static const char* esubghz_get_bgloader_app_path(const char* args) {
    size_t base_args_len = strlen(APP_BASE_ARGS);

    return (args + base_args_len + 1);
}

static bool esubghz_run_with_bgloader(const char* args) {
    size_t base_args_len = strlen(APP_BASE_ARGS);

    if(args == NULL) {
        return false;
    }

    if(strncmp(args, APP_BASE_ARGS, base_args_len) != 0) {
        return false;
    }

    if(strlen(args) < base_args_len + 2) {
        return false;
    }

    if(args[base_args_len] != ':') {
        return false;
    }

    const char* app_path = esubghz_get_bgloader_app_path(args);
    return furi_record_exists(app_path);
}

static void esubghz_attach_to_gui(ESubGhzChatState* state) {
    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(state->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
}

static void esubghz_detach_from_gui(ESubGhzChatState* state) {
    gui_remove_view_port(state->view_dispatcher->gui, state->view_dispatcher->view_port);
    state->view_dispatcher->gui = NULL;
    furi_record_close(RECORD_GUI);
}

static void esubghz_bgloader_loop(ESubGhzChatState* state, const char* bg_app_path) {
    while(true) {
        view_dispatcher_run(state->view_dispatcher);

        if(state->exit_for_real) {
            /* exit for real */
            break;
        }

        BGLoaderApp* bg_app = furi_record_open(bg_app_path);

        /* signal loader that we're ready to go to background */
        BGLoaderMessage msg;
        msg.type = BGLoaderMessageType_LoaderBackground;
        furi_check(
            furi_message_queue_put(bg_app->to_loader, &msg, FuriWaitForever) == FuriStatusOk);

        esubghz_detach_from_gui(state);

        while(true) {
            /* wait for loader to wake us up again */
            if(furi_message_queue_get(bg_app->to_app, &msg, TICK_INTERVAL) != FuriStatusOk) {
                /* check for messages on timeout */
                esubghz_chat_check_messages(state);
                continue;
            }
            if(msg.type == BGLoaderMessageType_AppReattached) {
                break;
            } else {
                furi_check(0);
            }
        }

        furi_record_close(bg_app_path);

        esubghz_attach_to_gui(state);
    }
}

static bool helper_strings_alloc(ESubGhzChatState* state) {
    furi_assert(state);

    state->name_prefix = furi_string_alloc();
    if(state->name_prefix == NULL) {
        return false;
    }

    state->msg_input = furi_string_alloc();
    if(state->msg_input == NULL) {
        furi_string_free(state->name_prefix);
        return false;
    }

    return true;
}

static void helper_strings_free(ESubGhzChatState* state) {
    furi_assert(state);

    furi_string_free(state->name_prefix);
    furi_string_free(state->msg_input);
}

static bool chat_box_alloc(ESubGhzChatState* state) {
    furi_assert(state);

    state->chat_box = text_box_alloc();
    if(state->chat_box == NULL) {
        return false;
    }

    state->chat_box_store = furi_string_alloc();
    if(state->chat_box_store == NULL) {
        text_box_free(state->chat_box);
        return false;
    }

    furi_string_reserve(state->chat_box_store, CHAT_BOX_STORE_SIZE);
    furi_string_set_char(state->chat_box_store, 0, 0);
    text_box_set_text(state->chat_box, furi_string_get_cstr(state->chat_box_store));
    text_box_set_focus(state->chat_box, TextBoxFocusEnd);

    return true;
}

static void chat_box_free(ESubGhzChatState* state) {
    furi_assert(state);

    text_box_free(state->chat_box);
    furi_string_free(state->chat_box_store);
}

int32_t esubghz_chat(const char* args) {
    if(furi_hal_nfc_is_hal_ready() != FuriHalNfcErrorNone) {
        printf("NFC chip failed to start\r\n");
        return -1;
    }

    furi_hal_nfc_acquire();
    furi_hal_nfc_low_power_mode_start();
    furi_hal_nfc_release();
    furry_hal_nfc_init();
    /* init the crypto system */
    crypto_init();

    int32_t err = -1;

    FURI_LOG_I(APPLICATION_NAME, "Starting...");

    /* allocate necessary structs and buffers */

    ESubGhzChatState* state = malloc(sizeof(ESubGhzChatState));
    if(state == NULL) {
        goto err_alloc;
    }
    memset(state, 0, sizeof(*state));

    state->scene_manager = scene_manager_alloc(&esubghz_chat_scene_event_handlers, state);
    if(state->scene_manager == NULL) {
        goto err_alloc_sm;
    }

    state->view_dispatcher = view_dispatcher_alloc();
    if(state->view_dispatcher == NULL) {
        goto err_alloc_vd;
    }

    if(!helper_strings_alloc(state)) {
        goto err_alloc_hs;
    }

    state->menu = menu_alloc();
    if(state->menu == NULL) {
        goto err_alloc_menu;
    }

    state->text_input = text_input_alloc();
    if(state->text_input == NULL) {
        goto err_alloc_ti;
    }

    state->hex_key_input = byte_input_alloc();
    if(state->hex_key_input == NULL) {
        goto err_alloc_hki;
    }

    if(!chat_box_alloc(state)) {
        goto err_alloc_cb;
    }

    state->key_display = dialog_ex_alloc();
    if(state->key_display == NULL) {
        goto err_alloc_kd;
    }

    state->nfc_popup = popup_alloc();
    if(state->nfc_popup == NULL) {
        goto err_alloc_np;
    }

    state->subghz_worker = subghz_tx_rx_worker_alloc();
    if(state->subghz_worker == NULL) {
        goto err_alloc_worker;
    }

    NfcDevice* nfcdevic = nfc_device_alloc();
    state->nfc_dev_data = &nfcdevic->dev_data;

    state->nfc_worker = nfc_worker_alloc();
    if(state->nfc_worker == NULL) {
        goto err_alloc_nworker;
    }

    /*state->nfc_dev_data = malloc(sizeof(NfcDeviceData));
    if(state->nfc_dev_data == NULL) {
        goto err_alloc_ndevdata;
    }*/

    //memset(state->nfc_dev_data, 0, sizeof(NfcDeviceData));

    state->crypto_ctx = crypto_ctx_alloc();
    if(state->crypto_ctx == NULL) {
        goto err_alloc_crypto;
    }

    /* set the default frequency */
    state->frequency = DEFAULT_FREQ;

    /* in the first few views there is no background support */
    state->exit_for_real = true;

    /* set the have_read callback of the Sub-GHz worker */
    subghz_tx_rx_worker_set_callback_have_read(state->subghz_worker, have_read_cb, state);

    /* enter suppress charge mode */
    furi_hal_power_suppress_charge_enter();

    /* init internal device */
    subghz_devices_init();

    state->subghz_device =
        radio_device_loader_set(state->subghz_device, SubGhzRadioDeviceTypeExternalCC1101);

    subghz_devices_reset(state->subghz_device);
    subghz_devices_idle(state->subghz_device);

    /* set chat name prefix */
    furi_string_printf(state->name_prefix, "%s", furi_hal_version_get_name_ptr());

    /* get notification record, we use this to make the flipper vibrate */
    /* no error handling here, don't know how */
    state->notification = furi_record_open(RECORD_NOTIFICATION);

    /* hook into the view port's draw and input callbacks */
    state->orig_draw_cb = state->view_dispatcher->view_port->draw_callback;
    state->orig_input_cb = state->view_dispatcher->view_port->input_callback;
    view_port_draw_callback_set(
        state->view_dispatcher->view_port, esubghz_hooked_draw_callback, state);
    view_port_input_callback_set(
        state->view_dispatcher->view_port, esubghz_hooked_input_callback, state);

    view_dispatcher_enable_queue(state->view_dispatcher);

    /* set callbacks for view dispatcher */
    view_dispatcher_set_event_callback_context(state->view_dispatcher, state);
    view_dispatcher_set_custom_event_callback(
        state->view_dispatcher, esubghz_chat_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        state->view_dispatcher, esubghz_chat_navigation_event_callback);
    view_dispatcher_set_tick_event_callback(
        state->view_dispatcher, esubghz_chat_tick_event_callback, TICK_INTERVAL);

    /* add our two views to the view dispatcher */
    view_dispatcher_add_view(
        state->view_dispatcher, ESubGhzChatView_Menu, menu_get_view(state->menu));
    view_dispatcher_add_view(
        state->view_dispatcher, ESubGhzChatView_Input, text_input_get_view(state->text_input));
    view_dispatcher_add_view(
        state->view_dispatcher,
        ESubGhzChatView_HexKeyInput,
        byte_input_get_view(state->hex_key_input));
    view_dispatcher_add_view(
        state->view_dispatcher, ESubGhzChatView_ChatBox, text_box_get_view(state->chat_box));
    view_dispatcher_add_view(
        state->view_dispatcher,
        ESubGhzChatView_KeyDisplay,
        dialog_ex_get_view(state->key_display));
    view_dispatcher_add_view(
        state->view_dispatcher, ESubGhzChatView_NfcPopup, popup_get_view(state->nfc_popup));

    /* get the GUI record and attach the view dispatcher to the GUI */
    /* no error handling here, don't know how */
    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(state->view_dispatcher, gui, ViewDispatcherTypeFullscreen);

    /* switch to the key menu scene */
    scene_manager_next_scene(state->scene_manager, ESubGhzChatScene_KeyMenu);

    /* run the view dispatcher, this call only returns when we close the
	 * application */
    if(!esubghz_run_with_bgloader(args)) {
        view_dispatcher_run(state->view_dispatcher);
    } else {
        const char* bg_app_path = esubghz_get_bgloader_app_path(args);
        esubghz_bgloader_loop(state, bg_app_path);
    }

    /* if it is running, stop the Sub-GHz worker */
    if(subghz_tx_rx_worker_is_running(state->subghz_worker)) {
        exit_chat(state);
        subghz_tx_rx_worker_stop(state->subghz_worker);
    }

    /* if it is running, stop the NFC worker */
    nfc_worker_stop(state->nfc_worker);

    err = 0;

    /* close GUI record */
    furi_record_close(RECORD_GUI);

    /* remove our two views from the view dispatcher */
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_Menu);
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_Input);
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_HexKeyInput);
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_ChatBox);
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_KeyDisplay);
    view_dispatcher_remove_view(state->view_dispatcher, ESubGhzChatView_NfcPopup);

    /* close notification record */
    furi_record_close(RECORD_NOTIFICATION);

    /* clear the key and potential password */
    crypto_explicit_bzero(state->text_input_store, sizeof(state->text_input_store));
    crypto_explicit_bzero(state->hex_key_input_store, sizeof(state->hex_key_input_store));
    crypto_explicit_bzero(state->key_hex_str, sizeof(state->key_hex_str));
    crypto_ctx_clear(state->crypto_ctx);

    /* clear nfc data */
    if(state->nfc_dev_data->parsed_data != NULL) {
        furi_string_free(state->nfc_dev_data->parsed_data);
    }

    //nfc_device_data_clear(state->nfc_dev_data);
    crypto_explicit_bzero(state->nfc_dev_data, sizeof(NfcDeviceData));

    /* deinit devices */
    radio_device_loader_end(state->subghz_device);

    subghz_devices_deinit();

    /* exit suppress charge mode */
    furi_hal_power_suppress_charge_exit();

    /* free everything we allocated */

    crypto_ctx_free(state->crypto_ctx);

err_alloc_crypto:
    //free(state->nfc_dev_data);

    //err_alloc_ndevdata:
    nfc_worker_free(state->nfc_worker);

    nfc_device_free(nfcdevic);

err_alloc_nworker:
    subghz_tx_rx_worker_free(state->subghz_worker);

err_alloc_worker:
    popup_free(state->nfc_popup);

err_alloc_np:
    dialog_ex_free(state->key_display);

err_alloc_kd:
    chat_box_free(state);

err_alloc_cb:
    byte_input_free(state->hex_key_input);

err_alloc_hki:
    text_input_free(state->text_input);

err_alloc_ti:
    menu_free(state->menu);

err_alloc_menu:
    helper_strings_free(state);

err_alloc_hs:
    view_dispatcher_free(state->view_dispatcher);

err_alloc_vd:
    scene_manager_free(state->scene_manager);

err_alloc_sm:
    free(state);

err_alloc:
    if(err != 0) {
        FURI_LOG_E(APPLICATION_NAME, "Failed to launch (alloc error)!");
    } else {
        FURI_LOG_I(APPLICATION_NAME, "Clean exit.");
    }

    furry_hal_nfc_deinit();

    //
    furi_hal_nfc_acquire();
    furi_hal_nfc_low_power_mode_start();
    furi_hal_nfc_release();

    return err;
}
