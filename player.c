#include "controller.h"
#include "gpio.h"
#include "timer.h"
#include "gl.h"
#include "fb.h"

static int x_pos = 0;
static int y_pos = 0;
static int width = 0;
static int height = 0;

void player_init() {
    //gl_init(c_w, c_h, GL_DOUBLEBUFFER);
    x_pos = x;
    y_pos = y;
    width = w;
    height= h;
    //gl_draw_rect(x, y, w, h, GL_RED);
    //gl_swap_buffer();
}

void player_move(int x, int y) {
    // In actual implementation, we'll probably wanna just
    // wanna redraw the background.
    gl_draw_rect(x_pos. y_pos, width, height, GL_BLACK);
    x_pos += x;
    y_pos += y;
    // Draw background
    gl_draw_rect(x_pos, y_pos, width, height, GL_RED);
    gl_swap_buffer();
}
