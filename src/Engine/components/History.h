#ifndef IG20260602231116
#define IG20260602231116

#include "EngineConstants.h"
#include "Record.h"

/// First record stays empty -> totalRecords match max index
typedef struct History
{
    Record records[HISTORY_SIZE];
    int lastRecordIdx;
    int totalRecords;
} History;

/// Return initialized object
History newHistory( void );

#endif
