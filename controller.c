#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "string.h"
#include "printf.h"
#include "uart.h"
#include "ringbuffer.h"
#include "controller.h"

static unsigned int IN;
static unsigned int OUT;

/*
void send_bit(int bit) {
    int val = 0;
    if (bit) {
        gpio_write(OUT, 0);
        gpio_write(OUT, 1);
        timer_delay_us(2);
    } else {
        gpio_write(OUT, 0);
        timer_delay_us(2);
        gpio_write(OUT, 1);
    }
}
*/

/*
void send_start_word() {
    // send 0100 0000 0000 0011 0000 0000
    send_bit(0);
    send_bit(1);
    for (int i = 0; i < 12; i++) {
        send_bit(0);
    }
    for (int i = 0; i < 2; i++) {
        send_bit(1);
    }
    for (int i = 0; i < 6; i++) {
        send_bit(0);
    }
    send_bit(1);
    send_bit(0);
    // Terminate the bit stream with a 1
    send_bit(1);
}*/

void controller_init(unsigned int out_gpio, unsigned int in_gpio) {
    OUT = out_gpio;
    IN = in_gpio;
    gpio_set_output(OUT);
    gpio_set_input(IN);
    //printf("Entering asm");
    controller_start_asm();
    printf("\n%d\n", gpio_read(20));
}

