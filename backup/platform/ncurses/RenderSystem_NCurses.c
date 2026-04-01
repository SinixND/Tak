#include "RenderSystem.h"

#include "App.h"
#include "Layout.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "StoneTypeId.h"
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
    renderBoard( app );

    refresh();
}

void renderInfoPaneContent( App* const app )
{
    //* Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%2i",
        app->game.reserves.regular[PLAYER_WHITE]
    );

    //* Print white capston reserves
    mvprintw(
        POSITION_WHITE_RESERVES_CAPSTONE[0],
        POSITION_WHITE_RESERVES_CAPSTONE[1],
        "%i",
        app->game.reserves.capstone[PLAYER_WHITE]
    );

    //* Print black regular reserves
    mvprintw(
        POSITION_BLACK_RESERVES_REGULAR[0],
        POSITION_BLACK_RESERVES_REGULAR[1],
        "%2i",
        app->game.reserves.regular[PLAYER_BLACK]
    );

    //* Print black capston reserves
    mvprintw(
        POSITION_BLACK_RESERVES_CAPSTONE[0],
        POSITION_BLACK_RESERVES_CAPSTONE[1],
        "%i",
        app->game.reserves.capstone[PLAYER_BLACK]
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
        PLAYER_CHARS[app->game.activePlayer]
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

    for ( int idx = 0; idx < app->game.stackBuffer.stoneCount; ++idx )
    {
        mvaddch(
            POSITION_STACK_BUFFER[0]
                + ( ( 1 + idx )
                    % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            POSITION_STACK_BUFFER[1]
                + ( ( 1 + idx )
                    / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            PLAYER_CHARS[app->game.stackBuffer.stoneIds[idx]]
        );
    }
}

void renderBoard( App* const app )
{
    for ( int fileX = 0; fileX < app->game.board.width; ++fileX )
    {
        for ( int rankY = 0; rankY < app->game.board.width; ++rankY )
        {
            renderSquare( app, fileX, rankY );
        }
    }
}

void renderSquare(
    App* const app,
    FileId const fileX,
    RankId const rankY
)
{
    int const squarePosY
        = 2 + ( ( app->game.board.width - 1 - rankY ) * LAYOUT_BOARD_SQUARE_SIZE );

    int const squarePosX
        = BOARD_OFFSET + 2
          + ( fileX * LAYOUT_BOARD_SQUARE_SIZE );

    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        app->game.board.width
    );

    //* Render stack type
    mvaddch(
        squarePosY,
        squarePosX,
        STONE_TYPE_CHARS[app->game.board.types[squareIdx]]
    );

    int const stoneCount = app->game.board.stoneCounts[squareIdx];

    for ( int idx = 0; idx < stoneCount; ++idx )
    {
        mvaddch(
            squarePosY
                + ( ( 1 + idx )
                    % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            squarePosX
                + ( ( 1 + idx )
                    / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
            PLAYER_CHARS[app->game.board.stoneIds[positionToSquare( fileX, rankY, app->game.board.width ) + ( stoneCount - idx - 1 )]]
        );
    }
}
