#ifndef IG20260323011843
#define IG20260323011843

#include "CommandStateId.h"
#include "Keymap.h"
#include "Layout.h"

typedef struct Prompts
{
    char* inputs[STATE_COUNT];
    char options[STATE_COUNT][MAX_PROMPT_LENGTH];
} Prompts;

/// Return initialized object
Prompts newPrompts( Keymap const* const pKeymap );

#endif
