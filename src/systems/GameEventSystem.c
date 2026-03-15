#include "GameEventSystem.h"

#include "ActionType.h"
#include "GameEvent.h"
#include <assert.h>

GameEvent newGameEvent( void )
{
    assert(
        !ACTION_TYPE_NONE
        && "(int)ACTION_TYPE_NONE must be 0"
    );

    GameEvent gameEvent = { 0 };

    return gameEvent;
}
