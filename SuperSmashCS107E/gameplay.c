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
    p1.con_num = 1;
    p1.sprite = &sprites[0];
    p1.color_num = 4;
    p2.con_num = 2;
    p2.sprite = &sprites[1];
    p2.color_num = 4;


    p1.sprite->base_color = GL_BLUE;
    p2.sprite->base_color = GL_RED;
    
    p1.sprite->sprite_num = 0;
    p2.sprite->sprite_num = 0; 
    character_select();
     
    
    int width = gl_get_width();
    int height = gl_get_height();
    gl_draw_background(GL_PURPLE);
    gl_swap_buffer();
    gl_draw_background(GL_PURPLE);

    sprite_count = NUMBER_OF_PLAYERS;

    // Set up player 1's sprite
    make_sprite(p1.con_num, p1.sprite->sprite_num, 100, height - 100, RIGHT);
    
    
    // Set up player 2's sprite
    make_sprite(p2.con_num, p2.sprite->sprite_num, width, height - 100,  LEFT);
    
    
    GROUND = gl_get_height() - 105;
    

    make_platforms(gl_get_width()/2 - 100, gl_get_height()/2 - 3, 200, 10, GL_PURPLE);
    //make_platforms(gl_get_width()/2 + 100, gl_get_height()/2 - 3, 200, 10, GL_PURPLE);
    
    player_init(sprite_count, p1.sprite, p2.sprite);
}

void character_select() {
    char *str0 = "CHARACTER SELECT";
    char *str1 = "Press A & X together to select character";
    char *str2 = "Press B & X together to deselect character";
    char *str3 = "Press L & R to cycle between colors";
    char *start_str = "Press START to begin";
    int y = gl_get_char_height();
    gl_draw_string(gl_get_width()/4 - strlen("Player 1") * gl_get_char_width()/2, 260, "Player 1", GL_GREEN);
    gl_draw_string(3 * gl_get_width() / 4 - strlen("Player 2") * gl_get_char_width() / 2, 260, "Player 2", GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str0) * gl_get_char_width()/2, 0, str0, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str1) * gl_get_char_width()/2, y * 2, str1, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str2) * gl_get_char_width()/2, y * 3, str2, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str3) * gl_get_char_width()/2, y * 4, str3, GL_GREEN);
    gl_draw_rect(0, 260 + gl_get_char_height(), gl_get_width()/2, gl_get_height() - 260 - gl_get_char_height(), GL_BLUE);
    gl_draw_rect(gl_get_width() / 2, 260 + gl_get_char_height(), gl_get_width()/2, gl_get_height() - 260 - gl_get_char_height(), GL_RED);
    gl_swap_buffer();
    gl_draw_string(gl_get_width()/4 - strlen("Player 1") * gl_get_char_width()/2, 260, "Player 1", GL_GREEN);
    gl_draw_string(3 * gl_get_width() / 4 - strlen("Player 2") * gl_get_char_width() / 2, 260, "Player 2", GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str0) * gl_get_char_width()/2, 0, str0, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str1) * gl_get_char_width()/2, y * 2, str1, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str2) * gl_get_char_width()/2, y * 3, str2, GL_GREEN);
    gl_draw_string(gl_get_width()/2 - strlen(str3) * gl_get_char_width()/2, y * 4, str3, GL_GREEN);
    gl_draw_rect(0, 260 + gl_get_char_height(), gl_get_width()/2, gl_get_height() - 260 - gl_get_char_height(), GL_BLUE);
    gl_draw_rect(gl_get_width() / 2, 260 + gl_get_char_height(), gl_get_width()/2, gl_get_height() - 260 - gl_get_char_height(), GL_RED); 
    sprites[0].x = gl_get_width()/2;
    sprites[1].x = gl_get_width()/2;
    sprites[0].y = gl_get_height()/2;
    sprites[1].y = gl_get_height()/2;
    sprites[0].vel_x = 0;
    sprites[1].vel_x = 0;
    sprites[0].vel_y = 0;
    sprites[1].vel_y = 0;
    sprites[0].base_color = 0;
    sprites[1].base_color = 0;
    while(p1.sprite->base_color == 0 || p2.sprite->base_color == 0 || p1.sprite->sprite_num == 0 || p2.sprite->sprite_num == 0 ||
            (controller_get_START(p1.con_num) == 0 && controller_get_START(p2.con_num) == 0))
   
    {
        int x_pos = 270;
        int y_pos = 135;
        int square_num = 0;
        for (int i = 0; i < 2; i++) {
                gl_draw_rect(x_pos + i * 50, y_pos, 50, 90, 0xFFA9A9A9);
                if (i) {
                    gl_draw_circle_sprite(x_pos+75, y_pos+45, BALL_RADIUS, EYE_RADIUS, GL_BLACK); 
                } else {
                    gl_draw_box(x_pos+25-BOX_WIDTH/2, y_pos+45-BOX_HEIGHT/2-BOX_FEET_RADIUS/2, BOX_WIDTH, BOX_FEET_RADIUS, GL_BLACK);
                }
                square_num++;
        }
        update_menu(p1);
        update_menu(p2);
        draw_cursor(&p1, GL_BLUE);
        draw_cursor(&p2, GL_RED);
        if (p1.sprite->sprite_num != 0 && p2.sprite->sprite_num != 0) { 
            gl_draw_string(gl_get_width()/2-gl_get_char_width()*strlen(start_str)/2, y_pos + 100, start_str, GL_GREEN);
        } else {
            gl_draw_rect(gl_get_width()/2-gl_get_char_width()*strlen(start_str)/2, y_pos + 100, gl_get_char_width()*strlen(start_str), gl_get_char_height(), GL_BLACK);
        }
        gl_swap_buffer();
    }
    gl_clear(GL_BLACK);
    gl_swap_buffer();
    gl_clear(GL_BLACK);
}

