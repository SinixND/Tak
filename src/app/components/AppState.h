#ifndef IG20260320101808
#define IG20260320101808

typedef enum
{
    STATE_FIRST_TURN,    // White places black
    STATE_SECOND_TURN,   // Black places white
    STATE_SELECT_ACTION, // Choose place/lift/drop
} AppStates;

#endif
