#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;

    int vel_x;
    int vel_y;
    
    int is_jumping;
    int is_grounded;

    int hit_x_left;
    int hit_x_right;
    int hit_y_top;
    int hit_y_bottom;
    int hit_points;
}sprite;

void player_init(sprite* player);

void player_move(sprite* player, int x, int y);

void player_jump(sprite* player);

void player_shoot(sprite* player);

#endif
