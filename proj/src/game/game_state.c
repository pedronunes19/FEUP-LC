#include "game_state.h"

static tetromino_type piece_type[] = {I, J, L, S, O, T, Z};
static int counter = 1;
bool spawned = false;

void start_game() {
  memset(*board, 0, sizeof(board));
  shuffle(piece_type);
  tetromino = create_tetromino(piece_type[0]);
  load_tetromino_image(tetromino);
  place_tetromino();

  draw_game_ui();
  for (int i = 0; i < 10; i++)
    board[0][i] = 1;
  draw_board(board);
}

void place_tetromino() {
  printf("Checking if piece can be drawn\n\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j] != 0) {
        if (board[15 - i - tetromino->y][j + tetromino->x] != 0) { 
          /*
          printf("board y: %d\nboard x: %d\n", 15 - i - tetromino->y, j + tetromino->x);
          printf("board block value: %d\n\n", board[15 - i - tetromino->y][j + tetromino->x]);
          printf("Can't draw!\n\n");
          */
          return;
        }
        else {
          /*
          printf("board y: %d\nboard x: %d\n", 15 - i - tetromino->y, j + tetromino->x);
          printf("board block value: %d\n\n", board[15 - i - tetromino->y][j + tetromino->x]);
          */
        }
      }
    }
  }
  //printf("Drawing piece\n\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j] != 0) {
        board[15 - i - tetromino->y][j + tetromino->x] = tetromino->type;
      }
    }
  }
  /*
  printf("End of drawing piece\n\n");
  printf("Board state after drawing\n\n");
  for (int i = 15; i > 0; i--) {
    for (int j = 0; j < 10; j++) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  */
}

void piece_fall() {
  if (!spawned) clear_tetromino();
  /*
  printf("Board state after clear (only if piece can move)\n\n");
  for (int i = 15; i > 0; i--) {
      for (int j = 0; j < 10; j++) {
        printf("%d", board[i][j]);
      }
      printf("\n");
    }
    printf("\n\n");
  */
  bool collision = check_collision();

  if (!collision) {
    tetromino->y += 1;
    spawned = false;
  }

  place_tetromino();
  draw_board(board);

  if (collision) {
    tetromino = create_tetromino(piece_type[counter]);
    load_tetromino_image(tetromino);
    counter++;
    spawned = true;
    
    if (counter > 6) {
      counter = 0;
      shuffle(piece_type);
    }

  }
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
      if (tetromino->matrix[i][j] != 0 && y + (j) > 15) {
        return true;
      }
    }

  return false;
}
