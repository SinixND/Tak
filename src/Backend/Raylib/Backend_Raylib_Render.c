#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
//* Only define once
#define RAYGUI_IMPLEMENTATION
//* Required for custom icons set
// #define RAYGUI_CUSTOM_ICONS
#include "Backend_Raylib_Layout.h"
#include "UIData.h"
#include <assert.h>
#include <raygui.h>
#include <raylib.h>

void renderStatic( App const* const pApp );
void renderInfoPane( UIData const* const pUIData );
// void renderFileLabels();
// void renderRankLabels();
// void renderBoard();
// void renderBoardEdges();

void renderDynamic( App const* const pApp );
// void renderCommand();
// void renderHistory();
// void renderInfoPaneContent();
// void renderStackBufferContent();
// void renderBoardContent();
// void renderSquareContent();

void renderStartScreen( App const* const pApp );

// void renderCommandGameEnd( App const* const pApp );

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
            renderStartScreen( pApp );

            break;
        }

        case APP_STATE_GAME_END:
        {
            renderStatic( pApp );
            renderDynamic( pApp );

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
    // renderFileLabels();
    // renderRankLabels();
    // renderBoard();
    // renderBoardEdges();
}

void renderInfoPane( UIData const* const pUIData )
{
    for ( int paneIdx = 0; paneIdx < ( LAYOUT_PANE_HEIGHT ); ++paneIdx )
    {
        // mvprintw(
        //     paneIdx,
        //     0,
        //     "%s",
        //     LAYOUT_INFO_PANE[paneIdx]
        // );
        DrawTextEx(
            pUIData->font,
            TextFormat( "%s", LAYOUT_INFO_PANE[paneIdx] ),
            (Vector2){
                paneIdx,
                0,
            },
            pUIData->fontSize,
            pUIData->spacing,
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

void renderStartScreen( App const* const pApp )
{
    DrawTextEx(
        pApp->uiData.font,
        "Choose board size. ",
        (Vector2){
            10.0f,
            10.0f
        },
        pApp->uiData.fontSize,
        pApp->uiData.spacing,
        RAYWHITE
    );

    DrawTextEx(
        pApp->uiData.font,
        TextFormat(
            "Options: %i - %i, confirm for default (%i)",
            BOARD_SIZE_MIN,
            BOARD_SIZE_MAX,
            BOARD_SIZE_DEFAULT
        ),
        (Vector2){
            10.0f,
            40.0f
        },
        pApp->uiData.fontSize,
        pApp->uiData.spacing,
        RAYWHITE
    );
}

#endif
