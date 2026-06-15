#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include <ncurses.h>

void setupBackend( void )
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

#if defined( PLATFORM_WEB )
    MaximizeWindow();
#endif

    SetTargetFPS( FPS_TARGET );
    // SetTextureFilter(
    //     GetFontDefault().texture,
    //     TEXTURE_FILTER_POINT
    // );

    /// Fonts
    // GameFont::load();

    // GuiSetStyle(
    //     DEFAULT,
    //     TEXT_SIZE,
    //     GameFont::fontSize
    // );
}

void closeBackend( void )
{
    /// Unload font
    unload();

    /// Close window and opengl context
    CloseWindow(); 
}

#endif
