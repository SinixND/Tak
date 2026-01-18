#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "GameSettings.h"
#include "MatchConfigs.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

typedef struct
{
    GameSettings gameSettings;
    MatchConfigs matchConfigs;
    Players players;
    Stones stones;
    Stacks stacks;
    Board board;
} Game;

/// Provide boardWidth 0 for default value
Game initGame( int const boardWidth );
// void run( Game* game );
void deinitGame( Game* game );

#endif
