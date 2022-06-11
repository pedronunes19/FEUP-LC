#include "mouse_event_handler.h"

void handle_mouse_event(struct packet pp) {
  
  switch(state) {
    case MAIN_MENU: handle_mouse_menu_event(pp); break;
    case PLAYING: handle_mouse_playing_event(pp); break;
    case FINISHED: break;
  }

}

void handle_mouse_playing_event(struct packet pp) {

  if (pp.lb) piece_fall();
  if (pp.rb) piece_rotate(R_RIGHT);

  if (pp.delta_x < 0) {
    move_piece_left();
  } else if (pp.delta_x > 0) {
    move_piece_right();
  }
}

void handle_mouse_menu_event(struct packet pp) {

  update_cursor(pp.delta_x, pp.delta_y);
  // checkButtonClicks();

}
