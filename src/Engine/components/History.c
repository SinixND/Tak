#include "History.h"

History newHistory( void )
{
    History history = {
        .lastRecordIdx = 1,
        .totalRecords = 0,
    };

    for ( int idx = 0; idx < HISTORY_SIZE; ++idx )
    {
        history.records[idx] = newRecord();
    }

    return history;
}

