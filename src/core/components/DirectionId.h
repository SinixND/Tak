#ifndef IG20260301194525
#define IG20260301194525

/**
 * @brief: Left and right are even for some logic in the application
 *
 * uneven will be used as dir -2
 * even will be used as dir - 3
 */
typedef enum
{
    DIR_NONE = -1, // No direction is invalid input
    DIR_DOWN = 0,  // '-': decrease rank
    DIR_LEFT = 1,  // '<': decrease file
    DIR_UP = 2,    // '+': increase rank
    DIR_RIGHT = 3, // '>': increase file
} DirectionId;

static char const DIRECTION_CHARS[] = {
    '-',
    '<',
    '+',
    '>',
};

#endif
