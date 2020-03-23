#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gl_kyl.h"

typedef struct {
    sprite* sprite;
    int con_num;
} player;

typedef enum {
    BOX_HEIGHT = 32,
    BOX_WIDTH = 32,
    // BOX FEET_RADIUS SHOULD BE 3/16 OF BOX_HEIGHT
    BOX_FEET_RADIUS = 6,
} box;

typedef enum {
    BALL_RADIUS = 10,
    //EYE RADIUS SHOULD BE 1/5 OF BALL RADIUS
    EYE_RADIUS = 2,
} ball;

typedef enum {
    FIREBALL_RADIUS = 10,
} projectiles;

typedef struct {
    int top;
    int bot;
    int left;
    int right;
} hitbox;

typedef enum {
    SHIELD_TIME = 75,
    PROJ_COOLDOWN = 75,
} values_t;

int gameplay_get_sprite_count(void);

void gameplay_set_sprite_count(int n);

#endif
