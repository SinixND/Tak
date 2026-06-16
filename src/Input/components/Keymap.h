#ifndef IG20260501181356
#define IG20260501181356

#include "CommandId.h"
#include "InputId.h"

typedef enum ContextId
{
    CONTEXT_ACTION_TYPE,
    CONTEXT_STONE_TYPE,
    CONTEXT_POSITION,
    CONTEXT_DIRECTION,
    CONTEXT_AMOUNT,
    CONTEXT_SIZE,
    CONTEXT_GLOBAL,
    CONTEXT_COUNT,
} ContextId;

/// Input mappings (2-way)
typedef struct Keymap
{
    InputId inputs[CONTEXT_COUNT][COMMAND_COUNT];
    CommandId commands[CONTEXT_COUNT][INPUT_COUNT];
} Keymap;

Keymap newKeymap( void );

#endif
