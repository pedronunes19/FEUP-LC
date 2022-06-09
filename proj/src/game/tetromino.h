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
  int32_t x;
  int32_t y;
  tetromino_type type;
  uint8_t **matrix;
  xpm_image_t image;
} tetromino_t;

void check_rotate_inside_border(tetromino_t* tetromino);

void rotatePieceLeft(tetromino_t* piece);

void rotatePieceRight(tetromino_t* piece);

tetromino_t* create_tetromino(tetromino_type type);

void delete_tetromino(tetromino_t * tetromino);
