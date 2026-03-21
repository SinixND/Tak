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
    DIR_NONE = 0,
    DIR_DOWN = 1,  /// -, decrease rank
    DIR_LEFT = 2,  /// <, decrease file
    DIR_UP = 3,    /// +, increase rank
    DIR_RIGHT = 4, /// >, increase file
} DirectionId;

static char const DIRECTION_CHARS[] = {
    ' ',
    '-',
    '<',
    '+',
    '>',
};

#endif
