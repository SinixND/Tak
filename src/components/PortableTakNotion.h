#ifndef IG20260301185150
#define IG20260301185150

#include "FileId.h"
#include "RankId.h"
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
    FileId file; // Column
    RankId rank; // Row
} PortableTakNotion;

#endif