void draw_cursor(player* p, color_t color) {
    color_t colors[10]; 
    colors[0] = GL_RED; colors[1] = GL_GREEN; colors[2] = GL_BLUE; colors[3] = GL_CYAN; colors[4] = GL_MAGENTA;
    colors[5] = GL_YELLOW; colors[6] = GL_AMBER; colors[7] = GL_ORANGE; colors[8] = GL_PURPLE; colors[9] = GL_INDIGO;
    
    sprite* s = p->sprite;
    if (s->x + s->vel_x + CURSOR_RADIUS < 370 && s->x + s->vel_x - CURSOR_RADIUS > 270) {
        if (s->y + s->vel_y + CURSOR_RADIUS < 225 && s->y + s->vel_y - CURSOR_RADIUS > 135) {
            s->x += s->vel_x;
            s->y += s->vel_y;
         }
    }

    if (controller_get_A(p->con_num) && controller_get_X(p->con_num)) {
        if (s->x > 270 && s->x < 320) {
            s->sprite_num = BOX;
        } else {
            s->sprite_num = BALL;
        }
    }
   
    if (controller_get_L(p->con_num)) {
        if (p->color_num > 0) {
            p->color_num = p->color_num - 1;
        } else {
            p->color_num = 9;
        }
    } else if (controller_get_R(p->con_num)) {
        if (p->color_num < 9) {
            p->color_num++;
        } else {
            p->color_num = 0;
        }
    }

    if (s->sprite_num != 0) {
        if (p->con_num == 1) {
            if (s->sprite_num == BOX) {
                gl_draw_rect(gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_BLUE);
                gl_draw_box(gl_get_width()/4 - BOX_WIDTH/2, 260 + gl_get_char_height() + 25, BOX_WIDTH, BOX_FEET_RADIUS, colors[p->color_num]);
            } else {
                gl_draw_rect(gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_BLUE);
                gl_draw_circle_sprite(gl_get_width()/4, 260 + gl_get_char_height() + 45, BALL_RADIUS, EYE_RADIUS, colors[p->color_num]);  
            }
        } else {
           if (s->sprite_num == BOX) {
                gl_draw_rect(3*gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_RED);
                gl_draw_box(gl_get_width()*3/4 - BOX_WIDTH/2, 260 + gl_get_char_height() + 25, BOX_WIDTH, BOX_FEET_RADIUS, colors[p->color_num]);
           } else {  
                gl_draw_rect(3*gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_RED);
                gl_draw_circle_sprite(3*gl_get_width()/4, 260 + gl_get_char_height() + 45, BALL_RADIUS, EYE_RADIUS, colors[p->color_num]);  
           }
        }
        s->base_color = colors[p->color_num];
    } 

    if (controller_get_B(p->con_num) && controller_get_X(p->con_num)) {
        s->sprite_num = 0;
        if (p->con_num == 1) gl_draw_rect(gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_BLUE);
        if (p->con_num == 2) gl_draw_rect(3*gl_get_width()/4 - BALL_RADIUS, 260 + gl_get_char_height() + 25, 50, 50, GL_RED);
    }

    gl_draw_circle(s->x, s->y, 5, GL_BLACK);
    gl_draw_circle(s->x, s->y, 4, color);
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

void make_sprite(int p_num, int sprite_number, int x_start, int y_start, int direc) {
    int sprite_height = BOX_HEIGHT + BOX_FEET_RADIUS + 5;
    int sprite_width = BOX_WIDTH;
    if (sprite_number == BALL) {
        sprite_height = BALL_RADIUS * 2 + 5;
        sprite_width = BALL_RADIUS * 2;
    }
    sprite* player = &sprites[p_num - 1];
    player->x = x_start - sprite_width;
    player->y = y_start - sprite_height;
    player->is_grounded = 1;
    player->is_jumping = 0;
    
    player->is_firing = 0;
    player->direction = direc;
    player->proj_sprite_num = p_num + NUMBER_OF_PLAYERS - 1;
    player->proj_cooldown = 0;

    player->is_shielding = 0;
    player->is_stunned = 0;
    player->shield_timer = SHIELD_TIME;
    
    player->is_punching = 0;
    player->knockback_timer = 0;

    player->vel_x = 0;
    player->vel_y = 0;
    player->color = player->base_color;
    if (sprite_number == BOX) {
        player->hit_points = 100; 
        player->hit_x_left = player->x;
        player->hit_x_right = player->x + BOX_WIDTH;
        player->hit_y_top = player->y;
        player->hit_y_bottom = player->y + BOX_WIDTH + BOX_FEET_RADIUS;
        player->height = BOX_HEIGHT + BOX_FEET_RADIUS;
    } else if (sprite_number == BALL) {
        player->hit_points = 100;
        player->hit_x_left = player->x - BALL_RADIUS;
        player->hit_x_right = player->x + BALL_RADIUS;
        player->hit_y_top = player->y - BALL_RADIUS;
        player->hit_y_bottom = player->y + BALL_RADIUS;
        player->height = BALL_RADIUS * 2;
    }
}

void main(void)
{
    uart_init();
    timer_init();
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER);
    controller_init(21, 20);
    while (1) {
        gameplay_init();
        play_game(); 
        timer_delay(5);
        gl_clear(GL_BLACK);
        gl_swap_buffer();
        gl_clear(GL_BLACK);
    }
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
    countdown();
    while(1) {
        update(p1);
        if (NUMBER_OF_PLAYERS >= 2) {
            update(p2); 
        }
        player_move(sprites);
        redraw_platforms();
        if (p1.sprite->hit_points <= 0 || p2.sprite->hit_points <= 0) {
            end_game();
            break;
        }
    }
    
}

