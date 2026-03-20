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
    PlayerId playerId;
    ActionType actionType;
    FileId fileX;
    RankId rankY;
    StoneType stoneType;
    DirectionId direction;
} GameEvent;

#endif
