#include "logic.h"

tetromino_t tmp;
int piece_count = 7;

void shuffle(tetromino_t* array) {
    for (int i = 6; i > 0; i--) {
        srand(time(NULL));
        int j = rand() % i;
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}

int test() {
    tetromino_t piece_1; piece_1.x = 1;
    tetromino_t piece_2; piece_2.x = 2;
    tetromino_t piece_3; piece_3.x = 3;
    tetromino_t piece_4; piece_4.x = 4;
    tetromino_t piece_5; piece_5.x = 5;
    tetromino_t piece_6; piece_6.x = 6;
    tetromino_t piece_7; piece_7.x = 7;
    tetromino_t curr_piece;
    tetromino_t test_array[7] = {piece_1, piece_2, piece_3, piece_4, piece_5, piece_6, piece_7};
    
    for (int i = 0; i < 7; i++) {
        curr_piece = test_array[i];
        printf("%d ", curr_piece.x);
    }

    printf("\n");
    shuffle(test_array);

    for (int i = 0; i < 7; i++) {
        curr_piece = test_array[i];
        printf("%d ", curr_piece.x);
    }
    return 0;
}