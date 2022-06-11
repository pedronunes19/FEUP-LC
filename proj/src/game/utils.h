#pragma once

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "devices/keyboard.h"


int msleep(long ms);

void reverseColumns(uint8_t **arr, unsigned R, unsigned C);

void reverseRows(uint8_t **arr, unsigned R, unsigned C);

// Function for do transpose of matrix
void transpose(uint8_t **arr, unsigned R, unsigned C);

// Function for print matrix
void printMatrix(uint8_t **arr, unsigned R, unsigned C);

void rotateLeft(uint8_t **arr, unsigned R, unsigned C);

void rotateRight(uint8_t **arr, unsigned R, unsigned C);

bool is_alpha(char character);

void get_keys();
