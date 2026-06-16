#ifndef IG20260601172328
#define IG20260601172328

#include "ActionTypeId.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/// History data for place event
typedef struct DataPlace
{
    int8_t squareIdx;
    PlayerId playerId;
    StoneType stoneType;
} DataPlace;

/// History data for lift event
typedef struct DataLift
{
    int8_t squareIdx;
} DataLift;

/// History data for drop event
typedef struct DataDrop
{
    int8_t squareIdx;
    int8_t dropCount;
    bool flattened;
} DataDrop;

/// History entry
typedef struct Record
{
    ActionType actionType;
    union
    {
        DataPlace place;
        DataLift lift;
        DataDrop drop;
    } Data;
} Record;

/// Return initialized object
Record newRecord( void );

#endif
