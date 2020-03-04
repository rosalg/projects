  
#include "gl.h"
#include "fb.h"
#include "font.h"
#include "malloc.h"
#include "strings.h"
#include "printf.h"
#include "shell.h"



void gl_init(unsigned int width, unsigned int height, gl_mode_t mode)
{
    fb_init(width, height, 4, mode);    // use 32-bit depth always for graphics library
}

void gl_swap_buffer(void)
{
   fb_swap_buffer();
}

unsigned int gl_get_width(void)
{
   
    return fb_get_width();
}

unsigned int gl_get_height(void)
{
    return fb_get_height();
}

color_t gl_color(unsigned char r, unsigned char g, unsigned char b)
{
    //opacity = first two digits
    //red = second two digits
    //green = third two digits
    //blue = fourth two digits
    int color = 0xFF000000;
    int red = r * 65536; //Move r over to the correct place (65,536  = 16 to the power of 4)
    color = color | red; 

    int green = g * 256;   //Move g over to the correct place (256  = 16 to the power of 2)
    color = color | green; 

    color = color | b; 

    return color;
}

void gl_clear(color_t c)
{
    gl_draw_rect(0,0, gl_get_width(), gl_get_height(), c);
}

void gl_draw_pixel(int x, int y, color_t c)   
{
    if ((x > gl_get_width()) || (x < 0) || (y > gl_get_height() ) || (y < 0) ){
        //If out of bounds
    }
    else {
    unsigned int row_length = fb_get_pitch()/4; // length of each row in pixels (include any padding)
    unsigned int (*im)[row_length] = fb_get_draw_buffer(); 
    im[y][x] = c; //Set the pixel at the correct x and y to the the color c
}
}

color_t gl_read_pixel(int x, int y)
{
if ((x > gl_get_width()) || (x < 0) || (y > gl_get_height() ) || (y < 0) ){
    //If out of bounds
        return(0xF0F0F0F0); //Choose a random, unlikely to be used color to test with.
    }
    else {
    unsigned int row_length = fb_get_pitch()/4; // length of each row in pixels (include any padding)
    unsigned int (*im)[row_length] = fb_get_draw_buffer(); 
        return  im[y][x]; //im[x][y] is the color 
}
}

void gl_draw_rect(int x, int y, int w, int h, color_t c)
{
        for( int z = x; z < (w + x); z++ ){ //Set int z to start at x and move to fill each pixel 
    for( int d= y; d < (h + y); d++ ){//Set int d to start at y and move to fill each pixel 
        gl_draw_pixel(z, d, c);
    }
}
}

void gl_draw_char(int x, int y, int ch, color_t c)
{
    int length = font_get_size();
    unsigned char buf[length];
    int buf_pos = 0; 
    if (font_get_char(ch, buf, length)){
        for (int i = 0; i < font_get_height(); i ++){
            for (int j = 0; j < font_get_width(); j++){
                if (buf[buf_pos] != 0){
                 gl_draw_pixel(x + j, y + i, c);
                }
                buf_pos++;
            }
        }
    }
}

void gl_draw_string(int x, int y, const char* str, color_t c)
{
    int original_x = x;
    int height = gl_get_char_height();
    int width = gl_get_char_width();


     for (int i = 0; i < strlen(str); i ++){
        gl_draw_char(x, y, str[i], c);
        x += width;
    if ( (x + width) > fb_get_width()){ //move to next line
        y +=height;
        x = original_x;
    }
     }
}

unsigned int gl_get_char_height(void)
{
    return font_get_height();
}

unsigned int gl_get_char_width(void)
{
    return font_get_width();
}

// void gl_draw_line(int x1, int y1, int x2, int y2, color_t c){
// int y = 0;
//     for(int i = x1; i <= x2; i++){ //Cycle through the x values
//         y = (y2 - y1) + y1  * (i - x1)/(x2 -x1); //Calculate the value of Y using the naive line equation
//         gl_draw_pixel(i, y, c);
//     }

// }
