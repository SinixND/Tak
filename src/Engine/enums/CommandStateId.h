#ifndef IG20260412014331
#define IG20260412014331

/// Current expected input
typedef enum CommandStateId
{
    // STATE_NONE,                  // Starting point
    STATE_GET_ACTION,            // Choose place/move
    STATE_GET_STONE_TYPE,        // Choose flat/standing/cap
    STATE_GET_FILE_X,            // Choose column
    STATE_GET_RANK_Y,            // Choose row
    STATE_GET_DIRECTION,         // Choose north/west/east/south
    STATE_GET_FIRST_DROP_AMOUNT, // Choose 0-8
    STATE_GET_DROP_AMOUNT,       // Choose 1-8
} CommandStateId;

#endif
