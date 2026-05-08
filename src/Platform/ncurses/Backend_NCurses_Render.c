#include "ActionTypeId.h"
#include "App.h"
#include "BackendInterface.h"

#include "Command.h"
#include "FileId.h"
#include "GameConstants.h"
#include "Layout.h"
#include "PlayerId.h"
#include "Position.h"
#include "RankId.h"

#ifdef BACKEND_NCURSES
#include <ncurses.h>

void renderInfoPane( void );

void renderCurrentCommand( Command const* const pCommand );

void renderFileLabels(
    int const fileLabelsOffsetX,
    int const boardSize
);

void renderRankLabels(
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderBoard(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderBoardEdges(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderInfoPaneContent( App const* const pApp );
void renderStackBufferContent( App const* const pApp );
void renderBoardContent( App const* const pApp );
void renderSquareContent(
    App const* const pApp,
    int const squareIdx
);

void renderStatic( App* const pApp )
{
    clear();
    renderInfoPane();

    int const boardSize = pApp->game.board.size;
    int const fileLabelsOffsetX = 1;
    int const ruleLabelsOffsetY = 1;

    renderFileLabels(
        fileLabelsOffsetX,
        boardSize
    );

    renderRankLabels(
        ruleLabelsOffsetY,
        boardSize
    );

    renderBoard(
        fileLabelsOffsetX,
        ruleLabelsOffsetY,
        boardSize
    );

    renderBoardEdges(
        fileLabelsOffsetX,
        ruleLabelsOffsetY,
        boardSize
    );
}

void renderInfoPane( void )
{
    for ( int paneIdx = 0; paneIdx < ( LAYOUT_PANE_HEIGHT ); ++paneIdx )
    {
        mvprintw(
            paneIdx,
            0,
            "%s",
            LAYOUT_INFO_PANE[paneIdx]
        );
    }
}

void renderFileLabels(
    int const fileLabelsOffsetX,
    int const boardSize
)
{
    // Top
    mvprintw(
        0,
        BOARD_OFFSET_X + fileLabelsOffsetX,
        "%.*s", // Partly render file labels
        fileLabelsOffsetX + 1 + ( boardSize * 4 ),
        LAYOUT_LABELS_FILE
    );

    // Bottom
    mvprintw(
        2 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
        BOARD_OFFSET_X + fileLabelsOffsetX,
        "%.*s",
        fileLabelsOffsetX + 1 + ( boardSize * 4 ),
        LAYOUT_LABELS_FILE
    );
}

void renderRankLabels(
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    int const offsetIntoRankLabelsLayout
        = ( ( BOARD_SIZE_MAX - boardSize )
            * LAYOUT_BOARD_SQUARE_SIZE );

    // Left
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            ruleLabelsOffsetY + y,
            BOARD_OFFSET_X,
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }

    // Right
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            ruleLabelsOffsetY + y,
            BOARD_OFFSET_X + 2 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }
}

void renderBoard(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    int const gridOffsetX = BOARD_OFFSET_X + fileLabelsOffsetX;
    int const gridOffsetY = ruleLabelsOffsetY;

    for ( int y = 0; y < boardSize; ++y )
    {
        for ( int x = 0; x < boardSize; ++x )
        {
            for ( int gridSquareIdx = 0; gridSquareIdx < ( LAYOUT_BOARD_SQUARE_SIZE + 1 ); ++gridSquareIdx )
            {
                mvprintw(
                    gridOffsetY + ( y * ( LAYOUT_BOARD_SQUARE_SIZE ) ) + gridSquareIdx,
                    gridOffsetX + ( x * ( LAYOUT_BOARD_SQUARE_SIZE ) ),
                    "%s",
                    LAYOUT_BOARD_SQUARE[gridSquareIdx]
                );
            }
        }
    }
}

void renderBoardEdges(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    // Render top board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            ruleLabelsOffsetY,
            BOARD_OFFSET_X + fileLabelsOffsetX + 1 + x,
            '-'
        );
    }

    // Render left board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            ruleLabelsOffsetY + 1 + y,
            BOARD_OFFSET_X + fileLabelsOffsetX,
            '|'
        );
    }

    // Render right board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            ruleLabelsOffsetY + 1 + y,
            BOARD_OFFSET_X + fileLabelsOffsetX + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            '|'
        );
    }

    // Render bottom board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            ruleLabelsOffsetY + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            BOARD_OFFSET_X + fileLabelsOffsetX + 1 + x,
            '-'
        );
    }
}

void renderDynamic( App const* const pApp )
{
    renderInfoPaneContent( pApp );
    renderStackBufferContent( pApp );
    renderBoardContent( pApp );

    refresh();
}

