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
    p1.con_num = 1;
    p1.sprite = &sprites[0];
    p2.con_num = 2;
    p2.sprite = &sprites[1];
    //color_t *p;
    //p = color_select();
    int width = gl_get_width();
    int height = gl_get_height();
    gl_draw_background(GL_PURPLE);
    gl_swap_buffer();
    gl_draw_background(GL_PURPLE);

    sprite_count = NUMBER_OF_PLAYERS;
    make_sprite(1, BOX, 10, height - 100 - BOX_WIDTH - BOX_FEET_RADIUS - 5, RIGHT, GL_RED);
    
    
    //Set up the box2
    make_sprite(2, BOX, width - BOX_WIDTH - 10, height - 100 - 5 - BOX_WIDTH - BOX_FEET_RADIUS,  LEFT, GL_BLUE);
    
    
    GROUND = gl_get_height() - 105;
    

    make_platforms(gl_get_width()/2 - 100, gl_get_height()/2 - 3, 200, 10, GL_PURPLE);
    //make_platforms(gl_get_width()/2 + 100, gl_get_height()/2 - 3, 200, 10, GL_PURPLE);
    
    player_init(sprite_count, p1.sprite, p2.sprite);
}

color_t* color_select() {
    p1.is_menuing = 1;
    p2.is_menuing = 1;
    static color_t p_colors[2];
    color_t colors[10]; 
    colors[0] = GL_RED; 
    colors[1] = GL_GREEN;
    colors[2] = GL_BLUE;
    colors[3] = GL_CYAN;
    colors[4] = GL_MAGENTA;
    colors[5] = GL_YELLOW;
    colors[6] = GL_AMBER;
    colors[7] = GL_ORANGE;
    colors[8] = GL_PURPLE;
    colors[9] = GL_INDIGO;
    p_colors[0] = 0;
    p_colors[1] = 0;
    sprites[0].x = gl_get_width()/2; sprites[1].x = gl_get_width()/2;
    sprites[0].y = gl_get_height()/2; sprites[1].y = gl_get_height()/2;
    sprites[0].vel_x = 0; sprites[1].vel_x = 0;
    sprites[0].vel_y = 0; sprites[1].vel_y = 0; 
    while(p_colors[0] == 0 && p_colors[1] == 0/* && (controller_get_START(1) == 0  && controller_get_START(2) == 0)*/) {
        int x_pos = 70;
        int y_pos = 30;
        int square_num = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                gl_draw_rect(x_pos + i * 100, y_pos + j * 150, 100, 150, colors[square_num]);
                square_num++;
            }
        }
        printf("E");
        controller_poll(p1.con_num);
        printf("E");
        update_menu(p1);
        //update(p2);
        //draw_cursor(p1.sprite);
        //draw_cursor(p2.sprite);
        gl_swap_buffer();
    }
    p1.is_menuing = 0;
    p2.is_menuing = 0;
    return p_colors;
}

void draw_cursor(sprite* s) {
    s->x += s->vel_x;
    s->y += s->vel_y;
    gl_draw_circle(s->x, s->y, 10, GL_WHITE);
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
     platform->base_color = color;
     gl_draw_rect(x, y, width, height, color);
     gl_swap_buffer();
     gl_draw_rect(x, y, width, height, color);
}

void redraw_platforms(){
    for (int i = 4; i <= 3 + number_of_platforms; i++) {
        sprite platform = sprites[i];
        if (should_draw_platform(platform)) 
            gl_draw_rect(platform.x, platform.y, platform.hit_x_right - platform.x, platform.hit_y_bottom - platform.y, platform.base_color);
    }
}

