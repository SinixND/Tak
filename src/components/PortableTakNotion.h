#ifndef IG20260301185150
#define IG20260301185150

#include "ColumnId.h"
#include "RowId.h"
#include "StoneType.h"

/**
 *@brief: PTN object
 * Place: (stone)(square)
 * Move: (count)(square)(direction)(drops)(stone)
 *
 * To differantiate placement from moves: Moves have stoneType == STONE_TYPE_NONE
 */
typedef struct
{
    StoneType stackType;
    ColumnId column;
    RowId row;

} PortableTakNotion;

#endif
