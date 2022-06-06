#include "int_manager.h"
#include "devices/video_card.h"
#include "game/tetromino.h"
#include "imgs/tetromino_blue.xpm"
#include "imgs/tetromino_yellow.xpm"
#include "imgs/tetromino_red.xpm"
#include "imgs/tetromino_purple.xpm"
#include "imgs/tetromino_green.xpm"
#include "imgs/tetromino_cyan.xpm"
#include "imgs/tetromino_orange.xpm"
#include "imgs/clear.xpm"
#include "imgs/menu_800x600.xpm"
#include "imgs/font.xpm"
#include "imgs/cursor.xpm"
#include "imgs/board.xpm"
#include "imgs/gradient.xpm"
#include "imgs/sidebar.xpm"

uint32_t timer_irq_set, kbd_irq_set, mouse_irq_set;
xpm_image_t tetromino_blue, tetromino_yellow, tetromino_red, tetromino_purple, tetromino_green, tetromino_cyan, tetromino_orange, cursor, main_menu, font, board, gradient, sidebar, clear;
// tetromino_type board_state[16][10];


int (init)() {
  uint8_t timer_bit_no = 0, kbd_bit_no = 1, mouse_bit_no = 2;

  // enabling interrupts
  timer_irq_set = BIT(timer_bit_no);
  kbd_irq_set = BIT(kbd_bit_no);
  mouse_irq_set = BIT(mouse_bit_no);

  timer_subscribe_int(&timer_bit_no);
  kbd_subscribe_int(&kbd_bit_no);
  mouse_subscribe_int(&mouse_bit_no);
  _mouse_enable_data_reporting();

  // initialize vc
  vg_init(DC_800x600_24);

  // loading xpms
  load_xpms();

  return 0;
}


int (main_loop)() {
  message msg;
  int ipc_status;

  tetromino_t *tetromino = createTetromino(O, tetromino_green);

  draw_board(board);
  draw_board_state();

  while (scan_code[kbd_i] != ESC_BREAK) {

    int r;
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
      printf("driver_receive failed with: %d", r);
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE: {

          if (msg.m_notify.interrupts & mouse_irq_set) {

            mouse_ih();
            if (mouse_ready) {

              mouse_ready = false;
              handle_mouse_event(&pp);

            }

          } else if (msg.m_notify.interrupts & kbd_irq_set) {
						 
						kbc_ih();
            
						if (scan_code[kbd_i] == TWO_BYTE_SC) {
							kbd_i++;
							continue;
						}

						kbd_i = 0;
            handle_kbd_event(&scan_code);

					} else if (msg.m_notify.interrupts & timer_irq_set) {

							timer_int_handler();
							
              if (timer_counter % 2 == 0) {
                handle_timer_event();
							}

              if (timer_counter % FAST == 0) {
                clear_tetromino(tetromino, clear);
                draw_board_state();
                draw_tetromino(tetromino);
                tetromino->y += 1;
              }

					}	

          break;
        }

        default: break;
      }
    }
  }

  return EXIT_SUCCESS;
}

int (leave)() {

	timer_unsubscribe_int();
	kbd_unsubscribe_int();
  mouse_unsubscribe_int();
  mouse_disable_data_reporting();
  vg_exit();

  return 0;
}

int (load_xpms)() {
  xpm_load(tetromino_blue_xpm, XPM_8_8_8, &tetromino_blue);
  xpm_load(tetromino_cyan_xpm, XPM_8_8_8, &tetromino_cyan);
  xpm_load(tetromino_orange_xpm, XPM_8_8_8, &tetromino_orange);
  xpm_load(tetromino_yellow_xpm, XPM_8_8_8, &tetromino_yellow);
  xpm_load(tetromino_purple_xpm, XPM_8_8_8, &tetromino_purple);
  xpm_load(tetromino_red_xpm, XPM_8_8_8, &tetromino_red);
  xpm_load(tetromino_green_xpm, XPM_8_8_8, &tetromino_green);
  xpm_load(font_xpm, XPM_8_8_8, &font);
  xpm_load(cursor_xpm, XPM_8_8_8, &cursor);
  xpm_load(menu_800x600, XPM_8_8_8, &main_menu);
  xpm_load(gradient_xpm, XPM_8_8_8, &gradient);
  xpm_load(sidebar_xpm, XPM_8_8_8, &sidebar);
  xpm_load(board_xpm, XPM_8_8_8, &board);
  xpm_load(clear_xpm, XPM_8_8_8, &clear);

  return 0;   
}

void draw_board_state() {
  tetromino_type mx[16][10] = {{1,2,3,4,5,6,1,1,1,1}};

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 10; j++) {
      switch(mx[i][j]) {
        case  0:
          break;
        case J:
          draw_board_space(tetromino_blue, j, i);
          break;
        case I:
          draw_board_space(tetromino_cyan, j, i);
          break;
        case L:
          draw_board_space(tetromino_orange, j, i);
          break;
        case S:
          draw_board_space(tetromino_green, j, i);
          break;
        case O:
          draw_board_space(tetromino_yellow, j, i);
          break;
        case T:
          draw_board_space(tetromino_purple, j, i);
          break;
        case Z:
          draw_board_space(tetromino_red, j, i);
          break;
      }        
    }
  }
}
