#ifndef IG20260317235410
#define IG20260317235410

#include "CommandId.h"
#include "InputId.h"
#include "Mappings.h"

/// Store per frame user input
typedef struct Input
{
    Mappings mappings;
    InputId lastInput;
    float mousePosition[2];
} Input;

/// Return initialized object
Input newInput( void );

#endif
