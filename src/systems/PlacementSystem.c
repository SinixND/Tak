#include "PlacementSystem.h"

#include "PlayerSystem.h"
#include "PositionSystem.h"
#include "StackSystem.h"
#include "StoneType.h"
#include <assert.h>

void placeStoneOnBoard(
    Game game,
    int const player,
    int const positionX,
    int const positionY,
    StoneType const type
)
{
    int const stackIdx = positionToBoardIndex(
        positionX,
        positionY,
        game.matchConfigs.boardWidth
    );

    //* Can it be placed?
    assert(
        ( game.stacks.types[stackIdx] != CAP )
        && !( ( type != CAP ) && ( game.stacks.types[stackIdx] == WALL ) )
        && "Cant place stone"
    );

    game.players = takeFromReserves(
        game.players,
        player,
        type
    );

    game.stacks = putStoneOnStack(
        game.stacks,
        stackIdx,
        type
    );
}
