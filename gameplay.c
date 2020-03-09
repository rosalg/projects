#include "assert.h"
#include "console.h"
#include "fb.h"
#include "gl_kyl.h"
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
  int start_box_move = 0; 
  int start_ball_move = 0; 
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER);
    gl_draw_sprites(start_box_move, start_ball_move);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    gl_draw_sprites(start_box_move, start_ball_move);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer(); //Set up both buffers with the background
    for (int x = 0; x <10; x++){
      gl_draw_sprites(start_box_move + (50 * x), start_ball_move + (50 * x)); //Redraw the sprites in another location
      gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED); //Draw the background again to restore the trees
      gl_swap_buffer();
      gl_draw_sprites(start_box_move + (50 * x) * x, start_ball_move + (50 * x)); //Redraw the sprites in another location
      gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED); //Draw the background again to restore the trees
      gl_swap_buffer();
      timer_delay(.5);
    }

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
    timer_delay(1);
    controller_init(21, 20);
     //test_gl();

    printf("\n%d\n", gpio_read(20));
    printf("Game over! Come back soon!\n");
    uart_putchar(EOT);
}
