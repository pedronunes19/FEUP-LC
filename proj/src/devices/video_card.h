#pragma once

#include "game/board.h"
#include "game/tetromino.h"
#include "vc_defines.h"
#include "imgs/tetromino_blue.xpm"
#include "imgs/tetromino_yellow.xpm"
#include "imgs/tetromino_red.xpm"
#include "imgs/tetromino_purple.xpm"
#include "imgs/tetromino_green.xpm"
#include "imgs/tetromino_cyan.xpm"
#include "imgs/tetromino_orange.xpm"
#include "imgs/menu_800x600.xpm"

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <stdint.h>

// TODO: IMPLEMENT GET MODE INFO (?)

// int (vbe_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

void *(vg_init) (uint16_t mode);
int(change_mode)(uint16_t mode);
int(map_vm)();
void(draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
void(draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);
uint8_t *(xpm_loader) (const tetromino_type tetromino, xpm_image_t *img);
int draw_board(board_t *board);
int draw_tetromino(tetromino_t *tetromino, bool spawn);
void draw_board_state();
void draw_menu();
