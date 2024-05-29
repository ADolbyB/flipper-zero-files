#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>

typedef enum {
	EventTypeTick,
	EventTypeKey,
} EventType;

typedef struct {
	EventType type;
	InputEvent input;
} GameOfLifeEvent;

// 128 x 64 screen, by using 4 x 4 cells we have a 32 x 16
// "cell grid" to play with
//
// (if space is a concern we could use a single char for each 8
// cells group, since they can only be 1 or 0, but for now each
// one be a uint8_t and this will work too)
#define GAME_OF_LIFE_GRID_WIDTH 32
#define GAME_OF_LIFE_GRID_HEIGHT 16

#define GAME_OF_LIFE_GRID_TOTAL GAME_OF_LIFE_GRID_WIDTH * GAME_OF_LIFE_GRID_HEIGHT

#define GAME_OF_LIFE_CELL_SIZE 4

typedef struct {
	uint8_t grid[GAME_OF_LIFE_GRID_TOTAL];
} GameOfLifeState;

static void game_of_life_draw_cell(Canvas* const canvas, int i, int j, uint8_t s) {
	if (s == 1) canvas_set_color(canvas, ColorBlack);
	else canvas_set_color(canvas, ColorWhite);

	canvas_draw_box(canvas, i * GAME_OF_LIFE_CELL_SIZE, j * GAME_OF_LIFE_CELL_SIZE, GAME_OF_LIFE_CELL_SIZE, GAME_OF_LIFE_CELL_SIZE);
}

static void game_of_life_render_callback(Canvas* const canvas, void* ctx) {

	const GameOfLifeState* game_of_life_state = acquire_mutex((ValueMutex*)ctx, 25);
	if(game_of_life_state == NULL) {
		return;
	}

	for (int i = 0; i < GAME_OF_LIFE_GRID_WIDTH; i++) {
		for (int j = 0; j < GAME_OF_LIFE_GRID_HEIGHT; j++) {
			game_of_life_draw_cell(canvas, i, j, game_of_life_state->grid[j * GAME_OF_LIFE_GRID_WIDTH + i]);
		}
	}

	canvas_set_color(canvas, ColorBlack);

	release_mutex((ValueMutex*)ctx, game_of_life_state);
}

static void game_of_life_input_callback(InputEvent* input_event, FuriMessageQueue* event_queue) {
	furi_assert(event_queue); 

	GameOfLifeEvent event = {.type = EventTypeKey, .input = *input_event};
    furi_message_queue_put(event_queue, &event, FuriWaitForever);
}

static void game_of_life_update_timer_callback(FuriMessageQueue* event_queue) {
	furi_assert(event_queue);

	GameOfLifeEvent event = {.type = EventTypeTick};
	furi_message_queue_put(event_queue, &event, 0);
}

static void game_of_life_step(GameOfLifeState* const game_of_life_state) {

	// maybe create a persistent tmp buffer on the state struct?
	uint8_t tmp_grid[GAME_OF_LIFE_GRID_TOTAL];

	// count the neighbours
	// 	if the cell is live
	// 		dies if < 2 neighbours
	// 		lives if == 2 || == 3 neighbours
	// 		dies if > 3 neighbours
	// if the cell is dead
	// 		lives if == 3 neighbours

	for (int i = 0; i < GAME_OF_LIFE_GRID_WIDTH; i++) {
		for (int j = 0; j < GAME_OF_LIFE_GRID_HEIGHT; j++) {
			uint8_t current_cell = game_of_life_state->grid[j * GAME_OF_LIFE_GRID_WIDTH + i];
			uint8_t new_cell;
			uint8_t neighbours_count = 0;

			// when reaching the grid limits just loop to the opposite side (infinite canvas)
			uint8_t i_left = i-1 < 0 ? GAME_OF_LIFE_GRID_WIDTH-1 : i-1;
			uint8_t i_right = i+1 > GAME_OF_LIFE_GRID_WIDTH-1 ? 0 : i+1;

			uint8_t j_left = j-1 < 0 ? GAME_OF_LIFE_GRID_HEIGHT-1 : j-1;
			uint8_t j_right = j+1 > GAME_OF_LIFE_GRID_HEIGHT-1 ? 0 : j+1;

			// LEFT
			neighbours_count += game_of_life_state->grid[j_left * GAME_OF_LIFE_GRID_WIDTH + i_left]; // TOP - LEFT
			neighbours_count += game_of_life_state->grid[j * GAME_OF_LIFE_GRID_WIDTH + i_left]; // MIDDLE - LEFT
			neighbours_count += game_of_life_state->grid[j_right * GAME_OF_LIFE_GRID_WIDTH + i_left]; // BOTTOM - LEFT

			// MIDDLE
			neighbours_count += game_of_life_state->grid[j_left * GAME_OF_LIFE_GRID_WIDTH + i]; // TOP - MIDDLE
			neighbours_count += game_of_life_state->grid[j_right * GAME_OF_LIFE_GRID_WIDTH + i]; // BOTTOM - MIDDLE

			// BOTTOM
			neighbours_count += game_of_life_state->grid[j_left * GAME_OF_LIFE_GRID_WIDTH + i_right]; // TOP - RIGHT
			neighbours_count += game_of_life_state->grid[j * GAME_OF_LIFE_GRID_WIDTH + i_right]; // MIDDLE - RIGHT
			neighbours_count += game_of_life_state->grid[j_right * GAME_OF_LIFE_GRID_WIDTH + i_right]; // BOTTOM - RIGHT

			if (
				(current_cell && (neighbours_count < 2 || neighbours_count > 3)) ||
				(!current_cell && neighbours_count != 3)
			) {
				new_cell = 0;
			} else {
				new_cell = 1;
			}

			tmp_grid[j * GAME_OF_LIFE_GRID_WIDTH + i] = new_cell;
		}
	}
	
	// copy the new grid
	memcpy(game_of_life_state->grid, tmp_grid, GAME_OF_LIFE_GRID_TOTAL);

} 

