#include "GameEventSystem.h"

#include "ActionTypeId.h"
#include "DirectionSystem.h"
#include "GameEvent.h"
#include "PositionSystem.h"
#include "StoneTypeId.h"
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    GameEvent event = {
        .stoneId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .liftCount = 0,
        .dropCounts = { 0 },
        .dropCountsSize = 0,
        .droppedCount = 0
    };

    for ( int idx = 0; idx < BOARD_WIDTH_MAX; ++idx )
    {
        event.dropCounts[idx] = -1;
    }

    return event;
}

bool validateEvent(
    GameEvent const* const event,
    Game const* const game
)
{
    switch ( event->actionType )
    {
        default:
            return false;

        case ACTION_TYPE_PLACE:
        {
            return validateEventPlace(
                event,
                game
            );
        }

        case ACTION_TYPE_LIFT:
        {
            return validateEventLift(
                event,
                game
            );
        }

        case ACTION_TYPE_DROP:
        {
            return validateEventDrop(
                event,
                game
            );
        }
    }

    return false;
}

bool validateEventPlace(
    GameEvent const* const event,
    Game const* const game
)
{
    //* Stone type available
    if ( !isStoneTypeAvailable(
             event,
             &game->players
         ) )
    {
        return false;
    }

    //* FileX on board
    if ( !isFileXOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    //* Can only place on empty square
    if ( !isSquareEmpty( event, &game->board ) )
    {
        return true;
    }

    return true;
}

bool validateEventLift(
    GameEvent const* const event,
    Game const* const game
)
{
    //* FileX on board
    if ( !isFileXOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    //* Must lift at least one stone
    if ( isSquareEmpty(
             event,
             &game->board
         ) )
    {
        return false;
    }

    //* Player must own square
    if ( doesPlayerOwnStack(
             event,
             &game->board
         ) )
    {
        return false;
    }

    return true;
}

bool validateEventDrop(
    GameEvent const* const event,
    Game const* const game
)
{
    //* Validate position
    if ( !isOffsetXOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    if ( !isOffsetYOnBoard(
             event,
             game->board.width
         ) )
    {
        return false;
    }

    //* Top vs. captive must obey rules
    if ( !isCaptiveValid(
             event,
             &game->board
         ) )
    {
        return false;
    }

    return true;
}

bool isStoneTypeAvailable(
    GameEvent const* const event,
    Players const* const players
)
{
    if ( event->stoneType != STONE_TYPE_CAP )
    {
        if ( players->reservesRegular[event->stoneId] > 0 )
        {
            return true;
        }
    }
    else
    {
        if ( players->reservesCapstone[event->stoneId] > 0 )
        {
            return true;
        }
    }

    return false;
}

bool isFileXOnBoard(
    GameEvent const* const event,
    int const boardWidth
)
{
    int const pos = event->fileX;

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}

bool isRankYOnBoard(
    GameEvent const* const event,
    int const boardWidth
)
{
    int const pos = event->rankY;

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}

bool isSquareEmpty(
    GameEvent const* const event,
    Board const* const board
)
{
    return ( board->stoneCounts[positionToSquare(
                 event->fileX,
                 event->rankY,
                 board->width
             )]
             > 0 )
               ? false
               : true;
}

bool doesPlayerOwnStack(
    GameEvent const* const event,
    Board const* const board
)
{
    int const squareIdx = positionToSquare(
        event->fileX,
        event->rankY,
        board->width
    );

    return ( board->stoneIds[squareIdx + board->stoneCounts[squareIdx] - 1]
             == event->stoneId )
               ? true
               : false;
}

bool isCaptiveValid(
    GameEvent const* const event,
    Board const* const board
)
{
    int const squareIdx = positionToSquare(
        event->fileX,
        event->rankY,
        board->width
    );

    StoneType const captiveType = board->types[squareIdx];
    StoneType const droppedType = event->stoneType;

    /// Nothing can be placed on capstone
    if ( captiveType == STONE_TYPE_CAP )
    {
        return false;
    }

    /// Only capstone can flatten standing
    if ( captiveType == STONE_TYPE_STANDING && droppedType != STONE_TYPE_CAP )
    {
        return false;
    }

    return true;
}

bool isOffsetXOnBoard(
    GameEvent const* const event,
    int const boardWidth
)
{
    int const pos
        = event->fileX
          + ( getOffsetX( event->direction )
              * ( event->dropCountsSize - 1 ) );

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}

bool isOffsetYOnBoard(
    GameEvent const* const event,
    int const boardWidth
)
{
    int const pos
        = event->fileX
          + ( getOffsetY( event->direction )
              * ( event->dropCountsSize - 1 ) );

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}
