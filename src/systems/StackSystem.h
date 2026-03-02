#ifndef IG20260225005807
#define IG20260225005807

#include "Stack.h"

/// Return new Stack object
Stack newStack( void );

Stack addStoneToStack(
    Stack stack,
    PlayerId const playerId
);

Stack takeStoneFromStack( Stack stack );

#endif
