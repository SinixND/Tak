#ifndef IG20260301194525
#define IG20260301194525

typedef enum
{
    DIR_NONE = 0,
    DIR_UP = 1,    /// +, increase rank
    DIR_DOWN = 2,  /// -, decrease rank
    DIR_LEFT = 3,  /// <, decrease file
    DIR_RIGHT = 4, /// >, increase file
} DirectionId;

static char const DIRECTION_CHARS[] = {
    ' ',
    '+',
    '-',
    '<',
    '>',
};

#endif
