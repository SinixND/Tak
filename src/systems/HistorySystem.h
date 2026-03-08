#ifndef IG20260308214101
#define IG20260308214101

#include "History.h"
#include "PlayerAction.h"

void recordAction(
    History* const pHistory,
    PlayerAction const pPlayerAction
);

void undoLastAction( History* const pHistory );
void redoNextAction( History* const pHistory );

#endif
