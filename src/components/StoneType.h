#ifndef IG20251123234409
#define IG20251123234409

/**
 * @brief Type and/or status of (placed) stones
 */
typedef enum
{
    STONE_TYPE_NONE = 0,
    STONE_TYPE_FLAT, // Type: regular
    STONE_TYPE_WALL, // Type: regular
    STONE_TYPE_CAP,  // Type: capstone
} StoneType;

#endif
