#include "ContextSystem_NCurses.h"

#include <ncurses.h>

void initBackend( void )
{
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering, pass keys to program immediately
    noecho();               // Don’t print typed characters automatically
    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void deinitBackend( void )
{
    endwin(); // Restore terminal
}

