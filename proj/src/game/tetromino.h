#pragma once

#include "utils.h"
#include <stdint.h>

typedef enum {
  CLEAR = 0,
  I,
  J,
  L,
  S,
  O,
  T,
  Z
} tetromino_type;

typedef struct {
  uint32_t x;
  uint32_t y;
  tetromino_type type;
  uint8_t matrix[4][4];
  xpm_image_t image;
} tetromino_t;

void rotatePieceLeft(tetromino_t* piece);

void rotatePieceRight(tetromino_t* piece);

tetromino_t* create_tetromino(tetromino_type type);

void delete_tetromino(tetromino_t * tetromino);
