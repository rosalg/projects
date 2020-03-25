#include <stdarg.h>
#include "controller.h"
#include "gpio.h"
#include "timer.h"
#include "fb.h"
#include "gl_kyl.h"
#include "player.h"
#include "printf.h"
#include "malloc.h"
#include "gameplay.h"
   
void player_init(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < gameplay_get_sprite_count(); i++) {
        sprite* _sprite = va_arg(ap, sprite*);
        player_draw_sprites(_sprite);
        gl_draw_rect(i * gl_get_width() - 100 * i, 0, _sprite->hit_points, 10, _sprite->base_color);
        gl_swap_buffer();
        gl_draw_rect(i * gl_get_width() - 100 * i, 0, _sprite->hit_points, 10, _sprite->base_color);
        gl_swap_buffer();
    }
    gl_swap_buffer();
}

void player_jump(sprite* _sprite) {
    _sprite->is_jumping = 10;
    _sprite->is_grounded = 0;
    _sprite->vel_y = -10;
}

void player_move(sprite sprites[30]) {
    for (int i = 0; i < gameplay_get_sprite_count(); i++) {
        if (sprites[i].x + sprites[i].vel_x >= gl_get_width() || sprites[i].x + sprites[i].vel_x <= 0) continue;
        sprites[i].x += sprites[i].vel_x;
        sprites[i].y += sprites[i].vel_y;
        update_hit_box(&sprites[i]);
        player_draw_sprites(&sprites[i]);
        if (sprites[i].is_firing) {
            sprite* proj = &sprites[sprites[i].proj_sprite_num];
            proj->x += proj->vel_x;
            proj->y += proj->vel_y;
            update_hit_box(proj);
            if (i == 0) {
                if (projectile_hit(&sprites[1], proj)) {
                    proj->hit = 1;
                    sprites[1].hit_points -= 10;
                    gl_draw_rect(gl_get_width() - 100, 0, 100, 10, GL_BLACK);
                    gl_draw_rect(gl_get_width() - sprites[1].hit_points, 0, sprites[1].hit_points, 10, sprites[i].base_color);
                    gl_swap_buffer();
                    gl_draw_rect(gl_get_width() - 100, 0, 100, 10, GL_BLACK);
                    gl_draw_rect(gl_get_width() - sprites[1].hit_points, 0, sprites[1].hit_points, 10, sprites[i].base_color);
                    gl_swap_buffer();
                }
            } else if (i == 1) {
                if (projectile_hit(&sprites[0], proj)) {
                    proj->hit = 1;
                    sprites[0].hit_points -= 10;
                    gl_draw_rect(0, 0, 100, 10, GL_BLACK);
                    gl_draw_rect(0, 0, sprites[0].hit_points, 10, sprites[i].base_color);
                    gl_swap_buffer();
                    gl_draw_rect(0, 0, 100, 10, GL_BLACK);
                    gl_draw_rect(0, 0, sprites[0].hit_points, 10, sprites[i].base_color);
                    gl_swap_buffer();
                }
            }
            player_draw_sprites(proj);
        }
    }
    gl_swap_buffer();
    for (int i = 0; i < gameplay_get_sprite_count(); i++) {
        player_erase_sprites(&sprites[i]);
        if (sprites[i].is_firing) {
            player_erase_sprites(&sprites[sprites[i].proj_sprite_num]);
        }
    } 
}

void player_projectile(sprite* p_sprite, sprite* projectile){
    if (p_sprite->direction == RIGHT) {
        projectile->x = p_sprite->hit_x_right + FIREBALL_RADIUS * 2;
        projectile->vel_x = 20;
        projectile->direction = RIGHT;
    } else {
        projectile->x = p_sprite->hit_x_left + FIREBALL_RADIUS * 2;
        projectile->vel_x = -20;
        projectile->direction = LEFT;
    }
    projectile->y = p_sprite->y + FIREBALL_RADIUS;
    projectile->hit_x_right = projectile->x + FIREBALL_RADIUS;
    projectile->hit_x_left = projectile->x - FIREBALL_RADIUS;
    projectile->hit_y_top = projectile->y + FIREBALL_RADIUS;
    projectile->hit_y_bottom= projectile->y - FIREBALL_RADIUS;
    p_sprite->is_firing = 1;
}



 void update_hit_box(sprite* _sprite){
    _sprite->hit_x_left += _sprite->vel_x;
    _sprite->hit_x_right += _sprite->vel_x;
    _sprite->hit_y_top += _sprite->vel_y;
    _sprite->hit_y_bottom += _sprite->vel_y;
 }

