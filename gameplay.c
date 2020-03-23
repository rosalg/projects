#include <stdarg.h>
#include "assert.h"
#include "console.h"
#include "fb.h"
#include "gl_kyl.h"
#include "printf.h"
#include "strings.h"
#include "timer.h"
#include "uart.h"
#include "gpio.h"
#include "gpioextra.h"
#include "controller.h"
#include "player.h"
#include "gameplay.h"
#include "gameplay_internal.h"
#include "malloc.h"
#include "strings.h"
#include "pi.h"

#define _WIDTH 640
#define _HEIGHT 360

#define NUMBER_OF_PLAYERS 2 

static player p1;
static player p2;
//static player p3; 
//static player p4;
static int sprite_count;
static int GROUND = 0;
static sprite sprites[30];
static int number_of_platforms = 0;

void gameplay_init(void) {
    uart_init();
    timer_init();
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER);
    int width = gl_get_width();
    int height = gl_get_height();
    gl_draw_background(GL_PURPLE);
    gl_swap_buffer();
    gl_draw_background(GL_PURPLE);

    sprite_count = NUMBER_OF_PLAYERS;
    make_sprite(1, BOX, width/4, height - 100 - BOX_WIDTH - BOX_FEET_RADIUS - 5, RIGHT, GL_BLUE);
    
    p1.con_num = 1;
    p1.sprite = &sprites[0];
    
    //Set up the box2
    make_sprite(2, BOX, 2*width/4, height - 100 - 5 - BOX_WIDTH - BOX_FEET_RADIUS,  LEFT, GL_BLUE);
    
    p2.con_num = 2;
    p2.sprite = &sprites[1];
    
    GROUND = gl_get_height() - 105;
    
    make_platforms(gl_get_width()/2 - 50, gl_get_height()/2, 100, 10, GL_PURPLE);

    player_init(sprite_count, p1.sprite, p2.sprite);
}

void make_platforms(int x, int y, int width, int height, color_t color) {
     number_of_platforms++;
     sprite* platform = &sprites[3 + number_of_platforms];
     platform->x = x;
     platform->y = y;
     platform->hit_x_left = platform->x;
     platform->hit_x_right = platform->x + width;
     platform->hit_y_top = platform->y;
     platform->hit_y_bottom = platform->y + height;
     gl_draw_rect(x, y, width, height, color);
     gl_swap_buffer();
     gl_draw_rect(x, y, width, height, color);
}

int is_touching_platform(player p) {
    for (int i = 4; i <= number_of_platforms; i++) {
        if ((p.sprite->hit_y_top <= sprites[i].hit_y_bottom && p.sprite->hit_y_top >= sprites[i].hit_y_top) ||
             (p.sprite->hit_y_bottom <= sprites[i].hit_y_bottom && p.sprite->hit_y_bottom >= sprites[i].hit_y_top)) {   
            if ((p.sprite->hit_x_right <= sprites[i].hit_x_right && p.sprite->hit_x_right >= sprites[i].hit_x_left) || 
                    (p.sprite->hit_x_left <= sprites[i].hit_x_right && p.sprite->hit_x_left >= sprites[i].hit_x_left)) {
                return 1;
            }
            
        }
    }     
    return 0;
}

void make_sprite(int p_num, int sprite_number, int x_start, int y_start, int direc, color_t color) {
    sprite* player = &sprites[p_num - 1];
    player->x = x_start;
    player->y = y_start;
    player->is_grounded = 1;
    player->is_jumping = 0;
    
    player->is_firing = 0;
    player->direction = direc;
    player->proj_sprite_num = p_num + NUMBER_OF_PLAYERS - 1;
    player->proj_cooldown = 0;

    player->is_shielding = 0;
    player->is_stunned = 0;
    player->shield_timer = SHIELD_TIME;
    
    player->vel_x = 0;
    player->vel_y = 0;
    player->color = color;
    player->base_color = color;
    if (sprite_number == BOX) {
        player->sprite_num = BOX; 
        player->hit_points = 100; 
        player->hit_x_left = player->x;
        player->hit_x_right = player->x + BOX_WIDTH;
        player->hit_y_top = player->y;
        player->hit_y_bottom = player->y + BOX_WIDTH + BOX_FEET_RADIUS;
    } else if (sprite_number == BALL) {
        player->sprite_num = BALL; 
        player->hit_points = 100;
        player->hit_x_left = player->x - BALL_RADIUS;
        player->hit_x_right = player->x + BALL_RADIUS;
        player->hit_y_top = player->y - BALL_RADIUS;
        player->hit_y_bottom = player->y + BALL_RADIUS;
    }
}

int gameplay_get_sprite_count(void) {
    return sprite_count;
}

