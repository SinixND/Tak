#include "GameEnd.h"

#include "Board.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PathSquare.h"
#include "PlayerId.h"
#include "Position.h"
#include "RankId.h"
#include <assert.h>

bool isWinConditionMet(
    Game const* const pGame,
    PlayerId const playerId
)
{
    return (
        isRoadComplete(
            &pGame->board,
            playerId
        )
    );
}

bool isRoadComplete(
    Board const* const pBoard,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE
          || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    PathSquare pathSquares[SQUARES_MAX];
    resetPathSquares( pathSquares );

    updatePathSquares(
        pathSquares,
        pBoard,
        playerId
    );

    /// Check vertical road starting squares
    for ( int rootFileX = 0; rootFileX < pBoard->size; ++rootFileX )
    {
        int const rootSquareIdx = rootFileX;

        /// Root must be valid
        if ( !pathSquares[rootSquareIdx].isValid )
        {
            continue;
        }

        /// Update root square
        pathSquares[rootSquareIdx].wasChecked = true;

        /// Continue path finding with first neighbor (required to be in RANK_2)
        if ( isRoadCompleteVertical(
                 pathSquares,
                 rootFileX,
                 RANK_2,
                 pBoard->size
             ) )
        {
            return true;
        };
    }

    /// Check horizontal road starting squares
    resetPathSquares( pathSquares );

    updatePathSquares(
        pathSquares,
        pBoard,
        playerId
    );

    for ( int rootRankY = 0; rootRankY < pBoard->size; ++rootRankY )
    {
        int const rootSquareIdx = positionToSquare(
            FILE_A,
            rootRankY,
            pBoard->size
        );

        /// Root must be valid
        if ( !pathSquares[rootSquareIdx].isValid )
        {
            continue;
        }

        /// Update root square
        pathSquares[rootSquareIdx].wasChecked = true;

        /// Continue path finding with first neighbor (required to be in FILE_B)
        if ( isRoadCompleteHorizontal(
                 pathSquares,
                 FILE_B,
                 rootRankY,
                 pBoard->size
             ) )
        {
            return true;
        };
    }

    return false;
}

void resetPathSquares( PathSquare pathSquares[SQUARES_MAX] )
{
    for ( int squareIdx = 0; squareIdx < SQUARES_MAX; ++squareIdx )
    {
        pathSquares[squareIdx].isValid = false;
        pathSquares[squareIdx].wasChecked = false;
    }
}

void updatePathSquares(
    PathSquare pathSquares[SQUARES_MAX],
    Board const* const pBoard,
    PlayerId const playerId
)
{
    for ( int squareIdx = 0; squareIdx < SQUARES_MAX; ++squareIdx )
    {
        pathSquares[squareIdx].isValid = isSquareValid(
            pBoard,
            squareIdx,
            playerId
        );

        pathSquares[squareIdx].wasChecked = false;
    }
}

bool isSquareValid(
    Board const* const pBoard,
    int const squareIdx,
    PlayerId const playerId
)
{
    return (
        /// Player owns square
        ( pBoard->stackIds[squareIdx]
          == playerId )
        /// Square counts towards path
        && ( ( pBoard->stackTypes[squareIdx] == STONE_TYPE_FLAT )
             || ( pBoard->stackTypes[squareIdx] == STONE_TYPE_CAP ) )
    );
}

bool isRoadCompleteVertical(
    PathSquare* const pathSquares,
    FileId const fileX,
    RankId const rankY,
    int const boardSize
)
{
    /// Check out of bounds
    if ( !(
             ( fileX >= 0 )
             && ( fileX < boardSize )
             && ( rankY >= 0 )
             && ( rankY < boardSize )
         ) )
    {
        return false;
    };

    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        boardSize
    );

    /// Skip if invalid or forms circle
    if (
        !pathSquares[squareIdx].isValid
        || pathSquares[squareIdx].wasChecked
    )
    {
        return false;
    };

    /// If path reached the other side
    if ( rankY == ( boardSize - 1 ) )
    {
        return true;
    }

    /// Update square
    pathSquares[squareIdx].wasChecked = true;

    /// Check neighbors
    if (
        /// Up
        isRoadCompleteVertical(
            pathSquares,
            // ( squareIdx + boardSize ),
            fileX,
            rankY + 1,
            boardSize
        )
        /// Down
        || isRoadCompleteVertical(
            pathSquares,
            fileX,
            rankY - 1,
            boardSize
        )
        /// Left
        || isRoadCompleteVertical(
            pathSquares,
            fileX - 1,
            rankY,
            boardSize
        )
        /// Right
        || isRoadCompleteVertical(
            pathSquares,
            fileX + 1,
            rankY,
            boardSize
        )
    )
    {
        return true;
    }

    return false;
}

bool isRoadCompleteHorizontal(
    PathSquare* const pathSquares,
    FileId const fileX,
    RankId const rankY,
    int const boardSize
)
{
    /// Check out of bounds
    if ( !(
             ( fileX >= 0 )
             && ( fileX < boardSize )
             && ( rankY >= 0 )
             && ( rankY < boardSize )
         ) )
    {
        return false;
    };

    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        boardSize
    );

    /// Skip if...
    if (
        /// ... path cannot continue here
        !pathSquares[squareIdx].isValid
        /// ... already checked
        || pathSquares[squareIdx].wasChecked
    )
    {
        return false;
    };

    /// If path reached the other side
    if ( fileX == ( boardSize - 1 ) )
    {
        return true;
    }

    /// Update square
    pathSquares[squareIdx].wasChecked = true;

    /// Check neighbors
    if (
        /// Up
        isRoadCompleteHorizontal(
            pathSquares,
            // ( squareIdx + boardSize ),
            fileX,
            rankY + 1,
            boardSize
        )
        /// Down
        || isRoadCompleteHorizontal(
            pathSquares,
            fileX,
            rankY - 1,
            boardSize
        )
        /// Left
        || isRoadCompleteHorizontal(
            pathSquares,
            fileX - 1,
            rankY,
            boardSize
        )
        /// Right
        || isRoadCompleteHorizontal(
            pathSquares,
            fileX + 1,
            rankY,
            boardSize
        )
    )
    {
        return true;
    }

    return false;
}