void player_draw_sprites(sprite* _sprite){ //Draw and move the sprites
    if ((_sprite->hit_x_right <= gl_get_width() && _sprite->hit_x_left >= 0 && _sprite->hit != 1)){ 
        if(_sprite->sprite_num == BOX){
            gl_draw_box(_sprite->x, _sprite->y, BOX_WIDTH, BOX_FEET_RADIUS, _sprite->color); //Draw the box
        } 
        else if (_sprite->sprite_num == BALL) {  
            gl_draw_circle_sprite(_sprite->x, _sprite->y, BALL_RADIUS, EYE_RADIUS);
        }
        else if (_sprite->sprite_num == FIRE) {
            gl_draw_circle(_sprite->x, _sprite->y, FIREBALL_RADIUS, GL_RED);
        }
    } else{
        if (_sprite->sprite_num == FIRE){ //If the fireball is moving outside of bounds, delete it
            _sprite->owner->is_firing = 0;
            gl_swap_buffer();
            if (_sprite->direction == RIGHT) {
                gl_draw_rect(_sprite->x - FIREBALL_RADIUS * 3, _sprite->y - FIREBALL_RADIUS, (FIREBALL_RADIUS * 2) + 1, (FIREBALL_RADIUS * 2) + 1, GL_BLACK);
            } else { 
                gl_draw_rect(_sprite->x + FIREBALL_RADIUS, _sprite->y - FIREBALL_RADIUS, (FIREBALL_RADIUS * 2) + 1, (FIREBALL_RADIUS * 2) + 1, GL_BLACK);
            }
            _sprite->x = 0;
            _sprite->y = 0;
            _sprite->vel_x = 0;
            _sprite->vel_y = 0;
            gl_swap_buffer();
            }      
        }
    }

void player_erase_sprites(sprite* _sprite) {
    if (_sprite->sprite_num == BOX) {
        gl_draw_rect(_sprite->x - _sprite->vel_x, _sprite->y - _sprite->vel_y, BOX_WIDTH + BOX_FEET_RADIUS + 1, BOX_WIDTH + BOX_FEET_RADIUS + 1, GL_BLACK);
    } else if (_sprite->sprite_num == BALL) { 
        gl_draw_rect(_sprite->x - _sprite->vel_x - BALL_RADIUS, _sprite->y - _sprite->vel_y - BALL_RADIUS, BALL_RADIUS * 2 + 1, BALL_RADIUS * 2 + 1, GL_BLACK);
    } else if (_sprite->sprite_num == FIRE) {
        gl_draw_rect(_sprite->x - _sprite->vel_x - FIREBALL_RADIUS, _sprite->y - _sprite->vel_y - FIREBALL_RADIUS, FIREBALL_RADIUS * 2 + 1, FIREBALL_RADIUS * 2 + 1, GL_BLACK);
    }
}

void gl_draw_circle_sprite(int x, int y, int circle_r, int eye_r){
    gl_draw_circle(x, y, circle_r, GL_YELLOW);
    gl_draw_circle(x - 15, y - 15, eye_r, GL_BLACK);
    gl_draw_circle(x + 15, y - 15, eye_r, GL_BLACK);
}

void gl_draw_box(int x, int y, int box_r, int wheel_r, color_t color){
    gl_draw_circle(x + wheel_r, y + box_r, wheel_r, GL_WHITE);
    gl_draw_circle(x + (wheel_r*4), y + box_r, wheel_r, GL_WHITE);
    gl_draw_rect(x, y, box_r, box_r, color);
}

int players_hit(sprite* player1, sprite* player0){    
    if(player1->hit_y_bottom >= player0->hit_y_top){       
        if (((player0->hit_x_right >= player1->hit_x_right) &&  (player1->hit_x_right >= player0->hit_x_left))){
            return 1; 
        }  else {
            return 0;
        }
    }
    return 0;   
}


int projectile_hit(sprite* target, sprite* projectile){
    if(( ((target->hit_y_bottom >= projectile->hit_y_top) && (target->hit_y_top <= projectile->hit_y_top)) ||
     ((target->hit_y_top <= projectile->hit_y_bottom) && (target->hit_y_bottom >= projectile->hit_y_bottom ))) && target->is_shielding == 0 ) {  
        if ((projectile->hit_x_right <= target->hit_x_right) &&  (projectile->hit_x_right >= target->hit_x_left)){
            return 1;
        }  else if ((projectile->hit_x_left >= target->hit_x_right) &&  (projectile->hit_x_left <= target->hit_x_left)){
            return 1;
        }  else {
            return 0;
        }
    }
    return 0;
}
