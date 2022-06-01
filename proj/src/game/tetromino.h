#pragma once

#include <stdint.h>
#include "utils.h"

typedef struct {
    uint32_t x;
    uint32_t y;
    char* tcolor;
    uint8_t** matrix; 
} tetromino_t;

void rotatePieceLeft(tetromino_t piece);

void rotatePieceRight(tetromino_t piece);
