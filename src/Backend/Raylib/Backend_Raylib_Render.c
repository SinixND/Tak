#include "BackendInterface.h"
#include "UIData.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include <assert.h>
#include <raylib.h>

void renderStatic( App const* const pApp );
void renderDynamic( App const* const pApp );
void renderStartScreen( App const* const pApp );

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
        (Vector2){ 10.0f, 10.0f },
        pApp->uiData.fontSize,
        1.0f,
        WHITE
    );

    DrawTextEx(
        pApp->uiData.font,
        TextFormat(
            "Options: %i - %i, confirm for default (%i)",
            BOARD_SIZE_MIN,
            BOARD_SIZE_MAX,
            BOARD_SIZE_DEFAULT
        ),
        (Vector2){ 10.0f, 40.0f },
        pApp->uiData.fontSize,
        1.0f,
        WHITE
    );
}

#endif
