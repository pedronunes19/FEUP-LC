#include "tetromino.h"

void rotatePieceLeft(tetromino_t* piece){
    rotateLeft(piece->matrix, 4, 4);
    // check borders and move accordingly
}

void rotatePieceRight(tetromino_t* piece){
    rotateRight(piece->matrix, 4, 4);
    // check borders and move accordingly
}

tetromino_t* createTetromino(tetromino_type type, xpm_image_t image){
    tetromino_t *tetromino = (tetromino_t*) malloc(sizeof(tetromino_t));
    tetromino->x = 4;
    tetromino->y = 0;
    tetromino->type = type;
    tetromino->image = image;

    tetromino->matrix = (uint8_t**) malloc(4*sizeof(uint8_t*));
    tetromino->matrix[0] = (uint8_t*) malloc(4*sizeof(uint8_t));
    tetromino->matrix[1] = (uint8_t*) malloc(4*sizeof(uint8_t));
    tetromino->matrix[2] = (uint8_t*) malloc(4*sizeof(uint8_t));
    tetromino->matrix[3] = (uint8_t*) malloc(4*sizeof(uint8_t));

    switch(type){
        default: // do this correctly later (very much pain coming)
            tetromino->matrix[0][0] = 0;
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[0][2] = 0;
            tetromino->matrix[0][3] = 0;
            tetromino->matrix[1][0] = 0;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[1][2] = 0;
            tetromino->matrix[1][3] = 0;
            tetromino->matrix[2][0] = 0;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][2] = 0;
            tetromino->matrix[2][3] = 0;
            tetromino->matrix[3][0] = 0;
            tetromino->matrix[3][1] = 1;
            tetromino->matrix[3][2] = 0;
            tetromino->matrix[3][3] = 0;
    }

    return tetromino;
}

void deleteTetromino(tetromino_t * tetromino){
    free(tetromino->matrix[0]);
    free(tetromino->matrix[1]);
    free(tetromino->matrix[2]);
    free(tetromino->matrix[3]);
    free(tetromino->matrix);
    free(tetromino);
}
