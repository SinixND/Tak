#ifndef IG20251123234409
#define IG20251123234409

/**
 * @brief Type and/or status of (placed) stones
 */
typedef enum StoneType
{
    STONE_TYPE_NONE = 0,
    STONE_TYPE_FLAT = 1,     // Type: regular
    STONE_TYPE_STANDING = 2, // Type: regular
    STONE_TYPE_CAP = 3,      // Type: capstone
} StoneType;

static char const STONE_TYPE_CHARS[] = {
    [STONE_TYPE_NONE] = ' ',
    [STONE_TYPE_FLAT] = 'F',
    [STONE_TYPE_STANDING] = 'S',
    [STONE_TYPE_CAP] = 'C',
};

#endif
