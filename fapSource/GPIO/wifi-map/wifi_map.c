#include <furi.h>
#include <furi_hal.h>
#include <storage/storage.h>

#define TAG "WIFI_MAP"
#define FILE_NAME "wifi_map_data.csv"

#include <gui/gui.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>
#include <gui/elements.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/dialog_ex.h>
#include <expansion/expansion.h>

#define LINES_ON_SCREEN 6
#define COLUMNS_ON_SCREEN 21
#define WORKER_EVENTS_MASK (WorkerEventStop | WorkerEventRx)

typedef struct UartDumpModel UartDumpModel;

typedef struct {
    Gui* gui;
    NotificationApp* notification;
    ViewDispatcher* view_dispatcher;
    View* view;
    FuriThread* worker_thread;
    FuriStreamBuffer* rx_stream;
    File* file;
    FuriHalSerialHandle* serial_handle;
} WiFiMapApp;

typedef struct {
    FuriString* text;
} ListElement;

struct UartDumpModel {
    ListElement* list[LINES_ON_SCREEN];
    uint8_t line;

    char last_char;
    bool escape;
    File* file;
};

typedef enum {
    WorkerEventReserved = (1 << 0), // Reserved for StreamBuffer internal event
    WorkerEventStop = (1 << 1),
    WorkerEventRx = (1 << 2),
} WorkerEventFlags;

const NotificationSequence sequence_notification = {
    &message_display_backlight_on,
    &message_green_255,
    &message_delay_10,
    NULL,
};

File* open_file() {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    if(!storage_file_open(file, APP_DATA_PATH(FILE_NAME), FSAM_WRITE, FSOM_OPEN_APPEND)) {
        FURI_LOG_E(TAG, "Failed to open file");
    }
    return file;
}

int32_t write_to_file(char data_line, File* file) {
    char* data = (char*)malloc(sizeof(char) + 1);
    data[0] = data_line;
    if(!storage_file_write(file, data, (uint16_t)strlen(data))) {
        FURI_LOG_E(TAG, "Failed to write to file");
    }
    free(data);
    return 0;
}

int32_t close_file(File* file) {
    storage_file_close(file);
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
    return 0;
}

static void uart_echo_view_draw_callback(Canvas* canvas, void* _model) {
    UartDumpModel* model = _model;

    // Prepare canvas
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontKeyboard);

    for(size_t i = 0; i < LINES_ON_SCREEN; i++) {
        canvas_draw_str(
            canvas,
            0,
            (i + 1) * (canvas_current_font_height(canvas) - 1),
            furi_string_get_cstr(model->list[i]->text));

        if(i == model->line) {
            uint8_t width =
                canvas_string_width(canvas, furi_string_get_cstr(model->list[i]->text));

            canvas_draw_box(
                canvas,
                width,
                (i) * (canvas_current_font_height(canvas) - 1) + 2,
                2,
                canvas_current_font_height(canvas) - 2);
        }
    }
}

static bool uart_echo_view_input_callback(InputEvent* event, void* context) {
    UNUSED(event);
    UNUSED(context);
    return false;
}

static uint32_t uart_echo_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

static void
    uart_echo_on_irq_cb(FuriHalSerialHandle* handle, FuriHalSerialRxEvent event, void* context) {
    furi_assert(context);
    WiFiMapApp* app = context;

    if(event == FuriHalSerialRxEventData) {
        uint8_t data = furi_hal_serial_async_rx(handle);
        furi_stream_buffer_send(app->rx_stream, &data, 1, 0);
        furi_thread_flags_set(furi_thread_get_id(app->worker_thread), WorkerEventRx);
    }
}

