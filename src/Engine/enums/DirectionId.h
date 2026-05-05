#ifndef IG20260301194525
#define IG20260301194525

/// Direction relative to fileX/rankY
typedef enum DirectionId
{
    DIR_NONE = -1, // No direction is invalid input
    DIR_DOWN = 0,  // '-': decrease rank
    DIR_LEFT = 1,  // '<': decrease file
    DIR_UP = 2,    // '+': increase rank
    DIR_RIGHT = 3, // '>': increase file
} DirectionId;

static char const DIRECTION_CHARS[] = {
    [DIR_DOWN] = '-',
    [DIR_LEFT] = '<',
    [DIR_UP] = '+',
    [DIR_RIGHT] = '>',
};

int getOffsetX( DirectionId const direction );
int getOffsetY( DirectionId const direction );

#endif
