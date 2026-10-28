#include "BackendRender_Interface.h"
#include "UIElement.h"
#include "UIElementId.h"

#ifdef BACKEND_NCURSES
#include "App.h"
#include "BackendLayout_NCurses.h"
#include <assert.h>
#include <ncurses.h>

void renderUI( App const* const pApp );
void renderInfoText( UIElement const* const pUI_Element );

void render( App const* const pApp )
{
    switch ( pApp->state )
    {
        default:
        {
            renderUI( pApp );

            break;
        }

            // case APP_STATE_CHOOSE_BOARD_SIZE:
            // {
            //     renderStartScreen();
            //
            //     break;
            // }

            // case APP_STATE_GAME_END:
            // {
            //     renderStatic( pApp );
            //     renderDynamic( pApp );
            //     renderCommandGameEnd( pApp );
            //
            //     break;
            // }
    }

    refresh();
}

void renderUI( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    clear();

    attron( COLOR_PAIR( CPAIR_LAYOUT ) );

    renderInfoText( &pApp->uiData.uiElements[UI_ELEMENT_INFO] );

    attroff( COLOR_PAIR( CPAIR_LAYOUT ) );
}

void renderInfoText( UIElement const* const pUI_Element )
{
    assert(
        pUI_Element
        && "Invalid pointer"
    );

    mvprintw(
        pUI_Element->y,
        pUI_Element->x,
        "%s",
        "StackBuffer <<  >>"
        "  +   +     <<  >>"
        ""
        "            |<  \\/"
        "            |<  /\\"
        "  +   +  R|C Score"
        "White:    |  "
        "Black:    |  "
        "Active:       [ ]"
        //  "> B:Ma1+12345678",
        ">"
        "History:"
    );
}

#endif
