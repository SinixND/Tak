#include "InputSystem.h"
#include "AppStateId.h"
#include "CommandId.h"
#include "InputBuffer.h"
#include "Keymap.h"
#include <assert.h>

void handleGlobalInput( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        &pApp->inputBuffer,
        CONTEXT_GLOBAL
    ) )
    {
        case COMMAND_QUIT:
        {
            pApp->shouldClose = true;

            return;
        }

        case COMMAND_UNDO:
        {
            pApp->state = APP_STATE_TURN_UNDO;

            return;
        }

        case COMMAND_REDO:
        {
            pApp->state = APP_STATE_TURN_REDO;

            return;
        }

        case COMMAND_RESET:
        {
            pApp->state = APP_STATE_TURN_RESET;

            return;
        }

        default:
            return;
    }
}
