#include <furi.h>
#include "floopper-bloopper/floopper-bloopper.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// narrative
const TextBlock NARRATIVE[15] = {
    {3, {"Welcome to Game!", "Use < > to move", "Use ^ to jump"}},
    {3, {"OMG, it's happened", "again! Wait, I try", "to help you..."}},
    {1, {"Please, return back"}},
    {3, {"No, you dawn into", "cycle deeply!", " Go back"}},
    {2, {"Okay, you stuck...", "try to press jump"}},
    {1, {"...then left"}},
    {1, {"...then right"}},
    {1, {"...left again"}},
    {3, {"Damn, it worked", "before. I need to", "read manual"}},
    {2, {"Hey! I found", "something helpful!"}},
    {3, {"You need to activate", "DCMPA 0x3A77 trigger", "u know what it is?"}},
    {3, {"Maybe some part of", "the earth looks", "special"}},
    {1, {"Try to jump over it"}},
    {1, {"Jump here!"}},
    {1, {"No, not here..."}}};

const int32_t HEIGHT_MAP[WORLD_WIDTH] = {
    5000,  5200,  5400,  5600,  5800,  6000,  6200,  6400,  6600,  6800,  7000,  7200,  7400,
    7600,  7800,  8000,  8200,  8400,  8600,  8800,  9000,  9200,  9400,  9600,  9800,  10000,
    10200, 10400, 10600, 10800, 11000, 10000, 9500,  9000,  8600,  8000,  8300,  7500,  7000,
    6800,  7200,  6400,  6000,  5500,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  4500,  4000,  3500,  3000,  2500,  2000,  1500,  1000,
    500,   0,     -500,  -1000, -2000, -3000, -4000, -5000, -6000, -7000, -8000, -8000, -8000,
    -8000, -7000, -6000, -5000, -7000, -5000, -7000, -5000, -7000, -5000, -4000, -3000, -2500,
    -2000, -1500, -500,  0,     500,   1200,  1800,  2500,  3000,  3500,  4000,  4500,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
    5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,  5000,
};

typedef enum {
    ComboInputKeyUp = 0,
    ComboInputKeyDown,
    ComboInputKeyRight,
    ComboInputKeyLeft,
    ComboInputEmpty,
} ComboInput;
ComboInput combo[COMBO_LENGTH];

ComboInput COMBO_PATTERNS[PATTERN_LENGTH][COMBO_LENGTH] = {
    {ComboInputKeyLeft,
     ComboInputKeyRight,
     ComboInputKeyRight,
     ComboInputKeyDown,
     ComboInputEmpty,
     ComboInputEmpty,
     ComboInputEmpty,
     ComboInputEmpty}, //text combo <>>!
    {ComboInputKeyLeft,
     ComboInputKeyDown,
     ComboInputKeyRight,
     ComboInputKeyDown,
     ComboInputKeyDown,
     ComboInputEmpty,
     ComboInputEmpty,
     ComboInputEmpty}, //text combo off <!>!!
    {ComboInputKeyLeft,
     ComboInputKeyUp,
     ComboInputKeyRight,
     ComboInputKeyDown,
     ComboInputEmpty,
     ComboInputEmpty,
     ComboInputEmpty,
     ComboInputEmpty},
};

void render_graphics(Canvas* canvas, void* ctx) {
    GameState* state = (GameState*)acquire_mutex((ValueMutex*)ctx, 25);
    uint32_t t = xTaskGetTickCount();

    canvas_clear(canvas);

    render_world(state, canvas, t);
    render_player(state, canvas);
    render_game_state(state, canvas);
    render_ui(state, canvas);

    release_mutex((ValueMutex*)ctx, state);
}

