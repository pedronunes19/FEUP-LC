#include "game/utils.h"

void reverseColumns(uint8_t arr[4][4])
{
    for (unsigned i = 0; i < 4; i++){
        for (unsigned j = 0, k = 4 - 1; j < k; j++, k--){
            //swap(arr[j][i], arr[k][i]);
            uint8_t temp = arr[j][i];
            arr[j][i] = arr[k][i];
            arr[k][i] = temp;
        } 
    }
}

void reverseRows(uint8_t arr[4][4])
{
    for (unsigned i = 0; i < 4; i++){
        for (unsigned j = 0, k = 4 - 1; j < k; j++, k--){
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[i][k];
            arr[i][k] = temp;
        } 
    }
}

// Function for do transpose of matrix
void transpose(uint8_t arr[4][4])
{
    for (unsigned i = 0; i < 4; i++){
        for (unsigned j = i; j < 4; j++){
            //swap(arr[i][j], arr[j][i]);
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}
 
// Function for print matrix
void printMatrix(uint8_t arr[4][4])
{
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

void rotateLeft(uint8_t arr[4][4])
{
    transpose(arr);
    reverseColumns(arr);
}

void rotateRight(uint8_t arr[4][4])
{
    transpose(arr);
    reverseRows(arr);
}
