#include "GameEventSystem.h"
#include "ActionType.h"
#include "GameEvent.h"

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
    //
}

bool validateEventLift(
    GameEvent const* const event,
    Game const* const game
)
{
}

bool validateEventDrop(
    GameEvent const* const event,
    Game const* const game
)
{
}