void render_ui(GameState* state, Canvas* canvas) {
    if(state->combo_panel_activated) {
        canvas_set_color(canvas, ColorWhite);
        //combo box background
        canvas_draw_box(
            canvas, CP_POSITION_X, CP_POSITION_Y, (SCREEN_WIDTH)-CP_POSITION_X * 2, CP_HEIGHT);
        canvas_set_color(canvas, ColorBlack);
        //progress
        canvas_draw_box(
            canvas,
            CP_POSITION_X,
            CP_POSITION_Y - CP_PROGRESS_HEIGHT,
            (SCREEN_WIDTH - CP_POSITION_X * 2) * state->combo_progress / (100 * SCALE),
            CP_PROGRESS_HEIGHT);
        //combo box frame
        canvas_draw_frame(
            canvas, CP_POSITION_X, CP_POSITION_Y, SCREEN_WIDTH - CP_POSITION_X * 2, CP_HEIGHT);

        //combo items
        canvas_set_font(canvas, FontGlyph);

        for(size_t i = 0; i < state->combo_panel_cnt; i++) {
            uint16_t item_x = CP_POSITION_X + CP_ITEM_WIDTH + (CP_ITEM_WIDTH + CP_ITEM_SPACE) * i;
            uint16_t item_y = CP_POSITION_Y + (CP_HEIGHT + CP_ITEM_HEIGHT) / 2;
            switch(combo[i]) {
            case ComboInputKeyUp:
                canvas_draw_glyph(canvas, item_x, item_y, 9206);
                break;
            case ComboInputKeyDown:
                canvas_draw_glyph(canvas, item_x, item_y, 9207);
                break;
            case ComboInputKeyRight:
                canvas_draw_glyph(canvas, item_x, item_y, 9205);
                break;
            case ComboInputKeyLeft:
                canvas_draw_glyph(canvas, item_x, item_y, 9204);
                break;
            default:
                break;
            }
        }
    }
}

void hadle_combo_input(GameState* state, InputEvent* input) {
    if(input->type == InputTypeShort) {
        combo[state->combo_panel_cnt] = input->key;
        state->combo_progress = 100 * SCALE;
        state->combo_panel_cnt += 1;
        state->combo_speed =
            ((SCREEN_WIDTH - CP_POSITION_X * 2) * 1000 * state->combo_panel_cnt) / COMBO_TIME;
    }
}

void update_combo_process(GameState* state, uint32_t dt) {
    if(state->combo_panel_activated && (state->combo_progress > 0)) {
        state->combo_progress -= state->combo_speed * dt;
    } else {
        state->combo_panel_activated = false;
        if(!memcmp(COMBO_PATTERNS[0], combo, COMBO_LENGTH)) {
            state->combo_text = true;
        } else if(!memcmp(COMBO_PATTERNS[1], combo, COMBO_LENGTH)) {
            state->combo_text = false;
        }
    }
}

void handle_key(GameState* state, InputEvent* input) {
    // printf("[kb] event: %02x %s\n", input->key, input->state ? "pressed" : "released");

    if(state->combo_panel_activated) {
        hadle_combo_input(state, input);
    } else {
        handle_player_input(state, input);
    }

    if(input->key == InputKeyDown) {
        /*
        if(input->type == InputTypeShort) {
            //for tests
            if(state->in_boundaries){
                state->in_boundaries = false;
            } else {
                state->in_boundaries = true;
            }
        }
        */
    }

    if(input->key == InputKeyOk) {
        if(input->type == InputTypeShort) {
            if(!state->combo_panel_activated) {
                state->combo_panel_cnt = 0;
                state->combo_panel_activated = true;
                state->combo_progress = 100 * SCALE;
                state->combo_speed =
                    ((SCREEN_WIDTH - CP_POSITION_X * 2) * 1000 * 0.5) / COMBO_TIME;
                for(size_t i = 0; i < COMBO_LENGTH; i++) {
                    combo[i] = ComboInputEmpty;
                }
            } else {
                state->combo_panel_activated = false;
            }
        }
    }
}

void handle_tick(GameState* state, uint32_t t, uint32_t dt) {
    // printf("t: %d, dt: %d\n", t, dt);

    update_player_coordinates(state, dt);
    update_game_state(state, t, dt);
    update_combo_process(state, dt);
}
