#include "Render_Interface.h"
#include "UIElement.h"
#include "UIElementId.h"

#ifdef BACKEND_NCURSES
#include "App.h"
#include "Layout_NCurses.h"
#include <assert.h>
#include <ncurses.h>

void renderStartScreen( App const* const pApp );
void renderChooseSizeText( UIElement const* const pUI_Element );

void renderUI( App const* const pApp );
void renderInfoText( UIElement const* const pUI_Element );

void render( App const* const pApp )
{
    switch ( pApp->state )
    {
        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            renderStartScreen( pApp );

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

void renderStartScreen( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    clear();

    attron( COLOR_PAIR( CPAIR_LAYOUT ) );

    renderChooseSizeText( &pApp->ui.uiElements[UI_ELEMENT_CHOOSE_SIZE_TEXT] );

    attroff( COLOR_PAIR( CPAIR_LAYOUT ) );
}

void renderChooseSizeText( UIElement const* const pUI_Element )
{
    assert(
        pUI_Element
        && "Pointer is nullptr"
    );
}

void renderUI( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    clear();

    attron( COLOR_PAIR( CPAIR_LAYOUT ) );

    renderInfoText( &pApp->ui.uiElements[UI_ELEMENT_INFO] );

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
