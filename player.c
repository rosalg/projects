#include "controller.h"
#include "gpio.h"
#include "timer.h"
#include "fb.h"
#include "gl_kyl.h"
#include "player.h"
#include "printf.h"

static volatile sprite box; 
static sprite ball;
<<<<<<< HEAD

void player_init(sprite* player) {
    gl_draw_rect(player->x, player->y, 10, 10, GL_RED);
    gl_swap_buffer();    
}

void player_move(sprite* player, int x, int y) {
    player->x += x;
    player->y += y;
    printf("\nplayer.x: %d\n", player->x);
    gl_draw_rect(player->x, player->y, 10, 10, GL_RED);
    gl_swap_buffer();
    gl_draw_rect(player->x - x, player->y - y, 10, 10, GL_BLACK);
    gl_draw_rect(player->x, player->y, 10, 10, GL_RED);
}

 void move_ball(int x){
    int movement = 0;
    if (x == 1){
       movement = move_forward;
    }
    else {
       movement = move_back;
    }
    player_draw_sprites(0, movement);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    player_draw_sprites(0, movement);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    timer_delay(.1);
 }

  void move_box(int x){
      int movement = 0;
    if (x == 1){
       movement = move_forward;
    }
    else {
       movement = move_back;
    }
    player_draw_sprites(movement, 0);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    player_draw_sprites(movement, 0);
    gl_draw_background(GL_AMBER, GL_PURPLE, GL_RED);
    gl_swap_buffer();
    timer_delay(.1);
 }
 

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
           // printf("%s\n", "move");
           // printf("%d\n", ball.hit_x_right);
           //  printf("%d\n", box.hit_x_right);
           //  printf("%d\n",  ball.hit_x_left);
        //|| (ball.hit_x_right >= box.hit_x_left) &&  (ball.hit_x_right <= box.hit_x_left)
        if (((ball.hit_x_right >= box.hit_x_right) &&  (box.hit_x_right >= ball.hit_x_left))){
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
