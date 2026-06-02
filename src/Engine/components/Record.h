#ifndef IG20260601172328
#define IG20260601172328

#include "ActionTypeId.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct Place
{
    int8_t squareIdx;
    PlayerId playerId;
    StoneType stoneType;
} Place;

typedef struct Lift
{
    int8_t squareIdx;
} Lift;

typedef struct Drop
{
    int8_t squareIdx;
    int8_t dropCount;
    bool flattened;
} Drop;

typedef struct Record
{
    ActionType actionType;
    union
    {
        Place place;
        Lift lift;
        Drop drop;
    } Data;
} Record;

/// Return initialized Record object
Record newRecord( void );

#endif
