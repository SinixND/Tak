#ifndef IG20260323011843
#define IG20260323011843

#include "CommandStateId.h"
#include "Layout.h"
#include "Mappings.h"

/// Struct to hold input prompts to render
typedef struct Prompts
{
    char* pInputs[COMMAND_STATE_COUNT];
    char options[COMMAND_STATE_COUNT][MAX_PROMPT_LENGTH];
} Prompts;

/// Return initialized object
Prompts newPrompts( Mappings const* const pMappings );

#endif
