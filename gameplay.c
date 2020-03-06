#include "assert.h"
#include "console.h"
#include "fb.h"
#include "gl.h"
#include "printf.h"
#include "strings.h"
#include "timer.h"
#include "uart.h"
#include "gpio.h"
#include "gpioextra.h"
#include "controller.h"

#define _WIDTH 640
#define _HEIGHT 512

#define _NROWS 30
#define _NCOLS 20

void test_gl(void)
{
    // Double buffer mode, make sure you test single buffer too!
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER);


    // Black derp face with rectangles
    gl_draw_rect(_WIDTH/2 - 100, _HEIGHT/2 - 100, 10, 10, GL_AMBER);
    gl_draw_rect(_WIDTH/2 + 100, _HEIGHT/2 -  100, 10, 10, GL_AMBER);
    gl_draw_rect(_WIDTH/2 - 100, _HEIGHT/2, 210, 10, GL_AMBER);
    



    // Single amber character
    gl_draw_char(60, 10, 'A', GL_AMBER);

    //Test clipping
    gl_draw_char(-5, 10, 'B', GL_AMBER);

    //Test bad character
    gl_draw_char(-5, 10, '\b', GL_AMBER);

    gl_draw_string(50, 100, "The rain in spain stays mainly in the plane. But typhoons on the moon are coming for us soon. ", GL_RED);




gl_swap_buffer();

    timer_delay(3);
    // Show buffer with drawn contents

}



/* TODO: Add tests to test your graphics library and console.
   For the graphics library, test both single & double
   buffering and confirm all drawing is clipeed to bounds
   of framebuffer
   For the console, make sure to test wrap-around and scrolling.
   Be sure to test each module separately as well as in combination
   with others.
*/

void main(void)
{
    uart_init();
    timer_init();
    printf("Time to play!\n");
    timer_delay(2);
    controller_init(21);
     //test_gl();
    gpio_set_input(21);



    printf("Game over! Come back soon!\n");
    uart_putchar(EOT);
}
