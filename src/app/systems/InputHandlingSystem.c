#include "InputHandlingSystem.h"

#include "ActionType.h"
#include "AppState.h"
#include "DirectionId.h"
#include "FileId.h"
#include "InputBuffer.h"
#include "InputId.h"
#include "RankId.h"
#include "StoneType.h"
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

void parseInputForAction( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_NONE;

            return;
        }

        case INPUT_P:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_PLACE;

            return;
        }

        case INPUT_L:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_LIFT;

            return;
        }

        case INPUT_D:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_DROP;

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

void parseInputForRankY( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            inputBuffer->gameEvent.rankY = RANK_NONE;

            return;
        }

        case INPUT_1:
        {
            inputBuffer->gameEvent.rankY = RANK_1;

            return;
        }

        case INPUT_2:
        {
            inputBuffer->gameEvent.rankY = RANK_2;

            return;
        }

        case INPUT_3:
        {
            inputBuffer->gameEvent.rankY = RANK_3;

            return;
        }

        case INPUT_4:
        {
            inputBuffer->gameEvent.rankY = RANK_4;

            return;
        }

        case INPUT_5:
        {
            inputBuffer->gameEvent.rankY = RANK_5;

            return;
        }

        case INPUT_6:
        {
            inputBuffer->gameEvent.rankY = RANK_6;

            return;
        }

        case INPUT_7:
        {
            inputBuffer->gameEvent.rankY = RANK_7;

            return;
        }

        case INPUT_8:
        {
            inputBuffer->gameEvent.rankY = RANK_8;

            return;
        }
    }
}

void parseInputForStoneType( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_NONE;

            return;
        }

        case INPUT_F:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_FLAT;

            return;
        }

        case INPUT_S:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_STANDING;

            return;
        }

        case INPUT_C:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_CAP;

            return;
        }
    }
}

void parseInputForDirection( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            inputBuffer->gameEvent.direction = DIR_NONE;

            return;
        }

        case INPUT_N:
        {
            inputBuffer->gameEvent.direction = DIR_UP;

            return;
        }

        case INPUT_E:
        {
            inputBuffer->gameEvent.direction = DIR_RIGHT;

            return;
        }

        case INPUT_S:
        {
            inputBuffer->gameEvent.direction = DIR_DOWN;

            return;
        }

        case INPUT_W:
        {
            inputBuffer->gameEvent.direction = DIR_LEFT;

            return;
        }
    }
}

