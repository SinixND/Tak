#include "InputBuffer.h"

#include "InputId.h"
#include "PlayerId.h"

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        // TODO: NONE?
        .playerId = PLAYER_WHITE,
        .keyboard = INPUT_NONE,
    };
}

