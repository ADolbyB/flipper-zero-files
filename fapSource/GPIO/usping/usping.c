// inspired by
// https://github.com/esphome/esphome/blob/ac0d921413c3884752193fe568fa82853f0f99e9/esphome/components/ultrasonic/ultrasonic_sensor.cpp
// Ported and modified by @xMasterX
// Modified by privet971 using PING))) sensor from Parallax (3 wires) 3/23/2023
// use only gpio 13 for TX & RX to SIG pin

#include <furi.h>
#include <furi_hal.h>
#include <furi_hal_power.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <gui/elements.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>
#include <expansion/expansion.h>

typedef enum {
    EventTypeTick,
    EventTypeKey,
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} PluginEvent;

typedef struct {
    FuriMutex* mutex;
    NotificationApp* notification;
    bool have_5v;
    bool measurement_made;
    uint32_t echo; // us
    float distance; // meters
} PluginState;

const NotificationSequence sequence_done = {
    &message_display_backlight_on,
    &message_green_255,
    &message_note_c5,
    &message_delay_50,
    &message_sound_off,
    NULL,
};

static void render_callback(Canvas* const canvas, void* ctx) {
    furi_assert(ctx);
    const PluginState* plugin_state = ctx;
    furi_mutex_acquire(plugin_state->mutex, FuriWaitForever);

    // border around the edge of the screen
    // canvas_draw_frame(canvas, 0, 0, 128, 64);

    canvas_set_font(canvas, FontPrimary);
    elements_multiline_text_aligned(
        canvas, 64, 2, AlignCenter, AlignTop, "PING Ultrasonic\nDistance Sensor");

    canvas_set_font(canvas, FontSecondary);

    if(!plugin_state->have_5v) {
        elements_multiline_text_aligned(
            canvas,
            4,
            28,
            AlignLeft,
            AlignTop,
            "5V on GPIO must be\nenabled, or USB must\nbe connected.");
    } else {
        if(!plugin_state->measurement_made) {
            elements_multiline_text_aligned(
                canvas, 64, 28, AlignCenter, AlignTop, "Press OK button to measure");
            elements_multiline_text_aligned(
                canvas, 64, 40, AlignCenter, AlignTop, "13/TX -> Sig pin\n");
        } else {
            elements_multiline_text_aligned(canvas, 4, 28, AlignLeft, AlignTop, "Readout:");

            FuriString* str_buf;
            str_buf = furi_string_alloc();
            furi_string_printf(str_buf, "Echo: %ld us", plugin_state->echo);

            canvas_draw_str_aligned(
                canvas, 8, 38, AlignLeft, AlignTop, furi_string_get_cstr(str_buf));
            furi_string_printf(str_buf, "Distance: %02f m", (double)plugin_state->distance);
            canvas_draw_str_aligned(
                canvas, 8, 48, AlignLeft, AlignTop, furi_string_get_cstr(str_buf));

            furi_string_free(str_buf);
        }
    }

    furi_mutex_release(plugin_state->mutex);
}

static void input_callback(InputEvent* input_event, FuriMessageQueue* event_queue) {
    furi_assert(event_queue);

    PluginEvent event = {.type = EventTypeKey, .input = *input_event};
    furi_message_queue_put(event_queue, &event, FuriWaitForever);
}

static void usping_state_init(PluginState* const plugin_state) {
    plugin_state->echo = -1;
    plugin_state->distance = -1;
    plugin_state->measurement_made = false;

    furi_hal_power_suppress_charge_enter();

    plugin_state->have_5v = false;
    if(furi_hal_power_is_otg_enabled() || furi_hal_power_is_charging()) {
        plugin_state->have_5v = true;
    } else {
        furi_hal_power_enable_otg();
        plugin_state->have_5v = true;
    }
}

float usping_us_to_m(uint32_t us) {
    //speed of sound for 20°C, 50% relative humidity
    //331.3 + 20 * 0.606 + 50 * 0.0124 = 0.034404
    const float speed_sound_m_per_s = 344.04f;
    const float time_s = us / 1e6f;
    const float total_dist = time_s * speed_sound_m_per_s;
    return total_dist / 2.0f;
}

