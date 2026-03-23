#include "ContextSystem_NCurses.h"

#include <ncurses.h>

void initBackend( void )
{
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering, pass keys to program immediately
#ifndef DEBUG
    halfdelay( 1 ); // Waits n/10ths of a second for input
#endif
    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void deinitBackend( void )
{
    endwin(); // Restore terminal
}

