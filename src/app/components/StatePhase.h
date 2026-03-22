#ifndef IG20260322004232
#define IG20260322004232

typedef enum
{
    PHASE_NONE,                  // Starting point
    PHASE_GET_STONE_TYPE,        // Choose flat/standing/cap
    PHASE_GET_FILE_X,            // Choose column
    PHASE_GET_RANK_Y,            // Choose row
    PHASE_GET_DIRECTION,         // Choose north/west/east/south
    PHASE_GET_FIRST_DROP_AMOUNT, // Choose 0-8
    PHASE_GET_DROP_AMOUNT,       // Choose 1-8
} StatePhase;

#endif
