#include "keyboard.h"

int (keyboard_subscribe_int) (uint8_t* bit_no) {

    *bit_no = hook_id;
    return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);

}

int (keyboard_unsubscribe_int) () {

    return sys_irqrmpolicy(&hook_id);

}

int (check_status) (uint8_t st) {

    if (st | PARITY) {
        return PARITY_ERR;
    }

    if (st | TIME_OUT) {
        return TIME_OUT_ERR;
    }

    if (st | IBF) {
        return IBF_FULL;
    }

    return OK;
}