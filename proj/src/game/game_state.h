#pragma once

#include "draw_graphics.h"
#include "logic.h"
#include "utils.h"

typedef enum {
  PLAYING,
  MAIN_MENU,
  FINISHED
} game_state;

typedef enum {
  DOWN,
  LEFT,
  RIGHT,
  NO_DIR
} collision_dir;

typedef enum {
  R_LEFT,
  R_RIGHT
} rotate_dir;

typedef struct {
  uint16_t x;
  uint16_t y;
} Cursor;

static tetromino_type board[16][10];
static tetromino_t *tetromino;
extern game_state state;
static uint8_t time_score;

void main_menu();
void start_game();
void draw_game_ui();
void piece_fall();
void clear_tetromino();
void place_tetromino();
bool check_collision(collision_dir dir);
void piece_rotate(rotate_dir rotation);
void update_cursor(uint16_t x_val, uint16_t y_val);
void move_tetromino(uint16_t x_displacement);
void hard_drop();
