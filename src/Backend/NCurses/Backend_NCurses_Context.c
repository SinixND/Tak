#include "BackendInterface.h"

#ifdef BACKEND_NCURSES
#include "Backend_NCurses_Layout.h"
#include <ncurses.h>

void setupBackend( void )
{
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering, pass keys to program immediately
    // halfdelay( 1 ); // Non-blocking: Waits n/10ths of a second for input

    /// Enable colors
    start_color();
    use_default_colors();
    init_color( COLOR_BLACK, 0, 0, 0 );
    init_color( COLOR_WHITE, 1000, 1000, 1000 );
    init_color( PLAYER_COLOR_WHITE, 700, 574, 413 );
    init_color( PLAYER_COLOR_BLACK, 486, 278, 0 );
    init_color( LAYOUT_COLOR, 380, 541, 239 );
    init_pair( CPAIR_WHITE_1, PLAYER_COLOR_BLACK, PLAYER_COLOR_WHITE );
    init_pair( CPAIR_BLACK_1, PLAYER_COLOR_WHITE, PLAYER_COLOR_BLACK );
    init_pair( CPAIR_WHITE_2, PLAYER_COLOR_WHITE, COLOR_BLACK );
    init_pair( CPAIR_BLACK_2, PLAYER_COLOR_BLACK, COLOR_BLACK );
    init_pair( CPAIR_LAYOUT, LAYOUT_COLOR, COLOR_BLACK );

    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void closeBackend( void )
{
    reset_color_pairs();
    endwin(); // Restore terminal
}

#endif
