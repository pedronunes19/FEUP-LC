#include "timer_event_handler.h"

void handle_timer_event() {
  _swap_buffer();
  switch (state) {
    case MAIN_MENU: handle_timer_menu_event(); break;
    case PLAYING: handle_timer_playing_event(); break;
    case FINISHED: handle_timer_finished_event(); break;
  }

}

void handle_timer_menu_event() {
  cursor_erase();
  _main_menu();
  cursor_draw();
}

void handle_timer_playing_event() {
  _draw_board();
}

void handle_timer_finished_event() {

}
