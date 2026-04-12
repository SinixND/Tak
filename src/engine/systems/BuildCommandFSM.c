#include "BuildCommandFSM.h"

#include "Command.h"
#include "CommandStateId.h"
#include "InputBuffer.h"

void runBuildCommandFSM(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pCommand->state )
    {
        default:
            return;

        case STATE_GET_ACTION:
        {
            handleStateGetAction(
                pCommand,
                pInputBuffer
            );

            return;
        }
    }
}

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

    //* Change state
    switch ( pCommand->actionType )
    {
        default:
            return;

        case ACTION_TYPE_PLACE:
        {
            pCommand->state = STATE_GET_STONE_TYPE;

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            pCommand->state = STATE_GET_FILE_X;

            return;
        }
    }
}

