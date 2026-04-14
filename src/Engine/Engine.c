#include "Engine.h"
#include "Command.h"

#include <stdbool.h>

void buildCommand( App* const pApp )
{
    if ( !parseInput(
             &pApp->command,
             &pApp->inputBuffer
         ) )
    {
        return;
    }
}

/*
void handleStateGetAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputAction(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    CommandStateId const nextState
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? STATE_GET_STONE_TYPE
              //* == ACTION_TYPE_LIFT
              : STATE_GET_FILE_X;

    //* Change state
    pCommand->state = nextState;

    return;
}

void handleStateGetStoneType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputStoneType(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    pCommand->state = STATE_GET_FILE_X;

    return;
}

void handleStateGetFileX(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputFileX(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    pCommand->state = STATE_GET_RANK_Y;

    return;
}

void handleStateGetRankY(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputRankY(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    CommandStateId const nextState
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? STATE_GET_ACTION
              //* == ACTION_TYPE_LIFT
              : STATE_GET_DIRECTION;

    ActionType const nextActionType
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? ACTION_TYPE_NONE
              //* == ACTION_TYPE_LIFT
              : ACTION_TYPE_DROP;

    //* Change state
    pCommand->state = nextState;
    //* Update command action type
    pCommand->actionType = nextActionType;

    return;
}

void handleStateGetDirection(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputDirection(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    pCommand->state = STATE_GET_FIRST_DROP_AMOUNT;

    return;
}

void handleStateGetFirstDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputFirstDropAmount(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    // TODO: Check if more drops possible/required

    //* Change state
    pCommand->state = STATE_GET_DROP_AMOUNT;

    return;
}

void handleStateGetDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputDropAmount(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    // TODO: Check if more drops possible/required

    //* Change state
    pCommand->state = STATE_GET_ACTION;

    return;
}

*/
