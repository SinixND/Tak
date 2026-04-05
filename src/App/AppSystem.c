#include "AppSystem.h"

#include "BackendInterface.h"
#include "GameEventSystem.h"
#include "GameSystem.h"
#include "HistorySystem.h"
#include "InputBufferSystem.h"
#include "InputSystem.h"
#include <assert.h>

App newApp( int const boardWidth )
{
    assert(
        ( boardWidth >= BOARD_WIDTH_MIN
          || !boardWidth )
        && "Board width value too small"
    );

    assert(
        ( boardWidth <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

    App app = {
        .game = newGame( boardWidth ),
        .inputBuffer = newInputBuffer(),
        .gameEvent = newGameEvent(),
        .history = newHistory(),
        .shouldClose = false,
    };

    return app;
}

void setupApp( void )
{
    setupBackend();
}

void runApp( App* const pApp )
{
    loopBackend( pApp );
}

void closeApp( void )
{
    closeBackend();
}

void updateFrame( App* const pApp )
{
    pollInput( &pApp->inputBuffer );
    handleGlobalInput( pApp );
}

void applyEvent(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    switch ( pEvent->actionType )
    {
        default:
        {
            assert( !"No action type set" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            applyEventPlace(
                pGame,
                pEvent
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            applyEventLift(
                pGame,
                pEvent
            );
            return;
        }

        case ACTION_TYPE_DROP:
        {
            applyEventDrop(
                pGame,
                pEvent
            );

            return;
        }
    }
}

void applyEventPlace(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    placeStone(
        pGame,
        pEvent->playerId,
        pEvent->fileX,
        pEvent->rankY,
        pEvent->stoneType
    );

    return;
}

void applyEventLift(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    liftStack(
        pGame,
        pEvent->fileX,
        pEvent->rankY
    );

    return;
}

void applyEventDrop(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    for ( int i = 0; i < pEvent->dropCount; ++i )
    {
        dropStone(
            pGame,
            pEvent->fileX,
            pEvent->rankY
        );
    }

    return;
}

