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
#include "player.h"

#define _WIDTH 640
#define _HEIGHT 512

#define _NROWS 30
#define _NCOLS 20

void test_gl(void)
{
  int start_box_move = 0; 
  int start_ball_move = 0; 
  int box_move = 0; 
  int ball_move = 0; 
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER); 
    player_draw_sprites(start_box_move, start_ball_move); //Draw the starting scene
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    player_draw_sprites(start_box_move, start_ball_move);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer(); //Set up both buffers with the background
   
    for (int x = 0; x <10; x++){
      box_move = start_box_move + (50 * x);
      ball_move = start_ball_move + (50 * x);
      player_draw_sprites(box_move, ball_move); //Redraw the sprites in another location
      gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED); //Draw the background again to restore the trees
      if(sprites_hit() == 1){
        printf("%s\n", "HIT!");
        if (box_move > ball_move){
          ball_hit(); 
        }
        else {
          box_hit();
        }
      }
      gl_swap_buffer();
      player_draw_sprites(box_move, ball_move); //Redraw the sprites in another location
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
    //gl_init(_WIDTH, _HEIGHT, FB_DOUBLEBUFFER);
    //player_init(_WIDTH/2, _HEIGHT/2, 10, 10, _WIDTH, _HEIGHT);
    //timer_delay(5);
    //printf("Time to play!\n");
    //timer_delay(1);
    //gl_draw_rect(100, 100, 10, 10, GL_RED);
// <<<<<<< HEAD
    // controller_init(21);
    // while(1) {
    //     controller_poll();
        
    //     if (controller_get_JOYSTICK_X() == 119) {
    //         player_move(10, 0);
    //     } else if (controller_get_JOYSTICK_X() == 8) {
    //         player_move(-10, 0);
    //     }
    //     controller_get_inputs();
    //     timer_delay(1);
    // }
//      test_gl();
// =======
//     controller_init(21);
//     while(1) {
//         controller_poll(); 
//         if (controller_get_JOYSTICK_X() == 119) {
//             player_move(10, 0);
//         } else if (controller_get_JOYSTICK_X() == 8) {
//             player_move(-10, 0);
//         }
//         timer_delay_ms(20);
   // }
>>>>>>> d22a397453a11a488955691f016172cb062d712d
     //test_gl();
// >>>>>>> a3398c7d597fd6987fe8530c55ac0d962f8032ce

    //printf("\n%d\n", gpio_read(20));
    //printf("Game over! Come back soon!\n");
    uart_putchar(EOT);
}