void update(player p) {
    controller_poll(p.con_num);
    update_gravity(p);
    if (p.sprite->knockback_timer > 0) {
        p.sprite->is_stunned = 0;
        p.sprite->shield_timer = SHIELD_TIME;
        p.sprite->vel_x = 10 * p.sprite->direction;
        p.sprite->vel_y = -10;
        p.sprite->knockback_timer--;
        return;
    }
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
    if (controller_get_A(p.con_num) && 
            p.sprite->is_firing == 0 && 
            (controller_get_JOYSTICK_X(p.con_num) == 119 || controller_get_JOYSTICK_X(p.con_num) == 8) 
            && (p.sprite->proj_cooldown == 0) 
            && p.sprite->is_shielding == 0) 
    {
        p.sprite->proj_cooldown = PROJ_COOLDOWN;
        sprite* fire = &sprites[p.sprite->proj_sprite_num];
        fire->sprite_num = FIRE;
        fire->owner = p.sprite;
        fire->hit = 0;
        player_projectile(p.sprite, fire);
    } else if (p.sprite->proj_cooldown > 0) {
        p.sprite->proj_cooldown--;
    }

    if ((controller_get_X(p.con_num) || controller_get_JOYSTICK_Y(p.con_num) == 119) 
            && p.sprite->is_grounded == 1) {
        player_jump(p.sprite);
    }
    // Update punch
    if (controller_get_CSTICK_X(p.con_num) == 119) {
        p.sprite->direction = RIGHT;
    } else if (controller_get_CSTICK_X(p.con_num) == 8) {
        p.sprite->direction = LEFT;
    }
    if ((controller_get_CSTICK_X(p.con_num) == 119 || controller_get_CSTICK_X(p.con_num) == 8) && 
            p.sprite->is_punching == 0 && 
            p.sprite->is_shielding == 0) 
    {
        update_punch(p);
    } else if (p.sprite->is_punching > 0) {
        p.sprite->is_punching--;
    }
}

