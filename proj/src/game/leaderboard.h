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

/**
 * @brief 
 * 
 * @param a 
 * @param init_size 
 */
void init_array(Array* a, size_t init_size);

/**
 * @brief 
 * 
 * @param a 
 * @param element 
 */
void insert_array(Array* a, Entry element);

/**
 * @brief 
 * 
 * @param a 
 */
void free_array(Array* a);

//-------------------------------------------------------------------

/**
 * @brief Get the scores object
 * 
 */
void get_scores();

/**
 * @brief 
 * 
 */
void draw_scores();
