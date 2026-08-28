#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include "UIData.h"
#include <raylib.h>

Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize
)
{
    Tile tile = { FILE_NONE, RANK_NONE };

    if (
        ( ( (int)mouseX - ( BOARD_POS_X + 1 ) ) % 4 )
        && ( (int)mouseY - BOARD_POS_Y ) % 4
    )
    {
        tile.fileX
            = ( (int)mouseX - ( BOARD_POS_X + 1 ) ) / 4;

        tile.rankY
            = ( boardSize - 1 ) - ( ( (int)mouseY - 1 ) / 4 );
    }

    return tile;
}
void setupBackend( UIData* const pUIData )
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
    pUIData->font = LoadFontEx(
        "assets/fonts/LiberationMono-Regular.ttf",
        pUIData->fontSize,
        0,
        0
    );
    pUIData->fontWidth
        = MeasureTextEx(
              pUIData->font,
              "X",
              pUIData->fontSize,
              pUIData->spacing
        )
              .x;

#if defined( PLATFORM_WEB )
    MaximizeWindow();
#endif

    SetTargetFPS( FPS_TARGET );
}

void closeBackend( UIData const* const pUIData )
{
    UnloadFont( pUIData->font );
    /// Close window and opengl context
    CloseWindow();
}

#endif
