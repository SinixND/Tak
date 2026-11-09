#include "InputSystem.h"

#include "CommandId.h"
#include "Input.h"
#include "UI.h"
#include <assert.h>

CommandId getCommandId(
    Input const* const pInput,
    UI const* const pUI,
    ContextId const contextId
)
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    Mappings const* const pMappings = &pInput->mappings;

    if ( pInput->lastInput != INPUT_MOUSE )
    {
        return pMappings->commands[contextId][pInput->lastInput];
    }

    /// Check if mouse is at uiElement
    UIElement const* pElements;
    int elementCount = 0;

    switch ( contextId )
    {
        case CONTEXT_SIZE:
        {
            pElements = pUI->selectScreenElements;
            elementCount = SELECT_SCREEN_ELEMENT_COUNT;

            break;
        }

        default:
        {
            pElements = pUI->gameScreenElements;
            elementCount = GAME_SCREEN_ELEMENT_COUNT;

            break;
        }
    }

    for ( int elementIdx = 0; elementIdx < elementCount; ++elementIdx )

    {
        if (
            pInput->mousePosition[0] >= pElements[elementIdx].x
            && pInput->mousePosition[0] < pElements[elementIdx].x + pElements[elementIdx].width - 1
            && pInput->mousePosition[1] >= pElements[elementIdx].y
            && pInput->mousePosition[1] < pElements[elementIdx].y + pElements[elementIdx].height - 1
        )
        {
            return pElements[elementIdx].commandId;
        }
    }

    return COMMAND_NONE;
}
