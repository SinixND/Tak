#include "ContextSystem.h"

#ifdef BACKEND_NCURSES
#include <ncurses.h>

void setupBackend( void )
{
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering, pass keys to program immediately
    // halfdelay( 1 ); // Non-blocking: Waits n/10ths of a second for input
    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void closeBackend( void )
{
    endwin(); // Restore terminal
}

#endif