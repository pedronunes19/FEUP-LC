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

#include "devices/video_card.h"


int load_xpms();
void load_tetromino_image(tetromino_t *tetromino);
void draw_board(tetromino_type board_state[16][10]);
void draw_board_bg();
void draw_menu();
