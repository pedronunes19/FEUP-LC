#pragma once

#include <stdint.h>

extern uint32_t *board_state[16][10];

typedef struct {
    int width;
    int height;
    int color;
    int stroke;
    int margin;
} board_t;
