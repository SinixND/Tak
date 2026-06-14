#include "History.h"
#include "CommandId.h"
#include "PlayerId.h"

History newHistory( void )
{
    History history = {
        .lastRecordIdx = 0,
        .totalRecords = 0,
        .lastCommandIdx = 0,
        .totalCommands = 0,
    };

    for ( int idx = 0; idx < RECORD_COUNT; ++idx )
    {
        history.records[idx] = newRecord();
    }

    for ( int idx = 0; idx < COMMAND_COUNT; ++idx )
    {
        history.commands[idx] = newCommand( PLAYER_NONE );
    }

    return history;
}

