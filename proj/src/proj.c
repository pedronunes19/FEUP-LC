#include "devices/video_card.h"
#include "devices/keyboard.h"
#include "devices/rtc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {

  vg_init(DC_800x600_24);

  board_t *board = malloc(sizeof(board_t));
  board->width = 10;
  board->height = 16;
  board->color = 0xFFFFFF;
  board->stroke = 10;
  board->margin = 5;

  tetromino_t *tetromino = malloc(sizeof(tetromino_t));
  tetromino->type = O;

  draw_character('I', false, 0, 0);
  /*
  draw_board(board);
  draw_tetromino(tetromino, true);
  draw_board_state();*/
  sleep(4);
  /*draw_menu();
  sleep(4);*/

  free(tetromino);
  free(board);

  vg_exit();  
  return 0;
  
}
