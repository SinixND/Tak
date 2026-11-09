#include "Render_Interface.h"

#ifdef BACKEND_NCURSES
#include "App.h"
#include "Command.h"
#include "Constants_NCurses.h"
#include "Conversion.h"
#include "Game.h"
#include "GameScreenElementId.h"
#include "History.h"
#include "UI.h"
#include "UIElement.h"
#include "UIPosition.h"
#include <assert.h>
#include <ncurses.h>

void renderText( UIElement const* const pUIElement );
/// UI elements position and size needs to include border weight
void renderBox( UIElement const* const pUIElement );
void renderButton( UIElement const* const pUIElement );

void renderStartScreen( UI const* const pUI );
void renderUI( App const* const pApp );

void renderUndo( UI const* const pUI );
void renderRedo( UI const* const pUI );
void renderReset( UI const* const pUI );
void renderQuit( UI const* const pUI );

void renderStackBuffer( UI const* const pUI );

void renderInfo( UI const* const pUI );
void renderActivePlayer( UI const* const pUI );
void renderCommand( UI const* const pUI );
void renderHistory( UI const* const pUI );

void renderBoard( UI const* const pUI, int const boardSize );

void renderInfoContent( UI const* const pUI, Game const* const pGame );
void renderActivePlayerContent( UI const* const pUI, Game const* const pGame );
void renderCommandContent( UI const* const pUI, Command const* const pCommand );
void renderHistoryContent( UI const* const pUI, Game const* const pGame, History const* const pHistory );

void renderBoardContent( UI const* const pUI, Game const* const pGame );

void render( App const* const pApp )
{
    clear();

    switch ( pApp->state )
    {
        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            renderStartScreen( &pApp->ui );

            break;
        }

        default:
        {
            renderUI( pApp );

            break;
        }
    }

    refresh();
}

void renderText( UIElement const* const pUIElement )
{
    mvprintw(
        pUIElement->y,
        pUIElement->x,
        "%s",
        pUIElement->text
    );
}

void renderBox( UIElement const* const pUIElement )
{
    /// Edges
    mvaddch(
        pUIElement->y,
        pUIElement->x,
        '+'
    );

    mvaddch(
        pUIElement->y + pUIElement->height - 1,
        pUIElement->x,
        '+'
    );

    mvaddch(
        pUIElement->y,
        pUIElement->x + pUIElement->width - 1,
        '+'
    );

    mvaddch(
        pUIElement->y + pUIElement->height - 1,
        pUIElement->x + pUIElement->width - 1,
        '+'
    );

    for ( int x = 1; x < ( pUIElement->width - 1 ); ++x )
    {
        mvaddch(
            pUIElement->y,
            pUIElement->x + x,
            '-'
        );

        mvaddch(
            pUIElement->y + pUIElement->height - 1,
            pUIElement->x + x,
            '-'
        );
    }

    for ( int y = 1; y < ( pUIElement->height - 1 ); ++y )
    {
        mvaddch(
            pUIElement->y + y,
            pUIElement->x,
            '|'
        );

        mvaddch(
            pUIElement->y + y,
            pUIElement->x + pUIElement->width - 1,
            '|'
        );
    }
}

void renderButton( UIElement const* const pUIElement )
{
    renderBox( pUIElement );

    mvprintw(
        pUIElement->y + 1,
        pUIElement->x + 1,
        "%s",
        pUIElement->text
    );
}

void renderStartScreen( UI const* const pUI )
{
    attron( COLOR_PAIR( COLORS_UI ) );

    renderText( &pUI->selectScreenElements[UIELEMENT_CHOOSE_SIZE] );

    renderButton( &pUI->selectScreenElements[UIELEMENT_3x3] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_4x4] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_5x5] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_6x6] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_7x7] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_8x8] );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderUI( App const* const pApp )
{
    /// Static
    attron( COLOR_PAIR( COLORS_UI ) );

    renderUndo( &pApp->ui );
    renderRedo( &pApp->ui );
    renderReset( &pApp->ui );
    renderQuit( &pApp->ui );

    renderStackBuffer( &pApp->ui );

    renderInfo( &pApp->ui );
    renderActivePlayer( &pApp->ui );
    renderCommand( &pApp->ui );
    renderHistory( &pApp->ui );

    renderBoard(
        &pApp->ui,
        pApp->game.board.size
    );

    attroff( COLOR_PAIR( COLORS_UI ) );

    /// Dynamic
    renderInfoContent(
        &pApp->ui,
        &pApp->game
    );

    renderActivePlayerContent(
        &pApp->ui,
        &pApp->game
    );

    attron( COLOR_PAIR( COLORS_DEFAULT ) );

    renderCommandContent(
        &pApp->ui,
        &pApp->command
    );

    renderHistoryContent(
        &pApp->ui,
        &pApp->game,
        &pApp->history
    );

    attroff( COLOR_PAIR( COLORS_DEFAULT ) );

    renderBoardContent(
        &pApp->ui,
        &pApp->game
    );
}

