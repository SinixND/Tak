#include "Engine.h"

#include "Command.h"
#include "CommandValidation.h"
#include "InputParsing.h"

#include <stdbool.h>

void buildCommand( App* const pApp )
{
    //* Temporary command
    Command cmd = pApp->command;

    //* Set command value from input
    if ( !parseInput(
             &cmd,
             &pApp->inputBuffer
         ) )
    {
        return;
    }

    //* Validate input
    if ( !validateCommand(
             &cmd,
             &pApp->game
         ) )
    {
        return;
    }
}
