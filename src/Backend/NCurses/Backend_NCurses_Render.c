#include "BackendInterface.h"

#ifdef BACKEND_NCURSES
#include "ActionTypeId.h"
#include "App.h"
#include "AppStateId.h"
#include "Backend_NCurses_Layout.h"
#include "Command.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "History.h"
#include "PlayerId.h"
#include "Position.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <ncurses.h>

void renderStatic( App const* const pApp );
void renderInfoPane( void );
void renderFileLabels( int const boardSize );
void renderRankLabels( int const boardSize );
void renderBoard( int const boardSize );
void renderBoardEdges( int const boardSize );

void renderDynamic( App const* const pApp );
void renderCommand( Command const* const pCommand );
void renderHistory( History const* const pHistory, int const entryCount );
void renderInfoPaneContent( App const* const pApp );
void renderStackBufferContent( App const* const pApp );
void renderBoardContent( App const* const pApp );
void renderSquareContent( App const* const pApp, int const squareIdx );

void renderStartScreen( void );

void renderCommandGameEnd( App const* const pApp );

void render( App const* const pApp )
{
    switch ( pApp->state )
    {
        default:
        {
            renderStatic( pApp );
            renderDynamic( pApp );

            break;
        }

        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            renderStartScreen();

            break;
        }

        case APP_STATE_GAME_END:
        {
            renderStatic( pApp );
            renderDynamic( pApp );
            renderCommandGameEnd( pApp );

            break;
        }
    }

    refresh();
}

void renderStatic( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    clear();

    attron( COLOR_PAIR( CPAIR_LAYOUT ) );
    renderInfoPane();

    int const boardSize = pApp->game.board.size;

    renderFileLabels( boardSize );
    renderRankLabels( boardSize );
    renderBoard( boardSize );
    renderBoardEdges( boardSize );

    attroff( COLOR_PAIR( CPAIR_LAYOUT ) );
}

void renderInfoPane( void )
{
    for ( int idx = 0; idx < ( LAYOUT_PANE_HEIGHT ); ++idx )
    {
        mvprintw(
            idx,
            0,
            "%s",
            LAYOUT_INFO_PANE[idx]
        );
    }
}

void renderFileLabels( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    /// Top
    mvprintw(
        BOARD_LABELS_Y_TOP,
        BOARD_LABELS_X_LEFT,
        "%.*s", // Partly render file labels
        boardSize * 4,
        LAYOUT_LABELS_FILE
    );

    /// Bottom
    mvprintw(
        BOARD_LABELS_Y_TOP + 2 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
        BOARD_LABELS_X_LEFT,
        "%.*s",
        boardSize * 4,
        LAYOUT_LABELS_FILE
    );
}

void renderRankLabels( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    int const offsetIntoRankLabelsLayout
        = ( ( BOARD_SIZE_MAX - boardSize )
            * LAYOUT_BOARD_SQUARE_SIZE );

    /// Left
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            BOARD_LABELS_Y_TOP + y,
            BOARD_LABELS_X_LEFT,
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }

    /// Right
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            BOARD_LABELS_Y_TOP + y,
            BOARD_LABELS_X_LEFT + 1 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) + 1,
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }
}

void renderBoard( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    for ( int y = 0; y < boardSize; ++y )
    {
        for ( int x = 0; x < boardSize; ++x )
        {
            for ( int layoutIdx = 0; layoutIdx < ( LAYOUT_BOARD_SQUARE_SIZE + 1 ); ++layoutIdx )
            {
                mvprintw(
                    BOARD_POS_Y + ( y * ( LAYOUT_BOARD_SQUARE_SIZE ) ) + layoutIdx,
                    BOARD_POS_X + ( x * ( LAYOUT_BOARD_SQUARE_SIZE ) ),
                    "%s",
                    LAYOUT_BOARD_SQUARE[layoutIdx]
                );
            }
        }
    }
}

void renderBoardEdges( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    /// Render top board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            BOARD_POS_Y,
            BOARD_POS_X + 1 + x,
            '-'
        );
    }

    /// Render left board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            BOARD_POS_Y + 1 + y,
            BOARD_POS_X,
            '|'
        );
    }

    /// Render right board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            BOARD_POS_Y + 1 + y,
            BOARD_POS_X + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            '|'
        );
    }

    /// Render bottom board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            BOARD_POS_Y + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            BOARD_POS_X + 1 + x,
            '-'
        );
    }
}

void renderDynamic( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    renderInfoPaneContent( pApp );
    renderStackBufferContent( pApp );
    renderBoardContent( pApp );

    refresh();
}