void renderUndo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_UNDO].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_UNDO].y + y,
            pUI->gameScreenElements[UIELEMENT_UNDO].x,
            "<<"
        );
    }
}

void renderRedo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_REDO].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_REDO].y + y,
            pUI->gameScreenElements[UIELEMENT_REDO].x,
            ">>"
        );
    }
}

void renderReset( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_RESET].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_RESET].y + y,
            pUI->gameScreenElements[UIELEMENT_RESET].x,
            "|<"
        );
    }
}

void renderQuit( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_QUIT].y,
        pUI->gameScreenElements[UIELEMENT_QUIT].x,
        "\\/"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_QUIT].y + 1,
        pUI->gameScreenElements[UIELEMENT_QUIT].x,
        "/\\"
    );
}

void renderStackBuffer( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].y,
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].y + pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].height - 1,
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );
}

void renderInfo( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "         R|C Score"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "White:    |  "
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "Black:    |  "
    );
}

void renderActivePlayer( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x,
        "Active:       [ ]"
    );
}

void renderCommand( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_COMMAND].y,
        pUI->gameScreenElements[UIELEMENT_COMMAND].x,
        //"> B:Ma1+12345678",
        ">"
    );
}

void renderHistory( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_HISTORY].y,
        pUI->gameScreenElements[UIELEMENT_HISTORY].x,
        "History:"
    );
}

void renderBoard(
    UI const* const pUI,
    int const boardSize
)
{
    /// Grid
    for ( int x = 0; x < boardSize; ++x )
    {
        for ( int y = 0; y < boardSize; ++y )
        {
            mvprintw(
                ( y * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y,
                ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );

            mvprintw(
                ( y * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y + 4,
                ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );
        }
    }

    /// Box
    renderBox( &pUI->gameScreenElements[UIELEMENT_BOARD] );

    /// Labels
    char ch = 'A';

    for ( int x = 0; x < boardSize; ++x )
    {
        mvaddch(
            pUI->gameScreenElements[UIELEMENT_BOARD].y - 1,
            ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x + 2,
            ch
        );

        mvaddch(
            pUI->gameScreenElements[UIELEMENT_BOARD].y + pUI->gameScreenElements[UIELEMENT_BOARD].height,
            ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x + 2,
            ch++
        );
    }

    ch = '1';
    for ( int y = 0; y < boardSize; ++y )
    {
        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y - 2,
            pUI->gameScreenElements[UIELEMENT_BOARD].x - 1,
            ch
        );

        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y - 2,
            pUI->gameScreenElements[UIELEMENT_BOARD].x + pUI->gameScreenElements[UIELEMENT_BOARD].width,
            ch++
        );
    }
}

