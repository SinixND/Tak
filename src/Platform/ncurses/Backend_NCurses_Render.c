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
