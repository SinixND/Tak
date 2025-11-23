#ifndef IG20251123234345
#define IG20251123234345

#include "StoneType.h"

/**
 * @brief A tile holds stacks
 *
 * The board contains stacks
 * A stacks affiliation is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of height 1
 */
typedef struct
{
    /// Height of stack including top stone
    int* heights;
    /// Id of top stone
    int* topStoneIds;
    /// Type of the stack / top stone
    StoneType* types;
} Stacks;

#endif
