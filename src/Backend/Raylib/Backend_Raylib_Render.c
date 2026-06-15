#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include <assert.h>
#include <raylib.h>

void renderStatic( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    BeginDrawing();
    ClearBackground( COLOR_BG );
    EndDrawing();
}

void renderDynamic( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    BeginDrawing();
    ClearBackground( COLOR_BG );
    EndDrawing();
}

void renderStartScreen( void )
{
    BeginDrawing();

    DrawText( "Choose board size. ", 10, 10, 11, RAYWHITE );

    DrawText(
        TextFormat(
            "Options: %i - %i, confirm for default (%i)",
            BOARD_SIZE_MIN,
            BOARD_SIZE_MAX,
            BOARD_SIZE_DEFAULT
        ),
        20,
        10,
        11,
        RAYWHITE
    );

    EndDrawing();
}

#endif
