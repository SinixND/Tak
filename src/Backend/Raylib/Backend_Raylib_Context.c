#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include "UIData.h"
#include <raylib.h>

void setupBackend( UIData* uiData )
{
    // TODO: Finish function
    /// Raylib flags
    SetConfigFlags( FLAG_WINDOW_RESIZABLE );
    SetConfigFlags( FLAG_VSYNC_HINT );

    /// Initialize window
    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Tak"
    );

    /// Raylib Settings
    // SetWindowIcon( AppData::FAVICON );
    SetWindowMinSize(
        WINDOW_WIDTH_MIN,
        WINDOW_HEIGHT_MIN
    );

    /// Font
    uiData->font = LoadFontEx(
        "assets/fonts/LiberationMono-Regular.ttf",
        uiData->fontSize,
        0,
        0
    );

#if defined( PLATFORM_WEB )
    MaximizeWindow();
#endif

    SetTargetFPS( FPS_TARGET );
}

void closeBackend( UIData* uiData )
{
    UnloadFont( uiData->font );
    /// Close window and opengl context
    CloseWindow();
}

#endif
