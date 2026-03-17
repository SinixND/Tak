#ifndef IG20260315154123
#define IG20260315154123

#include "ActionType.h"
#include "DirectionId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"

/**
 * @brief: Store multiple user inputs needed for a complete PlayerAction
 */
typedef struct
{
    PlayerId playerId;     // white, black
    ActionType actionType; // place, lift, drop

    union
    {
        struct
        {
            FileId fileX;
            RankId rankY;
            StoneType stoneType;
        } Place;

        struct
        {
            FileId fileX;
            RankId rankY;
            DirectionId direction;
        } Lift;

        struct
        {
            FileId fileX;
            RankId rankY;
        } Drop;
    } Action;
} GameEvent;

#endif
