#include "InputHandlingSystem.h"

#include "AppState.h"
#include "FileId.h"
#include "InputBuffer.h"
#include "InputId.h"
#include <assert.h>

void handleGlobalInput( App* const app )
{
    //* Conditionally terminate by
    //* changing main while loop condition
    app->shoudClose
        = ( app->inputBuffer.lastInput == INPUT_Q )
              ? true
              : false;
}

void handleStateInput( App* const app )
{
    switch ( app->state )
    {
        default:
        {
            assert( !"Invalid appState" );
        }

        case STATE_FIRST_TURN_CHOOSE_FILE_X:
        {
            parseInputForFileX( &app->inputBuffer );

            if ( app->inputBuffer.gameEvent.fileX >= FILE_A )
            {
                // app->state = STATE_FIRST_TURN_CHOOSE_RANK_Y;
            }

            return;
        }
    }
}

void parseInputForFileX( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            inputBuffer->gameEvent.fileX = FILE_NONE;

            return;
        }

        case INPUT_A:
        {
            inputBuffer->gameEvent.fileX = FILE_A;

            return;
        }

        case INPUT_B:
        {
            inputBuffer->gameEvent.fileX = FILE_B;

            return;
        }

        case INPUT_C:
        {
            inputBuffer->gameEvent.fileX = FILE_C;

            return;
        }

        case INPUT_D:
        {
            inputBuffer->gameEvent.fileX = FILE_D;

            return;
        }

        case INPUT_E:
        {
            inputBuffer->gameEvent.fileX = FILE_E;

            return;
        }

        case INPUT_F:
        {
            inputBuffer->gameEvent.fileX = FILE_F;

            return;
        }

        case INPUT_G:
        {
            inputBuffer->gameEvent.fileX = FILE_G;

            return;
        }

        case INPUT_H:
        {
            inputBuffer->gameEvent.fileX = FILE_H;

            return;
        }
    }
}
