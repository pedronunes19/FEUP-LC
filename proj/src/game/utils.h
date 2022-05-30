#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../imgs/tetromino.xpm"

void reverseColumns(uint8_t **arr, unsigned R, unsigned C);

void reverseRows(uint8_t **arr, unsigned R, unsigned C);

// Function for do transpose of matrix
void transpose(uint8_t **arr, unsigned R, unsigned C);
 
// Function for print matrix
void printMatrix(uint8_t **arr, unsigned R, unsigned C);

void rotateLeft(uint8_t **arr, unsigned R, unsigned C);

void rotateRight(uint8_t **arr, unsigned R, unsigned C);

void switchMainColor(char *color);

/* Currently not useful keeping this in case we decide to do something of this sort */
void switchSubColor(char *color);
