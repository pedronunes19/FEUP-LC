#include <stdint.h>

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t color;
    uint8_t** matrix; 
} piece_t;