#ifndef IG20260313163621
#define IG20260313163621

/**
 * @brief Type of action
 */
typedef enum ActionType
{
    ACTION_TYPE_NONE = 0,  // Invalid input
    ACTION_TYPE_PLACE = 1, // [P]lace stone
    ACTION_TYPE_LIFT = 2,  // [L]ift stack
    ACTION_TYPE_DROP = 3,  // [D]rop stone
} ActionType;

static char const ACTION_TYPE_CHARS[] = {
    [ACTION_TYPE_NONE] = ' ',
    [ACTION_TYPE_PLACE] = 'P',
    [ACTION_TYPE_LIFT] = 'M', // Lift displayed as move
    [ACTION_TYPE_DROP] = 'M', // Drop displayed as move
};

#endif
