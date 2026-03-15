#include "ncursesBackend.h"

#include "Application.h"
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

Application runMainLoop( Application app )
{
    char ch = 0;

    while ( ch != 'q' )
    { // Loop until 'q' is pressed
        ch = takeInput( ch );
        updateGame();
        renderOutput( ch );
    }

    return app;
}

char takeInput( char ch )
{
    ch = getch();

    return ch;
}

void updateGame( void )
{
    clear(); // Clear previous output
}

void renderOutput( char const ch )
{
    clear(); // Clear previous output
    printw( "You pressed: %d ('%c')\n", ch, ch );
    printw( "Press keys (q to quit):\n" );
    refresh(); // Refresh screen
}
