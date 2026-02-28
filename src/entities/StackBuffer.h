#ifndef IG20260224173020
#define IG20260224173020

#include "Stack.h"
#include "StoneType.h"

/**
 * @brief: This is the stack being moved
 *
 * Only the top stone of a stack can have a type other than `FLAT`
 * For this stacks Idx[0] is top
 */
typedef struct
{
    /// The stack being moved
    Stack stack;
    /// Type of stack / top stone
    StoneType type;
} StackBuffer;

#endif
