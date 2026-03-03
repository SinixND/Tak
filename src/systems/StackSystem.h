#ifndef IG20260225005807
#define IG20260225005807

#include "Stack.h"

/// Return new Stack object
Stack newStack( void );

Stack pushOntoStack(
    Stack stack,
    PlayerId const playerId
);

#endif
