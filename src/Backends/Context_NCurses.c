#include "BackendContext_Interface.h"

#ifdef BACKEND_NCURSES
#include "BackendLayout_NCurses.h"
#include "UI.h"
#include <assert.h>
#include <ncurses.h>

/// Color IDs 1-6 are available (BLACK = 0, WHIHTE = 7)
static int const COLOR_PLAYER_WHITE = 1;
static int const COLOR_PLAYER_BLACK = 2;
static int const COLOR_UI = 3;
static int const COLOR_INACTIVE = 4;

/// Colorpair IDs 1-6 are available (I think)
static int const COLORS_PLAYER_WHITE_STRONG = 1;
static int const COLORS_PLAYER_BLACK_STRONG = 2;
static int const COLORS_PLAYER_WHITE_WEAK = 3;
static int const COLORS_PLAYER_BLACK_WEAK = 4;
static int const COLORS_UI = 5;
static int const COLORS_INACTIVE = 6;

void setupBackend( UI* const pUI )
{
    /// Used for compatibility between backends
    assert(
        pUI
        && "Pointer is nullptr"
    );

    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering, pass keys to program immediately
    // halfdelay( 1 ); // Non-blocking: Waits n/10ths of a second for input

    /// Mouse events to listen to
    mousemask(
        BUTTON1_CLICKED,
        NULL
    );

    /// Enable colors
    start_color();
    use_default_colors();

    /// Set colors
    init_color( COLOR_BLACK, 0, 0, 0 );
    init_color( COLOR_WHITE, 1000, 1000, 1000 );

    init_color( COLOR_PLAYER_WHITE, 580, 741, 439 );
    init_color( COLOR_PLAYER_BLACK, 180, 341, 39 );
    init_color( COLOR_UI, 700, 574, 413 );
    init_color( COLOR_INACTIVE, 500, 500, 500 );

    /// Set color pairs
    init_pair( COLORS_PLAYER_WHITE_STRONG, COLOR_PLAYER_BLACK, COLOR_PLAYER_WHITE );
    init_pair( COLORS_PLAYER_BLACK_STRONG, COLOR_PLAYER_WHITE, COLOR_PLAYER_BLACK );
    init_pair( COLORS_PLAYER_WHITE_WEAK, PLAYER_COLOR_WHITE, COLOR_BLACK );
    init_pair( COLORS_PLAYER_BLACK_WEAK, PLAYER_COLOR_BLACK, COLOR_BLACK );
    init_pair( COLORS_UI, COLOR_UI, COLOR_BLACK );
    init_pair( COLORS_INACTIVE, COLOR_INACTIVE, COLOR_BLACK );

    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void closeBackend( UI const* const pUI )
{
    /// Used for compatibility between backends
    assert(
        pUI
        && "Pointer is nullptr"
    );

    reset_color_pairs();
    endwin(); // Restore terminal
}

#endif
