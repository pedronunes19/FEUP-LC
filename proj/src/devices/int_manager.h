#include <lcom/timer.h>

#include "timer.h"
#include "keyboard.h"
#include "mouse.h"

#include "game/game_state.h"

#include "../event_handler/kbd_event_handler.h"
#include "../event_handler/mouse_event_handler.h"
#include "../event_handler/timer_event_handler.h"

#define SLOW 40
#define NORMAL 30
#define FAST 20

int (init)();
int (main_loop)();
int (game_loop)();
int (leave)();
void tetromino_board_state(tetromino_t *tetromino, tetromino_type board_state[16][10]);
