#ifndef IG20260308205300
#define IG20260308205300

#include "GameConstants.h"
#include "HistoryRecord.h"
#include <stdint.h>

/// Stack to store player actions
typedef struct History
{
    /// Stack to store the records to be undone
    HistoryRecord records[HISTORY_SIZE];
    /// Track index of last record that can be undone
    int16_t lastRecordIdx;
    /// Track count of records that can be redone
    uint16_t redoCount;
} History;

#endif
