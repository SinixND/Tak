#ifndef IG20260320101808
#define IG20260320101808

typedef enum
{
    STATE_FIRST_TURN_CHOOSE_FILE_X,  // White places black flat
    STATE_FIRST_TURN_CHOOSE_RANK_Y,  // White places black flat
    STATE_SECOND_TURN_CHOOSE_FILE_X, // Black places white flat
    STATE_SECOND_TURN_CHOOSE_RANK_Y, // Black places white flat
    STATE_CHOOSE_ACTION,             // Choose place/lift/drop
    STATE_CHOOSE_FILE_X,             // Choose A-H
    STATE_CHOOSE_RANK_Y,             // Choose 1-8
    STATE_CHOOSE_STONE_TYPE,         // Choose flat/standing/cap
    STATE_CHOOSE_DIRECTION,          // Choose north/west/east/south
    STATE_CHOOSE_FIRST_DROP_AMOUNT,  // Choose 0-8
    STATE_CHOOSE_AMOUNT,             // Choose 1-8
    STATE_UPDATE_GAME,               // Update game from gameEvent
    STATE_END_TURN,                  // Reset turn data
} AppState;

#endif
