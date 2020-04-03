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

/*
 * Update the player p's sprite's y velocity based on whether its touching a platform, falling, or jumping.
 *
 * PARAMETERS
 * p - The player's gravity you are updating.
 */
void update_gravity(player p);

/*
 * Update the player p's sprite's x velocity based on remote inputs.
 *
 * PARAMETERS
 * p - The player's horizontal movement you are updating.
 */
void update_horizontal_movement(player p);

/*
 * Update the player p's sprite's shielding timer and is_shielding variable based on whether
 * L or R are being pressed.
 *
 * PARAMTERS
 * p - the player's shielding info you are updating.
 */
void update_shielding(player p);

/*
 * Helper function that makes rectangular platforms on screen.
 *
 * PARAMETERS
 * x - the x position of platform from the top right
 * y - the y position of platform from the top right
 * width - the width of the platform
 * height - the height of the platform
 * color - the color of the platform
 */
void make_platforms(int x, int y, int width, int height, color_t color);

/* 
 * Optimization function that checks whether any players have gone through the platforms edges,
 * then redraws the platform only if that is true.
 *
 * PARAMETERS
 * platform - The sprite that you are checking for redrawing.
 */
int should_draw_platform(sprite platform);

/*
 * Helper function that uses should_draw_platforms. It goes through each platform and checks if you should
 * redraw any of them, redrawing all the ones that need redrawing.
 */
void redraw_platforms(void);

/*
 * Function used on the main menu to redraw a player's cursor.
 *
 * PARAMETERS
 * p - Pointer to player's memory you are redrawing
 * color - color of the cursor
 */
void draw_cursor(player* p, color_t color);

/*
 * Update function that reads from the remote and updates the cursor's X and Y velocity correspondingly.
 */
void update_menu(player p);

/*
 * Goes through the character select screen loop, updating the screen whenever and allowing the
 * player to select character and color.
 */
void character_select(void);

/*
 * Update player p's sprite's punch in main update loop, adjusting cooldown time, checking for collision, and
 * updating corresponding damage as a result.
 *
 * PARAMETERS
 * p - Player's punch values you are updating.
 */
void update_punch(player p);

#endif
