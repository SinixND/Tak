#ifndef IG20261003182749
#define IG20261003182749

#include "FileId.h"
#include "InputBuffer.h"
#include "Mappings.h"
#include "RankId.h"
#include "UIData.h"

/// Utility
typedef struct UIPosition
{
    int x;
    int y;
} UIPosition;

typedef struct Tile
{
    FileId fileX;
    RankId rankY;
} Tile;

/// Returns ui position under mouse
UIPosition getUIPosition(
    float mouseX,
    float mouseY,
    UIData const* const pUIData
);

/// Returns file and rank under mouse
Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize,
    UIData const* const pUIData
);

/// UI Mappings
void addUIElements( Mappings* const pMappings );

/// Normalize user input from backend
void getInputFromUser( InputBuffer* const pInput );

#endif
