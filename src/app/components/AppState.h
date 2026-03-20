#ifndef IG20260320101808
#define IG20260320101808

typedef enum
{
    STATE_FIRST_TURN_CHOOSE_FILE_X,  // White places black flat
    STATE_FIRST_TURN_CHOOSE_RANK_Y,  // White places black flat
    STATE_SECOND_TURN_CHOOSE_FILE_X, // Black places white flat
    STATE_SECOND_TURN_CHOOSE_RANK_Y, // Black places white flat
    STATE_SELECT_ACTION,             // Choose place/lift/drop
} AppState;

#endif
