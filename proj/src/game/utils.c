#include "utils.h"

/* Was used with gravity(), might be useful
int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
*/

void reverseColumns(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < C; i++){
        for (unsigned j = 0, k = C - 1; j < k; j++, k--){
            //swap(arr[j][i], arr[k][i]);
            uint8_t temp = arr[j][i];
            arr[j][i] = arr[k][i];
            arr[k][i] = temp;
        } 
    }
}

void reverseRows(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < R; i++){
        for (unsigned j = 0, k = R - 1; j < k; j++, k--){
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[i][k];
            arr[i][k] = temp;
        } 
    }
}

// Function for do transpose of matrix
void transpose(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < R; i++){
        for (unsigned j = i; j < C; j++){
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
    for (unsigned i = 0; i < R; i++) {
        for (unsigned j = 0; j < C; j++)
            printf("%d ", arr[j][i]);
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

bool is_alpha(char character) {
    if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        return true;

    return false;
}
