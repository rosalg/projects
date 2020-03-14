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

void update(void);

static sprite player_1;
static sprite player_2;

void gameplay_init() {
    player_1.x = 50;
    player_1.y = 50;
    player_1.hit_x_left = 0;
    player_1.hit_x_right = 0;
    player_1.hit_y_top = 0;
    player_1.is_jumping = 0;
    player_1.is_grounded = 1;
    player_1.hit_y_bottom = 0;
    player_1.hit_points = 100;
    player_1.vel_x = 0;
    player_1.vel_y = 0;

    player_2.x = 100;
    player_2.y = 100;

    player_2.is_jumping = 0;
    player_2.is_grounded = 0;

    player_2.hit_x_left = 0;
    player_2.hit_x_right = 0;
    player_2.hit_y_top = 0;
    player_2.hit_y_bottom = 0;
    player_2.hit_points = 100;
    player_2.vel_x = 0;
    player_2.vel_y = 0;

   
}

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
   
    while (sprites_hit() == 0){
      move_ball(1);//1 means move forward, 0 means move back;
  //    move_box(1); 
      printf("%s\n", "move");
    } 
  //  gl_swap_buffer();
    timer_delay(3);
    // Show buffer with drawn contents
}

void test_con(void) {
    gl_init(_WIDTH, _HEIGHT, FB_DOUBLEBUFFER);
    player_init(&player_1);
    player_init(&player_2);
    //printf("Time to play!\n");
    //gl_draw_rect(100, 100, 10, 10, GL_RED);
    controller_init(21, 20);
    while(1) {
        //update();
        printf("Polling");
        controller_poll(1);
        timer_delay(1);
        controller_poll(2); 
        controller_get_inputs();
        timer_delay(1);
    }
}

void update() {
    controller_poll(1); 
    if (controller_get_JOYSTICK_X(1) == 119) {
        player_1.vel_x = 10;
    } 
    if (controller_get_JOYSTICK_X(1) == 8) {
        player_1.vel_x = -10;
    }
    if (controller_get_JOYSTICK_X(1) == 255 || controller_get_JOYSTICK_X(1) == 1) {
        player_1.vel_x = 0;
    }
    if (controller_get_X(1) && player_1.is_grounded == 1 && player_1.is_jumping == 0) {
        player_jump(&player_1);
    }
    if (player_1.is_jumping > 0) {
        player_1.vel_y = -10;
    }
    player_move(&player_1, player_1.vel_x, player_1.vel_y);
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
    // gl_init(_WIDTH, _HEIGHT, FB_DOUBLEBUFFER);

    // printf("Time to play!\n");
    // //timer_delay(1);
    test_con();
    //test_gl();
    // printf("Game over! Come back soon!\n");
    // uart_putchar(EOT);
}