void renderInfoPaneContent( App const* const pApp )
{
    // Print white regular reserves
    mvprintw(
        POSITION_WHITE_RESERVES_REGULAR[0],
        POSITION_WHITE_RESERVES_REGULAR[1],
        "%2i",
        pApp->game.reserves.regular[PLAYER_WHITE]
    );

    // Print white capston reserves
    mvprintw(
        POSITION_WHITE_RESERVES_CAPSTONE[0],
        POSITION_WHITE_RESERVES_CAPSTONE[1],
        "%i",
        pApp->game.reserves.capstone[PLAYER_WHITE]
    );

    // Print black regular reserves
    mvprintw(
        POSITION_BLACK_RESERVES_REGULAR[0],
        POSITION_BLACK_RESERVES_REGULAR[1],
        "%2i",
        pApp->game.reserves.regular[PLAYER_BLACK]
    );

    // Print black capston reserves
    mvprintw(
        POSITION_BLACK_RESERVES_CAPSTONE[0],
        POSITION_BLACK_RESERVES_CAPSTONE[1],
        "%i",
        pApp->game.reserves.capstone[PLAYER_BLACK]
    );

    // Print active player
    mvprintw(
        POSITION_ACTIVE_PLAYER[0],
        POSITION_ACTIVE_PLAYER[1],
        "%s",
        ( pApp->game.activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );

    // Print active player symbol
    mvprintw(
        POSITION_PLAYER_SYMBOL[0],
        POSITION_PLAYER_SYMBOL[1],
        "%c",
        PLAYER_CHARS[pApp->game.activePlayer]
    );

    // Print required input
    mvprintw(
        POSITION_INPUT_TYPE[0],
        POSITION_INPUT_TYPE[1],
        "%s",
        pApp->prompts.inputs[pApp->command.state]
    );

    // Print possible input options
    mvprintw(
        POSITION_INPUT_OPTIONS[0],
        POSITION_INPUT_OPTIONS[1],
        "%s",
        pApp->prompts.options[pApp->command.state]
    );

    // Print current player input
    renderCurrentCommand( &pApp->command );

    // TODO: Print history
}

void renderCurrentCommand( Command const* const pCommand )
{
    /// W:A@c#
    /// B:Ac#+#######

    mvprintw(
        POSITION_INPUT_CURRENT[0],
        POSITION_INPUT_CURRENT[1],
        "%c:%c",
        PLAYER_CHARS[pCommand->playerId],
        ACTION_TYPE_CHARS[pCommand->actionType]
    );

    switch ( pCommand->actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 3,
                "%c",
                STONE_TYPE_CHARS[pCommand->stoneType]
            );

            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 4,
                "%c",
                ( pCommand->fileX < 0 )
                    ? ' '
                    : FILE_CHARS[pCommand->fileX]
            );

            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 5,
                "%c",
                ( pCommand->rankY < 0 )
                    ? ' '
                    : RANK_CHARS[pCommand->rankY]
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        case ACTION_TYPE_DROP:
        {
            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 3,
                "%c",
                ( pCommand->fileX < 0 )
                    ? ' '
                    : FILE_CHARS[pCommand->fileX]
            );

            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 4,
                "%c",
                ( pCommand->rankY < 0 )
                    ? ' '
                    : RANK_CHARS[pCommand->rankY]
            );

            return;
        }

        default:
        {
            mvprintw(
                POSITION_INPUT_CURRENT[0],
                POSITION_INPUT_CURRENT[1] + 3,
                "%s",
                "            "
            );

            return;
        }
    }
}

void renderStackBufferContent( App const* const pApp )
{
    // Render buffer type
    if ( pApp->game.stackBuffer.stoneCount > 0 )
    {
        mvaddch(
            POSITION_STACK_BUFFER[0],
            POSITION_STACK_BUFFER[1],
            STONE_TYPE_CHARS[pApp->game.stackBuffer.stackType]
        );
    }
    else
    {
        mvaddch(
            POSITION_STACK_BUFFER[0],
            POSITION_STACK_BUFFER[1],
            ' '
        );
    }

    // Render stack Ids
    for ( int idx = 0; idx < BOARD_SIZE_MAX; ++idx )
    {
        if ( idx < pApp->game.stackBuffer.stoneCount )
        {
            mvaddch(
                POSITION_STACK_BUFFER[0]
                    + ( ( 1 + idx )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                POSITION_STACK_BUFFER[1]
                    + ( ( 1 + idx )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                PLAYER_CHARS[pApp->game.stackBuffer.stoneIds[idx]]
            );
        }
        else
        {
            mvaddch(
                POSITION_STACK_BUFFER[0]
                    + ( ( 1 + idx )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                POSITION_STACK_BUFFER[1]
                    + ( ( 1 + idx )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                ' '
            );
        }
    }
}

void renderBoardContent( App const* const pApp )
{
    int const boardSize = pApp->game.board.size;

    for ( int squareIdx = 0; squareIdx < ( boardSize * boardSize ); ++squareIdx )
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
    Board const* const pBoard = &pApp->game.board;

    int const squareEdgeY = ( ( pBoard->size - ( squareIdx / pBoard->size ) ) * LAYOUT_BOARD_SQUARE_SIZE ) - 2;

    int const squareEdgeX = ( BOARD_OFFSET_X + 2 ) + ( squareIdx % pBoard->size ) * LAYOUT_BOARD_SQUARE_SIZE;

    // Render stack type
    if ( pBoard->stoneCounts[squareIdx] > 0 )
    {
        mvaddch(
            squareEdgeY,
            squareEdgeX,
            STONE_TYPE_CHARS[pBoard->stackTypes[squareIdx]]
        );
    }
    else
    {
        mvaddch(
            squareEdgeY,
            squareEdgeX,
            ' '
        );
    }

    // Render stack Ids
    for ( int stoneIdxOffset = 0; stoneIdxOffset < BOARD_SIZE_MAX; ++stoneIdxOffset )
    {
        int const stackIdx = squareToStackIndex(
            squareIdx,
            pBoard->size
        );

        int stoneIdx = stackIdx + pBoard->stoneCounts[squareIdx] - 1;

        if ( stoneIdxOffset < pBoard->stoneCounts[squareIdx] )
        {
            mvaddch(
                squareEdgeY
                    + ( ( 1 + stoneIdxOffset )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                squareEdgeX
                    + ( ( 1 + stoneIdxOffset )
                        / ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                PLAYER_CHARS[pBoard->stoneIds[stoneIdx - stoneIdxOffset]]
            );
        }
        else
        {
            mvaddch(
                squareEdgeY
                    + ( ( 1 + stoneIdxOffset )
                        % ( LAYOUT_BOARD_SQUARE_SIZE - 1 ) ),
                squareEdgeX
                    + ( ( 1 + stoneIdxOffset )
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
