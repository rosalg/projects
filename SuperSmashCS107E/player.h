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

/*
 *  This function draws the initial player sprites to the doubleBuffered framebuffer.
 *
 *  PARAMETERS
 *  n - The number of players in the game.
 *  ... - A variadic number of sprite pointers, where each sprite is the sprite of a player.
 */
void player_init(int n, ...);

/*
 *  Function that moves each player simultaneously based on vel_x and vel_y. It also moves any projectiles fired,
 *  checking for collisions.
 *
 *  PARAMETERS
 *  sprites[30] - array in gameplay implementation that contains information about each sprite
 *  (WITH A MAX OF 30 SPRITES)
 */
void player_move(sprite sprites[30]);

/*
 *  Function takes a pointer to a sprite and makes that sprite jump by changing its vel_y and updating
 *  its is grounded and is_jumping variables.
 *
 *  PARAMETERS
 *  _sprite - The sprite you want to jump.
 */
void player_jump(sprite* _sprite);

/*
 *  Function that erases sprite on the hidden buffer.
 *
 *  PARAMETERS
 *  _sprite - Sprite you want to erase
 */
void player_erase_sprites(sprite* _sprite);

/*
 *  Helper function that updates the hitbox of _sprite.
 *
 *  PARAMETERS
 *  _sprite - sprite that contains hitbox you want to update
 */
void update_hit_box(sprite* _sprite);

/*
 *  Make p_sprite shoot projectile
 *
 *  PARAMETERS
 *  p_sprite - player_sprite: The sprite of player that you want to shoot.
 *  projectile - The sprite you want to treat as the projectile.
 */
void player_projectile(sprite* p_sprite, sprite* projectile);

/*
 *  Check whether projectile hit target by comparing hitboxes.
 *
 *  PARAMETERS
 *  target - pointer to target sprite
 *  projectile - pointer to projectile sprite that you want to check for collision
 */
int projectile_hit(sprite* target, sprite* projectile);

/*
 *  Check if p_sprite hit target_sprite, drawing a fist to represent a punch.
 *
 *  PARAMETERS
 *  p_sprite - player_sprite: The sprite of player you want punching
 *  target_sprite - The sprite of player you want to check for getting punched.
 */
int player_punch(sprite* p_sprite, sprite* target_sprite);

/*
 *  Helper function that registers whether p_sprite hit target_sprite by checking hitboxes.
 *
 *  PARAMETERS
 *  p_sprite - player_sprite: The sprite of player you want punching
 *  target_sprite - The sprite of player you want to check for getting punched.
 */
int punch_hit(sprite* p_sprite, sprite* target_sprite);

/*
 * Helper function that redrew each player's healthbars.
 *
 *  PARAMETERS
 *  x - x_pos of health_bar for p1
 *  y - y_pos of health_bar for p1
 *  x2 - x_pos of health_bar for p2
 *  y2 - y_pos of health_bar for p2
 *  _sprite - sprite that was hit
 */
void player_redraw_health_bar(int x, int y, int x2, int y2, sprite _sprite);

#endif
