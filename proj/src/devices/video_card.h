#include "vc_defines.h"
#include "./game/board.h"
#include "./game/tetromino.h"

#include <stdint.h>
#include <lcom/lcf.h>
#include <machine/int86.h>

// TODO: IMPLEMENT GET MODE INFO (?)

//int (vbe_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

void *(vg_init)(uint16_t mode);
int (change_mode)(uint16_t mode);
int (map_vm)();
void (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
void (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);
uint8_t *(xpm_loader)(xpm_map_t map, xpm_image_t *img);
int draw_board(board_t *board);
int draw_tetromino(tetromino_t *tetromino);
