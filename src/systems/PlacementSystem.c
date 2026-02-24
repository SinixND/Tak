#include "PlacementSystem.h"

#include "BoardSystem.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "StoneType.h"
#include <assert.h>

Game placeStoneOnBoard(
    Game game,
    int const playerIdx,
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
        ( ( game.board.types[stackIdx] != CAP )
          && !( ( type != CAP ) && ( game.board.types[stackIdx] == WALL ) ) )
        && "Cant place stone"
    );

    game.players = takeFromReserves(
        game.players,
        playerIdx,
        type
    );

    game.board = putStoneOnStack(
        game.board,
        stackIdx,
        playerIdx,
        type
    );

    return game;
}
