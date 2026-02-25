#ifndef IG20260222211441
#define IG20260222211441

#include "GameConstants.h"
#include "PlayerId.h"

/**
 * @brief A stack is a pile of stones
 *
 * The affiliation of a stack is determined by the its top stone
 * In terms of code a single stone is a stack of height 1
 */
typedef struct
{
    /// Stone affiliations
    PlayerId affiliations[STONES_MAX];
    /// Height of active stack stones (= valid affiliations)
    int height;
} Stack;

#endif