int should_draw_platform(sprite platform) {
    for (int i = platform.x; i <= platform.hit_x_right; i += (platform.hit_x_right - platform.x)) {
        for (int j = platform.y; j < platform.hit_y_bottom; j++) {
           if (gl_read_pixel(i, j) != platform.base_color) return 1; 
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

void main(void)
{
    gameplay_init();
    play_game();
    timer_delay(5);
    pi_reboot();
    uart_putchar(EOT);
}

void countdown(){
    gl_swap_buffer();
    int i = 3;
    char *buf = "";
    int x = (gl_get_width()-gl_get_char_width())/2;
    int y = (gl_get_height()-gl_get_char_height())/2 - 50;
    while (i > 0) {
        snprintf(buf, 3, "%d", i);
        gl_draw_string(x, y, buf, GL_YELLOW);
        gl_swap_buffer();
        timer_delay(1);
        gl_swap_buffer();
        gl_draw_rect(x, y, gl_get_char_width(), gl_get_char_height(), GL_BLACK);
        i--;
    }
    gl_draw_string(x - gl_get_char_width(), y, "GO!", GL_YELLOW);
    gl_swap_buffer();
    timer_delay_ms(100);
    gl_swap_buffer();
    gl_draw_rect(x - gl_get_char_width(), y, gl_get_char_width() * 3, gl_get_char_height(), GL_BLACK);

}

void play_game(void) {
    controller_init(21, 20);
    //countdown();
    while(1) {
        update(p1);
        if (NUMBER_OF_PLAYERS >= 2) {
            update(p2); 
        }
        player_move(sprites);
        redraw_platforms();
        if (p1.sprite->hit_points == 0 || p2.sprite->hit_points == 0) {
            end_game();
            break;
        }
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
                p.sprite->color = 0;
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

void update_menu(player p) {
    if (controller_get_JOYSTICK_X(p.con_num) == 119) {
        p.sprite->vel_x = 10;
    } else if (controller_get_JOYSTICK_X(p.con_num) == 8) {
        p.sprite->vel_x = -10;
    } else {
        p.sprite->vel_y = 0;
    }
    if (controller_get_JOYSTICK_Y(p.con_num) == 119) {
        p.sprite->vel_y = 10;
    } else if (controller_get_JOYSTICK_Y(p.con_num) == 8) {
        p.sprite->vel_y = -10;
    } else {
        p.sprite->vel_y = 0;
    }
}

void update_gravity(player p) {
    if (p.sprite->is_grounded == 0 && (p.sprite->hit_y_bottom >= GROUND || is_touching_platform(p) == BOTTOM_LEFT || is_touching_platform(p) == BOTTOM_RIGHT)) {
        p.sprite->is_grounded = 1;
        p.sprite->vel_y = 0;
    } else if (/*is_touching_platform(p) == TOP_LEFT || is_touching_platform(p) == TOP_RIGHT*/0) {
        p.sprite->is_jumping = 0;
        p.sprite->vel_y = 10;
    } else if (p.sprite->is_jumping == 0 && p.sprite->hit_y_bottom < GROUND && is_touching_platform(p) != BOTTOM_LEFT && is_touching_platform(p) != BOTTOM_RIGHT) {
        p.sprite->is_grounded = 0;
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
        p.sprite->color = (0xFF<<24)|
            ( ((0xFF&(p.sprite->color>>16)) * p.sprite->shield_timer/SHIELD_TIME) << 16)|
            ( ((0xFF&(p.sprite->color>>8)) * p.sprite->shield_timer/SHIELD_TIME) << 8)|
            ((0xFF&(p.sprite->color)) * p.sprite->shield_timer/SHIELD_TIME);
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

void end_game(void) {
    gl_clear(GL_BLACK);
    char* player_winner= "Player 1 wins";
    if (p1.sprite->hit_points <= 0) player_winner = "Player 2 wins";
    gl_draw_string(gl_get_width()/2 - gl_get_char_width() * strlen("GAME OVER") / 2,gl_get_height()/2, "GAME OVER", GL_YELLOW);
    gl_draw_string(gl_get_width()/2 - gl_get_char_width() * strlen(player_winner) / 2, gl_get_height()/2 + 20, player_winner, GL_YELLOW);
    gl_swap_buffer();
}

int gameplay_get_sprite_count(void) {
    return sprite_count;
}

void gameplay_set_sprite_count(int n) {
    sprite_count = n;
}

int is_touching_platform(player p) {
    sprite* ps = p.sprite;
    for (int i = 4; i <= 3 + number_of_platforms; i++) {
        sprite* curr = &sprites[i];
        if (ps->hit_y_top <= curr->hit_y_bottom && ps->hit_y_top >= curr->hit_y_top) {
            if (ps->hit_x_left >= curr->hit_x_left && ps->hit_x_left <= curr->hit_x_right) {
                return TOP_LEFT;
            } else if (ps->hit_x_right >= curr->hit_x_left && ps->hit_x_right <= curr->hit_x_right) {
                return TOP_RIGHT;
            }
        } else if (ps->hit_y_bottom + 5 <= curr->hit_y_bottom && ps->hit_y_bottom + 5 >= curr->hit_y_top) {
            if (ps->hit_x_left >= curr->hit_x_left && ps->hit_x_left <= curr->hit_x_right) {
                return BOTTOM_LEFT;
            } else if (ps->hit_x_right >= curr->hit_x_left && ps->hit_x_right <= curr->hit_x_right) {
                return BOTTOM_RIGHT;
            }
        }     
    }     
    return 0;
}
