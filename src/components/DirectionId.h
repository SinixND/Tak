#ifndef IG20260301194525
#define IG20260301194525

typedef enum
{
    DIR_NONE = 0,
    DIR_UP = 1,    /// +, increase rank
    DIR_DOWN = -1, /// -, decrease rank
    DIR_LEFT = -1, /// <, decrease file
    DIR_RIGHT = 1, /// >, increase file
} DirectionId;

#endif
