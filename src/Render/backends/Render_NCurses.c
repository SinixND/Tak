#include "Render_Interface.h"
#include "UI.h"

#ifdef BACKEND_NCURSES
#include "App.h"
#include "Constants_NCurses.h"
#include "UIElement.h"
#include "UIElementId.h"
#include <assert.h>
#include <ncurses.h>

void renderText( UIElement const* const pUIElement );
/// UI elements position and size needs to account for border
void renderBox( UIElement const* const pUIElement );
void renderButton( UIElement const* const pUIElement );

void renderStartScreen( App const* const pApp );
void renderUI( App const* const pApp );
void renderBoard(
    UI const* const pUI,
    int const boardSize
);

void renderUIContent( App const* const pApp );

void render( App const* const pApp )
{
    clear();

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

void renderStartScreen( App const* const pApp )
{
    attron( COLOR_PAIR( COLORS_UI ) );

    renderText( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_TEXT] );

    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_3x3] );
    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_4x4] );
    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_5x5] );
    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_6x6] );
    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_7x7] );
    renderButton( &pApp->ui.uiElements[UIELEMENT_CHOOSE_SIZE_8x8] );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderUI( App const* const pApp )
{
    attron( COLOR_PAIR( COLORS_UI ) );

    renderText( &pApp->ui.uiElements[UIELEMENT_STACK_BUFFER] );

    renderText( &pApp->ui.uiElements[UIELEMENT_UNDO] );
    renderText( &pApp->ui.uiElements[UIELEMENT_REDO] );
    renderText( &pApp->ui.uiElements[UIELEMENT_RESET] );
    renderText( &pApp->ui.uiElements[UIELEMENT_QUIT] );

    renderText( &pApp->ui.uiElements[UIELEMENT_INFO] );
    renderText( &pApp->ui.uiElements[UIELEMENT_ACTIVE_PLAYER] );
    renderText( &pApp->ui.uiElements[UIELEMENT_COMMAND] );
    renderText( &pApp->ui.uiElements[UIELEMENT_HISTORY] );

    renderBoard(
        &pApp->ui,
        pApp->game.board.size
    );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderBoard(
    UI const* const pUI,
    int const boardSize
)
{
    /// Board
    for ( int file = 0; file < ( boardSize * boardSize ); ++file )
    {
        for ( int rank = 0; rank < ( boardSize * boardSize ); ++rank )
        {
            mvprintw(
                pUI->uiElements[UIELEMENT_BOARD].y + rank,
                pUI->uiElements[UIELEMENT_BOARD].x + file,
                "%s",
                "+   +"
            );

            mvprintw(
                pUI->uiElements[UIELEMENT_BOARD].y + rank + 4,
                pUI->uiElements[UIELEMENT_BOARD].x + file,
                "%s",
                "+   +"
            );
        }
    }

    /// Borders

    /// Labels
}

void renderUIContent( App const* const pApp );

#endif
