#include <ncurses.h>

//extern int display_size;
/*!
 * Number of processes to be displayed on the window.
 */
#define DISPLAY_SIZE 20
/*!
 * Wrapper function to initialise window with ncurses.
 */
void init_window();
/*!
 * Wrapper function to close window.
 */
void close_window();
/*!
 * Customize display according to user's key press.
 */
void customize_display(char ch);
/*!
 * Check user's input, sort the top entries accordingly and display.\n This is a wrapper for all these functions
 */
void sort_and_display(char ch, linklist *l);
