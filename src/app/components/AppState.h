#ifndef IG20260320101808
#define IG20260320101808

typedef enum
{
    // STATE_NONE,                  // Starting point
    STATE_FIRST_TURN,            // White places black flat
    STATE_SECOND_TURN,           // Black places white flat
    STATE_CHOOSE_ACTION,         // Choose place/lift/drop
    STATE_RESOLVE_ACTION,        // Update game from built game event
    STATE_END_TURN,              // Advance turn
    STATE_GET_STONE_TYPE,        // Choose flat/standing/cap
    STATE_GET_FILE_X,            // Choose column
    STATE_GET_RANK_Y,            // Choose row
    STATE_GET_DIRECTION,         // Choose north/west/east/south
    STATE_GET_FIRST_DROP_AMOUNT, // Choose 0-8
    STATE_GET_DROP_AMOUNT,       // Choose 1-8
} AppState;

#endif
