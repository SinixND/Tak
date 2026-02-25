#include "PlacementSystem.h"

#include "BoardSystem.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "StoneType.h"
#include <assert.h>

Game placeStoneOnBoard(
    Game game,
    PlayerId const playerId,
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
        ( ( game.board.types[stackIdx] != STONE_TYPE_CAP )
          && !( ( type != STONE_TYPE_CAP ) && ( game.board.types[stackIdx] == STONE_TYPE_WALL ) ) )
        && "Cant place stone"
    );

    game.players = takeFromReserves(
        game.players,
        playerId,
        type
    );

    game.board = putStoneOnStack(
        game.board,
        stackIdx,
        playerId,
        type
    );

    return game;
}
