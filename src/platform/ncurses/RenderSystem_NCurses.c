#include "RenderSystem_NCurses.h"

#include "App.h"
#include "Layout.h"
#include "PlayerId.h"
#include <ncurses.h>

void renderStatic( App* const app )
{
    //* Render UI / Layout
    int const boardWidth = app->game.board.width + 3; // WARN: Temporary +3 for 8x8 default

    //* Precompute constants
    //* Sizes
    int const layoutSquareSize = (int)( sizeof( LAYOUT_BOARD_SQUARE ) / sizeof( LAYOUT_BOARD_SQUARE[0] ) ) - 1;

    int const layoutPaneHeight = (int)( sizeof( LAYOUT_INFO_PANE ) / sizeof( LAYOUT_INFO_PANE[0] ) );

    int const windowHeight = ( boardWidth * layoutSquareSize ) + 3; // Add 2x Header & 1 extra square edge

    //* Render top board header
    mvprintw(
        0,
        0,
        "%.*s",
        ( 1 + ( boardWidth * 4 ) + 1 ), // Add header; & 1 extra square edge
        LAYOUT_BOARD_HEADER_RANK
    );

    //* Render left board header
    int offsetIntoLayout = ( ( BOARD_WIDTH_MAX - boardWidth ) * layoutSquareSize ) + 1;

    for ( int y = 0; y < ( boardWidth * layoutSquareSize ); ++y )
    {
        mvprintw(
            y + 1, // Add  header
            0,
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offsetIntoLayout + y]
        );
    }

    //* Render board
    for ( int y = 0; y < boardWidth; ++y )
    {
        for ( int x = 0; x < boardWidth; ++x )
        {
            for ( int idx = 0; idx < ( layoutSquareSize + 1 ); ++idx )
            {
                mvprintw(
                    1 + ( y * ( layoutSquareSize ) ) + idx, // Add header
                    1 + ( x * ( layoutSquareSize ) ),       // Add header
                    "%s",
                    LAYOUT_BOARD_SQUARE[idx]
                );
            }
        }
    }

    //* Render top board edge
    for ( int x = 0; x < ( boardWidth * layoutSquareSize ) - 1; ++x ) // Subtract board edge
    {
        mvaddch(
            1,     // Add header
            2 + x, // Add header & board edge
            '-'
        );
    }
    //* Render left board edge
    for ( int y = 0; y < ( boardWidth * layoutSquareSize ) - 1; ++y ) // Subtract board edge
    {
        mvaddch(
            2 + y, // Add header + board edge
            1,     // Add header
            '|'
        );
    }
    //* Render right board edge
    for ( int y = 0; y < ( boardWidth * layoutSquareSize ) - 1; ++y ) // Subtract board edge
    {
        mvaddch(
            2 + y,                                 // Add header + board edge
            1 + ( boardWidth * layoutSquareSize ), // Add header
            '|'
        );
    }
    //* Render bottom board edge
    for ( int x = 0; x < ( boardWidth * layoutSquareSize ) - 1; ++x ) // Subtract square edge
    {
        mvaddch(
            1 + ( boardWidth * layoutSquareSize ), // Add header
            2 + x,                                 // Add header & board edge
            '-'
        );
    }

    //* Render info pane
    for ( int idx = 0; idx < ( layoutPaneHeight ); ++idx )
    {
        mvprintw(
            idx,
            ( boardWidth * layoutSquareSize ) + 6, // Add border & 2x header  & 1 extra square edge & 2x gap
            "%s",
            LAYOUT_INFO_PANE[idx]
        );
    }

    //* Render right board header
    for ( int y = 0; y < ( boardWidth * layoutSquareSize ); ++y )
    {
        mvprintw(
            y + 1,
            ( boardWidth * layoutSquareSize ) + 2, // Add  header + & 1 extra square edge
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offsetIntoLayout + y]
        );
    }

    //* Render bottom board header
    mvprintw(
        ( boardWidth * layoutSquareSize ) + 2, // Add header & & 1 extra square edge
        0,
        "%.*s",
        ( 1 + ( boardWidth * 4 ) + 1 ), // Add header; & 1 extra square edge,
        LAYOUT_BOARD_HEADER_RANK
    );

    //* Render separator
    mvaddch(
        0,
        ( boardWidth * layoutSquareSize ) + 4, // Add 2x header  & 1 extra square edge & gap
        '@'
    );

    for ( int y = 0; y < windowHeight - 2; ++y ) // Subtract 2x header
    {
        mvaddch(
            y + 1,                                 // Add header
            ( boardWidth * layoutSquareSize ) + 4, // Add 2x header  & 1 extra square edge & gap
            '|'
        );
    }

    mvaddch(
        windowHeight - 1,                      // Subtract header
        ( boardWidth * layoutSquareSize ) + 4, // Add 2x header  & 1 extra square edge & gap
        '@'
    );
}

void render( App* const app )
{
    renderInfoPaneContent( app );

    refresh();
}

void renderInfoPaneContent( App* const app )
{
    /// Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%i",
        app->game.players.reservesRegular[PLAYER_WHITE]
    );
}
