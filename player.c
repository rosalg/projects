#include <stdarg.h>
#include "controller.h"
#include "gpio.h"
#include "timer.h"
#include "fb.h"
#include "gl_kyl.h"
#include "player.h"
#include "printf.h"
#include "malloc.h"
    // static volatile sprite box; 
    // static sprite ball;

    static char* sprites;
    static int sprite_count = 0;

    void player_init(int n, ...) {
        sprites = (char*)malloc(sizeof(sprite) *n);
        sprite* (*_sprites)[sizeof(sprite)] = (sprite* (*)[sizeof(sprite)])sprites;
        va_list ap;
        va_start(ap, n);
        sprite_count = n;
        for (int i = 0; i < sprite_count; i++) {
            sprite* _sprite = va_arg(ap, sprite*);    
            player_draw_sprites(_sprite);
            (*_sprites)[i] = _sprite;
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
        sprite* (*_sprites)[sizeof(sprite)] = (sprite* (*)[sizeof(sprite)])sprites; 
        for (int i = 0; i < sprite_count; i++) {
            (*_sprites)[i]->x += (*_sprites)[i]->vel_x;
            (*_sprites)[i]->y += (*_sprites)[i]->vel_y;
            update_hit_box((*_sprites)[i]);
            player_draw_sprites((*_sprites)[i]);
        }        
        gl_swap_buffer();
        
        for (int i = 0; i < sprite_count; i++) {
            if ((*_sprites)[i]->sprite_num == BOX) {
                gl_draw_rect((*_sprites)[i]->x - (*_sprites)[i]->vel_x, (*_sprites)[i]->y - (*_sprites)[i]->vel_y, 100, 100, GL_BLACK);
            } else if ((*_sprites)[i]->sprite_num == BALL) {
                //TODO
            } else if ((*_sprites)[i]->sprite_num == FIRE) {
                gl_draw_rect((*_sprites)[i]->x - (*_sprites)[i]->vel_x - 10, (*_sprites)[i]->y - (*_sprites)[i]->vel_y - 10, 21, 21, GL_BLACK);
            }
        }
    }

    void player_projectile(sprite* p_sprite, sprite* projectile){ //Puts fireball at the position of the passed sprite
        int fireball_radius = 10;
        if (p_sprite->direction == RIGHT) {
            projectile->x = p_sprite->hit_x_right + fireball_radius * 2;
            projectile->vel_x = 20;
            projectile->direction = RIGHT;
        } else {
            projectile->x = p_sprite->hit_x_left + fireball_radius * 2;
            projectile->vel_x = -20;
            projectile->direction = LEFT;
        }
        projectile->y = p_sprite->y + fireball_radius;
        projectile->hit_x_right = projectile->x + fireball_radius;
        projectile->hit_x_left = projectile->x - fireball_radius;
        projectile->hit_y_top = projectile->y + fireball_radius;
        projectile->hit_y_bottom= projectile->y - fireball_radius;
        sprite_count++;
        realloc(sprites, sizeof(sprite)*sprite_count);
        sprite* (*_sprites)[sizeof(sprite)] = (sprite* (*)[sizeof(sprite)])sprites;
        (*_sprites)[sprite_count - 1] = projectile;
        p_sprite->is_firing = 1;
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
            if(_sprite->sprite_num == BOX){
                gl_draw_box(_sprite->x, _sprite->y, box_radius, wheel_radius); //Draw the box
            } 
            else if (_sprite->sprite_num == BALL) {  
                gl_draw_circle_sprite(_sprite->x, _sprite->y, ball_radius, eye_radius);
            }
            else if (_sprite->sprite_num == FIRE) {
                gl_draw_circle(_sprite->x, _sprite->y, fireball_radius, GL_RED);
            }
        } else{
            if (_sprite->sprite_num == FIRE){ //If the fireball is moving outside of bounds, delete it
                _sprite->owner->is_firing = 0;
                gl_swap_buffer();
                if (_sprite->direction == RIGHT) {
                    gl_draw_rect(_sprite->x - 30, _sprite->y - 10, (fireball_radius * 2) + 1, (fireball_radius *2) + 1, GL_BLACK);
                } else { 
                    gl_draw_rect(_sprite->x + 30, _sprite->y + 10, (fireball_radius * 2) + 1, (fireball_radius *2) + 1, GL_BLACK);
                }
                sprite_count--;
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

    int players_hit(sprite* player1, sprite* player0){
        
    if(player1->hit_y_bottom >= player0->hit_y_top){       
        if (((player0->hit_x_right >= player1->hit_x_right) &&  (player1->hit_x_right >= player0->hit_x_left))){
                return 1;
            }  
            else {
                return 0;
            }
        }   
    }


int projectile_hit(sprite* player1, sprite* player0, sprite* projectile){
    if((player1->hit_y_bottom >= projectile->hit_y_top) && (player1->hit_y_top >= projectile->hit_y_top)) {  
        if (((player0->hit_x_right >= projectile->hit_x_right) &&  (player0->hit_x_left <= projectile->hit_x_left))){
                return 1;
            }  

        else if (((player1->hit_x_right >= projectile->hit_x_right) &&  (player1->hit_x_left <= projectile->hit_x_left))){
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
    // }CK);GL_BLACK);
