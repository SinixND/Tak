#ifndef IG20260313163621
#define IG20260313163621

/**
 * @brief Type of action
 */
typedef enum
{
    ACTION_TYPE_NONE = -1, // Invalid input
    ACTION_TYPE_PLACE = 0, // [P]lace stone
    ACTION_TYPE_LIFT = 1,  // [L]ift stack
    ACTION_TYPE_DROP = 2,  // [D]rop stone
} ActionType;

static char const ACTION_TYPE_CHARS[] = {
    'P',
    'M', // Lift displayed as move
    'M', // Drop displayed as move
};

#endif
