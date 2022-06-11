#include <stdio.h>
#include "../devices/keyboard.h"
#include "../game/game_state.h"

void handle_kbd_event(uint8_t scan_code[2]);
void handle_kbd_playing_event(uint8_t scan_code[2]);
void handle_kbd_finished_event(uint8_t scan_code[2]);
void handle_kbd_leaderboard_event(uint8_t scan_code[2]);
