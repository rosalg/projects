#ifndef CONTROLLER_H
#define CONTROLLER_H

// ENUMERATION: Easy reference from byte array in controller.c
// to bit containing information about the given button
typedef enum {
    // Empty bit
    // Empty bit
    // Empty bit
    CONTROLLER_START = 3,
    CONTROLLER_Y = 4,
    CONTROLLER_X = 5,
    CONTROLLER_B = 6,
    CONTROLLER_A = 7,
    // Empty bit
    CONTROLLER_L = 9,
    CONTROLLER_R = 10,
    CONTROLLER_Z = 11,
    CONTROLLER_D_UP = 12,
    CONTROLLER_D_DOWN = 13,
    CONTROLLER_D_RIGHT = 14,
    CONTROLLER_D_LEFT = 15,
    // Joystick X values
    //
    // Bits 16-23 tell the extent of the X value for the JOYSTICK.
    CONTROLLER_JOYSTICK_X_SB = 16,
    // Joystick Y values
    //
    // Bits 24-31 tell the extent of the Y value for the JOYSTICK.
    CONTROLLER_JOYSTICK_Y_SB = 24,
    // C-Stick X Values
    //
    // Bits 32-39 tell the extent of the X value for the C-Stick
    CONTROLLER_CSTICK_X_SB = 32,
    // C-Stick Y Values
    //
    // Bits 40-47 tell C-Stick Y Value
    CONTROLLER_CSTICK_Y_SB = 40,
    // Left Trigger Press
    //
    // Bits 48-55 tell Left Trigger Press Value (how deeply it is pressed)
    CONTROLLER_LEFT_TRIGGER_SB = 48,
    // Right Trigger Press
    //
    // Bits 56-63 tell Right Trigger Press (how deeply it is pressed)
    CONTROLLER_RIGHT_TRIGGER_SB = 56,
} controller_button_t;

// Initializes pin data_p1 and pin data_p2 as I/O pins on Raspberry Pi.
//
// PARAMETERS
// data_p1: pin on the Raspberry Pi from which information from controller 1 will be sent and recieved.
// data_p2: pin on the Raspberry Pi from which information from controller 2 will be sent and recieved.
void controller_init(unsigned int data_p1, unsigned int data_p2);

// Assmebly declaration that sends on information along pins data_p1 and data_p2. Assembly is used for precise
// timing
void controller_asm_write(void); 

/* 
 * Reads the 64 bit return message from the controller that holds information about each button and joystick.
 *
 * See controller_button_t to see what each bit represents.
 *
 * PARAMETERS
 * controller - Which controller you are reading
 */
void controller_read(int controller);

/*
 * Larger helpful function that writes the message that causes the gamecube remote to send button data,
 * then reads that information.
 *
 * PARAMETERS
 * controller - Which controller you are polling.
 */
void controller_poll(int controller);

/*
 * Debugging function that writes what buttons are being pushed to the console, specifically writing
 * 0 and 1s from binary buttons and 0-255 from Joystick, CStick, and L/R trigger values.
 */
void controller_get_inputs(void);

/*
 * The following functions are all getter functions so that other modules can access the controller
 * information.
 *
 * PARAMTERS
 * controller - The player number's controller you are getting information from (1 or 2)
 */

int controller_get_A(int controller);

int controller_get_B(int controller);

int controller_get_X(int controller);

int controller_get_Y(int controller);

int controller_get_START(int controller);

int controller_get_L(int controller);

int controller_get_R(int controller);

int controller_get_Z(int controller);

int controller_get_D_UP(int controller);

int controller_get_D_DOWN(int controller);

int controller_get_D_LEFT(int controller);

int controller_get_D_RIGHT(int controller);

int controller_get_LEFT_TRIGGER(int controller);

int controller_get_RIGHT_TRIGGER(int controller);

int controller_get_JOYSTICK_X(int controller);

int controller_get_JOYSTICK_Y(int controller);

int controller_get_CSTICK_X(int controller);

int controller_get_CSTICK_Y(int controller);

#endif
