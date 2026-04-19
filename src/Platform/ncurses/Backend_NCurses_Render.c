#include "BackendInterface.h"
#include "Layout.h"

#ifdef BACKEND_NCURSES

#include <ncurses.h>

void renderStatic( App* const pApp )
{
    mvprintw(
        0,
        0,
        "%s %i",
        "BoardSize: ",
        pApp->game.board.size
    );

    int const boardSize = pApp->game.board.size;

    //* Render info pane
    for ( int paneIdx = 0; paneIdx < ( LAYOUT_PANE_HEIGHT ); ++paneIdx )
    {
        mvprintw(
            paneIdx,
            0,
            "%s",
            LAYOUT_INFO_PANE[paneIdx]
        );
    }

    //* Render top file labels
    int const fileLabelsOffsetX = 1;

    mvprintw(
        0,
        BOARD_OFFSET_X + fileLabelsOffsetX,
        "%.*s", // Partly render file labels
        fileLabelsOffsetX + 1 + ( boardSize * 4 ),
        LAYOUT_LABELS_FILE
    );

    //* Render left rank labels
    int const ruleLabelsOffsetY = 1;

    int const offsetIntoRankLabelsLayout
        = ( ( BOARD_SIZE_MAX - boardSize )
            * LAYOUT_BOARD_SQUARE_SIZE );

    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            y + ruleLabelsOffsetY,
            BOARD_OFFSET_X,
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }

    //* Render board
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

void renderDynamic( App* const pApp )
{
    mvprintw(
        1,
        0,
        "%c",
        INPUT_CHARS[pApp->inputBuffer.keyboard]
    );
}

#endif
