#include <furi.h>
#include "floopper-bloopper/floopper-bloopper.h"

void update_game_state(GameState* state, uint32_t t, uint32_t dt) {
    switch(state->label_id) {
    case WELCOME:
        state->player_odo += state->player_v.x * dt;

        if(state->player_odo / SCALE > 180 || state->player_odo / SCALE < -160) {
            state->glitch_level = 2;
        }

        if((abs((LABEL_X - state->screen.x) / SCALE)) % 256 < 2 && state->glitch_level == 2 &&
           state->player_t == 0) {
            state->in_boundaries = true;
        }

        if((abs((LABEL_X - state->screen.x) / SCALE)) % 256 < 10 && state->glitch_level == 2 &&
           state->player_t == 0) {
            state->player_t = t;
        }

        if(state->player_t > 0 && t - state->player_t > 2000) {
            state->player_t = t;

            state->label_id = OMG;
            state->glitch_level = 0;
        }
        break;

    case OMG:
        if(t - state->player_t > 3000) {
            state->label_id = OMG_HELP;
            state->in_boundaries = false;
            state->player_odo = 0;
        }
        break;

    case OMG_HELP:
        state->player_odo += state->player_v.x * dt;

        if(state->player_odo / SCALE > WORLD_WIDTH * 0.8) {
            state->label_id = WRONG;
            state->player_odo = 0;
        }

        if(state->player_odo / SCALE < -WORLD_WIDTH * 0.8 &&
           (abs((LABEL_X - state->screen.x) / SCALE)) % 256 < 2) {
            state->label_id = STUCK;
            state->in_boundaries = true;
        }
        break;

    case STUCK:
        if(state->player_v.y < -20) {
            state->label_id = HELP_1;
        }
        break;

    case HELP_1:
        if(state->player_v.x < 0) {
            state->label_id = HELP_2;
        }
        break;

    case HELP_2:
        if(state->player_v.x > 0) {
            state->label_id = HELP_3;
        }
        break;

    case HELP_3:
        if(state->player_v.x < 0) {
            state->label_id = DAMN;
            state->player_t = t;
        }
        break;

    case DAMN:

        if(t - state->player_t > 3000 && state->glitch_level == 0) {
            state->player_t = t;
            state->glitch_level = 5;
        }

        if(t - state->player_t > 5000 && state->glitch_level == 5) {
            state->glitch_level = 0;
            state->label_id = MANUAL_FOUND;
        }
        break;

    case MANUAL_FOUND:
        if(t - state->player_t > 2000) {
            state->glitch_level = 0;
            state->label_id = MANUAL;
            state->player_odo = 0;
            state->in_boundaries = false;
        }
        break;

    case MANUAL:
        state->player_odo += state->player_v.x * dt;

        if(state->player_odo / SCALE > 180 || state->player_odo / SCALE < -160) {
            state->label_id = TIP_0;
            state->player_odo = 0;
        }
        break;

    case TIP_0:
        state->player_odo += state->player_v.x * dt;

        if(state->player_odo / SCALE > 180 || state->player_odo / SCALE < -160) {
            state->label_id = TIP_1;
            state->player_odo = 0;
        }
        break;

    case TIP_1:
        state->player_odo += state->player_v.x * dt;

        if(state->player_odo / SCALE > 180 || state->player_odo / SCALE < -160) {
            state->label_id = TIP_NO_HERE;
        }
        break;

        // TIP_NO_HERE

    default:
        break;
    }

    int32_t global_x = (state->player_global.x / SCALE) % WORLD_WIDTH;
    if(global_x > 177 && global_x < 183 && state->player_v.y > 20) {
        state->next_level = true;
    }

    if(state->combo_text) {
        state->next_level = false;
        state->player_global.x = 0;
    }
}

void render_game_state(GameState* state, Canvas* canvas) {
    /*
    char buf[32];

    canvas_set_font(canvas, FontSecondary);
    canvas_set_color(canvas, ColorBlack);

    sprintf(buf, "x: %ld", (state->player_global.x / SCALE) % WORLD_WIDTH);
    canvas_draw_str(canvas, 0, 40, buf);
    */
}