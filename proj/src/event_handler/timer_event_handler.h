#include <stdio.h>
#include "devices/timer.h"
#include <lcom/timer.h>
#include "devices/int_manager.h"
#include "game/game_state.h"

void handle_timer_event();
void handle_timer_menu_event();
void handle_timer_playing_event();
void handle_timer_finished_event();
