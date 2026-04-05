#include "DemoSystem.h"

#include "App.h"
#include "AppSystem.h"
#include "BoardSystem.h"
#include "GameEventSystem.h"
#include "GameSystem.h"
#include "History.h"
#include "HistorySystem.h"
#include "PlayerId.h"
#include "StoneTypeId.h"

void demo( App* const pApp )
{
    placeStone(
        &pApp->game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    putOntoStack(
        &pApp->game.board,
        PLAYER_BLACK,
        0,
        STONE_TYPE_STANDING
    );

    liftStack(
        &pApp->game,
        0,
        0
    );

    dropStone(
        &pApp->game,
        0,
        1
    );

    validateEvent(
        &pApp->gameEvent,
        &pApp->game
    );

    pApp->gameEvent.actionType = ACTION_TYPE_PLACE;

    applyEvent(
        &pApp->game,
        &pApp->gameEvent
    );

    History history = newHistory();

    recordPlacementAction(
        &history,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    recordLiftAction(
        &history,
        0,
        STONE_TYPE_FLAT,
        1
    );

    recordDropAction(
        &history,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT,
        false
    );

    undoHistory( &history );
    redoHistory( &history );
}
