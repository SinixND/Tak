#include "BackendInterface.h"
#include "FileId.h"

#ifdef BACKEND_NCURSES
#include "Backend_NCurses_Layout.h"
#include <assert.h>
#include <ncurses.h>

Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize
)
{
    Tile tile = { FILE_NONE, RANK_NONE };

    if (
        ( ( (int)mouseX - ( BOARD_POS_X + 1 ) ) % 4 )
        && ( (int)mouseY - BOARD_POS_Y ) % 4
    )
    {
        tile.fileX
            = ( (int)mouseX - ( BOARD_POS_X + 1 ) ) / 4;

        tile.rankY
            = ( boardSize - 1 ) - ( ( (int)mouseY - 1 ) / 4 );
    }

    return tile;
}

void setupBackend( UIData* const pUIData )
{
    /// Used for compatibility between backends
    assert(
        pUIData
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
    init_color( COLOR_BLACK, 0, 0, 0 );
    init_color( COLOR_WHITE, 1000, 1000, 1000 );
    // init_color( PLAYER_COLOR_WHITE, 700, 574, 413 );
    // init_color( PLAYER_COLOR_BLACK, 486, 278, 0 );
    // init_color( LAYOUT_COLOR, 380, 541, 239 );
    init_color( PLAYER_COLOR_WHITE, 580, 741, 439 );
    init_color( PLAYER_COLOR_BLACK, 180, 341, 39 );
    init_color( LAYOUT_COLOR, 700, 574, 413 );
    init_color( HIGHLIGHT_COLOR, 500, 500, 500 );
    init_pair( CPAIR_FGB_BGW, PLAYER_COLOR_BLACK, PLAYER_COLOR_WHITE );
    init_pair( CPAIR_FGW_BGB, PLAYER_COLOR_WHITE, PLAYER_COLOR_BLACK );
    init_pair( CPAIR_FGW, PLAYER_COLOR_WHITE, COLOR_BLACK );
    init_pair( CPAIR_FGB, PLAYER_COLOR_BLACK, COLOR_BLACK );
    init_pair( CPAIR_LAYOUT, LAYOUT_COLOR, COLOR_BLACK );
    init_pair( CPAIR_HIGHLIGHT, HIGHLIGHT_COLOR, COLOR_BLACK );

    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void closeBackend( UIData const* const pUIData )
{
    /// Used for compatibility between backends
    assert(
        pUIData
        && "Pointer is nullptr"
    );

    reset_color_pairs();
    endwin(); // Restore terminal
}

#endif
