#ifndef IG20260313163621
#define IG20260313163621

/**
 * @brief Type of action
 */
typedef enum
{
    ACTION_TYPE_NONE = 0,  // Invalid input
    ACTION_TYPE_PLACE = 1, // [P]lace stone
    ACTION_TYPE_LIFT = 2,  // [L]ift stack
    ACTION_TYPE_DROP = 3,  // [D]rop stone
} ActionType;

static char const ACTION_TYPE_CHARS[] = {
    ' ',
    'P',
    'L',
    'D',
};

#endif
