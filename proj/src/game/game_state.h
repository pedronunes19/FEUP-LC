#include "draw_graphics.h"
#include "tetromino.h"

typedef enum {
  PLAYING,
  MAIN_MENU,
  FINISHED
} game_state;

static tetromino_type board[16][10];
static tetromino_t *tetromino;
extern game_state state;

void start_game();
void draw_game_ui();
void piece_fall();
void clear_tetromino();
void place_tetromino();
bool check_collision();
