#ifndef IG20260507172347
#define IG20260507172347

#include "InputId.h"

static InputId const SIMULATION_DATA[] = {
    INPUT_8,

    /// Select board size
    INPUT_5,

    /// W: First turn
    INPUT_A,
    INPUT_1,

    /// B: Second turn - invalid placement
    INPUT_A,
    INPUT_1,

    /// B: Correct input
    INPUT_C,
    INPUT_3,

    /// W: Build stack > 8
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_F,
    INPUT_A,
    INPUT_2,

    /// W: Invalid move (non-owned)
    INPUT_M,
    INPUT_A,
    INPUT_2,

    /// W: Invalid move (empty)
    INPUT_M,
    INPUT_A,
    INPUT_3,

    /// W: Correct input
    INPUT_B,
    INPUT_1,
    INPUT_L,

    /// B:
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_D,

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_F,
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

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_F,
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

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_1,

    /// B:
    INPUT_P,
    INPUT_F,
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

    /// W: Place standing
    INPUT_P,
    INPUT_S,
    INPUT_C,
    INPUT_1,

    /// B: Move non-cap stack into standing
    INPUT_M,
    INPUT_A,
    INPUT_1,
    INPUT_R,
    /// Leave one at source
    INPUT_1,

    /// W: Move standing onto stack
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// B: Place capstone
    INPUT_P,
    INPUT_C,
    INPUT_B,
    INPUT_3,

    /// W: Move standing stack into capstone
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_U,
    /// Leave none at source
    INPUT_0,

    /// B: Move capstone onto stack
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_D,

    /// W: Place standing
    INPUT_P,
    INPUT_S,
    INPUT_B,
    INPUT_1,

    /// B: Move capstone stack into standing
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_D,

    /// W: Move  stack into border
    INPUT_M,
    INPUT_B,
    INPUT_2,
    INPUT_L,
    /// Leave none at source
    INPUT_0,

    /// B: Dummy move
    INPUT_M,
    INPUT_B,
    INPUT_1,
    INPUT_L,
    /// Leave none at source
    INPUT_0,

    /// W: Move stack to win game
    INPUT_M,
    INPUT_A,
    INPUT_2,
    INPUT_R,
    INPUT_2,
    INPUT_2,
    INPUT_2,
    INPUT_2,

    /// B: Build stacks
    INPUT_P,
    INPUT_F,
    INPUT_C,
    INPUT_1,

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_F,
    INPUT_C,
    INPUT_1,

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_F,
    INPUT_C,
    INPUT_1,

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_F,
    INPUT_C,
    INPUT_1,

    /// W:
    INPUT_P,
    INPUT_F,
    INPUT_B,
    INPUT_3,

    /// B:
    INPUT_M,
    INPUT_C,
    INPUT_1,
    INPUT_L,

    /// W:
    INPUT_M,
    INPUT_B,
    INPUT_3,
    INPUT_R,

    /// B:
    INPUT_P,
    INPUT_F,
    INPUT_C,
    INPUT_1,

    /// W:
    INPUT_M,
    INPUT_C,
    INPUT_3,
    INPUT_R,
    INPUT_0,
    INPUT_1,
    INPUT_1,
    INPUT_1,
    INPUT_1,
    INPUT_1,
};

#endif

