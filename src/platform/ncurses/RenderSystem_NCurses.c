#include "RenderSystem_NCurses.h"

#include "App.h"
#include "Layout.h"
#include "PlayerId.h"
#include <ncurses.h>

void renderStatic( App* const app )
{
    int const boardWidth = app->game.board.width + 3;

    //* Precompute constants
    //* Sizes
    int const layoutSquareSize
        = (int)( sizeof( LAYOUT_BOARD_SQUARE ) / sizeof( LAYOUT_BOARD_SQUARE[0] ) ) - 1;

    int const layoutPaneSize
        = (int)( sizeof( LAYOUT_INFO_PANE ) / sizeof( LAYOUT_INFO_PANE[0] ) );

    //* Render top board border
    mvprintw(
        0,
        0,
        "%.*s",
        ( 2 + ( boardWidth * 4 ) + 1 ),
        LAYOUT_BOARD_HEADER_RANK
    );

    //* Render bottom board border
    mvprintw(
        ( boardWidth * layoutSquareSize ) + 2,
        0,
        "%.*s",
        ( 2 + ( boardWidth * 4 ) + 1 ),
        LAYOUT_BOARD_HEADER_RANK
    );

    //* Render left board border
    int offset = ( ( BOARD_WIDTH_MAX - boardWidth ) * layoutSquareSize );

    for ( int y = 0; y < ( boardWidth * layoutSquareSize ); ++y )
    {
        mvprintw(
            y,
            0,
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offset + y]
        );
    }

    //* Render right board border
    for ( int y = 0; y < ( boardWidth * layoutSquareSize ); ++y )
    {
        mvprintw(
            y,
            ( boardWidth * layoutSquareSize ) + 2,
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offset + y]
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
                    1 + ( y * ( layoutSquareSize ) ) + idx,
                    1 + ( x * ( layoutSquareSize ) ),
                    "%s",
                    LAYOUT_BOARD_SQUARE[idx]
                );
            }
        }
    }

    //* Render info pane

    for ( int idx = 0; idx < ( layoutPaneSize ); ++idx )
    {
        mvprintw(
            0 + idx,
            ( boardWidth * layoutSquareSize ) + 5,
            "%s",
            LAYOUT_INFO_PANE[idx]
        );
    }
}

void render( App* const app )
{
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%i",
        app->game.players.reservesRegular[PLAYER_WHITE]
    );

    refresh();
}

