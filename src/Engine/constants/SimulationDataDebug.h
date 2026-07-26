#ifndef IG20260507172347
#define IG20260507172347

#include "InputId.h"

static InputId const SIMULATION_DATA[] = {
    /// Select board size
    INPUT_5,

    // /*
    /// Simulation for board size 5
    /// First turn
    /// W:
    INPUT_A,
    INPUT_1,

    /// Second turn
    /// Invalid placement (non-empty)
    /// B:
    INPUT_A,
    INPUT_1,

    /// B:
    /// Invalid placement (out-of-bounds)
    INPUT_H,
    INPUT_8,

    /// Correct input
    /// B:
    INPUT_C,
    INPUT_3,

    /// Build stack > 5
    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_A,
    INPUT_2,

    /// Invalid move (non-owned)
    /// W:
    INPUT_M,
    INPUT_A,
    INPUT_2,

    /// Invalid move (empty)
    /// W:
    INPUT_A,
    INPUT_3,

    /// Invalid move (out-of-bounds)
    /// W:
    INPUT_A,
    INPUT_8,

    /// Correct input
    /// W:
    INPUT_B,
    INPUT_1,
    INPUT_L,

    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_D,
    /// H=3

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_A,
    INPUT_2,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_L,

    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_D,
    /// H=5

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_A,
    INPUT_2,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_L,

    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_D,
    /// H=7

    /// Place standing
    /// W:
    INPUT_P,
    INPUT_CAP_S,
    INPUT_C,
    INPUT_1,

    /// Move non-cap stack into standing
    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_1,
    INPUT_R,
    /// Leave one at source
    INPUT_1,

    /// Move standing onto stack
    /// W:
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// Place capstone
    /// B:
    INPUT_P,
    INPUT_CAP_C,
    INPUT_B,
    INPUT_3,

    /// Move standing stack into capstone
    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_U,
    /// Leave none at source
    INPUT_0,

    /// Move capstone onto stack
    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_D,

    /// Place standing
    /// W:
    INPUT_P,
    INPUT_CAP_S,
    INPUT_B,
    INPUT_1,

    /// Move capstone stack into standing
    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// Move  stack into border
    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_L,
    /// Leave none at source
    INPUT_0,

    /// Dummy move
    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_L,
    /// Leave none at source
    INPUT_0,

    /// Move stack to prepare road for BLACK
    /// W:
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_U,
    INPUT_2,
    INPUT_2,
    /// Autocompletes last placement (H=5)

    /// Place for road
    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_A,
    INPUT_5,

    /// Fill board
    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_E,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_E,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_E,
    INPUT_3,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_E,
    INPUT_4,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_E,
    INPUT_5,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_D,
    INPUT_1,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_D,
    INPUT_2,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_D,
    INPUT_3,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_D,
    INPUT_4,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_D,
    INPUT_5,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_C,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_C,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_C,
    INPUT_4,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_C,
    INPUT_5,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_4,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// Deplete reserves
    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_M,
    INPUT_C,
    INPUT_2,
    INPUT_U,
    INPUT_1,

    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_M,
    INPUT_C,
    INPUT_3,
    INPUT_D,
    INPUT_2,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_2,

    /// W:
    INPUT_P,
    INPUT_CAP_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_1,
    INPUT_R,
    INPUT_3,
    INPUT_2,

    /// W:
    INPUT_M,
    INPUT_C,
    INPUT_3,
    INPUT_D,
    INPUT_4,
    //*/
};

#endif

