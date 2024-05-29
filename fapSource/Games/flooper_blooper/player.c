#include <furi.h>
#include "floopper-bloopper/floopper-bloopper.h"

#include "floopper-bloopper/player_0/player_0_0.xbm"
#include "floopper-bloopper/player_0/player_0_1.xbm"
#include "floopper-bloopper/player_0/player_0_2.xbm"
#include "floopper-bloopper/player_0/player_0_3.xbm"
#include "floopper-bloopper/player_0/player_0_4.xbm"
#include "floopper-bloopper/player_0/player_0_5.xbm"
#include "floopper-bloopper/player_0/player_0_6.xbm"

void render_player(GameState* state, Canvas* canvas) {
    unsigned char* player_sprite = NULL;

    if(state->player_v.y > 40) {
        player_sprite = (unsigned char*)player_0_2_bits;
    } else if(state->player_v.y < -40) {
        player_sprite = (unsigned char*)player_0_3_bits;
    } else {
        if(state->player_v.x < 0) {
            if(state->player_anim == 0) {
                player_sprite = (unsigned char*)player_0_0_bits;
            } else {
                player_sprite = (unsigned char*)player_0_1_bits;
            }
        } else if(state->player_v.x > 0) {
            if(state->player_anim == 0) {
                player_sprite = (unsigned char*)player_0_5_bits;
            } else {
                player_sprite = (unsigned char*)player_0_6_bits;
            }
        } else {
            player_sprite = (unsigned char*)player_0_4_bits;
        }
    }

    if(player_sprite != NULL) {
        canvas_draw_xbm(
            canvas,
            state->player.x / SCALE,
            state->player.y / SCALE,
            player_0_0_width,
            player_0_0_height,
            (unsigned char*)player_sprite);
    }
}

void handle_player_input(GameState* state, InputEvent* input) {
    if(input->type == InputTypePress) {
        if(input->key == InputKeyRight) {
            state->player_v.x = SPEED_X;
        } else if(input->key == InputKeyLeft) {
            state->player_v.x = -SPEED_X;
        }
    } else if(input->type == InputTypeRelease) {
        if(input->key == InputKeyRight || input->key == InputKeyLeft) {
            state->player_v.x = 0;
        }
    }

    if(input->key == InputKeyUp) {
        if(input->type == InputTypePress) {
            state->player_v.y = JUMP_SPEED;
        }
    }
}

void update_player_coordinates(GameState* state, uint32_t dt) {
    state->player.y += state->player_v.y * dt;
    state->player_global.y += state->player_v.y * dt;

    if(state->player.x < BONDARIES_X_LEFT * SCALE) {
        state->player.x = BONDARIES_X_LEFT * SCALE;
    } else if(state->player.x > (BONDARIES_X_RIGHT - PLAYER_WIDTH) * SCALE) {
        state->player.x = (BONDARIES_X_RIGHT - PLAYER_WIDTH) * SCALE;
    } else {
        state->player.x += state->player_v.x * dt;
    }

    if(state->player.x <= BONDARIES_X_LEFT * SCALE) {
        if(!state->in_boundaries) {
            state->player_global.x += state->player_v.x * dt;
        }
    } else if(state->player.x >= (BONDARIES_X_RIGHT - PLAYER_WIDTH) * SCALE) {
        if(!state->in_boundaries) {
            state->player_global.x += state->player_v.x * dt;
        }
    } else {
        state->player_global.x += state->player_v.x * dt;
    }

    // gravity + floor

    int32_t floor_height = SCREEN_HEIGHT * SCALE -
                           HEIGHT_MAP[(abs(state->player_global.x) / SCALE) % WORLD_WIDTH] -
                           PLAYER_HEIGHT * SCALE;

    int32_t f_h;
    for(size_t i = 1; i < PLAYER_WIDTH; i++) {
        f_h = SCREEN_HEIGHT * SCALE -
              HEIGHT_MAP[(abs(state->player_global.x) / SCALE + i) % WORLD_WIDTH] -
              PLAYER_HEIGHT * SCALE;
        if(f_h < floor_height) {
            floor_height = f_h;
        }
    }

    if(state->player_global.y >= floor_height && !state->next_level) {
        state->player.y = floor_height;
        state->player_global.y = floor_height;
        state->player_v.y = 0;
    } else {
        state->player_v.y += 5;
    }

    if(state->player.y > (SCREEN_HEIGHT - PLAYER_HEIGHT - 4) * SCALE) {
        state->player.y = (SCREEN_HEIGHT - PLAYER_HEIGHT - 4) * SCALE;
    }

    // global
    state->screen.x = state->player_global.x - state->player.x;
    state->screen.y = state->player.y - state->player_global.y;

    if(state->player_global.x < BONDARIES_X_LEFT * SCALE) {
        state->player_global.x += WORLD_WIDTH * SCALE;
    }

    /*
    if (state->player_global.x > (WORLD_WIDTH - BONDARIES_X_RIGHT * SCALE)) {
        state->player_global.x -= WORLD_WIDTH * SCALE;
    }
    */

    state->player_anim = (state->player_global.x / (SCALE * 4)) % 2;
}