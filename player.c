    #include "controller.h"
    #include "gpio.h"
    #include "timer.h"
    #include "fb.h"
    #include "gl_kyl.h"
    #include "player.h"
    #include "printf.h"

    // static volatile sprite box; 
    // static sprite ball;

    void player_init(sprite* player) {
        player_draw_sprites(player, 0, 0);
        //gl_draw_rect(player->x, player->y, 10, 10, GL_RED);
        gl_swap_buffer();  
        player_draw_sprites(player, 0 ,0);
        gl_swap_buffer();  //Draw the player on both buffers
    }

    void player_move(sprite* player, int x, int y) {
        player->x += x;
        player->y += y;
        update_hit_box(player, x, y);
        player_draw_sprites(player, x, y);
        gl_swap_buffer();
        player_draw_sprites(player, x, y);

    }

    void fireball(sprite* player, sprite* fire){ //Puts fireball at the position of the passed sprite
        int fireball_radius = 10; 
        fire->x = player->hit_x_right + fireball_radius *2;
        fire->y = player->y;
        fire->hit_x_right = fire->x + fireball_radius;
        fire->hit_x_left = fire->x - fireball_radius;
        fire->hit_y_top = fire->y + fireball_radius;
        fire->hit_y_bottom= fire->y - fireball_radius;
        player_draw_sprites(fire, 0, 0);
        gl_swap_buffer();
        player_draw_sprites(fire, 0, 0);


    }



     void update_hit_box(sprite* player, int x, int y){
        player->hit_x_left +=x;
        player->hit_x_right +=x;
        player->hit_y_top += y;
        player->hit_y_bottom += y;
     }

    void player_draw_sprites(sprite* player, int x, int y){ //Draw and move the sprites
        int box_radius = 80;
        int wheel_radius = 15;
        int ball_radius = 50; 
        int eye_radius = 5; 
        int fireball_radius = 10; 

    if (player->hit_x_right <= gl_get_width() && player->hit_x_left >= 0){
        if(player->sprite_num == 1){
        gl_draw_rect(player->x - x, player->y - y, 100, 100, GL_BLACK);
        gl_draw_box(player->x, player->y, box_radius, wheel_radius); //Draw the box
        } 
        else if (player->sprite_num == 0) {  
        gl_draw_rect(player->x - x - ball_radius, player->y - y - ball_radius, (ball_radius * 2) + 5, (ball_radius *2)+ 5, GL_BLACK);
        gl_draw_circle_sprite(player->x, player->y, ball_radius, eye_radius);
        }
        else {
            gl_draw_rect(player->x - x - fireball_radius, player->y - y - fireball_radius, (fireball_radius * 2) + 3, (fireball_radius *2) + 3, GL_BLACK);
            gl_draw_circle(player->x, player->y, fireball_radius, GL_RED);
        }


    
    } else{


        if (player->sprite_num == 1){ //If the fireball is moving outside of bounds, delete it
        printf("%d\n", player->x);
        printf("%d\n", player->y);

       // gl_draw_rect(player->x - x - fireball_radius, player->y - y - fireball_radius, (fireball_radius * 2), (fireball_radius *2), GL_BLACK);
        gl_draw_rect(player->x, player->y, (fireball_radius * 2), (fireball_radius *2), GL_BLACK);


        }
    }

    }

    void gl_draw_circle_sprite(int x, int y, int circle_r, int eye_r){
        gl_draw_circle(x, y, circle_r, GL_YELLOW);
        gl_draw_circle(x - 15, y - 15, eye_r, GL_BLACK);
        gl_draw_circle(x + 15, y - 15, eye_r, GL_BLACK);
    }

    void gl_draw_box(int x, int y, int box_r, int wheel_r){
        gl_draw_circle(x + wheel_r, y + box_r, wheel_r, GL_WHITE);
        gl_draw_circle(x + (wheel_r*4), y + box_r, wheel_r, GL_WHITE);
        gl_draw_rect(x, y, box_r, box_r, GL_BLUE);
    }

    int sprites_hit(sprite* player1, sprite* player0){
        
    if(player1->hit_y_bottom >= player0->hit_y_top){       
        if (((player0->hit_x_right >= player1->hit_x_right) &&  (player1->hit_x_right >= player0->hit_x_left))){
            return 1;
         }
        }   
        else {
            return 0;
        }
    }

    // void box_hit(){
    //     box.hit_points -= 10;
    // }
    // void ball_hit(){
    //     ball.hit_points -=10;
    // }
