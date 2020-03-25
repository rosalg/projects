#ifndef GAMEPLAY_INTERNAL_H
#define GAMEPLAY_INTERNAL_H

/*
 
Make player p_num's sprite with sprite_number, x_start, y_start, direction, and color.

PARAMS:
    p_num: Which player's sprite to create (1-2)
    sprite_number: Which sprite that player wants
    x_start: Starting x_position
    y_start: Starting y_position
    direc: Starting direction
    color: Player's color

*/
void make_sprite(int p_num, int sprite_number, int x_start, int y_start, int direc);


/*

Takes players out of play_game loop, printing to screen game over and who won. Computed based off of final HP for each player

 */
void end_game(void);

/*

Main update look that takes in a player and polls that player's controller to read inputs. Based on inputs, it updates player's x_vel and y_vel which
are then used to redraw the sprites to the screen after updating.

PARAMS:
    p: Player that needs to be updated
 */
void update(player p);

/*

Main play loop. Takes each player, updates their x_vel and y_vel in update, then moves them based on their x_vel and y_vel.

*/
void play_game(void);

void update_gravity(player p);

void update_horizontal_movement(player p);

void update_shielding(player p);

void make_platforms(int x, int y, int width, int height, color_t color);

int any_sprite_is_moving(void);

int should_draw_platform(sprite platform);

void redraw_platforms();

void draw_cursor(player p, color_t color);

void update_menu(player p);

void color_select();

void update_punch(player p);

#endif
