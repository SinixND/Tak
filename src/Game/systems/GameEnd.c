#include "GameEnd.h"

#include "Board.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PathSquare.h"
#include "PlayerId.h"
#include "Position.h"
#include "RankId.h"
#include <assert.h>

bool satisfiesWinCondition(
    Game const* const pGame,
    PlayerId const playerId
)
{
    return (
        checkRoadCondition(
            &pGame->board,
            playerId
        )
    );
}

bool checkRoadCondition(
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

    initPathSquares(
        pathSquares,
        pBoard,
        playerId
    );

    /// Check road starting squares
    for ( int fileX = 0; fileX < pBoard->size; ++fileX )
    {
        int const rootSquareIdx = fileX;

        /// Root must be valid
        if ( !pathSquares[rootSquareIdx].isValid )
        {
            continue;
        }

        /// Update root square
        pathSquares[rootSquareIdx].wasChecked = true;

        /// Continue path finding with first neighbor (required to be in RANK_2)
        if ( findVerticalRoad(
                 pathSquares,
                 fileX,
                 RANK_2,
                 pBoard->size
             ) )
        {
            return true;
        };
    }

    /// Check for horizontal road roots
    for ( int rankY = 0; rankY < pBoard->size; ++rankY )
    {
        int const rootSquareIdx = positionToSquare(
            FILE_A,
            rankY,
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
        if ( findHorizontalRoad(
                 pathSquares,
                 FILE_B,
                 rankY,
                 pBoard->size
             ) )
        {
            return true;
        };
    }

    return false;
}

void initPathSquares(
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

bool findVerticalRoad(
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
        findVerticalRoad(
            pathSquares,
            // ( squareIdx + boardSize ),
            fileX,
            rankY + 1,
            boardSize
        )
        /// Down
        || findVerticalRoad(
            pathSquares,
            fileX,
            rankY - 1,
            boardSize
        )
        /// Left
        || findVerticalRoad(
            pathSquares,
            fileX - 1,
            rankY,
            boardSize
        )
        /// Right
        || findVerticalRoad(
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

bool findHorizontalRoad(
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
        findHorizontalRoad(
            pathSquares,
            // ( squareIdx + boardSize ),
            fileX,
            rankY + 1,
            boardSize
        )
        /// Down
        || findHorizontalRoad(
            pathSquares,
            fileX,
            rankY - 1,
            boardSize
        )
        /// Left
        || findHorizontalRoad(
            pathSquares,
            fileX - 1,
            rankY,
            boardSize
        )
        /// Right
        || findHorizontalRoad(
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
