#include "game_state.h"

void start_game() {

  memset(*board, 0, sizeof(board));
  tetromino = create_tetromino(I);
  load_tetromino_image(tetromino);
  place_tetromino(tetromino);

  draw_game_ui();
  for (int i = 0; i < 10; i++)
    board[0][i] = 1;
  draw_board(board);
}

void place_tetromino() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (tetromino->matrix[i][j] != 0)
        board[15 - i - tetromino->y][j + tetromino->x] = tetromino->type;
}

void piece_fall() {
  clear_tetromino();
  bool collision = check_collision();

  if (!collision)
    tetromino->y += 1;

  place_tetromino();
  draw_board(board);
}

void clear_tetromino() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (tetromino->matrix[i][j] != 0)
        board[15 - i - tetromino->y][j + tetromino->x] = 0;
}

void draw_game_ui() {
  // todo: draw other ui elements
  draw_board_bg();
}

bool check_collision() {
  uint8_t y = tetromino->y + 1;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j] != 0 && board[15 - i - y][j + tetromino->x] != 0) {
        return true;
      }
      if (tetromino->matrix[i][j] != 0 && y + (j + 1) > 15) {
        return true;
      }
    }

  return false;
}
