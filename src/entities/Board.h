#ifndef IG20251123234345
#define IG20251123234345

#include "GameConstants.h"
#include "Stack.h"
#include "StoneType.h"

/**
 * @brief A board consists of stacks of stones
 *
 * The affiliation of a stack is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of count 1
 * The board is represented by its stacks.
 * For board stacks Idx[0] is bottom
 */
typedef struct
{
    /// Stacks on board
    Stack stacks[STACKS_MAX];
    /// Types of stacks / top stones
    StoneType types[STACKS_MAX];
} Board;

#endif
