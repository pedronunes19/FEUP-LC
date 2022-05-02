#include "defines.h"
#include <stdint.h>
#include <lcom/lcf.h>

int (read_mode)(vbe_mode_info_t* buffer, uint16_t mode);
int (change_mode)(uint16_t mode);