void renderInfoContent(
    UI const* const pUI,
    Game const* const pGame
)
{
    /// Stone counts
    attron( COLOR_PAIR( COLORS_DEFAULT ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 8,
        "%2i",
        pGame->reserves.regular[PLAYER_WHITE]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 11,
        "%i",
        pGame->reserves.capstone[PLAYER_WHITE]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 8,
        "%2i",
        pGame->reserves.regular[PLAYER_BLACK]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 11,
        "%i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    /// Player scores
    attron( COLOR_PAIR( COLORS_PLAYER_WHITE_STRONG ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 14,
        "%2i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    attron( COLOR_PAIR( COLORS_PLAYER_BLACK_STRONG ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 14,
        "%2i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    attroff( COLOR_PAIR( COLORS_PLAYER_BLACK_STRONG ) );
}

void renderActivePlayerContent(
    UI const* const pUI,
    Game const* const pGame
)
{
    attron( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x + 8,
        "%s",
        ( pGame->activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );

    attroff( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

    attron( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x + 15,
        "%c",
        PLAYER_CHARS[pGame->activePlayer]
    );
    attroff( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );
}

void renderCommandContent(
    UI const* const pUI,
    Command const* const pCommand
)
{
    /// W:A@c#
    /// B:Ac#+#######
    ///
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_COMMAND].y,
        pUI->gameScreenElements[UIELEMENT_COMMAND].x + 2,
        "%c:",
        PLAYER_CHARS[pCommand->playerId]
    );

    switch ( pCommand->actionType )
    {
        default:
        case ACTION_TYPE_PLACE:
        {
            mvprintw(
                pUI->gameScreenElements[UIELEMENT_COMMAND].y,
                pUI->gameScreenElements[UIELEMENT_COMMAND].x + 4,
                "%c%c%c%c",
                ACTION_TYPE_CHARS[pCommand->actionType],
                STONE_TYPE_CHARS[pCommand->stoneType],
                ( pCommand->fileX < 0 ) ? ' ' : FILE_CHARS[pCommand->fileX],
                ( pCommand->rankY < 0 ) ? ' ' : RANK_CHARS[pCommand->rankY]
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        case ACTION_TYPE_DROP:
        {
            mvprintw(
                pUI->gameScreenElements[UIELEMENT_COMMAND].y,
                pUI->gameScreenElements[UIELEMENT_COMMAND].x + 4,
                "%c%c%c%c%c%c%c%c%c%c%c%c",
                ACTION_TYPE_CHARS[pCommand->actionType],
                ( pCommand->fileX < 0 ) ? ' ' : FILE_CHARS[pCommand->fileX],
                ( pCommand->rankY < 0 ) ? ' ' : RANK_CHARS[pCommand->rankY],
                ( pCommand->direction < 0 ) ? ' ' : DIRECTION_CHARS[pCommand->direction],
                ( pCommand->dropCounts[0] < 0 ) ? ' ' : '0' + pCommand->dropCounts[0],
                ( pCommand->dropCounts[1] < 0 ) ? ' ' : '0' + pCommand->dropCounts[1],
                ( pCommand->dropCounts[2] < 0 ) ? ' ' : '0' + pCommand->dropCounts[2],
                ( pCommand->dropCounts[3] < 0 ) ? ' ' : '0' + pCommand->dropCounts[3],
                ( pCommand->dropCounts[4] < 0 ) ? ' ' : '0' + pCommand->dropCounts[4],
                ( pCommand->dropCounts[5] < 0 ) ? ' ' : '0' + pCommand->dropCounts[5],
                ( pCommand->dropCounts[6] < 0 ) ? ' ' : '0' + pCommand->dropCounts[6],
                ( pCommand->dropCounts[7] < 0 ) ? ' ' : '0' + pCommand->dropCounts[7]
            );

            attron( COLOR_PAIR( COLORS_INACTIVE ) );
            mvaddch(
                pUI->gameScreenElements[UIELEMENT_COMMAND].y,
                pUI->gameScreenElements[UIELEMENT_COMMAND].x + 8 + pCommand->currentDropIdx,
                '0' + pCommand->bufferedDropCount
            );
            attroff( COLOR_PAIR( COLORS_INACTIVE ) );

            return;
        }
    }
}

void renderHistoryContent(
    UI const* const pUI,
    Game const* const pGame,
    History const* const pHistory
)
{
    int const entryCount = ( 4 * ( pGame->board.size - 3 ) + 3 );

    for ( int i = 0; i < entryCount; ++i )
    {
        if ( pHistory->lastCommandIdx - i <= 0 )
        {
            return;
        }

        Command const* const pLastCommand
            = &pHistory->commands[pHistory->lastCommandIdx - i];

        switch ( pLastCommand->actionType )
        {
            case ACTION_TYPE_PLACE:
            {
                mvprintw(
                    pUI->gameScreenElements[UIELEMENT_HISTORY].y + 1 + i,
                    pUI->gameScreenElements[UIELEMENT_HISTORY].x,
                    "%c[%i] %c%c%c%c%c%c%c%c%c%c%c",
                    PLAYER_CHARS[pLastCommand->playerId],
                    ( 1 + pHistory->lastCommandIdx - i ) / 2,
                    STONE_TYPE_CHARS[pLastCommand->stoneType],
                    ( ( pLastCommand->fileX < 0 )
                          ? ' '
                          : FILE_CHARS[pLastCommand->fileX] ),
                    ( ( pLastCommand->rankY < 0 )
                          ? ' '
                          : RANK_CHARS[pLastCommand->rankY] ),
                    ' ',
                    ' ',
                    ' ',
                    ' ',
                    ' ',
                    ' ',
                    ' ',
                    ' '
                );

                break;
            }

            case ACTION_TYPE_LIFT:
            case ACTION_TYPE_DROP:
            {
                mvprintw(
                    pUI->gameScreenElements[UIELEMENT_HISTORY].y + 1 + i,
                    pUI->gameScreenElements[UIELEMENT_HISTORY].x,
                    "%c[%i] %c%c%c%c%c%c%c%c%c%c%c",
                    PLAYER_CHARS[pLastCommand->playerId],
                    ( 1 + pHistory->lastCommandIdx - i ) / 2,
                    ( ( pLastCommand->fileX < 0 )
                          ? ' '
                          : FILE_CHARS[pLastCommand->fileX] ),
                    ( ( pLastCommand->rankY < 0 )
                          ? ' '
                          : RANK_CHARS[pLastCommand->rankY] ),
                    ( ( pLastCommand->direction < 0 )
                          ? ' '
                          : DIRECTION_CHARS[pLastCommand->direction] ),
                    ( ( pLastCommand->dropCounts[0] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[0] ),
                    ( ( pLastCommand->dropCounts[1] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[1] ),
                    ( ( pLastCommand->dropCounts[2] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[2] ),
                    ( ( pLastCommand->dropCounts[3] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[3] ),
                    ( ( pLastCommand->dropCounts[4] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[4] ),
                    ( ( pLastCommand->dropCounts[5] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[5] ),
                    ( ( pLastCommand->dropCounts[6] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[6] ),
                    ( ( pLastCommand->dropCounts[7] < 0 )
                          ? ' '
                          : '0' + pLastCommand->dropCounts[7] )
                );

                break;
            }

            default:
            {
                mvprintw(
                    pUI->gameScreenElements[UIELEMENT_HISTORY].y + 1,
                    pUI->gameScreenElements[UIELEMENT_HISTORY].x,
                    "%s",
                    "            "
                );

                break;
            }
        }
    }
}

void renderBoardContent( UI const* const pUI, Game const* const pGame )
{
    int const squareCount = pGame->board.squareCount;
    Board const* const pBoard = &pGame->board;
    UIPosition squareEdge = {
        .x = -1,
        .y = -1,
    };

    for ( int squareIdx = 0; squareIdx < squareCount; ++squareIdx )
    {
        /// Define top-left square position
        squareEdge.x = ( pUI->gameScreenElements[UIELEMENT_BOARD].x + 1 ) + 4 * ( squareIdx % pBoard->size );
        squareEdge.y = ( pUI->gameScreenElements[UIELEMENT_BOARD].y + 1 ) + 4 * ( ( pBoard->size - (int)( squareIdx / pBoard->size ) ) - 1 );

        /// Render stack type
        if (
            pBoard->stoneCounts[squareIdx] > 0
            && pBoard->stackTypes[squareIdx] != STONE_TYPE_STANDING
        )
        {
            attron( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );

            mvaddch(
                squareEdge.y,
                squareEdge.x,
                STONE_TYPE_SYMBOLS[pBoard->stackTypes[squareIdx]]
            );

            attroff( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );
        }
        else if (
            pBoard->stoneCounts[squareIdx] > 0
            && pBoard->stackTypes[squareIdx] == STONE_TYPE_STANDING
        )
        {
            attron( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

            mvaddch(
                squareEdge.y,
                squareEdge.x,
                STONE_TYPE_SYMBOLS[pBoard->stackTypes[squareIdx]]
            );

            attroff( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );
        }
        else
        {
            mvaddch(
                squareEdge.y,
                squareEdge.x,
                ' '
            );
        }

        /// Render stack Ids
        for ( int stoneIdxOffset = 1; stoneIdxOffset <= BOARD_SIZE_MAX; ++stoneIdxOffset )
        {
            int const stackIdx = squareToStackIndex(
                squareIdx,
                pBoard->size
            );

            int stoneIdx = stackIdx + pBoard->stoneCounts[squareIdx] - 1;

            if ( stoneIdxOffset < pBoard->stoneCounts[squareIdx] )
            {
                attron( COLOR_PAIR( ( pBoard->stoneIds[stoneIdx - stoneIdxOffset] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

                mvaddch(
                    squareEdge.y
                        + (int)( stoneIdxOffset
                                 % ( 4 - 1 ) ),
                    squareEdge.x
                        + (int)( stoneIdxOffset
                                 / ( 4 - 1 ) ),
                    STONE_TYPE_SYMBOLS[STONE_TYPE_FLAT]
                );

                attron( COLOR_PAIR( ( pBoard->stoneIds[stoneIdx - stoneIdxOffset] == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );
            }
            else
            {
                mvaddch(
                    squareEdge.y
                        + (int)( stoneIdxOffset
                                 % ( 4 - 1 ) ),
                    squareEdge.x
                        + (int)( stoneIdxOffset
                                 / ( 4 - 1 ) ),
                    ' '
                );
            }
        }
    }
}

#endif