void game_of_life_init(GameOfLifeState* const game_of_life_state) {

	for (int i = 0; i < GAME_OF_LIFE_GRID_TOTAL; i++) {
		// each cell has a 50% chance of being alive at the beginning
		game_of_life_state->grid[i] = rand() % 2 ? 1 : 0;
	}

	/*
		// testing values
		game_of_life_state->grid[0] = 1;

		game_of_life_state->grid[2] = 1;
		game_of_life_state->grid[3] = 1;

		// classic glider
		game_of_life_state->grid[5 * GAME_OF_LIFE_GRID_WIDTH + 10] = 1;
		game_of_life_state->grid[6 * GAME_OF_LIFE_GRID_WIDTH + 11] = 1;
		game_of_life_state->grid[7 * GAME_OF_LIFE_GRID_WIDTH + 9] = 1;
		game_of_life_state->grid[7 * GAME_OF_LIFE_GRID_WIDTH + 10] = 1;
		game_of_life_state->grid[7 * GAME_OF_LIFE_GRID_WIDTH + 11] = 1;
	*/

	game_of_life_state->grid[(GAME_OF_LIFE_GRID_HEIGHT - 1) * GAME_OF_LIFE_GRID_WIDTH + (GAME_OF_LIFE_GRID_WIDTH - 1)] = 1;

}

// main entry point
int32_t game_of_life_app(void* p) {
    UNUSED(p);
    srand(DWT->CYCCNT); // use last wiegand bit recieved as seed

	// get event queue
	FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(GameOfLifeEvent));

	// allocate state
	GameOfLifeState* game_of_life_state = malloc(sizeof(GameOfLifeState));

	// set mutex for plugin state (different threads can access it)
	ValueMutex state_mutex;
	if(!init_mutex(&state_mutex, game_of_life_state, sizeof(game_of_life_state))) {
		FURI_LOG_E("GameOfLife", "cannot create mutex\r\n");
		free(game_of_life_state);
		return 255;
	}

	// register callbacks for drawing and input processing
	ViewPort* view_port = view_port_alloc();
	view_port_draw_callback_set(view_port, game_of_life_render_callback, &state_mutex);
	view_port_input_callback_set(view_port, game_of_life_input_callback, event_queue);

	FuriTimer* timer = furi_timer_alloc(game_of_life_update_timer_callback, FuriTimerTypePeriodic, event_queue);
    furi_timer_start(timer, furi_kernel_get_tick_frequency() / 2); // systick counts per second, so this means "each second / 2"

	// open GUI and register view_port
	Gui* gui = furi_record_open("gui");
	gui_add_view_port(gui, view_port, GuiLayerFullscreen);

	// init game
	game_of_life_init(game_of_life_state);

	// main loop
	GameOfLifeEvent event;
	for (bool processing = true; processing;) {
		FuriStatus event_status = furi_message_queue_get(event_queue, &event, 100);
		GameOfLifeState* game_of_life_state = (GameOfLifeState*)acquire_mutex_block(&state_mutex);

		if (event_status == FuriStatusOk) {
			// press events
			if (event.type == EventTypeKey) {
				if (event.input.type == InputTypePress) {
					switch(event.input.key) {
						default:
							break;
						case InputKeyOk:
							game_of_life_init(game_of_life_state);
							break;
						case InputKeyBack:
							processing = false;
							break;
					}
				}
			} else if(event.type == EventTypeTick) {
				game_of_life_step(game_of_life_state);
			}
		} else {
			// event timeout
		}
	
		view_port_update(view_port);
		release_mutex(&state_mutex, game_of_life_state);
	}

    furi_timer_free(timer);
	view_port_enabled_set(view_port, false);
	gui_remove_view_port(gui, view_port);
	furi_record_close("gui");
	view_port_free(view_port);
    furi_message_queue_free(event_queue);
    delete_mutex(&state_mutex);
    free(game_of_life_state);

    return 0;
}