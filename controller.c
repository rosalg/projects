#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "string.h"
#include "printf.h"
#include "uart.h"
#include "ringbuffer.h"
#include "controller.h"

static unsigned int DATA;
static unsigned int bytes[64];

void controller_write() {
    gpio_set_output(DATA);
    controller_asm_write();
    gpio_set_input(DATA);
 
}

void controller_read() {
    int cycle = 0;
    int low_time = 0;
    while (cycle < 64) {
        low_time = 0;
        while (gpio_read(DATA) == 0) low_time++;
        if (low_time >= 2) {
            bytes[cycle] = 0;
        } else {
            bytes[cycle] = 1;
        }
        while (gpio_read(DATA) == 1);
        cycle++;
    }

}

void controller_get_inputs() {
    printf("\n\n\nStart Value: %d\n", bytes[CONTROLLER_START]);
    printf("Y Value: %d\n", bytes[CONTROLLER_Y]);
    printf("X Value: %d\n", bytes[CONTROLLER_X]);
    printf("B Value: %d\n", bytes[CONTROLLER_B]);
    printf("A Value: %d\n", bytes[CONTROLLER_A]);
    printf("L Trigger: %d\n", bytes[CONTROLLER_L]);
    printf("R Trigger: %d\n", bytes[CONTROLLER_R]);
    printf("Z Value: %d\n", bytes[CONTROLLER_Z]);
    printf("D-Pad Up: %d\n", bytes[CONTROLLER_D_UP]);
    printf("D-Pad Down: %d\n", bytes[CONTROLLER_D_DOWN]);
    printf("D-Pad Right: %d\n", bytes[CONTROLLER_D_RIGHT]);
    printf("D-Pad Left: %d\n", bytes[CONTROLLER_D_LEFT]);
    
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_JOYSTICK_X_SB + i] << i);
    }
    printf("Joystick X Value: %d\n", val);
    
    val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_JOYSTICK_Y_SB + i] << i);
    }
    printf("Joystick Y Value: %d\n", val);
    
    val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_CSTICK_X_SB + i] << i);
    }
    printf("C-Stick X Value: %d\n", val);
    
    val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_CSTICK_Y_SB + i] << i);
    }
    printf("C-Stick Y Value: %d\n", val);

    val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_LEFT_TRIGGER_SB + i] << i);
    }
    printf("L Trigger Value: %d\n", val);

    val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_RIGHT_TRIGGER_SB + i] << i);
    }
    printf("R Trigger Value: %d\n", val);

 
}

void controller_init(unsigned int data_gpio) {
    DATA = data_gpio;
    while (1) {
        controller_write();
        while (gpio_read(DATA));
        controller_read();
        controller_get_inputs();
    }
}