static void usping_measure(PluginState* const plugin_state) {
    //plugin_state->echo = 1;
    //return;

    if(!plugin_state->have_5v) {
        if(furi_hal_power_is_otg_enabled() || furi_hal_power_is_charging()) {
            plugin_state->have_5v = true;
        } else {
            return;
        }
    }

    //furi_hal_light_set(LightRed, 0xFF);
    notification_message(plugin_state->notification, &sequence_blink_start_yellow);

    const uint32_t timeout_ms = 2000;
    // Pin 13 / TX -> Trig
    furi_hal_gpio_write(&gpio_usart_tx, false);
    furi_hal_gpio_init(&gpio_usart_tx, GpioModeOutputPushPull, GpioPullNo, GpioSpeedVeryHigh);

    //FURI_CRITICAL_ENTER();
    // 10 ms pulse on TX
    furi_hal_gpio_write(&gpio_usart_tx, true);
    furi_delay_ms(10);
    furi_hal_gpio_write(&gpio_usart_tx, false);

    // change TX > RX
    furi_hal_gpio_write(&gpio_usart_tx, false);
    furi_hal_gpio_init(&gpio_usart_tx, GpioModeInput, GpioPullNo, GpioSpeedVeryHigh);

    const uint32_t start = furi_get_tick();

    while(furi_get_tick() - start < timeout_ms && furi_hal_gpio_read(&gpio_usart_tx))
        ;
    while(furi_get_tick() - start < timeout_ms && !furi_hal_gpio_read(&gpio_usart_tx))
        ;

    const uint32_t pulse_start = DWT->CYCCNT;

    while(furi_get_tick() - start < timeout_ms && furi_hal_gpio_read(&gpio_usart_tx))
        ;
    const uint32_t pulse_end = DWT->CYCCNT;

    //FURI_CRITICAL_EXIT();

    plugin_state->echo =
        (pulse_end - pulse_start) / furi_hal_cortex_instructions_per_microsecond();
    plugin_state->distance = usping_us_to_m(plugin_state->echo);
    plugin_state->measurement_made = true;

    //furi_hal_light_set(LightRed, 0x00);
    notification_message(plugin_state->notification, &sequence_blink_stop);
    notification_message(plugin_state->notification, &sequence_done);
}

int32_t usping_app() {
    // Disable expansion protocol to avoid interference with UART Handle
    Expansion* expansion = furi_record_open(RECORD_EXPANSION);
    expansion_disable(expansion);

    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(PluginEvent));

    PluginState* plugin_state = malloc(sizeof(PluginState));

    usping_state_init(plugin_state);

    FuriHalSerialHandle* serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);

    plugin_state->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    if(!plugin_state->mutex) {
        FURI_LOG_E("usping", "cannot create mutex\r\n");
        if(furi_hal_power_is_otg_enabled()) {
            furi_hal_power_disable_otg();
        }
        furi_hal_serial_control_release(serial_handle);
        furi_hal_power_suppress_charge_exit();
        furi_message_queue_free(event_queue);
        free(plugin_state);
        // Return previous state of expansion
        expansion_enable(expansion);
        furi_record_close(RECORD_EXPANSION);
        return 255;
    }

    plugin_state->notification = furi_record_open(RECORD_NOTIFICATION);

    // Set system callbacks
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_callback, plugin_state);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    // Open GUI and register view_port
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    PluginEvent event;
    for(bool processing = true; processing;) {
        FuriStatus event_status = furi_message_queue_get(event_queue, &event, 100);

        furi_mutex_acquire(plugin_state->mutex, FuriWaitForever);

        if(event_status == FuriStatusOk) {
            // press events
            if(event.type == EventTypeKey) {
                if(event.input.type == InputTypePress) {
                    switch(event.input.key) {
                    case InputKeyUp:
                    case InputKeyDown:
                    case InputKeyRight:
                    case InputKeyLeft:
                        break;
                    case InputKeyOk:
                        usping_measure(plugin_state);
                        break;
                    case InputKeyBack:
                        processing = false;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        furi_mutex_release(plugin_state->mutex);
        view_port_update(view_port);
    }

    if(furi_hal_power_is_otg_enabled()) {
        furi_hal_power_disable_otg();
    }
    furi_hal_power_suppress_charge_exit();

    // Return TX / RX back to usart mode
    furi_hal_gpio_init_ex(
        &gpio_usart_tx,
        GpioModeAltFunctionPushPull,
        GpioPullUp,
        GpioSpeedVeryHigh,
        GpioAltFn7USART1);

    furi_hal_serial_control_release(serial_handle);

    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_NOTIFICATION);
    view_port_free(view_port);
    furi_message_queue_free(event_queue);
    furi_mutex_free(plugin_state->mutex);
    free(plugin_state);
    
    // Return previous state of expansion
    expansion_enable(expansion);
    furi_record_close(RECORD_EXPANSION);

    return 0;
}
