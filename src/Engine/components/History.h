#ifndef IG20260602231116
#define IG20260602231116

#include "EngineConstants.h"
#include "Record.h"

typedef struct History
{
    Record records[HISTORY_SIZE];
    int recordIdx;
} History;

/// Return initialized History object
History newHistory( void );

#endif
