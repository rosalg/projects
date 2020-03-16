#ifndef PLAYER_H
#define PLAYER_H

#include <stdarg.h>

typedef struct {
    int x;
    int y;
    int vel_x;
    int vel_y;
    
    int is_jumping;
    int is_grounded;

    int sprite_num; //Ball = 0, box = 1
    int hit_x_left;
    int hit_x_right;
    int hit_y_top;
    int hit_y_bottom;
    int hit_points;
}sprite;

//void player_init(sprite* player);

void player_init(int n, ...);

//void player_move(sprite* player, int x, int y);

void player_move();

void player_jump(sprite* _sprite);

//void update_hit_box(sprite* player, int x, int y);

sprite* player_get_players();

void update_hit_box(sprite* _sprite);

void player_fireball(sprite* p_sprite, sprite* fire);

#endif
