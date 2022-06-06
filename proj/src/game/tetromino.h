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
  uint8_t **matrix;
  xpm_image_t image;
} tetromino_t;

void rotatePieceLeft(tetromino_t* piece);

void rotatePieceRight(tetromino_t* piece);

tetromino_t* createTetromino(tetromino_type type, xpm_image_t image);

void deleteTetromino(tetromino_t * tetromino);
