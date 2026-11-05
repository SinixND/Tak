#include "Render_Interface.h"

#ifdef BACKEND_NCURSES
#include "App.h"
#include "Constants_NCurses.h"
#include "GameScreenElementId.h"
#include "UI.h"
#include "UIElement.h"
#include <assert.h>
#include <ncurses.h>

void renderText( UIElement const* const pUIElement );
/// UI elements position and size needs to include border weight
void renderBox( UIElement const* const pUIElement );
void renderButton( UIElement const* const pUIElement );

void renderStartScreen( UI const* const pUI );
void renderUI( App const* const pApp );

void renderUndo( UI const* const pUI );
void renderRedo( UI const* const pUI );
void renderReset( UI const* const pUI );
void renderQuit( UI const* const pUI );

void renderStackBuffer( UI const* const pUI );

void renderInfo( UI const* const pUI );
void renderActivePlayer( UI const* const pUI );
void renderCommand( UI const* const pUI );
void renderHistory( UI const* const pUI );

void renderBoard( UI const* const pUI, int const boardSize );

void renderInfoContent( UI const* const pUI, Game const* const pGame );
void renderActivePlayerContent( UI const* const pUI, Game const* const pGame );
void renderCommandContent( UI const* const pUI, Game const* const pGame );
void renderHistoryContent( UI const* const pUI, Game const* const pGame );

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

    renderText( &pUI->selectScreenElements[UIELEMENT_CHOOSE_SIZE] );

    renderButton( &pUI->selectScreenElements[UIELEMENT_3x3] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_4x4] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_5x5] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_6x6] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_7x7] );
    renderButton( &pUI->selectScreenElements[UIELEMENT_8x8] );

    attroff( COLOR_PAIR( COLORS_UI ) );
}

void renderUI( App const* const pApp )
{
    /// Static
    attron( COLOR_PAIR( COLORS_UI ) );

    renderUndo( &pApp->ui );
    renderRedo( &pApp->ui );
    renderReset( &pApp->ui );
    renderQuit( &pApp->ui );

    renderStackBuffer( &pApp->ui );

    renderInfo( &pApp->ui );
    renderActivePlayer( &pApp->ui );
    renderCommand( &pApp->ui );
    renderHistory( &pApp->ui );

    renderBoard(
        &pApp->ui,
        pApp->game.board.size
    );

    attroff( COLOR_PAIR( COLORS_UI ) );

    /// Dynamic
    renderInfoContent(
        &pApp->ui,
        &pApp->game
    );

    renderActivePlayerContent(
        &pApp->ui,
        &pApp->game
    );

    renderCommandContent(
        &pApp->ui,
        &pApp->game
    );

    renderHistoryContent(
        &pApp->ui,
        &pApp->game
    );
}

void renderUndo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_UNDO].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_UNDO].y + y,
            pUI->gameScreenElements[UIELEMENT_UNDO].x,
            "<<"
        );
    }
}

void renderRedo( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_REDO].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_REDO].y + y,
            pUI->gameScreenElements[UIELEMENT_REDO].x,
            ">>"
        );
    }
}

void renderReset( UI const* const pUI )
{
    for ( int y = 0; y < pUI->gameScreenElements[UIELEMENT_RESET].height; ++y )
    {
        mvprintw(
            pUI->gameScreenElements[UIELEMENT_RESET].y + y,
            pUI->gameScreenElements[UIELEMENT_RESET].x,
            "|<"
        );
    }
}

void renderQuit( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_QUIT].y,
        pUI->gameScreenElements[UIELEMENT_QUIT].x,
        "\\/"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_QUIT].y + 1,
        pUI->gameScreenElements[UIELEMENT_QUIT].x,
        "/\\"
    );
}

void renderStackBuffer( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].y,
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].y + pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].height - 1,
        pUI->gameScreenElements[UIELEMENT_STACK_BUFFER].x,
        "+   +"
    );
}

void renderInfo( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "         R|C Score"
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "White:    |  "
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x,
        "Black:    |  "
    );
}

void renderActivePlayer( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x,
        "Active:       [ ]"
    );
}

void renderCommand( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_COMMAND].y,
        pUI->gameScreenElements[UIELEMENT_COMMAND].x,
        //"> B:Ma1+12345678",
        ">"
    );
}

void renderHistory( UI const* const pUI )
{
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_HISTORY].y,
        pUI->gameScreenElements[UIELEMENT_HISTORY].x,
        "History:"
    );
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
                ( y * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y,
                ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );

            mvprintw(
                ( y * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y + 4,
                ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x,
                "%s",
                "+   +"
            );
        }
    }

    /// Box
    renderBox( &pUI->gameScreenElements[UIELEMENT_BOARD] );

    /// Labels
    char ch = 'A';

    for ( int x = 0; x < boardSize; ++x )
    {
        mvaddch(
            pUI->gameScreenElements[UIELEMENT_BOARD].y - 1,
            ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x + 2,
            ch
        );

        mvaddch(
            pUI->gameScreenElements[UIELEMENT_BOARD].y + pUI->gameScreenElements[UIELEMENT_BOARD].height,
            ( x * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].x + 2,
            ch++
        );
    }

    ch = '1';
    for ( int y = 0; y < boardSize; ++y )
    {
        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y - 2,
            pUI->gameScreenElements[UIELEMENT_BOARD].x - 1,
            ch
        );

        mvaddch(
            ( ( boardSize - y ) * 4 ) + pUI->gameScreenElements[UIELEMENT_BOARD].y - 2,
            pUI->gameScreenElements[UIELEMENT_BOARD].x + pUI->gameScreenElements[UIELEMENT_BOARD].width,
            ch++
        );
    }
}

void renderInfoContent(
    UI const* const pUI,
    Game const* const pGame
)
{
    /// Stone counts
    attron( COLOR_PAIR( COLORS_DEFAULT ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 8,
        "%2i",
        pGame->reserves.regular[PLAYER_WHITE]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 11,
        "%i",
        pGame->reserves.capstone[PLAYER_WHITE]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 8,
        "%2i",
        pGame->reserves.regular[PLAYER_BLACK]
    );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 11,
        "%i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    /// Player scores
    attron( COLOR_PAIR( COLORS_PLAYER_WHITE_STRONG ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 1,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 14,
        "%2i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    attron( COLOR_PAIR( COLORS_PLAYER_BLACK_STRONG ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_INFO].y + 2,
        pUI->gameScreenElements[UIELEMENT_INFO].x + 14,
        "%2i",
        pGame->reserves.capstone[PLAYER_BLACK]
    );

    attroff( COLOR_PAIR( COLORS_PLAYER_BLACK_STRONG ) );
}

void renderActivePlayerContent(
    UI const* const pUI,
    Game const* const pGame
)
{
    attron( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x + 8,
        "%s",
        ( pGame->activePlayer == PLAYER_WHITE ) ? "WHITE" : "BLACK"
    );

    attroff( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_WEAK : COLORS_PLAYER_BLACK_WEAK ) );

    attron( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );
    mvprintw(
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y,
        pUI->gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x + 15,
        "%c",
        PLAYER_CHARS[pGame->activePlayer]
    );
    attroff( COLOR_PAIR( ( pGame->activePlayer == PLAYER_WHITE ) ? COLORS_PLAYER_WHITE_STRONG : COLORS_PLAYER_BLACK_STRONG ) );
}

void renderCommandContent(
    UI const* const pUI,
    Game const* const pGame
)
{
}

void renderHistoryContent(
    UI const* const pUI,
    Game const* const pGame
)
{
}

#endif
