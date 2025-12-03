#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "GameSettings.h"
#include "MatchConstants.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

typedef struct
{
    GameSettings gameSettings;
    MatchConstants matchConstants;
    Players players;
    Stones stones;
    Stacks stacks;
    Board board;
} Game;

/// Provide boardSize 0 for default value
Game initGame( int const boardSize );
void run( Game* game );
void deinitGame( Game* game );

#endif
