#ifndef IG20261017014302
#define IG20261017014302

#include "FileId.h"
#include "Input.h"
#include "RankId.h"
#include "UI.h"

typedef struct Tile
{
    FileId fileX;
    RankId rankY;
} Tile;

/// Get file/rank under cursor
Tile getTile(
    float const mouseX,
    float const mouseY,
    int const boardSize,
    UI const* const pUI
);

/// Normalize user input from backend
void readUserInput( Input* const pInput );

#endif
