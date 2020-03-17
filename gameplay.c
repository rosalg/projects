#include <stdarg.h>
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
#include "gameplay.h"

#define _WIDTH 640
#define _HEIGHT 512

#define _NROWS 30
#define _NCOLS 20

void update(player curr_player);

static player p1;
static player p2;
//static player p3; 
//static player p4;
static int player_count;
static int GROUND = 0;

void gameplay_init(int player_num) {
    int width = gl_get_width();
    int height = gl_get_height();
    gl_draw_background(GL_PURPLE);
    gl_swap_buffer();
    gl_draw_background(GL_PURPLE);

    player_count = player_num;

    //Set up the box
    static sprite p1_box;
    int box_radius = 80;
    int wheel_radius = 15;
    p1_box.sprite_num = BOX; 
    p1_box.hit_points = 100; 
    p1_box.x = width/4;
    p1_box.y = height - 200;
    p1_box.is_grounded = 1;
    p1_box.is_jumping = 0;
    p1_box.is_firing = 0;
    p1_box.direction = RIGHT;
    p1_box.vel_x = 0;
    p1_box.vel_y = 0;
    p1_box.hit_x_left = p1_box.x;
    p1_box.hit_x_right = p1_box.x + box_radius;
    p1_box.hit_y_top = p1_box.y;
    p1_box.hit_y_bottom = p1_box.y + box_radius + wheel_radius;
    p1.sprite = &p1_box;
    p1.con_num = 1;
    GROUND = p1_box.hit_y_bottom;
    
    //Set up the box2
    static sprite p2_box;
    p2_box.sprite_num = BOX; 
    p2_box.hit_points = 100; 
    p2_box.x = 2*width/4;
    p2_box.y = height - 200;
    p2_box.is_grounded = 1;
    p2_box.is_jumping = 0;
    p2_box.direction = LEFT;
    p2_box.vel_x = 0;
    p2_box.vel_y = 0;
    p2_box.hit_x_left = p2_box.x;
    p2_box.hit_x_right = p2_box.x + box_radius;
    p2_box.hit_y_top = p2_box.y;
    p2_box.hit_y_bottom = p2_box.y + box_radius + wheel_radius;
    p2.sprite = &p2_box;
    p2.con_num = 2;

    

    player_init(player_count, &p1_box, &p2_box);
}

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
    //player_init(&box);
/*
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
    player_fireball(&ball, &fire);
*/
     for(int i = 0; i < 10; i++){
      //player_move(&box, 10*i, 0);
      //player_move(&ball, (-10*i), 0);
      //player_move(&fire, (-10*i), 0);
      timer_delay_ms(100);
     }
}

void test_con(void) {
    gameplay_init(1);
    //printf("Time to play!\n");
    //gl_draw_rect(100, 100, 10, 10, GL_RED);
    controller_init(21, 20);
    while(1) {
        update(p1);
        //update(p2);
        player_move();
    }
}

void update(player p) {
    controller_poll(p.con_num);
    if (controller_get_JOYSTICK_X(p.con_num) == 119) {
        p.sprite->vel_x = 10;
        p.sprite->direction = RIGHT;
    } 
    if (controller_get_JOYSTICK_X(p.con_num) == 8) {
        p.sprite->vel_x = -10;
        p.sprite->direction = LEFT;
    }
    if (controller_get_JOYSTICK_X(p.con_num) == 254 || controller_get_JOYSTICK_X(p.con_num) == 1) {
        p.sprite->vel_x = 0;
    }
    
    if (controller_get_A(p.con_num) && p.sprite->is_firing == 0) {
        static sprite fire;
        fire.sprite_num = 3;
        fire.owner = p.sprite;
        player_projectile(p.sprite, &fire);
    }
    if (p.sprite->is_grounded == 0 && p.sprite->hit_y_bottom >= GROUND) {
        p.sprite->is_grounded = 1;
        p.sprite->vel_y = 0;
    } else if (p.sprite->is_grounded == 0 && p.sprite->is_jumping == 0 && p.sprite->hit_y_bottom < GROUND) {
        p.sprite->vel_y = 10;
    } else if (p.sprite->is_jumping > 0) {
        p.sprite->is_jumping--;
    }
    if (controller_get_X(p.con_num) && p.sprite->is_grounded == 1) {
        player_jump(p.sprite);
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
    test_con();
    //test_gl();
    // printf("Game over! Come back soon!\n");
     uart_putchar(EOT);
}
