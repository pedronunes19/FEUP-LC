#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseColumns(uint8_t **arr, unsigned R, unsigned C);

void reverseRows(uint8_t **arr, unsigned R, unsigned C);

// Function for do transpose of matrix
void transpose(uint8_t **arr, unsigned R, unsigned C);

// Function for print matrix
void printMatrix(uint8_t **arr, unsigned R, unsigned C);

void rotateLeft(uint8_t **arr, unsigned R, unsigned C);

void rotateRight(uint8_t **arr, unsigned R, unsigned C);
