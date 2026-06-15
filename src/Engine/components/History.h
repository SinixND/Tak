#ifndef IG20260602231116
#define IG20260602231116

#include "Command.h"
#include "EngineConstants.h"
#include "Record.h"

/// First record stays empty -> totalRecords match max index
typedef struct History
{
    Record records[RECORD_COUNT];
    int lastRecordIdx;
    int totalRecords;
    Command commands[TURN_COUNT];
    int lastCommandIdx;
    int totalCommands;
} History;

/// Return initialized object
History newHistory( void );

#endif
