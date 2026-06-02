#include "History.h"

History newHistory( void )
{
    History history = {
        .recordIdx = 0,
    };

    for ( int idx = 0; idx < HISTORY_SIZE; ++idx )
    {
        history.records[idx] = newRecord();
    }

    return history;
}

