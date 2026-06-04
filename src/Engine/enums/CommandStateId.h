#ifndef IG20260412014331
#define IG20260412014331

/// Current expected input
typedef enum CommandStateId
{
    COMMAND_STATE_NONE = 0,              // Starting point
    COMMAND_STATE_GET_ACTION_TYPE,       // Choose place/move
    COMMAND_STATE_GET_STONE_TYPE,        // Choose flat/standing/cap
    COMMAND_STATE_GET_FILE_X,            // Choose column
    COMMAND_STATE_GET_RANK_Y,            // Choose row
    COMMAND_STATE_GET_DIRECTION,         // Choose north/west/east/south
    COMMAND_STATE_GET_FIRST_DROP_AMOUNT, // Choose 0-8
    COMMAND_STATE_GET_DROP_AMOUNT,       // Choose 1-8
    COMMAND_STATE_COUNT,
} CommandStateId;

#endif
