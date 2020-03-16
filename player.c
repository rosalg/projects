#include <stdarg.h>
#include "controller.h"
#include "gpio.h"
#include "timer.h"
#include "fb.h"
#include "gl_kyl.h"
#include "player.h"
#include "printf.h"

    // static volatile sprite box; 
    // static sprite ball;

    static sprite* sprites[4];
    static int player_count = 0;

    void player_init(int n, ...) {
        va_list ap;
        va_start(ap, n);
        player_count = n;
        for (int i = 0; i < player_count; i++) {
            sprite* _sprite = va_arg(ap, sprite*);        
            player_draw_sprites(_sprite);
            sprites[i] = _sprite;
        }
        gl_swap_buffer();
    }
    
    void player_jump(sprite* _sprite) {
        _sprite->is_jumping = 5;
        _sprite->is_grounded = 0;
        _sprite->vel_y = -10;
    }
 /*
    void player_move(sprite* player, int x, int y) {
        player->x += x;
        player->y += y;
        update_hit_box(player);
        player_draw_sprites(player);
        gl_swap_buffer();
        gl_draw_rect(player->x - player->vel_x, player->y - player->vel_y, 100, 100, GL_BLACK);
    }*/

    void player_move(void) {
        for (int i = 0; i < player_count; i++) {
            sprites[i]->x += sprites[i]->vel_x;
            sprites[i]->y += sprites[i]->vel_y;
            update_hit_box(sprites[i]);
            player_draw_sprites(sprites[i]);
        }        
        gl_swap_buffer();
        for (int i = 0; i < player_count; i++) 
            gl_draw_rect(sprites[i]->x - sprites[i]->vel_x, sprites[i]->y - sprites[i]->vel_y, 100, 100, GL_BLACK);
    }

    void player_fireball(sprite* p_sprite, sprite* fire){ //Puts fireball at the position of the passed sprite
        int fireball_radius = 10; 
        fire->x = p_sprite->hit_x_right + fireball_radius *2;
        fire->y = p_sprite->y;
        fire->hit_x_right = fire->x + fireball_radius;
        fire->hit_x_left = fire->x - fireball_radius;
        fire->hit_y_top = fire->y + fireball_radius;
        fire->hit_y_bottom= fire->y - fireball_radius;
        player_draw_sprites(fire);
        gl_swap_buffer();
        player_draw_sprites(fire);
    }



     void update_hit_box(sprite* _sprite){
        _sprite->hit_x_left += _sprite->vel_x;
        _sprite->hit_x_right += _sprite->vel_x;
        _sprite->hit_y_top += _sprite->vel_y;
        _sprite->hit_y_bottom += _sprite->vel_y;
     }

    void player_draw_sprites(sprite* _sprite){ //Draw and move the sprites
        int box_radius = 80;
        int wheel_radius = 15;
        int ball_radius = 50; 
        int eye_radius = 5; 
        int fireball_radius = 10; 

        if (_sprite->hit_x_right <= gl_get_width() && _sprite->hit_x_left >= 0){ 
            if(_sprite->sprite_num == 1){
                gl_draw_box(_sprite->x, _sprite->y, box_radius, wheel_radius); //Draw the box
            } 
            else if (_sprite->sprite_num == 0) {  
                gl_draw_circle_sprite(_sprite->x, _sprite->y, ball_radius, eye_radius);
            }
            else {
                gl_draw_circle(_sprite->x, _sprite->y, fireball_radius, GL_RED);
            }
        } else{
            if (_sprite->sprite_num == 1){ //If the fireball is moving outside of bounds, delete it
                // gl_draw_rect(player->x - x - fireball_radius, player->y - y - fireball_radius, (fireball_radius * 2), (fireball_radius *2), GL_BLACK);
                gl_draw_rect(_sprite->x, _sprite->y, (fireball_radius * 2), (fireball_radius *2), GL_BLACK);
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
            else {
                return 0;
            }
        }   
    }
    // void box_hit(){
    //     box.hit_points -= 10;
    // }
    // void ball_hit(){
    //     ball.hit_points -=10;
    // }
