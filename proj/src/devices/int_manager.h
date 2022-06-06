#include <lcom/timer.h>

#include "timer.h"
#include "keyboard.h"
#include "mouse.h"

#include "../event_handler/kbd_event_handler.h"
#include "../event_handler/mouse_event_handler.h"
#include "../event_handler/timer_event_handler.h"

#define SLOW 40
#define NORMAL 30
#define FAST 20

int (init)();
int (main_loop)();
int (leave)();
int (load_xpms)();
void draw_board_state();
