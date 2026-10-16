#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "BackendLayout_Raylib.h"
#include "UI.h"
#include <raylib.h>

void setupBackend( UI* const pUI )
{
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
    pUI->font = LoadFontEx(
        "assets/fonts/LiberationMono-Regular.ttf",
        pUI->fontSize,
        0,
        0
    );

    pUI->fontWidth
        = MeasureTextEx(
              pUI->font,
              "X",
              pUI->fontSize,
              pUI->spacing
        )
              .x;

#if defined( PLATFORM_WEB )
    MaximizeWindow();
#endif

    SetTargetFPS( FPS_TARGET );
}

void closeBackend( UI const* const pUI )
{
    UnloadFont( pUI->font );
    /// Close window and opengl context
    CloseWindow();
}

#endif