static void uart_echo_push_to_list(UartDumpModel* model, const char data, WiFiMapApp* app) {
    if(model->escape) {
        // escape code end with letter
        if((data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z')) {
            model->escape = false;
        }
    } else if(data == '[' && model->last_char == '\e') {
        // "Esc[" is a escape code
        model->escape = true;
    } else if((data >= ' ' && data <= '~') || (data == '\n' || data == '\r')) {
        write_to_file((char)data, app->file);
        bool new_string_needed = false;
        if(furi_string_size(model->list[model->line]->text) >= COLUMNS_ON_SCREEN) {
            new_string_needed = true;
        } else if((data == '\n' || data == '\r')) {
            // pack line breaks
            if(model->last_char != '\n' && model->last_char != '\r') {
                new_string_needed = true;
            }
        }

        if(new_string_needed) {
            if((model->line + 1) < LINES_ON_SCREEN) {
                model->line += 1;
            } else {
                ListElement* first = model->list[0];

                for(size_t i = 1; i < LINES_ON_SCREEN; i++) {
                    model->list[i - 1] = model->list[i];
                }

                furi_string_reset(first->text);
                model->list[model->line] = first;
            }
        }

        if(data != '\n' && data != '\r') {
            furi_string_push_back(model->list[model->line]->text, data);
        }
    }
    model->last_char = data;
}

static int32_t uart_echo_worker(void* context) {
    furi_assert(context);
    WiFiMapApp* app = context;

    while(1) {
        uint32_t events =
            furi_thread_flags_wait(WORKER_EVENTS_MASK, FuriFlagWaitAny, FuriWaitForever);
        furi_check((events & FuriFlagError) == 0);

        if(events & WorkerEventStop) break;
        if(events & WorkerEventRx) {
            size_t length = 0;
            do {
                uint8_t data[64];
                length = furi_stream_buffer_receive(app->rx_stream, data, 64, 0);
                if(length > 0) {
                    furi_hal_serial_tx(app->serial_handle, data, length);
                    with_view_model(
                        app->view,
                        UartDumpModel * model,
                        {
                            for(size_t i = 0; i < length; i++) {
                                uart_echo_push_to_list(model, data[i], app);
                            }
                        },
                        false);
                }
            } while(length > 0);

            notification_message(app->notification, &sequence_notification);
            with_view_model(
                app->view, UartDumpModel * model, { UNUSED(model); }, true);
        }
    }

    return 0;
}

static WiFiMapApp* uart_echo_app_alloc() {
    WiFiMapApp* app = malloc(sizeof(WiFiMapApp));

    app->file = open_file();

    app->rx_stream = furi_stream_buffer_alloc(2048, 1);

    // Gui
    app->gui = furi_record_open(RECORD_GUI);
    app->notification = furi_record_open(RECORD_NOTIFICATION);

    // View dispatcher
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    // Views
    app->view = view_alloc();
    view_set_draw_callback(app->view, uart_echo_view_draw_callback);
    view_set_input_callback(app->view, uart_echo_view_input_callback);
    view_allocate_model(app->view, ViewModelTypeLocking, sizeof(UartDumpModel));
    with_view_model(
        app->view,
        UartDumpModel * model,
        {
            for(size_t i = 0; i < LINES_ON_SCREEN; i++) {
                model->line = 0;
                model->escape = false;
                model->list[i] = malloc(sizeof(ListElement));
                model->list[i]->text = furi_string_alloc();
            }
        },
        true);

    view_set_previous_callback(app->view, uart_echo_exit);
    view_dispatcher_add_view(app->view_dispatcher, 0, app->view);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    app->worker_thread = furi_thread_alloc_ex("UsbUartWorker", 1024, uart_echo_worker, app);
    furi_thread_start(app->worker_thread);

    // Enable uart listener
    app->serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);
    furi_check(app->serial_handle);
    furi_hal_serial_init(app->serial_handle, 115200);
    furi_hal_serial_async_rx_start(app->serial_handle, uart_echo_on_irq_cb, app, false);

    return app;
}

static void uart_echo_app_free(WiFiMapApp* app) {
    furi_assert(app);

    furi_hal_serial_async_rx_stop(app->serial_handle);
    furi_hal_serial_deinit(app->serial_handle);
    furi_hal_serial_control_release(app->serial_handle);

    furi_thread_flags_set(furi_thread_get_id(app->worker_thread), WorkerEventStop);
    furi_thread_join(app->worker_thread);
    furi_thread_free(app->worker_thread);

    // Free views
    view_dispatcher_remove_view(app->view_dispatcher, 0);

    with_view_model(
        app->view,
        UartDumpModel * model,
        {
            for(size_t i = 0; i < LINES_ON_SCREEN; i++) {
                furi_string_free(model->list[i]->text);
                free(model->list[i]);
            }
        },
        true);
    view_free(app->view);
    view_dispatcher_free(app->view_dispatcher);

    // Close gui record
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_NOTIFICATION);
    app->gui = NULL;

    furi_stream_buffer_free(app->rx_stream);

    close_file(app->file);

    // Free rest
    free(app);
}

int32_t wifi_map_app(void* p) {
    UNUSED(p);
    // Disable expansion protocol to avoid interference with UART Handle
    Expansion* expansion = furi_record_open(RECORD_EXPANSION);
    expansion_disable(expansion);
    
    FURI_LOG_D(TAG, "wifi_map_app");
    WiFiMapApp* app = uart_echo_app_alloc();
    view_dispatcher_run(app->view_dispatcher);
    uart_echo_app_free(app);

    // Return previous state of expansion
    expansion_enable(expansion);
    furi_record_close(RECORD_EXPANSION);

    return 0;
}
