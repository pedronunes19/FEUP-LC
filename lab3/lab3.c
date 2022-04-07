#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "keyboard.h"
#include "i8042.h"

extern uint16_t scan_code;
extern int scan_code_size;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t bit_no;
  kbd_subscribe_int(&bit_no);

  uint32_t irq_set = BIT(bit_no);
  
  message msg;
  int ipc_status;

  while (scan_code != ESC_BREAK) {}

    int r;
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
      printf("driver_receive failed with: %d", r);
    }

    if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          
          case HARDWARE: {
            if (msg.m_notify.interrupts & irq_set) {
              
              /*
              switch( kbd_int_handler() ) {

                case 1: {
                  kbd_print_scancode(false, scan_code_size, &scan_code);
                  scan_code_size = 0;
                  scan_code = 0;
                  break;
                }

                case 2: {
                  kbd_print_scancode(true, scan_code_size, &scan_code);
                  scan_code_size = 0;
                  scan_code = 0;
                  break;
                }

                default: break;

              }
              */
            }
            break;
          }

          default: break;
        }
    } else {

    }

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
