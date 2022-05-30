#include "tetromino.h"

void rotatePieceLeft(tetromino_t piece){
    rotateLeft(piece.matrix, 4, 4);
    // check borders and move accordingly
}

void rotatePieceRight(tetromino_t piece){
    rotateRight(piece.matrix, 4, 4);
    // check borders and move accordingly
}
