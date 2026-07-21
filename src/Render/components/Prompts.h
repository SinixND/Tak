#ifndef IG20260323011843
#define IG20260323011843

#include "CommandStateId.h"
#include "Keymap.h"
#include "Layout.h"

/// Struct to hold input prompts to render
typedef struct Prompts
{
    char* pInputs[COMMAND_STATE_COUNT];
    char options[COMMAND_STATE_COUNT][MAX_PROMPT_LENGTH];
} Prompts;

/// Return initialized object
Prompts newPrompts( Keymap const* const pKeymap );

#endif