void renderInfoPaneContent( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%2i",
        pApp->game.reserves.regular[PLAYER_WHITE]
    );

    /// Print white capstone reserves
    mvprintw(
        POSITION_WHITE_RESERVES_CAPSTONE[0],
        POSITION_WHITE_RESERVES_CAPSTONE[1],
        "%i",
        pApp->game.reserves.capstone[PLAYER_WHITE]
    );

    /// Print white flat score
    attron( COLOR_PAIR( CPAIR_FGB_BGW ) );
    mvprintw(
        POSITION_WHITE_SCORE[0],
        POSITION_WHITE_SCORE[1],
        "%2i",
        pApp->game.scores[PLAYER_WHITE]
    );
    attroff( COLOR_PAIR( CPAIR_FGB_BGW ) );

    /// Print black regular reserves
    mvprintw(
        POSITION_BLACK_RESERVES_REGULAR[0],
        POSITION_BLACK_RESERVES_REGULAR[1],
        "%2i",
        pApp->game.reserves.regular[PLAYER_BLACK]
    );

    /// Print black capstone reserves
    mvprintw(
        POSITION_BLACK_RESERVES_CAPSTONE[0],
        POSITION_BLACK_RESERVES_CAPSTONE[1],
        "%i",
        pApp->game.reserves.capstone[PLAYER_BLACK]
    );

    /// Print black flat score
    attron( COLOR_PAIR( CPAIR_FGW_BGB ) );
    mvprintw(
        POSITION_BLACK_SCORE[0],
        POSITION_BLACK_SCORE[1],
        "%2i",
        pApp->game.scores[PLAYER_BLACK]
    );
    attroff( COLOR_PAIR( CPAIR_FGW_BGB ) );

    /// Print active player
    attron( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
    mvprintw(
        POSITION_ACTIVE_PLAYER[0],
        POSITION_ACTIVE_PLAYER[1],
        "%s",
        ( pApp->game.activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );
    attroff( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );

    /// Print active player symbol
    attron( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );
    mvprintw(
        POSITION_PLAYER_SYMBOL[0],
        POSITION_PLAYER_SYMBOL[1],
        "%c",
        PLAYER_CHARS[pApp->game.activePlayer]
    );
    attroff( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );

    /// Print required input
    mvprintw(
        POSITION_INPUT_TYPE[0],
        POSITION_INPUT_TYPE[1],
        "%s",
        pApp->prompts.pInputs[pApp->command.state]
    );

    /// Print possible input options
    mvprintw(
        POSITION_INPUT_OPTIONS[0],
        POSITION_INPUT_OPTIONS[1],
        "%s",
        pApp->prompts.options[pApp->command.state]
    );

    /// Print current player input
    renderCommand( &pApp->command );

    renderHistory(
        &pApp->history,
        /// 2 rows @ size == 3, +4 for every board size increase
        ( 2 + ( pApp->game.board.size - 3 ) * 4 )
    );
}

void renderCommand( Command const* const pCommand )
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    /// W:A@c#
    /// B:Ac#+#######
    ///
    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1],
        "%c:",
        PLAYER_CHARS[pCommand->playerId]
    );

    switch ( pCommand->actionType )
    {
        default:
        case ACTION_TYPE_PLACE:
        {
            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 2,
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
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 2,
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

            attron( COLOR_PAIR( CPAIR_HIGHLIGHT ) );
            mvaddch(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 6 + pCommand->currentDropIdx,
                '0' + pCommand->bufferedDropCount
            );
            attroff( COLOR_PAIR( CPAIR_HIGHLIGHT ) );

            return;
        }
    }
}

void renderHistory(
    History const* const pHistory,
    int const entryCount
)
{
    assert(
        pHistory
        && "Pointer is nullptr"
    );

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
                    POSITION_HISTORY_TOP_LEFT[0] + i,
                    POSITION_HISTORY_TOP_LEFT[1],
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
                    POSITION_HISTORY_TOP_LEFT[0] + i,
                    POSITION_HISTORY_TOP_LEFT[1],
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
                    POSITION_HISTORY_TOP_LEFT[0],
                    POSITION_HISTORY_TOP_LEFT[1],
                    "%s",
                    "            "
                );

                break;
            }
        }
    }
}

void renderCommandGameEnd( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    attron( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1],
        "%c: WIN! ",
        PLAYER_CHARS[pApp->game.activePlayer]
    );
    attroff( COLOR_PAIR( ( pApp->game.activePlayer == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );

    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1] + 8,
        "[Q]uit"
    );

    refresh();
}

