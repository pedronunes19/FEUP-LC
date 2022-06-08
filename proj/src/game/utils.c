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

bool is_alpha(char character) {
    if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        return true;

    return false;
}
