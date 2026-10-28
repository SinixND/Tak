#include "Render_Interface.h"

#ifdef BACKEND_RAYLIB
/// Only define once
#define RAYGUI_IMPLEMENTATION
/// Required for custom icons set
// #define RAYGUI_CUSTOM_ICONS
#include "Layout_Raylib.h"
#include "UI.h"
#include <assert.h>
#include <raygui.h>
#include <raylib.h>

void renderStatic( App const* const pApp );
void renderInfoPane( UI const* const pUI );
void renderStackBuffer( UI const* const pUI );
void renderPlayerInfo( UI const* const pUI );
void renderStackBuffer( UI const* const pUI );
void renderFileLabels( UI const* const pUI, int const boardSize );
void renderRankLabels( UI const* const pUI, int const boardSize );
void renderBoard( UI const* const pUI, int const boardSize );
void renderBoardEdges( UI const* const pUI, int const boardSize );

void renderDynamic( App const* const pApp );
void renderCommand( UI const* const pUI, Command const* const pCommand );
void renderHistory( UI const* const pUI, History const* const pHistory, int const entryCount );
void renderInfoPaneContent( App const* const pApp );
void renderStackBufferContent( App const* const pApp );
void renderBoardContent( App const* const pApp );
void renderSquareContent( App const* const pApp, int const squareIdx );

void renderStartScreen( UI const* const pUI );

void renderCommandGameEnd( App const* const pApp );

void render( App const* const pApp )
{
    BeginDrawing();

    ClearBackground( COLOR_BG );

    DrawFPS( 0, 0 );

    switch ( pApp->state )
    {
        default:
        {
            renderStatic( pApp );
            renderDynamic( pApp );

            break;
        }

        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            renderStartScreen( &pApp->uiData );

            break;
        }

        case APP_STATE_GAME_END:
        {
            renderStatic( pApp );
            renderDynamic( pApp );
            renderCommandGameEnd( pApp );

            break;
        }
    }

    EndDrawing();
}

void renderStatic( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    renderInfoPane( &pApp->uiData );

    int const boardSize = pApp->game.board.size;

    renderFileLabels(
        &pApp->uiData,
        boardSize
    );
    renderRankLabels(
        &pApp->uiData,
        boardSize
    );
}

void renderInfoPane( UI const* const pUI )
{
    renderStackBuffer( pUI );
    renderPlayerInfo( pUI );
}

void renderStackBuffer( UI const* const pUI )
{
    for ( int idx = 0; idx < ( LAYOUT_STACK_BUFFER_SIZE ); ++idx )
    {
        DrawTextEx(
            pUI->font,
            TextFormat( "%s", LAYOUT_STACK_BUFFER[idx] ),
            (Vector2){
                POSITION_STACK_BUFFER[0] * pUI->fontWidth,
                ( POSITION_STACK_BUFFER[1] + idx ) * pUI->fontSize,
            },
            pUI->fontSize,
            pUI->spacing,
            RAYWHITE
        );
    }
}

void renderPlayerInfo( UI const* const pUI )
{
    for ( int idx = 0; idx < ( LAYOUT_PLAYER_INFO_SIZE ); ++idx )
    {
        DrawTextEx(
            pUI->font,
            TextFormat( "%s", LAYOUT_PLAYER_INFO[idx] ),
            (Vector2){
                POSITION_PLAYER_INFO[0] * pUI->fontWidth,
                ( POSITION_PLAYER_INFO[1] + idx ) * pUI->fontSize,
            },
            pUI->fontSize,
            pUI->spacing,
            RAYWHITE
        );
    }
}

void renderFileLabels(
    UI const* const pUI,
    int const boardSize
)
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    // Top
    DrawTextEx(
        pUI->font,
        TextFormat(
            "%.*s", // Partly render file labels
            boardSize * 4,
            LAYOUT_LABELS_FILE
        ),
        (Vector2){
            BOARD_LABELS_X_LEFT * pUI->fontWidth,
            BOARD_LABELS_Y_TOP * pUI->fontSize,
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );

    // Bottom
    DrawTextEx(
        pUI->font,
        TextFormat(
            "%.*s", // Partly render file labels
            boardSize * 4,
            LAYOUT_LABELS_FILE
        ),
        (Vector2){
            BOARD_LABELS_X_LEFT * pUI->fontWidth,
            ( BOARD_LABELS_Y_TOP + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) ) * pUI->fontSize,
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );
}

void renderRankLabels(
    UI const* const pUI,
    int const boardSize
)
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    int const offsetIntoRankLabelsLayout
        = ( ( BOARD_SIZE_MAX - boardSize )
            * LAYOUT_BOARD_SQUARE_SIZE );

    // Left
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        DrawTextEx(
            pUI->font,
            TextFormat(
                "%s",
                LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
            ),
            (Vector2){
                BOARD_LABELS_X_LEFT * pUI->fontWidth,
                ( BOARD_LABELS_Y_TOP + y ) * pUI->fontSize,
            },
            pUI->fontSize,
            pUI->spacing,
            RAYWHITE
        );
    }

    // Right
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        DrawTextEx(
            pUI->font,
            TextFormat(
                "%s",
                LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
            ),
            (Vector2){
                ( BOARD_LABELS_X_LEFT + 1 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) + 1 ) * pUI->fontWidth,
                ( BOARD_LABELS_Y_TOP + y ) * pUI->fontSize,
            },
            pUI->fontSize,
            pUI->spacing,
            RAYWHITE
        );
    }
}

void renderDynamic( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );
}

void renderStartScreen( UI const* const pUI )
{
    DrawTextEx(
        pUI->font,
        "Choose board size:",
        (Vector2){
            1 * pUI->fontSize,
            1 * pUI->fontSize,
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );

    DrawTextEx(
        pUI->font,
        " 3x3                4x4",
        (Vector2){
            1 * pUI->fontSize,
            3 * pUI->fontSize
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );

    DrawTextEx(
        pUI->font,
        " 5x5 <- Standard    6x6",
        (Vector2){
            1 * pUI->fontSize,
            6 * pUI->fontSize
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );

    DrawTextEx(
        pUI->font,
        " 7x7                8x8",
        (Vector2){
            1 * pUI->fontSize,
            9 * pUI->fontSize
        },
        pUI->fontSize,
        pUI->spacing,
        RAYWHITE
    );
}

void renderCommandGameEnd( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    DrawTextEx(
        pApp->uiData.font,
        TextFormat(
            "%c: WIN! ",
            PLAYER_CHARS[pApp->game.activePlayer]
        ),
        (Vector2){
            50,
            50
        },
        pApp->uiData.fontSize,
        pApp->uiData.spacing,
        RAYWHITE
    );
}

#endif
