#include "BackendInterface.h"

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
