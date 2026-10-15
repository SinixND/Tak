#include "InputSystem.h"
#include "AppStateId.h"
#include "CommandId.h"
#include "Input.h"
#include <assert.h>

CommandId getCommandId(
    Input const* const pInput,
    ContextId const contextId
)
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    Mappings const* const pMappings = &pInput->mappings;

    if ( pInput->lastInput == INPUT_MOUSE )
    {
        /// Check if mouse is at uiElement
        for ( int elementIdx = 0; elementIdx < LAYOUT_UI_ELEMENTS; ++elementIdx )

        {
            UIElement const* const pUIElement = &pMappings->uiElements[contextId][elementIdx];

            if (
                pInput->mousePosition[0] >= pUIElement->x
                && pInput->mousePosition[0] < pUIElement->x + pUIElement->width
                && pInput->mousePosition[1] >= pUIElement->y
                && pInput->mousePosition[1] < pUIElement->y + pUIElement->height
            )
            {
                return pUIElement->commandId;
            }
        }

        return COMMAND_NONE;
    }

    return pMappings->commands[contextId][pInput->lastInput];
}