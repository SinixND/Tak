#ifndef IG20260224160920
#define IG20260224160920

/**
 * @brief Player identifier
 */
typedef enum PlayerId
{
    PLAYER_NONE = -1,
    PLAYER_WHITE = 0,
    PLAYER_BLACK = 1,
} PlayerId;

static char const PLAYER_CHARS[] = {
   [PLAYER_WHITE] = 'W',
   [PLAYER_BLACK] = 'B',
};

#endif
