  
#include "gl_kyl.h"
#include "fb.h"
#include "font.h"
#include "malloc.h"
#include "strings.h"
#include "printf.h"
#include "shell.h"

// static volatile sprite box; 
// static sprite ball;
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


// Function to put pixels at points in each octant
// //Use bessemer's algorithm, algorithm/basic code explained here: https://en.wikipedia.org/wiki/Midpoint_circle_algorithm, https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

void eight_points_circle(int xc, int yc, int x, int y, color_t c) 
{ 
    gl_draw_pixel(xc+x, yc+y, c); 
    gl_draw_pixel(xc-x, yc+y, c); 
    gl_draw_line((xc-x), (yc+y), (xc+x), (yc+y), c); //Use draw line to fill in the circle (original code)
    gl_draw_pixel(xc+x, yc-y, c); 
    gl_draw_pixel(xc-x, yc-y, c); 
    gl_draw_line(xc-x, yc-y, xc+x, yc-y, c);
    gl_draw_pixel(xc+y, yc+x, c); 
    gl_draw_pixel(xc-y, yc+x, c); 
    gl_draw_line(xc-y, yc+x, xc+y, yc+x, c);
    gl_draw_pixel(xc+y, yc-x, c); 
    gl_draw_pixel(xc-y, yc-x, c); 
    gl_draw_line(xc-y, yc-x, xc+y, yc-x, c);

} 
  
// Function for circle-generation 
// using Bresenham's algorithm 
void gl_draw_circle(int xc, int yc, int r, color_t c)
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    eight_points_circle(xc, yc, x, y, c); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        eight_points_circle(xc, yc, x, y, c); 
    } 
} 

// void gl_draw_sprites(int box_move, int ball_move){
//     int width = gl_get_width();
//     int height = gl_get_height();
//     gl_draw_rect(0, height- 200, width, 100, GL_BLACK); //Cover any previous sprites with a black rectangle
//     //Set up and draw the box
//     int box_radius = 80;
//     int wheel_radius = 15;
//     box.hit_points = 100; 
//     if((width/4 + box_move) > 0 && (width/4 + box_move) < (width -box_radius)){ //If the movement doesn't move the box out of bounds
//     box.x = width/4 + box_move; //Starting position = width/4, as player hits buttons the sprite moves
//     } 
//     box.y = height - 200;
//     box.hit_x_left = box.x;
//     int hit_x_right = box.x + box_radius;
//     int hit_y_top = box.y;
//     int hit_y_bottom = box.y + box_radius + wheel_radius;
//     gl_draw_box(box.x, box.y, box_radius, wheel_radius); //Draw the box
    
//     //set up and draw the ball 
//     int ball_radius = 50; 
//     int eye_radius = 5; 
//     ball.hit_points = 100;
//     if((width - (width/4 + 65) + ball_move) > 0 && (width - (width/4 + 65) + ball_move) < (width - ball_radius)){ //If the movement doesn't move the ball out of bounds, then move the ball
//     ball.x = width - (width/4 + 65) + ball_move; //As player hits buttons the sprite moves by ball_move amount
//    }
//     ball.y = height - 150; 
//     ball.hit_x_left = ball.x - ball_radius/2;
//     ball.hit_x_right = ball.x + ball_radius/2;
//     ball.hit_y_top = ball.y + ball_radius/2;
//     ball.hit_y_bottom = ball.y - ball_radius/2;
//     gl_draw_circle_sprite(ball.x, ball.y, ball_radius, eye_radius); //Draw the ball
// }
// void gl_draw_circle_sprite(int x, int y, int circle_r, int eye_r){
//     gl_draw_circle(x, y, circle_r, GL_ORANGE);
//     gl_draw_circle(x - 15, y - 15, eye_r, GL_BLACK);
//     gl_draw_circle(x + 15, y - 15, eye_r, GL_BLACK);
// }

// void gl_draw_box(int x, int y, int box_r, int wheel_r){
//     gl_draw_circle(x + wheel_r, y + box_r, wheel_r, GL_WHITE);
//     gl_draw_circle(x + (wheel_r*4), y + box_r, wheel_r, GL_WHITE);
//     gl_draw_rect(x, y, box_r, box_r, GL_BLUE);
// }

// bool sprites_hit(){
//     if((ball.hit_y_top <= box.hit_y_top) && (ball.hit_y_bottom >= box.hit_y_bottom)){
//         if (box.hit_x_right >= ball.hit_x_right >= box.hit_x_left || box.hit_x_right >= ball.hit_x_left >= box.hit_x_left){
//             return true;
//         }
// }
// else {
//     return false;
// }
// }

// void box_hit(){
//     box.hit_points -= 10;
// }
// void ball_hit(){
//     ball.hit_points -=10;
// }

void gl_draw_background(color_t platform, color_t trunk, color_t trees){
    int tree_width = 10; 
    int width = gl_get_width();
    gl_draw_rect(0, gl_get_height() - 100, width, 50, platform); //The platform
    gl_draw_rect(width/6, 112, tree_width, 300, trunk); //Set a tree trunk at one end of the platform
    gl_draw_rect(width - width/6, 112, tree_width, 300, trunk); //Set a tree trunk at the other end of the platform
    gl_draw_circle(width/6 + tree_width/2, 112, 50, trees);
    gl_draw_circle((width - width/6) + tree_width/2, 112, 50, trees);

}

unsigned int gl_get_char_height(void)
{
    return font_get_height();
}

unsigned int gl_get_char_width(void)
{
    return font_get_width();
}

void gl_draw_line(int x1, int y1, int x2, int y2, color_t c){
    //Use algorithm from https://en.wikipedia.org/wiki/Line_drawing_algorithm
    // code from https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
    int m_new = 2 * (y2 - y1); 
   int slope_error_new = m_new - (x2 - x1); 
   for (int x = x1, y = y1; x <= x2; x++) 
   {   
        gl_draw_pixel(x, y, c);
      // Add slope to increment angle formed 
      slope_error_new += m_new; 
  
      // Slope error reached limit, time to 
      // increment y and update slope error. 
      if (slope_error_new >= 0) 
      { 
         y++; 
         slope_error_new  -= 2 * (x2 - x1); 
      } 
   } 

}
