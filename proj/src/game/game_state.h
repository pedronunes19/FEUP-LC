#include "draw_graphics.h"
#include "logic.h"

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
