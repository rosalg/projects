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
    int width = gl_get_width();
    int height = gl_get_height();

    //Set up the background on both buffers
    gl_draw_background(GL_PURPLE);
    gl_swap_buffer(); 
    gl_draw_background(GL_PURPLE);
     gl_swap_buffer();  

    //Set up the box
    sprite box;
    int box_radius = 80;
    int wheel_radius = 15;
    box.sprite_num = 1; 
    box.hit_points = 100; 
    box.x = width/4;
    box.y = height - 200;
    box.hit_x_left = box.x;
    box.hit_x_right = box.x + box_radius;
    box.hit_y_top = box.y;
    box.hit_y_bottom = box.y + box_radius + wheel_radius;
    player_init(&box);

    //Set up the ball
    sprite ball;
    int ball_radius = 50; 
    ball.sprite_num = 0; 
    ball.hit_points = 100;
    ball.x = width - (width/4 + 65);
    ball.y = height - 155; 
    ball.hit_x_left = ball.x - ball_radius;
    ball.hit_x_right = ball.x + ball_radius;
    ball.hit_y_top = ball.y + ball_radius/2;
    ball.hit_y_bottom = ball.y - ball_radius/2;
     player_init(&ball);

//Set up one fireball off the scnree
 int fireball_radius = 10;
    sprite fire;
    fire.sprite_num = 3;
    fire.x = gl_get_height() + fireball_radius;
    fire.y = gl_get_width() + fireball_radius;
    fire.hit_x_right = fire.x + fireball_radius;
    fire.hit_x_left = fire.x - fireball_radius;
    fire.hit_y_top = fire.y + fireball_radius;
    fire.hit_y_bottom= fire.y - fireball_radius;
    player_init(&fire);
    fireball(&ball, &fire);

     for(int i = 0; i < 10; i++){
      player_move(&box, 10*i, 0);
      player_move(&ball, (-10*i), 0);
      player_move(&fire, (-10*i), 0);
      timer_delay_ms(100);
     }
}

void test_con(void) {
    sprite player;
    player.x = 50;
    player.y = 50;
    player.hit_x_left = 0;
    player.hit_x_right = 0;
    player.hit_y_top = 0;
    player.hit_y_bottom = 0;
    player.hit_points = 100;
    gl_init(_WIDTH, _HEIGHT, FB_DOUBLEBUFFER);
    player_init(&player);
    //printf("Time to play!\n");
    //gl_draw_rect(100, 100, 10, 10, GL_RED);
    controller_init(21);
    while(1) {
        controller_poll(); 
        if (controller_get_JOYSTICK_X() == 119) {
            player_move(&player, 10, 0);
        } 
        if (controller_get_JOYSTICK_X() == 8) {
            player_move(&player, -10, 0);
        }
        if (controller_get_JOYSTICK_Y() == 119) {
            player_move(&player, 0, -10);
        }
        if (controller_get_JOYSTICK_Y() == 8) {
            player_move(&player, 0, 10);
        }
        timer_delay_ms(10);
    }
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
     gl_init(_WIDTH, _HEIGHT, FB_DOUBLEBUFFER);

    // printf("Time to play!\n");
    // //timer_delay(1);
  //  test_con();
    test_gl();
    // printf("Game over! Come back soon!\n");
     uart_putchar(EOT);
}
