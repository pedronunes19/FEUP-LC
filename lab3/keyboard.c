#include "keyboard.h"

static int hook_id = 0;
uint16_t scan_code = 0;
int scan_code_size = 0;

int (kbd_subscribe_int) (uint8_t* bit_no) {

    *bit_no = hook_id;
    return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);

}

int (kbd_unsubscribe_int) () {

    return sys_irqrmpolicy(&hook_id);

}

int (kbd_int_handler) () {

    uint8_t output;
    util_sys_inb(OUT_BUF, &output);

    uint8_t st;
    util_sys_inb(STATUS_REG, &st);

    if (check_status(st) == OK) {
        
        scan_code |= output;
        scan_code_size++;

        if (output == TWO_BYTE_SC) {
            scan_code = scan_code << 8;
            return 0;
        }

        if (output & IS_BREAK) return 1; 
        else return 2;

    }

    return -1;
}

int (check_status) (uint8_t st) {

    if (st & PARITY) {
        return PARITY_ERR;
    }

    if (st & TIME_OUT) {
        return TIME_OUT_ERR;
    }

    /* might cause issues with the lab, since we won't be writing to the input buffer
    if (st & IBF) {
        return IBF_FULL;
    }
    */

    return OK;
}
