#ifndef IG20251123234409
#define IG20251123234409

/**
 * @brief Type and/or status of (placed) stones
 */
typedef enum StoneType
{
    STONE_TYPE_NONE = -1,
    STONE_TYPE_FLAT = 0,     // Type: regular
    STONE_TYPE_STANDING = 1, // Type: regular
    STONE_TYPE_CAP = 2,      // Type: capstone
} StoneType;

static char const STONE_TYPE_CHARS[] = {
    'F',
    'S',
    'C',
};

#endif
