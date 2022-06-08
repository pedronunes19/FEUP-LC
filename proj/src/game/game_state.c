#include "game_state.h"

static tetromino_type piece_type[] = {I, J, L, S, O, T, Z};
static int counter = 1;
game_state state = PLAYING;
bool spawned = false;
bool end = false;

void start_game() {
  memset(*board, 0, sizeof(board));
  shuffle(piece_type);
  tetromino = create_tetromino(piece_type[0]);
  load_tetromino_image(tetromino);
  place_tetromino(tetromino);
  
  draw_game_ui();
  
  for (int i = 0; i < 10; i++)
    board[0][i] = 1;
  
  draw_board(board);
}

bool check_space() {
  //printf("Checking if piece can be drawn\n\n");
  int last_y_idx = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j] != 0) {
        last_y_idx = i;
        if ((board[15 - i - tetromino->y][j + tetromino->x] != 0) && ((i + tetromino->y) >= 0)) {
          /*
          printf("board y: %d\nboard x: %d\n", 15 - i - tetromino->y, j + tetromino->x);
          printf("board block value: %d\n\n", board[15 - i - tetromino->y][j + tetromino->x]);
          printf("Can't draw!\n\n");
          */
          return false;
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
  //bottom piece block is outside of the board -> adjust failed, game over
  if (last_y_idx + tetromino->y < 0) {
    end = true;
    return false;
  }
  return true;
}

void place_tetromino() {

  while (!check_space() && !end) {
    //Push the piece up trying to fit it in the remaining space
    tetromino->y--;
  }
  //printf("Drawing piece\n\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((tetromino->matrix[i][j] != 0) && (i + tetromino->y >= 0)) {
        board[15 - i - tetromino->y][j + tetromino->x] = tetromino->type;
      }
    }
  }
  /*
  printf("End of drawing piece\n\n");
  printf("Board state after drawing\n\n");
  for (int i = 15; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  */
}

void piece_fall() {
  //printf("\nThe end? %s", end ? "Yes!\n\n" : "Not yet...\n\n");
  if (end) return;
  if (!spawned) clear_tetromino();
  /*
  printf("Board state after clear (only if piece can move)\n\n");
  for (int i = 15; i >= 0; i--) {
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
  draw_gradient();
  draw_board_bg();
  draw_score("9999");
}

bool check_collision() {
  uint8_t y = tetromino->y + 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((tetromino->matrix[i][j] != 0) && (board[15 - i - y][j + tetromino->x] != 0)) {
        return true;
      }
      printf("\n\n%d - %d - %d\n\n", y + j, tetromino->matrix[i][j] != 0, y + (j) > 15);
      if ((tetromino->matrix[i][j] != 0) && (y + (i) > 15)) {
        return true;
      }
    }
    printf("\n");
  }
  printf("\n");
  return false;
}

void main_menu() {
  draw_main_menu();
}
