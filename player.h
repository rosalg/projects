#ifndef PLAYER_H
#define PLAYER_H

#include <stdarg.h>

typedef struct sprite {
    int x;
    int y;
    int vel_x;
    int vel_y;
    
    int is_jumping;
    int is_grounded;
    int is_firing;

    int direction;

    int sprite_num; //Ball = 0, box = 1
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

void player_move();

void player_jump(sprite* _sprite);

//void update_hit_box(sprite* player, int x, int y);

sprite* player_get_players();

void update_hit_box(sprite* _sprite);

void player_projectile(sprite* p_sprite, sprite* projectile);

//See if the projectiles on screen have impacted any sprites
int projectile_hit(sprite* player1, sprite* player0, sprite*projectile);

#endif
