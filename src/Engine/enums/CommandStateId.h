#ifndef IG20260412014331
#define IG20260412014331

/// Current expected input
typedef enum CommandStateId
{
    COMMAND_STATE_NONE = 0,              // Starting point
    COMMAND_STATE_DEFAULT,               // Stone type or position
    COMMAND_STATE_GET_POSITION,          // Choose column / row
    COMMAND_STATE_GET_DIRECTION,         // Choose north/west/east/south
    COMMAND_STATE_GET_FIRST_DROP_AMOUNT, // Choose 0-8
    COMMAND_STATE_GET_DROP_AMOUNT,       // Choose 1-8
    COMMAND_STATE_COUNT,
} CommandStateId;

#endif
