#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "game_state.h"

typedef struct {
  char* name;
  char* score;
  char* date;
} Entry;

typedef struct {
    Entry* array;
    size_t used;
    size_t size;
} Array;

extern Array scores;

void init_array(Array* a, size_t init_size);
void insert_array(Array* a, Entry element);
void free_array(Array* a);

//-------------------------------------------------------------------

void get_scores();
void draw_scores();
