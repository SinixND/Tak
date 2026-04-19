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
        "%s",
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
