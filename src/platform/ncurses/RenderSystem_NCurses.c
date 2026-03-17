#include "RenderSystem_NCurses.h"

#include "App.h"
#include <ncurses.h>

void render( App* const app )
{
    clear();
    printw( "%i\n", (int)app->input.last );
    refresh();
}
