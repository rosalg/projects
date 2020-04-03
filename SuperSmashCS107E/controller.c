#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "string.h"
#include "printf.h"
#include "uart.h"
#include "ringbuffer.h"
#include "controller.h"

// Static variable to indicate which data pins the user is using on the Raspberry Pi
static unsigned int DATA_1;
static unsigned int DATA_2;

// Static variable to indicate byte by byte information for each gamecube controller
static unsigned int bytes_1[64];
static unsigned int bytes_2[64];

void controller_write() {
    gpio_set_output(DATA_1);
    gpio_set_output(DATA_2);
    // Check asm file to see exact implementation
    //
    // Write to controller the start command
    controller_asm_write();
    
    
    gpio_set_input(DATA_1);
    gpio_set_input(DATA_2);
 
}

void controller_read(int controller) {
    int low_time = 0;
    int cycle = 0;
    unsigned int (*bytes)[64] = &bytes_1;
    if (controller != 1) bytes = &bytes_2; 
    while (cycle < 64) {
        low_time = 0;
        while(gpio_read(controller + 19) == 0) {
            low_time++;
            if (low_time > 10) break;
        }
        if (low_time > 10) break;
        if (low_time >= 2) {
            (*bytes)[cycle] = 0;
        } else {
            (*bytes)[cycle] = 1;
        }
        int high_time = 0;
        while(gpio_read(controller + 19)) {
            high_time++;
            if (high_time > 10) break;
        }
        if (high_time > 10) break;
        cycle++;
    }
}

void controller_poll(int controller) {
    int time = timer_get_ticks();
    controller_write();
    while (gpio_read(controller + 19) && timer_get_ticks() < time + 300);
    controller_read(controller);
}

int controller_get_A(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_A];
    }
    return bytes_2[CONTROLLER_A];
}

int controller_get_B(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_B];
    }
    return bytes_2[CONTROLLER_B];
}

int controller_get_X(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_X];
    }
    return bytes_2[CONTROLLER_X];
}

int controller_get_Y(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_Y];
    }
    return bytes_2[CONTROLLER_Y];
}

int controller_get_START(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_START];
    }
    return bytes_2[CONTROLLER_START];
}

int controller_get_L(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_L];
    }
    return bytes_2[CONTROLLER_L];
}

int controller_get_R(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_R];
    }
    return bytes_2[CONTROLLER_R];
}

int controller_get_Z(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_Z];
    }
    return bytes_2[CONTROLLER_Z];
}

int controller_get_D_UP(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_D_UP];
    }
    return bytes_2[CONTROLLER_D_UP];
}

int controller_get_D_RIGHT(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_D_RIGHT];
    }
    return bytes_2[CONTROLLER_D_RIGHT];
}

int controller_get_D_DOWN(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_D_DOWN];
    }
    return bytes_2[CONTROLLER_D_DOWN];
}

int controller_get_D_LEFT(int controller){
    if (controller == 1) {
        return bytes_1[CONTROLLER_D_LEFT];
    }
    return bytes_2[CONTROLLER_D_LEFT];
}

int controller_get_JOYSTICK_X(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_JOYSTICK_X_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_JOYSTICK_X_SB + i] << i);
        }
    }
    return val;
}

int controller_get_JOYSTICK_Y(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_JOYSTICK_Y_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_JOYSTICK_Y_SB + i] << i);
        }
    }
    return val;
}

int controller_get_CSTICK_X(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_CSTICK_X_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_CSTICK_X_SB + i] << i);
        }
    }
    return val;
}

int controller_get_CSTICK_Y(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_CSTICK_Y_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_CSTICK_Y_SB + i] << i);
        }
    }
    return val;
}

int controller_get_LEFT_TRIGGER(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_LEFT_TRIGGER_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_LEFT_TRIGGER_SB + i] << i);
        }
    }
    return val;
}

