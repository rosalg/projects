#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gl_kyl.h"


/*
 * Player struct that contains information about a player, like their sprite, their color_num (from 0 - 9),
 * and their controller number (1 or 2).
 */
typedef struct {
    sprite* sprite;
    int con_num;
    int color_num;
} player;

/*
 * Enumeration of key values for the BOX sprite in the game.
 */
typedef enum {
    BOX_HEIGHT = 32,
    BOX_WIDTH = 32,
    // BOX FEET_RADIUS SHOULD BE 3/16 OF BOX_HEIGHT
    BOX_FEET_RADIUS = 6,
    BOX_ARM_WIDTH = 20,
    BOX_ARM_HEIGHT = 10,
} box;


/*
 * Enumeration of key values for BALL sprite in the game.
 */
typedef enum {
    BALL_RADIUS = 20,
    //EYE RADIUS SHOULD BE 1/5 OF BALL RADIUS
    EYE_RADIUS = 2,
} ball;

/*
 * Enumeration of key values for PROJECTILES fired by sprites. At the moment, there is only one projectile type.
 */
typedef enum {
    FIREBALL_RADIUS = 10,
} projectiles;

/*
 * Enumeration of key values for cursor on the main menu.
 */
typedef enum {
    CURSOR_RADIUS = 5,
} cursor_t;

/*
 *  Miscellaneous enumerations for things like cooldown, damage, and direction recognition.
 */
typedef enum {
    SHIELD_TIME = 75,
    PROJ_COOLDOWN = 75,
    PUNCH_COOLDOWN = 6,
    PUNCH_DAMAGE = 5,
    PUNCH_KNOCKBACK_TIME = 3,
    TOP_RIGHT = 1,
    TOP_LEFT = 2,
    BOTTOM_RIGHT = 3,
    BOTTOM_LEFT = 4,
} values_t;

/*
 * Helper function that compute's whether or not a player is touching a platform.
 *
 * PARAMETER
 * p - the player that you are checking for platform collision
 */
int is_touching_platform(player p);

#endif