void gameplay_set_sprite_count(int n) {
    sprite_count = n;
}

void end_game(void) {
    gl_clear(GL_BLACK);
    char* player_winner= "Player 1 wins";
    if (p1.sprite->hit_points <= 0) player_winner = "Player 2 wins";
    gl_draw_string(gl_get_width()/2 - gl_get_char_width() * strlen("GAME OVER") / 2,gl_get_height()/2, "GAME OVER", GL_YELLOW);
    gl_draw_string(gl_get_width()/2 - gl_get_char_width() * strlen(player_winner) / 2, gl_get_height()/2 + 20, player_winner, GL_YELLOW);
    gl_swap_buffer();
}

void play_game(void) {
    controller_init(21, 20);
    while(1) {
        update(p1);
        if (NUMBER_OF_PLAYERS >= 2) {
            update(p2); 
        }
        player_move(sprites);
        if (p1.sprite->hit_points == 0 || p2.sprite->hit_points == 0) {
            end_game();
            break;
        }
    }
    
}

void update_gravity(player p) {
    if (p.sprite->is_grounded == 0 && (p.sprite->hit_y_bottom >= GROUND || is_touching_platform(p))) {
        p.sprite->is_grounded = 1;
        p.sprite->vel_y = 0;
    } else if (p.sprite->is_grounded == 0 && p.sprite->is_jumping == 0 && p.sprite->hit_y_bottom < GROUND) {
        p.sprite->vel_y = 10;
    } else if (p.sprite->is_jumping > 0) {
        p.sprite->is_jumping--;
    }
}

void update_shielding(player p) {
    if (p.sprite->is_grounded && (controller_get_L(p.con_num) || controller_get_R(p.con_num)) && p.sprite->shield_timer > 0) {
        p.sprite->is_shielding = 1;
        p.sprite->vel_x = 0;
        p.sprite->shield_timer--;
        p.sprite->color &= 0xFFFFFF00;
        p.sprite->color |= (0xFF * p.sprite->shield_timer/SHIELD_TIME);
        return;
    } else if (p.sprite->shield_timer <= 0){
        p.sprite->is_stunned = 1;
        p.sprite->color = p.sprite->base_color;
        p.sprite->is_shielding = 0;
    } else {
        p.sprite->color = p.sprite->base_color;
        p.sprite->is_shielding = 0;
        if (p.sprite->shield_timer < SHIELD_TIME) p.sprite->shield_timer++;
    }
}

void update_horizontal_movement(player p) {
    if (controller_get_JOYSTICK_X(p.con_num) == 119) {
            p.sprite->vel_x = 10;
            p.sprite->direction = RIGHT;
        } 
        if (controller_get_JOYSTICK_X(p.con_num) == 8) {
            p.sprite->vel_x = -10;
            p.sprite->direction = LEFT;
        }
        if (controller_get_JOYSTICK_X(p.con_num) == 254 || controller_get_JOYSTICK_X(p.con_num) == 1) {
            p.sprite->vel_x = 0;
        }
}

void update(player p) {
    controller_poll(p.con_num);
    update_gravity(p); 
    // Update stun
    if (p.sprite->is_stunned) {
        p.sprite->vel_x = 0;
        if (p.sprite->shield_timer == SHIELD_TIME) {
            p.sprite->color = p.sprite->base_color;
            p.sprite->is_stunned = 0;
        } else {
            if ((p.sprite->color&0xFF) == 0 && p.sprite->shield_timer % 5 == 0) {
                p.sprite->color = p.sprite->base_color;
            } else {
                p.sprite->color = p.sprite->color & 0xFFFFFF00;
            }
            p.sprite->shield_timer++;
            return;
        }
    }
    update_horizontal_movement(p); 
    update_shielding(p); 
    //Update shoot
    if (controller_get_A(p.con_num) && p.sprite->is_firing == 0 && (controller_get_JOYSTICK_X(p.con_num) == 119 || controller_get_JOYSTICK_X(p.con_num) == 8) && (p.sprite->proj_cooldown == 0)) {
        p.sprite->proj_cooldown = PROJ_COOLDOWN;
        sprite* fire = &sprites[p.sprite->proj_sprite_num];
        fire->sprite_num = FIRE;
        fire->owner = p.sprite;
        fire->hit = 0;
        player_projectile(p.sprite, fire);
    } else if (p.sprite->proj_cooldown > 0) {
        p.sprite->proj_cooldown--;
    }
    if ((controller_get_X(p.con_num) || controller_get_JOYSTICK_Y(p.con_num) == 119) && p.sprite->is_grounded == 1) {
        player_jump(p.sprite);
    }
}

void main(void)
{
    gameplay_init();
    play_game();
    timer_delay(5);
    pi_reboot();
    uart_putchar(EOT);
}
