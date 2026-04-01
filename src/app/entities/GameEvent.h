#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief: Store multiple user inputs needed for a complete game event
 */
typedef union GameEvent
{
    ActionType actionType;

    struct
    {
        PlayerId stoneId;
        StoneType stoneType;
        FileId fileX;
        RankId rankY;
    } Place;

    struct
    {
        FileId fileX;
        RankId rankY;
    } Lift;

    struct
    {
        FileId fileX;
        RankId rankY;
        int8_t dropsDone; // Dropping none counts as drop
        int8_t stonesToDrop;
    } Drop;
} GameEvent;

#endif
