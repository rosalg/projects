#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gl_kyl.h"

typedef struct {
    sprite* sprite;
    int con_num;
    int color_num;
} player;

typedef enum {
    BOX_HEIGHT = 32,
    BOX_WIDTH = 32,
    // BOX FEET_RADIUS SHOULD BE 3/16 OF BOX_HEIGHT
    BOX_FEET_RADIUS = 6,
    BOX_ARM_WIDTH = 20,
    BOX_ARM_HEIGHT = 10,
} box;

typedef enum {
    BALL_RADIUS = 20,
    //EYE RADIUS SHOULD BE 1/5 OF BALL RADIUS
    EYE_RADIUS = 2,
} ball;

typedef enum {
    FIREBALL_RADIUS = 10,
} projectiles;

typedef enum {
    CURSOR_RADIUS = 5,
} cursor_t;

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

int gameplay_get_sprite_count(void);

void gameplay_set_sprite_count(int n);

int is_touching_platform(player p);

#endif
