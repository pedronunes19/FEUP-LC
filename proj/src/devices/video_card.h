#pragma once

#include "game/board.h"
#include "game/tetromino.h"
#include "vc_defines.h"

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
int draw_board(xpm_image_t board);
int draw_tetromino(tetromino_t *tetromino);
int clear_tetromino(tetromino_t *tetromino, xpm_image_t clear);
void draw_board_state();
void draw_menu();
void draw_character(const char character, const bool is_number, uint16_t x, uint16_t y);
void draw_board_space(xpm_image_t img, uint8_t x, uint8_t y);