void renderStackBufferContent( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Render buffer type
    if ( pApp->game.stackBuffer.stoneCount > 0 )
    {
        attron( COLOR_PAIR( ( pApp->game.stackBuffer.stoneIds[0] == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );
        mvaddch(
            POSITION_STACK_BUFFER[0],
            POSITION_STACK_BUFFER[1],
            STONE_TYPE_SYMBOLS[pApp->game.stackBuffer.stackType]
        );
        attroff( COLOR_PAIR( ( pApp->game.stackBuffer.stoneIds[0] == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );
    }
    else
    {
        mvaddch(
            POSITION_STACK_BUFFER[0],
            POSITION_STACK_BUFFER[1],
            ' '
        );
    }

    /// Render stack Ids
    for ( int idx = 1; idx <= BOARD_SIZE_MAX; ++idx )
    {
        if ( idx < pApp->game.stackBuffer.stoneCount )
        {
            attron( COLOR_PAIR( ( pApp->game.stackBuffer.stoneIds[idx] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
            mvaddch(
                POSITION_STACK_BUFFER[0]
                    + ( ( idx )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                POSITION_STACK_BUFFER[1]
                    + ( ( idx )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                STONE_TYPE_SYMBOLS[STONE_TYPE_FLAT]

            );
            attroff( COLOR_PAIR( ( pApp->game.stackBuffer.stoneIds[idx] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
        }
        else
        {
            mvaddch(
                POSITION_STACK_BUFFER[0]
                    + ( ( idx )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                POSITION_STACK_BUFFER[1]
                    + ( ( idx )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                ' '
            );
        }
    }
}

void renderBoardContent( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    int const squareCount = pApp->game.board.squareCount;

    for ( int squareIdx = 0; squareIdx < squareCount; ++squareIdx )
    {
        renderSquareContent(
            pApp,
            squareIdx
        );
    }
}

void renderSquareContent(
    App const* const pApp,
    int const squareIdx
)
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < pApp->game.board.squareCount
        && "Square index invalid"
    );

    Board const* const pBoard = &pApp->game.board;

    int const squareEdgeY = ( ( pBoard->size - ( squareIdx / pBoard->size ) ) * LAYOUT_BOARD_SQUARE_SIZE ) - 2;

    int const squareEdgeX = ( BOARD_POS_X + 1 ) + ( squareIdx % pBoard->size ) * LAYOUT_BOARD_SQUARE_SIZE;

    /// Render stack type
    if (
        pBoard->stoneCounts[squareIdx] > 0
        && pBoard->stackTypes[squareIdx] != STONE_TYPE_STANDING
    )
    {
        attron( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );
        mvaddch(
            squareEdgeY,
            squareEdgeX,
            STONE_TYPE_SYMBOLS[pBoard->stackTypes[squareIdx]]
        );
        attroff( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? CPAIR_FGB_BGW : CPAIR_FGW_BGB ) );
    }

    else if (
        pBoard->stoneCounts[squareIdx] > 0
        && pBoard->stackTypes[squareIdx] == STONE_TYPE_STANDING
    )
    {
        attron( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
        mvaddch(
            squareEdgeY,
            squareEdgeX,
            STONE_TYPE_SYMBOLS[pBoard->stackTypes[squareIdx]]
        );
        attroff( COLOR_PAIR( ( pBoard->stackIds[squareIdx] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
    }

    else
    {
        mvaddch(
            squareEdgeY,
            squareEdgeX,
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
            attron( COLOR_PAIR( ( pBoard->stoneIds[stoneIdx - stoneIdxOffset] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
            mvaddch(
                squareEdgeY
                    + ( ( stoneIdxOffset )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                squareEdgeX
                    + ( ( stoneIdxOffset )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                STONE_TYPE_SYMBOLS[STONE_TYPE_FLAT]
            );
            attroff( COLOR_PAIR( ( pBoard->stoneIds[stoneIdx - stoneIdxOffset] == PLAYER_WHITE ) ? CPAIR_FGW : CPAIR_FGB ) );
        }
        else
        {
            mvaddch(
                squareEdgeY
                    + ( ( stoneIdxOffset )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                squareEdgeX
                    + ( ( stoneIdxOffset )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                ' '
            );
        }
    }
}

void renderStartScreen( void )
{
    mvprintw(
        1,
        1,
        "%s",
        "Choose board size. "
    );

    mvprintw(
        2,
        1,
        "Options: %i - %i, confirm for default (%i)",
        BOARD_SIZE_MIN,
        BOARD_SIZE_MAX,
        BOARD_SIZE_DEFAULT
    );
}

#endif
