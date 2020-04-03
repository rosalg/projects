#ifndef PLAYER_H
#define PLAYER_H

#include <stdarg.h>
#include "gl_kyl.h"

/* 
 * sprite struct containing ALL information about a sprite, like location, velocity, whether it is jumping
 * or grounded, whether it is shielding and for how long, whether the character is knockbacked and for
 * how long, whether the sprite is punching, information about the projectile the character fires, hitboxes,
 * and sprite number for different sprites..
 */
typedef struct sprite {
    int x;
    int y;
    volatile int vel_x;
    volatile int vel_y;
    int height;    

    int is_jumping;
    int is_grounded;
    
    int is_shielding;
    int is_stunned;
    int shield_timer;

    int is_punching;
    int knockback_timer;

    int proj_sprite_num;
    int hit;
    int is_firing;
    int direction;
    int proj_cooldown;

    int color;
    int base_color;
    int sprite_num; //Ball == 1, box == 2, fire == 3
    int hit_x_left;
    int hit_x_right;
    int hit_y_top;
    int hit_y_bottom;
    int hit_points;
    struct sprite* owner;
}sprite;

/*
 * Sprite nums enum for redrawing. Based on which sprite number the player's sprite has, the GPU will redraw
 * the sprite shape.
 */
typedef enum {
    BOX = 1,
    BALL = 2,
    FIRE = 3,
} sprite_nums;

/*
 * Enums for directions the sprite is facing. Affects punch direction and shot direction.
 */
typedef enum {
    LEFT = -1,
    RIGHT = 1,
    NONE = 0,
} directions;

void player_init(int n, ...);

void player_move(sprite sprites[30]);

void player_jump(sprite* _sprite);

void player_erase_sprites(sprite* _sprites);

void update_hit_box(sprite* _sprite);

void player_projectile(sprite* p_sprite, sprite* projectile);

//See if the projectiles on screen have impacted any sprites
int projectile_hit(sprite* target, sprite* projectile);

int player_punch(sprite* p_sprite, sprite* target_sprite);

int punch_hit(sprite* p_sprite, sprite* target_sprite);

void player_redraw_health_bar(int x, int y, int x2, int y2, sprite _sprite);

#endif
