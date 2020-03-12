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
        while(gpio_read(DATA) == 0) {
            low_time++;
            if (low_time > 10) break;
        }
        if (low_time > 10) break;
        if (low_time >= 2) {
            bytes[cycle] = 0;
        } else {
            bytes[cycle] = 1;
        }
        int high_time = 0;
        while(gpio_read(DATA)) {
            high_time++;
            if (high_time > 10) break;
        }
        if (high_time > 10) break;
        cycle++;
    }

}

void controller_poll() {
    controller_write();
    while (gpio_read(DATA));
    controller_read();
}

int controller_get_A(void){
    return bytes[CONTROLLER_A];
}

int controller_get_B(void){
    return bytes[CONTROLLER_B];
}

int controller_get_X(void){
    return bytes[CONTROLLER_X];
}

int controller_get_Y(void){
    return bytes[CONTROLLER_Y];
}

int controller_get_START(void){
    return bytes[CONTROLLER_START];
}

int controller_get_L(void){
    return bytes[CONTROLLER_R];
}

int controller_get_R(void){
    return bytes[CONTROLLER_L];
}

int controller_get_Z(void) {
    return bytes[CONTROLLER_Z];
}

int controller_get_D_UP(void){
    return bytes[CONTROLLER_D_UP];
}

int controller_get_D_RIGHT(void){
    return bytes[CONTROLLER_D_RIGHT];
}

int controller_get_D_LEFT(void){
    return bytes[CONTROLLER_D_LEFT];
}

int controller_get_D_DOWN(void){
    return bytes[CONTROLLER_D_DOWN];
}

int controller_get_JOYSTICK_X(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_JOYSTICK_X_SB + i] << i);
    }
    return val;
}

int controller_get_JOYSTICK_Y(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_JOYSTICK_Y_SB + i] << i);
    }
    return val;
}

int controller_get_CSTICK_X(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_CSTICK_X_SB + i] << i);
    }
    return val;
}

int controller_get_CSTICK_Y(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_CSTICK_Y_SB + i] << i);
    }
    return val;
}

int controller_get_LEFT_TRIGGER(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_LEFT_TRIGGER_SB + i] << i);
    }
    return val;
}

int controller_get_RIGHT_TRIGGER(void){
    int val = 0;
    for (int i = 7; i >= 0; i--) {
        val += (bytes[CONTROLLER_RIGHT_TRIGGER_SB + i] << i);
    }
    return val;
}

void controller_get_inputs(void) {
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
    printf("Joystick X Value: %d\n", controller_get_JOYSTICK_X());
    printf("Joystick Y Value: %d\n", controller_get_JOYSTICK_Y());
    printf("C-Stick X Value: %d\n", controller_get_CSTICK_X());
    printf("C-Stick Y Value: %d\n", controller_get_CSTICK_Y());
    printf("L Trigger Value: %d\n", controller_get_LEFT_TRIGGER());
    printf("R Trigger Value: %d\n", controller_get_RIGHT_TRIGGER());
}

void controller_init(unsigned int data_gpio) {
    DATA = data_gpio;
    for (int i = 0; i < 64; i++) {
        bytes[i] = 0;
    }
}

