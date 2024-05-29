#include <furi.h>
#include "floopper-bloopper/floopper-bloopper.h"

typedef enum {
    EventTypeTick,
    EventTypeKey,
} EventType;

typedef struct {
    union {
        InputEvent input;
    } value;
    EventType type;
} AppEvent;

void game_engine_tick_cb(void* p) {
    osMessageQueueId_t event_queue = p;
    AppEvent tick_event;
    tick_event.type = EventTypeTick;
    osMessageQueuePut(event_queue, (void*)&tick_event, 0, osWaitForever);
}

static void game_engine_event_cb(InputEvent* input_event, void* ctx) {
    osMessageQueueId_t event_queue = ctx;

    AppEvent event;
    event.type = EventTypeKey;
    event.value.input = *input_event;
    osMessageQueuePut(event_queue, (void*)&event, 0, osWaitForever);
}

int32_t floopper_bloopper(void* p) {
    // create event queue
    osMessageQueueId_t event_queue = osMessageQueueNew(2, sizeof(AppEvent), NULL);
    osTimerId_t id1 = osTimerNew(game_engine_tick_cb, osTimerPeriodic, event_queue, NULL);
    osTimerStart(id1, 20);

    GameState state = {
        .player =
            {
                .x = (SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2) * SCALE,
                .y = (SCREEN_HEIGHT / 2) * SCALE,
            },
        .player_global =
            {
                .x = (SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2) * SCALE,
                .y = (SCREEN_HEIGHT / 2) * SCALE,
            },
        .player_v =
            {
                .x = 0,
                .y = 0,
            },

        .in_boundaries = false,
        .player_jump = false,
        .player_anim = 0,

        .combo_panel_activated = false,

        .label_id = WELCOME,

        .glitch_level = 0,
        .glitch_t = 0,

        .player_odo = 0,
        .player_t = 0,

        .combo_text = false,

        .next_level = false,
    };

    state.screen.x = state.player_global.x - state.player.x;
    state.screen.y = state.player_global.y - state.player.y;

    ValueMutex state_mutex;
    if(!init_mutex(&state_mutex, &state, sizeof(GameState))) {
        printf("[game] cannot create mutex\r\n");
        return 255;
    }

    ViewPort* view_port = view_port_alloc();

    view_port_draw_callback_set(view_port, render_graphics, &state_mutex);
    view_port_input_callback_set(view_port, game_engine_event_cb, event_queue);

    // Open GUI and register view_port
    Gui* gui = furi_record_open("gui");
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    AppEvent event;

    uint32_t t = xTaskGetTickCount();
    uint32_t prev_t = 0;

    while(1) {
        if(osMessageQueueGet(event_queue, (void*)&event, 0, osWaitForever) == osOK) {
            GameState* _state = (GameState*)acquire_mutex_block(&state_mutex);

            if(event.type == EventTypeTick) {
                t = xTaskGetTickCount();
                handle_tick(_state, t, (t - prev_t) % 1024);
                prev_t = t;
            } else if(event.type == EventTypeKey) {
                handle_key(_state, &event.value.input);
            }

            release_mutex(&state_mutex, _state);
            view_port_update(view_port);
        }
    }

    return 0;
}