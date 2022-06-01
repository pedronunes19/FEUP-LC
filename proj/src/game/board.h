#pragma once

#include <stdint.h>

extern int matrix[16][10];

typedef struct {
    int width;
    int height;
    int color;
    int stroke;
    int margin;
} board_t;
