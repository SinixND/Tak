#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"
#include "FileId.h"
#include "RankId.h"
#include "UIData.h"

/// Utility
typedef struct Tile
{
    FileId fileX;
    RankId rankY;
} Tile;

/// Returns file and rank under mouse
Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize
);

/// Context

/// Setup backend context
void setupBackend( UIData* const pUIData );

/// Close backend context
void closeBackend( UIData const* const pUIData );

/// Timing

/// Delay execution for n milliseconds
void wait( int const ms );

/// Input

/// Normalize user input from backend
void getInputFromUser( InputBuffer* const pInput );

/// Render

/// Render app state
void render( App const* const pApp );

#endif
