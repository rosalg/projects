#ifndef PLAYER_H
#define PLAYER_H

#include <stdarg.h>
#include "gl_kyl.h"

typedef struct sprite {
    int x;
    int y;
    volatile int vel_x;
    volatile int vel_y;
    
    int is_jumping;
    int is_grounded;
    
    int is_shielding;
    int is_stunned;
    int shield_timer;

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

typedef enum {
    BOX = 1,
    BALL = 2,
    FIRE = 3,
} sprite_nums;

typedef enum {
    LEFT = 0,
    RIGHT = 1,
} directions;

//void player_init(sprite* player);

void player_init(int n, ...);

//void player_move(sprite* player, int x, int y);

void player_move(sprite sprites[30]);

void player_jump(sprite* _sprite);

void player_erase_sprites(sprite* _sprites);

//void update_hit_box(sprite* player, int x, int y);

sprite* player_get_players();

void update_hit_box(sprite* _sprite);

void player_projectile(sprite* p_sprite, sprite* projectile);

//See if the projectiles on screen have impacted any sprites
int projectile_hit(sprite* target, sprite* projectile);

#endif
