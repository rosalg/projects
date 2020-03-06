#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "string.h"
#include "printf.h"
#include "uart.h"
#include "ringbuffer.h"
#include "controller.h"

#define LONG_DELAY 3
#define SHORT_DELAY 1

static unsigned int DATA;

void send_bit(int bit) {
    if (bit) {
        gpio_write(DATA, 1);
        timer_delay_us(LONG_DELAY);
        gpio_write(DATA, 0);
        timer_delay_us(SHORT_DELAY);
    } else {
        gpio_write(DATA, 0);
        timer_delay_us(LONG_DELAY);
        gpio_write(DATA, 1);
        timer_delay_us(SHORT_DELAY);
    }
}

void send_start_word() {
    // send 0100 0000 0000 0011 0000 0010
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
    gpio_write(DATA, 1);
}

void controller_init(unsigned int data_gpio) {
    DATA = data_gpio;
    gpio_set_output(DATA);
    send_start_word();
}

