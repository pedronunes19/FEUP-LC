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
#include "imgs/empty_cursor.xpm"
#include "imgs/board.xpm"
#include "imgs/gradient.xpm"
#include "imgs/sidebar.xpm"
#include "imgs/square_resized.xpm"
#include "imgs/blank_menu.xpm"
#include "imgs/font_white.xpm"

#include "devices/video_card.h"


int load_xpms();
void load_tetromino_image(tetromino_t *tetromino);
void draw_board(tetromino_type board_state[16][10]);
void draw_board_bg();
void draw_main_menu();
void draw_gradient();
void draw_leaderboard_menu();
void draw_finished_menu();
void draw_save_score();
void draw_string(const char *string, uint16_t x, uint16_t y, uint8_t scale, bool white);
void draw_character(const char character, uint16_t x, uint16_t y, uint8_t scale, bool white);
void draw_score(char *score);
void _swap_buffer();
void draw_cursor(uint16_t x, uint16_t y);
void erase_cursor(uint16_t x, uint16_t y);
