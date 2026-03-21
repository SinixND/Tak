#include "RenderSystem_NCurses.h"

#include "ActionType.h"
#include "App.h"
#include "AppState.h"
#include "Layout.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "StoneType.h"
#include <assert.h>
#include <ncurses.h>

void renderStatic( App* const app )
{
    //* Render UI / Layout
    int const boardWidth = app->game.board.width;

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

void renderDynamic( App* const app )
{
    renderInfoPaneContent( app );
    renderChangedBoardSquare( app );

    refresh();
}

void renderInfoPaneContent( App* const app )
{
    int const paneOffset = ( app->game.board.width - 3 ) * ( (int)( sizeof( LAYOUT_BOARD_SQUARE ) / sizeof( LAYOUT_BOARD_SQUARE[0] ) ) - 1 );

    //* Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1] + paneOffset,
        "%2i",
        app->game.players.reservesRegular[PLAYER_WHITE]
    );

    //* Print white capston reserves
    mvprintw(
        POSITION_WHITE_RESERVES_CAPSTONE[0],
        POSITION_WHITE_RESERVES_CAPSTONE[1] + paneOffset,
        "%i",
        app->game.players.reservesCapstone[PLAYER_WHITE]
    );

    //* Print black regular reserves
    mvprintw(
        POSITION_BLACK_RESERVES_REGULAR[0],
        POSITION_BLACK_RESERVES_REGULAR[1] + paneOffset,
        "%2i",
        app->game.players.reservesRegular[PLAYER_BLACK]
    );

    //* Print black capston reserves
    mvprintw(
        POSITION_BLACK_RESERVES_CAPSTONE[0],
        POSITION_BLACK_RESERVES_CAPSTONE[1] + paneOffset,
        "%i",
        app->game.players.reservesCapstone[PLAYER_BLACK]
    );

    //* Print active player
    mvprintw(
        POSITION_TURN[0],
        POSITION_TURN[1] + paneOffset,
        "%s",
        ( app->game.activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );

    //* Print active player symbol
    mvprintw(
        POSITION_PLAYER_SYMBOL[0],
        POSITION_PLAYER_SYMBOL[1] + paneOffset,
        "%c",
        PLAYER_CHARS[app->game.activePlayer]
    );

    char* input = "       ";
    char* opts = "          ";

    switch ( app->state )
    {
        default:
        {
            //* Do nonthing
            break;
        }

        case STATE_FIRST_TURN_CHOOSE_FILE_X:
        case STATE_SECOND_TURN_CHOOSE_FILE_X:
        case STATE_CHOOSE_FILE_X:
        {
            input = "File X ";
            opts = "a-h       ";

            break;
        }

        case STATE_FIRST_TURN_CHOOSE_RANK_Y:
        case STATE_SECOND_TURN_CHOOSE_RANK_Y:
        case STATE_CHOOSE_RANK_Y:
        {
            input = "Rank Y ";
            opts = "1-8       ";

            break;
        }

        case STATE_CHOOSE_ACTION:
        {
            input = "Action ";
            opts = "p, m      ";

            break;
        }

        case STATE_CHOOSE_STONE_TYPE:
        {
            input = "StType ";
            opts = "f, s, c   ";

            break;
        }

        case STATE_CHOOSE_DIRECTION:
        {
            input = "Direct.";
            opts = "n, e, s, w";

            break;
        }

        case STATE_CHOOSE_FIRST_DROP_AMOUNT:
        {
            input = "Amount ";
            opts = "0-8       ";

            break;
        }

        case STATE_CHOOSE_AMOUNT:
        {
            input = "Amount ";
            opts
                = "1-8       ";

            break;
        }
    }

    //* Print required input
    mvprintw(
        POSITION_INPUT_TYPE[0],
        POSITION_INPUT_TYPE[1] + paneOffset,
        "%s",
        input
    );

    //* Print possible input options
    mvprintw(
        POSITION_INPUT_OPTIONS[0],
        POSITION_INPUT_OPTIONS[1] + paneOffset,
        "%s",
        opts
    );

    //* TODO: Print history

    //* Print current player input
    //* W:@c#
    //* B:#c#+#######
    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1] + paneOffset,
        "%s",
        app->inputBuffer.currentInput
    );
}

void renderChangedBoardSquare( App* const app )
{
    int const layoutSquareSize = (int)( sizeof( LAYOUT_BOARD_SQUARE ) / sizeof( LAYOUT_BOARD_SQUARE[0] ) ) - 1;

    int const dir = (int)app->inputBuffer.gameEvent.direction;

    int const offsetY
        = !!dir
          * ( dir % 2 )
          * ( dir - 2 );

    int const offsetX
        = !!dir
          * !( dir % 2 )
          * ( dir - 3 );

    int const posY = 2 + ( ( app->inputBuffer.gameEvent.rankY + offsetY ) * layoutSquareSize );

    int const posX = 4 + ( ( app->inputBuffer.gameEvent.fileX + offsetX ) * layoutSquareSize );

    //* Render buffer type
    mvaddch(
        posY,
        posX,
        STONE_TYPE_CHARS[app->game.stackBuffer.stoneType]
    );
}
