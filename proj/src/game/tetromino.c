#include "tetromino.h"

void check_rotate_border_collision(tetromino_t* tetromino) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j] != 0 && tetromino->x + j > 9) {
        (tetromino->x)-= ((tetromino->x + j)-9);
      }
    }
}


void rotatePieceLeft(tetromino_t* piece){
    rotateLeft(piece->matrix);
    check_rotate_border_collision(piece);
    // check borders and move accordingly
}

void rotatePieceRight(tetromino_t* piece){
    rotateRight(piece->matrix);
    check_rotate_border_collision(piece);
    // check borders and move accordingly
}

tetromino_t* create_tetromino(tetromino_type type){
    tetromino_t *tetromino = (tetromino_t*) malloc(sizeof(tetromino_t));
    memset(tetromino->matrix, 0, 16);
    (type == O) ? (tetromino->x = 2) : (tetromino->x = 4);
    tetromino->y = 0;
    tetromino->type = type;

    switch(type){
        case I:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[3][1] = 1;
            break;
        case J:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][0] = 1;
            break;
        case L:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][2] = 1;
            break;
        case S:
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[2][0] = 1;
            tetromino->matrix[2][1] = 1;
            break;
        case O:
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[1][3] = 1;
            tetromino->matrix[2][2] = 1;
            tetromino->matrix[2][3] = 1;
            break;
        case T:
            tetromino->matrix[1][0] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[2][1] = 1;
            break;
        case Z:
            tetromino->matrix[1][0] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][2] = 1;
            break;
        case CLEAR: // do this correctly later (very much pain coming)
            break;
    }

    return tetromino;
}

void delete_tetromino(tetromino_t * tetromino){
    free(tetromino);
}
