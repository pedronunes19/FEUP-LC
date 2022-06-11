#include <stdio.h>
#include "devices/mouse.h"
#include "game/game_state.h"

void handle_mouse_event(struct packet pp);
void handle_mouse_menu_event(struct packet pp);
void handle_mouse_playing_event(struct packet pp);
void handle_mouse_finished_event(struct packet pp);
