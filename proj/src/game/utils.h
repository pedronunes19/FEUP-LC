#pragma once

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseColumns(uint8_t arr[4][4]);

void reverseRows(uint8_t arr[4][4]);

// Function for do transpose of matrix
void transpose(uint8_t arr[4][4]);

// Function for print matrix
void printMatrix(uint8_t arr[4][4]);

void rotateLeft(uint8_t arr[4][4]);

void rotateRight(uint8_t arr[4][4]);

bool is_alpha(char character);
