#include <furi.h>
#include "floopper-bloopper/floopper-bloopper.h"

void render_world(GameState* state, Canvas* canvas, uint32_t t) {
    char buf[32];

    canvas_set_color(canvas, ColorBlack);
    for(size_t i = 0; i < SCREEN_WIDTH; i++) {
        int32_t floor_height = HEIGHT_MAP[abs(state->screen.x / SCALE + i) % WORLD_WIDTH];

        canvas_draw_box(canvas, i, SCREEN_HEIGHT - (floor_height - state->screen.y) / SCALE, 1, 5);
    }

    // in-level label
    canvas_set_font(canvas, FontSecondary);
    canvas_set_color(canvas, ColorBlack);

    if(t - state->glitch_t > 250) {
        state->glitch_t = t;
    }

    const TextBlock* label = &NARRATIVE[state->label_id];
    for(size_t i = 0; i < label->line_size; i++) {
        strcpy(buf, label->lines[i]);

        for(size_t glitch = 0; glitch < state->glitch_level; glitch++) {
            buf[(state->glitch_t + glitch * 23) % strlen(buf)] =
                ' ' + (state->glitch_t + glitch * 17) % ('z' - ' ');
        }

        canvas_draw_str(
            canvas,
            (LABEL_X - state->screen.x) / SCALE,
            ((LABEL_Y + LABEL_HEIGHT * i) + state->screen.y) / SCALE,
            buf);
    }

    if(state->combo_text) {
        canvas_set_color(canvas, ColorWhite);
        canvas_draw_box(canvas, SCREEN_WIDTH / 2 - 15, 0, SCREEN_WIDTH / 2 + 15, 25);
        canvas_set_color(canvas, ColorBlack);
        canvas_draw_frame(canvas, SCREEN_WIDTH / 2 - 15, 0, SCREEN_WIDTH / 2 + 15, 25);
        canvas_draw_str(canvas, SCREEN_WIDTH / 2 - 10, 15, "COCOCOCOMBO!");
    }
}
