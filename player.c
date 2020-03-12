#include "controller.h"
#include "gpio.h"
#include "timer.h"
//#include "gl.h"
#include "fb.h"
#include "gl_kyl.h"

static int x_pos = 0;
static int y_pos = 0;
static int width = 0;
static int height = 0;
static volatile sprite box; 
static sprite ball;

//!!! I COMMENTED OUT GL.H!!!!!!!


// void player_init(int x, int y, int w, int h, int c_w, int c_h) {
//     //gl_init(c_w, c_h, GL_DOUBLEBUFFER);
//     x_pos = x;
//     y_pos = y;
//     width = w;
//     height= h;
//     //gl_draw_rect(x, y, w, h, GL_RED);
//     //gl_swap_buffer();
// }

// void player_move(int x, int y) {
//     gl_clear(GL_BLACK);
//     x_pos += x;
//     y_pos += y;
//     gl_draw_rect(x_pos, y_pos, width, height, GL_RED);
//     gl_swap_buffer();
// }

void player_draw_sprites(int box_move, int ball_move){ //Draw and move the sprites
    int width = gl_get_width();
    int height = gl_get_height();
    gl_draw_rect(0, height- 200, width, 100, GL_BLACK); //Cover any previous sprites with a black rectangle
    //Set up and draw the box
    int box_radius = 80;
    int wheel_radius = 15;
    box.hit_points = 100; 
    if((width/4 + box_move) > 0 && (width/4 + box_move) < (width -box_radius)){ //If the movement doesn't move the box out of bounds
    box.x = width/4 + box_move; //Starting position = width/4, as player hits buttons the sprite moves
    } 
    box.y = height - 200;
    box.hit_x_left = box.x;
    box.hit_x_right = box.x + box_radius;
    box.hit_y_top = box.y;
    box.hit_y_bottom = box.y + box_radius + wheel_radius;
    gl_draw_box(box.x, box.y, box_radius, wheel_radius); //Draw the box
    
    //set up and draw the ball 
    int ball_radius = 50; 
    int eye_radius = 5; 
    ball.hit_points = 100;
    if((width - (width/4 + 65) + ball_move) > 0 && (width - (width/4 + 65) + ball_move) < (width - ball_radius)){ //If the movement doesn't move the ball out of bounds, then move the ball
    ball.x = width - (width/4 + 65) + ball_move; //As player hits buttons the sprite moves by ball_move amount
   }
    ball.y = height - 150; 
    ball.hit_x_left = ball.x - ball_radius;
    ball.hit_x_right = ball.x + ball_radius;
    ball.hit_y_top = ball.y + ball_radius/2;
    ball.hit_y_bottom = ball.y - ball_radius/2;
    gl_draw_circle_sprite(ball.x, ball.y, ball_radius, eye_radius); //Draw the ball
}
void gl_draw_circle_sprite(int x, int y, int circle_r, int eye_r){
    gl_draw_circle(x, y, circle_r, GL_ORANGE);
    gl_draw_circle(x - 15, y - 15, eye_r, GL_BLACK);
    gl_draw_circle(x + 15, y - 15, eye_r, GL_BLACK);
}

void gl_draw_box(int x, int y, int box_r, int wheel_r){
    gl_draw_circle(x + wheel_r, y + box_r, wheel_r, GL_WHITE);
    gl_draw_circle(x + (wheel_r*4), y + box_r, wheel_r, GL_WHITE);
    gl_draw_rect(x, y, box_r, box_r, GL_BLUE);
}

int sprites_hit(){
    
   
    if(box.hit_y_bottom >= ball.hit_y_top){       
           printf("%s\n", "move");
           printf("%d\n", ball.hit_x_right);
            printf("%d\n", box.hit_x_right);
            printf("%d\n",  ball.hit_x_left);

        if ((ball.hit_x_right >= box.hit_x_right >= ball.hit_x_left) || (ball.hit_x_right >= box.hit_x_left >= ball.hit_x_left)){
            printf("%d\n", ball.hit_y_top);
            printf("%d\n", box.hit_y_bottom);
            return 1;
        }
}
else {
    return 0;
}
}

void box_hit(){
    box.hit_points -= 10;
}
void ball_hit(){
    ball.hit_points -=10;
}