int controller_get_RIGHT_TRIGGER(int controller){
    int val = 0;
    if (controller == 1) {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_1[CONTROLLER_RIGHT_TRIGGER_SB + i] << i);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            val += (bytes_2[CONTROLLER_RIGHT_TRIGGER_SB + i] << i);
        }
    }
    return val;
}

void controller_get_inputs(void) {
    printf("\n\n\nCONTROLLER 1\n\n\n");
    printf("Start Value: %d\n", bytes_1[CONTROLLER_START]);
    printf("Y Value: %d\n", bytes_1[CONTROLLER_Y]);
    printf("X Value: %d\n", bytes_1[CONTROLLER_X]);
    printf("B Value: %d\n", bytes_1[CONTROLLER_B]);
    printf("A Value: %d\n", controller_get_A(1));
    printf("L Trigger: %d\n", bytes_1[CONTROLLER_L]);
    printf("R Trigger: %d\n", bytes_1[CONTROLLER_R]);
    printf("Z Value: %d\n", bytes_1[CONTROLLER_Z]);
    printf("D-Pad Up: %d\n", bytes_1[CONTROLLER_D_UP]);
    printf("D-Pad Down: %d\n", bytes_1[CONTROLLER_D_DOWN]);
    printf("D-Pad Right: %d\n", bytes_1[CONTROLLER_D_RIGHT]);
    printf("D-Pad Left: %d\n", bytes_1[CONTROLLER_D_LEFT]);
    printf("Joystick X Value: %d\n", controller_get_JOYSTICK_X(1));
    printf("Joystick Y Value: %d\n", controller_get_JOYSTICK_Y(1));
    printf("C-Stick X Value: %d\n", controller_get_CSTICK_X(1));
    printf("C-Stick Y Value: %d\n", controller_get_CSTICK_Y(1));
    printf("L Trigger Value: %d\n", controller_get_LEFT_TRIGGER(1));
    printf("R Trigger Value: %d\n", controller_get_RIGHT_TRIGGER(1));

    
    printf("\n\n\nCONTROLLER 2\n\n\n");
    printf("Start Value: %d\n", bytes_2[CONTROLLER_START]);
    printf("Y Value: %d\n", bytes_2[CONTROLLER_Y]);
    printf("X Value: %d\n", bytes_2[CONTROLLER_X]);
    printf("B Value: %d\n", bytes_2[CONTROLLER_B]);
    printf("A Value: %d\n", bytes_2[CONTROLLER_A]);
    printf("L Trigger: %d\n", bytes_2[CONTROLLER_L]);
    printf("R Trigger: %d\n", bytes_2[CONTROLLER_R]);
    printf("Z Value: %d\n", bytes_2[CONTROLLER_Z]);
    printf("D-Pad Up: %d\n", bytes_2[CONTROLLER_D_UP]);
    printf("D-Pad Down: %d\n", bytes_2[CONTROLLER_D_DOWN]);
    printf("D-Pad Right: %d\n", bytes_2[CONTROLLER_D_RIGHT]);
    printf("D-Pad Left: %d\n", bytes_2[CONTROLLER_D_LEFT]);
    printf("Joystick X Value: %d\n", controller_get_JOYSTICK_X(2));
    printf("Joystick Y Value: %d\n", controller_get_JOYSTICK_Y(2));
    printf("C-Stick X Value: %d\n", controller_get_CSTICK_X(2));
    printf("C-Stick Y Value: %d\n", controller_get_CSTICK_Y(2));
    printf("L Trigger Value: %d\n", controller_get_LEFT_TRIGGER(2));
    printf("R Trigger Value: %d\n", controller_get_RIGHT_TRIGGER(2));
}

void controller_init(unsigned int data_p1, unsigned int data_p2) {
    DATA_1 = data_p1;
    DATA_2 = data_p2;
    for (int i = 0; i < 64; i++) {
        bytes_1[i] = 0;
        bytes_2[i] = 0;
    }
}

