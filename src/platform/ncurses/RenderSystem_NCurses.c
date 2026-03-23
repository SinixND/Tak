#include "RenderSystem_NCurses.h"

#include "App.h"
#include "Layout.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <assert.h>
#include <ncurses.h>

void renderStatic( App* const app )
{
    int const boardWidth = app->game.board.width;

    //* Render info pane
    for ( int idx = 0; idx < ( LAYOUT_PANE_HEIGHT ); ++idx )
    {
        mvprintw(
            idx,
            0,
            "%s",
            LAYOUT_INFO_PANE[idx]
        );
    }

    //* Render top board header
    mvprintw(
        0,
        BOARD_OFFSET,
        "%.*s",
        ( 1 + ( boardWidth * 4 ) + 1 ), // Add header; & 1 extra square edge
        LAYOUT_BOARD_HEADER_RANK
    );

    //* Render left board header
    int offsetIntoLayout = ( ( BOARD_WIDTH_MAX - boardWidth ) * LAYOUT_BOARD_SQUARE_SIZE ) + 1;

    for ( int y = 0; y < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            y + 1, // Add  header
            BOARD_OFFSET,
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offsetIntoLayout + y]
        );
    }

    //* Render board
    for ( int y = 0; y < boardWidth; ++y )
    {
        for ( int x = 0; x < boardWidth; ++x )
        {
            for ( int idx = 0; idx < ( LAYOUT_BOARD_SQUARE_SIZE + 1 ); ++idx )
            {
                mvprintw(
                    1 + ( y * ( LAYOUT_BOARD_SQUARE_SIZE ) ) + idx,          // Add header
                    BOARD_OFFSET + 1 + ( x * ( LAYOUT_BOARD_SQUARE_SIZE ) ), // Add header
                    "%s",
                    LAYOUT_BOARD_SQUARE[idx]
                );
            }
        }
    }

    //* Render top board edge
    for ( int x = 0; x < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x ) // Subtract board edge
    {
        mvaddch(
            1,                    // Add header
            BOARD_OFFSET + 2 + x, // Add header & board edge
            '-'
        );
    }
    //* Render left board edge
    for ( int y = 0; y < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y ) // Subtract board edge
    {
        mvaddch(
            2 + y,            // Add header + board edge
            BOARD_OFFSET + 1, // Add header
            '|'
        );
    }
    //* Render right board edge
    for ( int y = 0; y < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y ) // Subtract board edge
    {
        mvaddch(
            2 + y,                                                        // Add header + board edge
            BOARD_OFFSET + 1 + ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ), // Add header
            '|'
        );
    }
    //* Render bottom board edge
    for ( int x = 0; x < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x ) // Subtract square edge
    {
        mvaddch(
            1 + ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ), // Add header
            BOARD_OFFSET + 2 + x,                          // Add header & board edge
            '-'
        );
    }

    //* Render right board header
    for ( int y = 0; y < ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            y + 1,
            BOARD_OFFSET + ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) + 2, // Add  header + & 1 extra square edge
            "%s",
            LAYOUT_BOARD_HEADER_FILE[offsetIntoLayout + y]
        );
    }

    //* Render bottom board header
    mvprintw(
        ( boardWidth * LAYOUT_BOARD_SQUARE_SIZE ) + 2, // Add header & & 1 extra square edge
        BOARD_OFFSET,
        "%.*s",
        ( 1 + ( boardWidth * 4 ) + 1 ), // Add header; & 1 extra square edge,
        LAYOUT_BOARD_HEADER_RANK
    );
}

void renderDynamic( App* const app )
{
    renderInfoPaneContent( app );
    renderStackBuffer( app );
    renderSquare( app );

    refresh();
}

void renderInfoPaneContent( App* const app )
{
    //* Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%2i",
        app->game.players.reservesRegular[PLAYER_WHITE]
    );

    //* Print white capston reserves
    mvprintw(
        POSITION_WHITE_RESERVES_CAPSTONE[0],
        POSITION_WHITE_RESERVES_CAPSTONE[1],
        "%i",
        app->game.players.reservesCapstone[PLAYER_WHITE]
    );

    //* Print black regular reserves
    mvprintw(
        POSITION_BLACK_RESERVES_REGULAR[0],
        POSITION_BLACK_RESERVES_REGULAR[1],
        "%2i",
        app->game.players.reservesRegular[PLAYER_BLACK]
    );

    //* Print black capston reserves
    mvprintw(
        POSITION_BLACK_RESERVES_CAPSTONE[0],
        POSITION_BLACK_RESERVES_CAPSTONE[1],
        "%i",
        app->game.players.reservesCapstone[PLAYER_BLACK]
    );

    //* Print active player
    mvprintw(
        POSITION_TURN[0],
        POSITION_TURN[1],
        "%s",
        ( app->game.activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );

    //* Print active player symbol
    mvprintw(
        POSITION_PLAYER_SYMBOL[0],
        POSITION_PLAYER_SYMBOL[1],
        "%c",
        PLAYER_CHARS[app->game.activePlayer + 1]
    );

    //* Print required input
    mvprintw(
        POSITION_INPUT_TYPE[0],
        POSITION_INPUT_TYPE[1],
        "%s",
        app->prompt.input
    );

    //* Print possible input options
    mvprintw(
        POSITION_INPUT_OPTIONS[0],
        POSITION_INPUT_OPTIONS[1],
        "%s",
        app->prompt.options
    );

    //* TODO: Print history

    //* Print current player input
    //* W:@c#
    //* B:#c#+#######
    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1],
        "%s",
        app->inputBuffer.currentCommand
    );
}

void renderStackBuffer( App* const app )
{
    //* Render buffer type
    mvaddch(
        POSITION_STACK_BUFFER[0],
        POSITION_STACK_BUFFER[1],
        STONE_TYPE_CHARS[app->game.stackBuffer.stoneType]
    );

    for ( int idx = 0; idx < app->game.stackBuffer.stoneCount + 8; ++idx )
    {
        mvaddch(
            POSITION_STACK_BUFFER[0]
                + ( ( 1 + idx )
                    % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            POSITION_STACK_BUFFER[1]
                + ( ( 1 + idx )
                    / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            PLAYER_CHARS[app->game.stackBuffer.stoneIds[idx] + 1]
        );
    }
}

void renderSquare( App* const app )
{
    int const dir = (int)app->inputBuffer.gameEvent.direction;

    int const offsetY
        = !!dir
          * ( dir % 2 )
          * ( dir - 2 );

    int const offsetX
        = !!dir
          * !( dir % 2 )
          * ( dir - 3 );

    int const posY = 2 + ( ( app->inputBuffer.gameEvent.rankY + offsetY ) * LAYOUT_BOARD_SQUARE_SIZE );

    int const posX = 4 + ( ( app->inputBuffer.gameEvent.fileX + offsetX ) * LAYOUT_BOARD_SQUARE_SIZE );

    //* Render buffer type
    mvaddch(
        posY - 999,
        posX - 999,
        STONE_TYPE_CHARS[app->game.stackBuffer.stoneType]
    );
}
