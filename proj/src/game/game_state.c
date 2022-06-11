#include "game_state.h"

static tetromino_type piece_type[] = {I, J, L, S, O, T, Z};
static int counter = 1;
game_state state = PLAYING;
bool spawned = false;
bool end = false;
bool cleared = false;
int score = 0;
char* score_string = "0";
Cursor cursor_pos = {0, 0};
 
void start_game() {
  memset(*board, 0, sizeof(board));
  shuffle(piece_type);
  tetromino = create_tetromino(piece_type[0]);
  load_tetromino_image(tetromino);
  place_tetromino();
  /*
  for (int i = 0; i < 10; i++) {
    board[0][i] = I;
    board[1][i] = I;
    board[2][i] = I;
    board[3][i] = I;    
  }
  board[0][5] = 0;
  board[1][5] = 0;
  board[2][5] = 0;
  board[3][5] = 0;
  board[5][0] = I;
  */
  draw_game_ui();
  
  draw_board(board);
}

bool check_space() {
  //printf("Checking if piece can be drawn\n\n");
  int last_y_idx = 0;
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
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
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  //printf("Drawing piece\n\n");
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
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

bool clear_lines() {
  //printf("\n\nclearing lines\n\n");
  bool full = true;
  bool clearing = false;
  while (full) {
    for (int i = 0; i < 16; i++) {
      full = true;
      for (int j = 0; j < 10; j++) {
        if (board[i][j] == 0) {
          //printf("Not full!\n");
          full = false;
          break;
        }
      }
      if (full) {
        clearing = true;
        score++;
        sprintf(score_string, "%d", score);
        //printf("Clearing!\n");
        //printf("%d", i);
        for (int idx = i; idx < 15; idx++) {
          for (int j = 0; j < 10; j++) {
            board[idx][j] = 0;
            board[idx][j] = board[idx+1][j];
          }
        }
        for (int j = 0; j < 10; j++) {
          board[15][j] = 0;
        }
        /*
        printf("Board state after drawing\n\n");
        for (int i = 15; i >= 0; i--) {
          for (int j = 0; j < 10; j++) {
            printf("%d", board[i][j]);
          }
          printf("\n");
        }
        printf("\n\n");
        */
        i--;
      }
    }
  }
  return clearing;
}

/* In loving memory of Gravity, RIP. (unneeded function)
void gravity() {
  for (int i = 1; i < 16; i++) {
    for (int j = 0; j < 10; j++) {
      while ((board[i][j] != 0) && (board[i-1][j] == 0)){
        board[i-1][j] = board[i][j];
        board[i][j] = 0;
        if (i>1) i--;
      }
    }
  }
}
*/

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
  bool collision = check_collision(DOWN);
  //printf("\n\nCollided? %d\n\n", collision);

  if (!collision) {
    if (!spawned) tetromino->y += 1;
    spawned = false;
  }
  place_tetromino();

  if (collision) {
    cleared = clear_lines();
    if (cleared) draw_score(score_string);
    //printf("\nCleared? %d\n", cleared);
    delete_tetromino(tetromino);
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

void hard_drop(){
  bool collision = check_collision(DOWN);
  while (!collision) {
    clear_tetromino();
    collision = check_collision(DOWN);
    if (!collision) {
      tetromino->y += 1;
    }
    place_tetromino();
  }

  if (collision) {
    cleared = clear_lines();
    if (cleared) draw_score(score_string);
    //printf("\nCleared? %d\n", cleared);
    delete_tetromino(tetromino);
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
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++)
    for (int j = 0; j < iter; j++)
      if (tetromino->matrix[i][j] != 0)
        board[15 - i - tetromino->y][j + tetromino->x] = 0;
}

void draw_game_ui() {
  draw_gradient();
  draw_board_bg();
  draw_score(score_string);
}

bool check_collision(collision_dir dir) {
  int y = tetromino->y + 1;
  int left = tetromino->x - 1;
  int right = tetromino->x + 1;
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
      switch(dir){
        case DOWN:
          if ((tetromino->matrix[i][j] != 0) && (board[15 - i - y][j + tetromino->x] != 0)) {
            return true;
          }
          //printf("\n\n%d - %d - %d\n\n", y + j, tetromino->matrix[i][j] != 0, y + (j) > 15);
          if ((tetromino->matrix[i][j] != 0) && (y + (i) > 15)) {
            return true;
          }
          break;
        case LEFT:
          if (((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + left] != 0)) || ((tetromino->matrix[i][j] != 0) && (j + left < 0))) {
            
            return true;
          }
          break;
        case RIGHT:
          if (((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + right] != 0))|| ((tetromino->matrix[i][j] != 0) && (j + right > 9))) {
            return true;
          }
          break;
        case NO_DIR:  
          if ((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + tetromino->x] != 0)) {
            return true;
          }
          break;  
      }
    }
    //printf("\n");
  }
  //printf("\n");
  return false;
}

void move_piece_right() {
  if (spawned) return;
  clear_tetromino();

  bool collision = check_collision(RIGHT);

  if (!collision) {
    tetromino->x += 1;
  }

  place_tetromino();
}

void move_piece_left() {
  if (spawned) return;
  clear_tetromino();

  bool collision = check_collision(LEFT);
  
  if (!collision) {
    tetromino->x -= 1;
  }

  place_tetromino();
}

void piece_rotate(rotate_dir rotation) {
  clear_tetromino();

  switch(rotation) {
    case R_LEFT: rotatePieceLeft(tetromino); break;
    case R_RIGHT: rotatePieceRight(tetromino); break;
  }
  
  place_tetromino();
}

void update_cursor(uint16_t x_val, uint16_t y_val) {

  uint16_t new_x_pos = cursor_pos.x + x_val;
  uint16_t new_y_pos = cursor_pos.y + y_val;

  if (new_x_pos > 0 && new_x_pos < 800) cursor_pos.x = new_x_pos;
  if (new_y_pos > 0 && new_y_pos < 600) cursor_pos.y = new_y_pos;

}

void move_tetromino(uint16_t x_displacement) {
  tetromino->x += x_displacement;
}

void _main_menu() {
  draw_main_menu();
}

void draw_scores() {
  FILE* file = fopen("scores.txt", "r");
  char *line = NULL;
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s\n", line);
  }
  fclose(file);
}

void _leaderboard_menu() {
  draw_leaderboard_menu();

  draw_scores();
}

void _draw_board() {
  draw_board(board);
}
