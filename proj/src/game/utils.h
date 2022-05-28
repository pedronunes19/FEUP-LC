#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void reverseColumns(uint8_t **arr, unsigned R, unsigned C)
{
    for (int i = 0; i < C; i++){
        for (int j = 0, k = C - 1; j < k; j++, k--){
            //swap(arr[j][i], arr[k][i]);
            uint8_t temp = arr[j][i];
            arr[j][i] = arr[k][i];
            arr[k][i] = temp;
        } 
    }
}

void reverseRows(uint8_t **arr, unsigned R, unsigned C)
{
    for (int i = 0; i < R; i++){
        for (int j = 0, k = R - 1; j < k; j++, k--){
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[i][j];
            arr[i][j] = temp;
        } 
    }
}
 
// Function for do transpose of matrix
void transpose(uint8_t **arr, unsigned R, unsigned C)
{
    for (int i = 0; i < R; i++){
        for (int j = i; j < C; j++){
            //swap(arr[i][j], arr[j][i]);
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}
 
// Function for print matrix
void printMatrix(uint8_t **arr, unsigned R, unsigned C)
{
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

void rotateLeft(uint8_t **arr, unsigned R, unsigned C)
{
    transpose(arr, R, C);
    reverseColumns(arr, R, C);
}

void rotateRight(uint8_t **arr, unsigned R, unsigned C)
{
    transpose(arr, R, C);
    reverseRows(arr, R, C);
}

