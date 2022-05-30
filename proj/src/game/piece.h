#include <stdint.h>
#include "utils.h"

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t color;
    uint8_t** matrix; 
} piece_t;

void rotatePieceLeft(piece_t piece){
    rotateLeft(piece.matrix, 3, 3);
    // check borders and move accordingly
}

void rotatePieceRight(piece_t piece){
    rotateRight(piece.matrix, 3, 3);
    // check borders and move accordingly
}