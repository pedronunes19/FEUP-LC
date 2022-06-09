#pragma once

#include "game/board.h"
#include "game/tetromino.h"
#include "vc_defines.h"

#include <machine/int86.h>
#include <stdint.h>

// TODO: IMPLEMENT GET MODE INFO (?)

// int (vbe_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

void *(vg_init) (uint16_t mode);
int(change_mode)(uint16_t mode);
int(map_vm)();
void(draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
void(draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);
int vg_draw_board(xpm_image_t board);
void draw_board_block(xpm_image_t img, uint8_t x, uint8_t y);
void vg_draw_character(xpm_image_t font, uint16_t x, uint16_t y, uint8_t scale, uint8_t *pnt);
int vg_draw_score_bg(xpm_image_t square);