void update_menu(player p) {
    controller_poll(p.con_num);
    if (controller_get_JOYSTICK_X(p.con_num) == 119) {
        p.sprite->vel_x = 5;
    } else if (controller_get_JOYSTICK_X(p.con_num) == 8) {
        p.sprite->vel_x = -5;
    } else {
        p.sprite->vel_x = 0;
    }
    if (controller_get_JOYSTICK_Y(p.con_num) == 119) {
        p.sprite->vel_y = -5;
    } else if (controller_get_JOYSTICK_Y(p.con_num) == 8) {
        p.sprite->vel_y = 5;
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
            ( ((0xFF&(p.sprite->base_color>>16)) * p.sprite->shield_timer/SHIELD_TIME) << 16)|
            ( ((0xFF&(p.sprite->base_color>>8)) * p.sprite->shield_timer/SHIELD_TIME) << 8)|
            ((0xFF&(p.sprite->base_color)) * p.sprite->shield_timer/SHIELD_TIME);
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

void update_punch(player p) {
    p.sprite->is_punching = PUNCH_COOLDOWN; 
    if (p.con_num == 1) {
        if (player_punch(p.sprite, p2.sprite)) {
            p2.sprite->hit_points -= PUNCH_DAMAGE;
            player_redraw_health_bar(gl_get_width() - 100, 0, gl_get_width() - p2.sprite->hit_points, 0, sprites[1]);
            p2.sprite->knockback_timer = PUNCH_KNOCKBACK_TIME;
            p2.sprite->direction = p1.sprite->direction;
        }
    } else {
        if (player_punch(p.sprite, p1.sprite)) {
            p1.sprite->hit_points -= PUNCH_DAMAGE;
            player_redraw_health_bar(0, 0, 0, 0, sprites[0]);
            p1.sprite->knockback_timer = PUNCH_KNOCKBACK_TIME;
            p1.sprite->direction = p2.sprite->direction;
        }
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
