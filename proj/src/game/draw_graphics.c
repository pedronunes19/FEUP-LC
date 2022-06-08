#include "draw_graphics.h"

xpm_image_t tetromino_blue, tetromino_yellow, tetromino_red, tetromino_purple, tetromino_green, tetromino_cyan, tetromino_orange, cursor, main_menu, font, board, gradient, sidebar, clear, square;


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
  xpm_load(square_xpm, XPM_8_8_8, &square);
  return 0;   
}

void draw_board_bg() {
  vg_draw_board(board);
}

void draw_menu() {
  draw_xpm(main_menu, 0, 0);
}
void draw_gradient() {
  draw_xpm(gradient, 0, 0);
}

void draw_score(char *score) {
  uint16_t offset = vg_draw_score_bg(square);

  uint16_t text_x = offset + 5;
  uint16_t text_y = 10 + 5;
  
  draw_string(score, text_x, text_y, 3);
}

void load_tetromino_image(tetromino_t *tetromino) {
  switch(tetromino->type) {
    case CLEAR:
      break;
    case J:
      tetromino->image = tetromino_blue;
      break;
    case I:
      tetromino->image = tetromino_cyan;
      break;
    case L:
      tetromino->image = tetromino_orange;
      break;
    case S:
      tetromino->image = tetromino_green;
      break;
    case O:
      tetromino->image = tetromino_yellow;
      break;
    case T:
      tetromino->image = tetromino_purple;
      break;
    case Z:
      tetromino->image = tetromino_red;
      break;
  }
} 

void draw_board(tetromino_type board[16][10]) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 10; j++) {
      switch(board[i][j]) {
        case CLEAR:
          draw_board_block(clear, j, i);
          break;
        case J:
          draw_board_block(tetromino_blue, j, i);
          break;
        case I:
          draw_board_block(tetromino_cyan, j, i);
          break;
        case L:
          draw_board_block(tetromino_orange, j, i);
          break;
        case S:
          draw_board_block(tetromino_green, j, i);
          break;
        case O:
          draw_board_block(tetromino_yellow, j, i);
          break;
        case T:
          draw_board_block(tetromino_purple, j, i);
          break;
        case Z:
          draw_board_block(tetromino_red, j, i);
          break;
      }        
    }
  }
}

void draw_string(const char *string, uint16_t x, uint16_t y, uint8_t scale) {
  for (unsigned int i = 0; i < strlen(string); i++) {
    draw_character(string[i], x + (11 * i) , y, scale);
  }
}

void draw_character(const char character, uint16_t x, uint16_t y, uint8_t scale) {
  uint8_t *pnt = NULL;
  uint8_t font_bpp = (font.size / (font.height * font.width));
  
  if (!is_alpha(character)) {
    int num = character - '0';
    pnt = font.bytes + (6 * num) * font_bpp;

    vg_draw_character(font, x, y, scale, pnt);
  } else {
    int num = (int) character - 65;
    if (num < 0 || num > 25) return;

    if (num >=0 && num <= 14) {
      pnt = font.bytes + (6 * (num + 1)) * font_bpp + (font.width * 7) * font_bpp;
    } else if (num >= 15 && num <=25) {
      pnt = font.bytes + (6 * (num - 15)) * font_bpp + (font.width * 14) * font_bpp;
    }

    vg_draw_character(font, x, y, scale, pnt);
  }
}
