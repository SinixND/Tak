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

void renderStartScreen( UI const* const pUI );
void renderUI( App const* const pApp );

void renderStackBuffer( UI const* const pUI );
void renderUndo( UI const* const pUI );
void renderRedo( UI const* const pUI );
void renderReset( UI const* const pUI );
void renderQuit( UI const* const pUI );
void renderInfo( UI const* const pUI );
void renderActivePlayer( UI const* const pUI );
void renderCommand( UI const* const pUI );
void renderHistory( UI const* const pUI );
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
            renderStartScreen( &pApp->ui );

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

void renderStartScreen( UI const* const pUI )
{
    attron( COLOR_PAIR( COLORS_UI ) );

    renderText( &pUI->elements[UIELEMENT_CHOOSE_SIZE_TEXT] );

    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_3x3] );
    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_4x4] );
    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_5x5] );
    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_6x6] );
    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_7x7] );
    renderButton( &pUI->elements[UIELEMENT_CHOOSE_SIZE_8x8] );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderUI( App const* const pApp )
{
    attron( COLOR_PAIR( COLORS_UI ) );

    renderStackBuffer( &pApp->ui );
    renderUndo( &pApp->ui );
    renderRedo( &pApp->ui );
    renderReset( &pApp->ui );
    renderQuit( &pApp->ui );

    renderInfo( &pApp->ui );
    renderActivePlayer( &pApp->ui );
    renderCommand( &pApp->ui );
    renderHistory( &pApp->ui );

    renderBoard(
        &pApp->ui,
        pApp->game.board.size
    );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderStackBuffer( UI const* const pUI )
{
    mvprintw(
        pUI->elements[UIELEMENT_STACK_BUFFER].y,
        pUI->elements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );

    mvprintw(
        pUI->elements[UIELEMENT_STACK_BUFFER].y + pUI->elements[UIELEMENT_STACK_BUFFER].height - 1,
        pUI->elements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );
}

void renderUndo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->elements[UIELEMENT_UNDO].height; ++y )
    {
        mvprintw(
            pUI->elements[UIELEMENT_UNDO].y + y,
            pUI->elements[UIELEMENT_UNDO].x,
            "<<"
        );
    }
}

void renderRedo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->elements[UIELEMENT_REDO].height; ++y )
    {
        mvprintw(
            pUI->elements[UIELEMENT_REDO].y + y,
            pUI->elements[UIELEMENT_REDO].x,
            ">>"
        );
    }
}

void renderReset( UI const* const pUI )
{
    for ( int y = 0; y < pUI->elements[UIELEMENT_RESET].height; ++y )
    {
        mvprintw(
            pUI->elements[UIELEMENT_RESET].y + y,
            pUI->elements[UIELEMENT_RESET].x,
            "|<"
        );
    }
}

void renderQuit( UI const* const pUI )
{
    mvprintw(
        pUI->elements[UIELEMENT_QUIT].y,
        pUI->elements[UIELEMENT_QUIT].x,
        "\\/"
    );

    mvprintw(
        pUI->elements[UIELEMENT_QUIT].y + 1,
        pUI->elements[UIELEMENT_QUIT].x,
        "/\\"
    );
}

void renderInfo( UI const* const pUI )
{
    mvprintw(
        pUI->elements[UIELEMENT_INFO].y,
        pUI->elements[UIELEMENT_INFO].x,
        "         R|C Score"
    );

    mvprintw(
        pUI->elements[UIELEMENT_INFO].y + 1,
        pUI->elements[UIELEMENT_INFO].x,
        "White:    |  "
    );

    mvprintw(
        pUI->elements[UIELEMENT_INFO].y + 2,
        pUI->elements[UIELEMENT_INFO].x,
        "Black:    |  "
    );
}

void renderActivePlayer( UI const* const pUI )
{
}

void renderCommand( UI const* const pUI )
{
}

void renderHistory( UI const* const pUI )
{
}

void renderBoard(
    UI const* const pUI,
    int const boardSize
)
{
    /// Grid
    for ( int x = 0; x < boardSize; ++x )
    {
        for ( int y = 0; y < boardSize; ++y )
        {
            mvprintw(
                ( y * 4 ) + pUI->elements[UIELEMENT_BOARD].y,
                ( x * 4 ) + pUI->elements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );

            mvprintw(
                ( y * 4 ) + pUI->elements[UIELEMENT_BOARD].y + 4,
                ( x * 4 ) + pUI->elements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );
        }
    }

    /// Box
    renderBox( &pUI->elements[UIELEMENT_BOARD] );

    /// Labels
    char ch = 'A';

    for ( int x = 0; x < boardSize; ++x )
    {
        mvaddch(
            pUI->elements[UIELEMENT_BOARD].y - 1,
            ( x * 4 ) + pUI->elements[UIELEMENT_BOARD].x + 2,
            ch
        );

        mvaddch(
            pUI->elements[UIELEMENT_BOARD].y + pUI->elements[UIELEMENT_BOARD].height,
            ( x * 4 ) + pUI->elements[UIELEMENT_BOARD].x + 2,
            ch++
        );
    }

    ch = '1';
    for ( int y = 0; y < boardSize; ++y )
    {
        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->elements[UIELEMENT_BOARD].y - 2,
            pUI->elements[UIELEMENT_BOARD].x - 1,
            ch
        );

        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->elements[UIELEMENT_BOARD].y - 2,
            pUI->elements[UIELEMENT_BOARD].x + pUI->elements[UIELEMENT_BOARD].width,
            ch++
        );
    }
}

void renderUIContent( App const* const pApp );

#endif
