#ifndef IG20260501181356
#define IG20260501181356

#include "CommandId.h"
#include "ContextId.h"
#include "InputId.h"
#include "Layout.h"
#include "UIElement.h"

/// Input mappings (2-way)
typedef struct Mappings
{
    InputId inputs[CONTEXT_COUNT][COMMAND_COUNT];
    CommandId commands[CONTEXT_COUNT][INPUT_COUNT];
    UIElement uiElements[CONTEXT_COUNT][LAYOUT_UI_ELEMENTS];
} Mappings;

Mappings newMappings( void );

#endif
