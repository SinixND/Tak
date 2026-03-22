#ifndef IG20260320101808
#define IG20260320101808

typedef enum
{
    STATE_FIRST_TURN,          // White places black flat
    STATE_SECOND_TURN,         // Black places white flat
    STATE_CHOOSE_ACTION,       // Choose place/lift/drop
    STATE_PREPARE_EVENT_PLACE, // Build stone place event
    STATE_PREPARE_EVENT_LIFT,  // Build stack move event
    STATE_PREPARE_EVENT_DROP,  // Build stack move event
    STATE_UPDATE_GAME,         // Update game from built game event
    STATE_END_TURN,            // Advance turn
} AppState;

#endif
