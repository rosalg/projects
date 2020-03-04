#include "assert.h"
#include "console.h"
#include "fb.h"
#include "gl.h"
#include "printf.h"
#include "strings.h"
#include "timer.h"
#include "uart.h"


#define _WIDTH 640
#define _HEIGHT 512

#define _NROWS 30
#define _NCOLS 20

void test_fb(void)
{
    fb_init(700, 700, 4, FB_SINGLEBUFFER);
    printf("Frame buffer pitch is %d\n", fb_get_pitch());
    assert(fb_get_height() == 700); //Check functioning of get height
    assert(fb_get_width() == 700); //Check functioning of get width
    unsigned char *cptr3 = fb_get_draw_buffer(); //Test drawing in singlebuffer
    int nbytes3 = fb_get_pitch()*fb_get_height();
    memset(cptr3, 0x99, nbytes3); // fill entire framebuffer with light gray pixels
    timer_delay(3);


    fb_init(700, 700, 4, FB_DOUBLEBUFFER);
    unsigned char *cptr = fb_get_draw_buffer(); //Test first buffer of a double buffer
    int nbytes = fb_get_pitch()*fb_get_height();
    memset(cptr, 0x000000FF, nbytes); // fill entire framebuffer with white pixels
    timer_delay(3);
    

     fb_swap_buffer(); //Test other buffer of double buffer
    unsigned char *cptr2 = fb_get_draw_buffer();
    int nbytes2 = fb_get_pitch()*fb_get_height();
    memset(cptr2, 0x99, nbytes2); // fill entire framebuffer with light gray pixels
    timer_delay(3);
 }

void test_gl(void)
{
    // Double buffer mode, make sure you test single buffer too!
    gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER);

   // gl_init(_WIDTH, _HEIGHT, GL_SINGLEBUFFER);// Test with singlebuffer


   assert(gl_get_height() == _HEIGHT); //Check functioning of get height
   assert(gl_get_width() == _WIDTH); //Check functioning of get width


    //Test color
    assert(gl_color(0xFF, 0xFF, 0xFF) == 0xFFFFFFFF);


    // Background is yellow, test clear and color
    gl_clear(gl_color(0xFF, 0xFF, 0x00));
    //gl_swap_buffer();

    // Draw green pixel at an arbitrary spot
    gl_draw_pixel(_WIDTH/3, _HEIGHT/3, GL_GREEN);
    assert(gl_read_pixel(_WIDTH/3, _HEIGHT/3) == GL_GREEN);
    timer_delay(3);

    gl_draw_pixel(_WIDTH +1, _HEIGHT/3, GL_GREEN); // Checking upper limit of x
    assert(gl_read_pixel(_WIDTH +1, _HEIGHT/3) == 0xF0F0F0F0); //Returns rare color if out of bounds
    gl_draw_pixel(_WIDTH/3, _HEIGHT+1, GL_GREEN); //Checking upper limit of y
    assert(gl_read_pixel(_WIDTH +1, _HEIGHT/3) == 0xF0F0F0F0);
    gl_draw_pixel(_WIDTH/3, -1, GL_GREEN); //Check to prevent pixel from being drawn below zero (y)
     assert(gl_read_pixel(_WIDTH/3, -1) == 0xF0F0F0F0);
    gl_draw_pixel(-1, 1, GL_GREEN); //Check to prevent pixel from being drawn below zero (x)
    assert(gl_read_pixel(-1, 1) == 0xF0F0F0F0);



    // Black derp face with rectangles
    gl_draw_rect(_WIDTH/2 - 100, _HEIGHT/2 - 100, 10, 10, GL_BLACK);
    gl_draw_rect(_WIDTH/2 + 100, _HEIGHT/2 -  100, 10, 10, GL_BLACK);
    gl_draw_rect(_WIDTH/2 - 100, _HEIGHT/2, 210, 10, GL_BLACK);
    timer_delay(3);



    // Single amber character
    gl_draw_char(60, 10, 'A', GL_AMBER);

    //Test clipping
    gl_draw_char(-5, 10, 'B', GL_AMBER);

    //Test bad character
    gl_draw_char(-5, 10, '\b', GL_AMBER);

    gl_draw_string(50, 100, "The rain in spain stays mainly in the plane. But typhoons on the moon are coming for us soon. ", GL_RED);


    gl_draw_line( 10,  10,  50,  150, GL_RED); //Test a line



    // Show buffer with drawn contents
    gl_swap_buffer();
    timer_delay(3);
}

void test_console(void)
{
    console_init(_NROWS, _NCOLS);
    //gl_init(_WIDTH, _HEIGHT, GL_SINGLEBUFFER); //Initialize buffer - single. Uncomment and comment doublebuffer to test
     gl_init(_WIDTH, _HEIGHT, GL_DOUBLEBUFFER); //Initialize double buffer

  // 1: "HELLO WORLD"


   console_printf("HELLO WORLD\r");
   // 1: "HAPPY WORLD"
   // 2: "CODING"
   console_printf("HAPPY\nCODING\n");
  
   // 1: "Goodbye"
    console_printf("Goodbye!\n");
    gl_swap_buffer();
    timer_delay(3);


     // Clear
    console_printf("\f");
 


    //Test horizontal wrapping and stopping at the correct row
    console_printf(" Add tests to test your graphics library and console.  Add tests to test your graphics library and console.  Add tests to test your graphics library and console. Add tests to test your graphics library and console.  Add tests to test your graphics library and console. Add tests to test your graphics library and console. Add tests to test your graphics library and console. Add tests to test your graphics library and console. ");
    gl_swap_buffer();
    timer_delay(3);
   
    timer_delay(3);




}

/* TODO: Add tests to test your graphics library and console.
   For the graphics library, test both single & double
   buffering and confirm all drawing is clipeed to bounds
   of framebuffer
   For the console, make sure to test wrap-around and scrolling.
   Be sure to test each module separately as well as in combination
   with others.
*/

void main(void)
{
    uart_init();
    timer_init();
    printf("Executing main() in test_gl_console.c\n");

    //test_fb();
     test_gl();
     //test_console();

    printf("Completed main() in test_gl_console.c\n");
    uart_putchar(EOT);
}
