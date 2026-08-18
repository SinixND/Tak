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
void renderStackBuffer( UIData const* const pUIData );
void renderPlayerInfo( UIData const* const pUIData );
void renderStackBuffer( UIData const* const pUIData );
void renderFileLabels( UIData const* const pUIData, int const boardSize );
void renderRankLabels( UIData const* const pUIData, int const boardSize );
void renderBoard( UIData const* const pUIData, int const boardSize );
void renderBoardEdges( UIData const* const pUIData, int const boardSize );

void renderDynamic( App const* const pApp );
void renderCommand( UIData const* const pUIData, Command const* const pCommand );
void renderHistory( UIData const* const pUIData, History const* const pHistory, int const entryCount );
void renderInfoPaneContent( App const* const pApp );
void renderStackBufferContent( App const* const pApp );
void renderBoardContent( App const* const pApp );
void renderSquareContent( App const* const pApp, int const squareIdx );

void renderStartScreen( UIData const* const pUIData );

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

void renderInfoPane( UIData const* const pUIData )
{
    renderStackBuffer( pUIData );
    renderPlayerInfo( pUIData );
}

void renderStackBuffer( UIData const* const pUIData )
{
    for ( int idx = 0; idx < ( LAYOUT_STACK_BUFFER_SIZE ); ++idx )
    {
        DrawTextEx(
            pUIData->font,
            TextFormat( "%s", LAYOUT_STACK_BUFFER[idx] ),
            (Vector2){
                POSITION_STACK_BUFFER[0] * pUIData->fontWidth,
                ( POSITION_STACK_BUFFER[1] + idx ) * pUIData->fontSize,
            },
            pUIData->fontSize,
            pUIData->spacing,
            RAYWHITE
        );
    }
}

void renderPlayerInfo( UIData const* const pUIData )
{
    for ( int idx = 0; idx < ( LAYOUT_PLAYER_INFO_SIZE ); ++idx )
    {
        DrawTextEx(
            pUIData->font,
            TextFormat( "%s", LAYOUT_PLAYER_INFO[idx] ),
            (Vector2){
                POSITION_PLAYER_INFO[0] * pUIData->fontWidth,
                ( POSITION_PLAYER_INFO[1] + idx ) * pUIData->fontSize,
            },
            pUIData->fontSize,
            pUIData->spacing,
            RAYWHITE
        );
    }
}

void renderFileLabels(
    UIData const* const pUIData,
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
        pUIData->font,
        TextFormat(
            "%.*s", // Partly render file labels
            boardSize * 4,
            LAYOUT_LABELS_FILE
        ),
        (Vector2){
            BOARD_LABELS_X_LEFT * pUIData->fontWidth,
            BOARD_LABELS_Y_TOP * pUIData->fontSize,
        },
        pUIData->fontSize,
        pUIData->spacing,
        RAYWHITE
    );

    // Bottom
    DrawTextEx(
        pUIData->font,
        TextFormat(
            "%.*s", // Partly render file labels
            boardSize * 4,
            LAYOUT_LABELS_FILE
        ),
        (Vector2){
            BOARD_LABELS_X_LEFT * pUIData->fontWidth,
            ( BOARD_LABELS_Y_TOP + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) ) * pUIData->fontSize,
        },
        pUIData->fontSize,
        pUIData->spacing,
        RAYWHITE
    );
}

void renderRankLabels(
    UIData const* const pUIData,
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
            pUIData->font,
            TextFormat(
                "%s",
                LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
            ),
            (Vector2){
                BOARD_LABELS_X_LEFT * pUIData->fontWidth,
                ( BOARD_LABELS_Y_TOP + y ) * pUIData->fontSize,
            },
            pUIData->fontSize,
            pUIData->spacing,
            RAYWHITE
        );
    }

    // Right
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        DrawTextEx(
            pUIData->font,
            TextFormat(
                "%s",
                LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
            ),
            (Vector2){
                ( BOARD_LABELS_X_LEFT + 1 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) + 1 ) * pUIData->fontWidth,
                ( BOARD_LABELS_Y_TOP + y ) * pUIData->fontSize,
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

void renderStartScreen( UIData const* const pUIData )
{
    DrawTextEx(
        pUIData->font,
        "Choose board size. ",
        (Vector2){
            10.0f,
            10.0f
        },
        pUIData->fontSize,
        pUIData->spacing,
        RAYWHITE
    );

    DrawTextEx(
        pUIData->font,
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
        pUIData->fontSize,
        pUIData->spacing,
        RAYWHITE
    );
}

#endif
