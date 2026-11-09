#ifndef IG20260327185327
#define IG20260327185327

#include "CommandId.h"
#include "Input.h"
#include "UI.h"

/// Get context dependent command input
CommandId getCommandId(
    Input const* const pInput,
    UI const * const pUI,
    ContextId const contextId
);

#endif
