#include "leaderboard.h"

Array scores;

void init_array(Array* a, size_t init_size) {

    a->array = malloc(sizeof(Entry) * init_size);
    a->size = init_size;
    a->used = 0;

}

void insert_array(Array* a, Entry element) {

    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, sizeof(Entry) * a->size);
    }

    a->array[a->used++] = element;

}

void free_array(Array* a) {

    for (size_t i = 0; i < a->used; i++) {
      free(a->array[i].name);
      free(a->array[i].score);
      free(a->array[i].date);
    }

    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
}

//------------------------------------

void get_scores() {

  init_array(&scores, 10);

  FILE* file = fopen("home/lcom/labs/proj/src/game/scores.txt", "r");

  if (file == NULL) {
    printf("file was null :((\n");
    return;
  }

  char line[30];
  fgets(line, 20, file);

  while (fgets(line, 30, file)) {
    char name[4];
    strcpy(name, strtok(line, " \n"));

    char score[4];
    sprintf(score, "%d", atoi(strtok(NULL, " \n")));

    char date[11];
    strcpy(date, strtok(NULL, " \n"));

    Entry lb_entry;
    lb_entry.name = strdup(name); lb_entry.score = strdup(score); lb_entry.date = strdup(date);

    insert_array(&scores, lb_entry);
  }

  fclose(file);

}

void draw_scores() {

  Position leaderboard_pos = {100, 200};
  int lines_to_write = (scores.used > 10) ? 10 : scores.used;

  for (int i = 0; i < lines_to_write; i++) {

    draw_string(scores.array[i].name, leaderboard_pos.x, leaderboard_pos.y, 3, true);
    draw_string(scores.array[i].date, leaderboard_pos.x + 260, leaderboard_pos.y, 3, true);
    draw_string(scores.array[i].score, leaderboard_pos.x + 500, leaderboard_pos.y, 3, true);

    leaderboard_pos.y += 30;
    
  }

}
