#include "InputBuffer.h"

#include "CommandId.h"
#include "InputId.h"
#include "Mappings.h"
#include "UIElement.h"
#include <assert.h>

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        .mappings = newMappings(),
        .lastInput = INPUT_NONE,
        .mousePosition = { 0, 0 },
    };
}

CommandId getCommandId(
    InputBuffer const* const pInputBuffer,
    ContextId const contextId
)
{
    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    Mappings const* const pMappings = &pInputBuffer->mappings;

    if ( pInputBuffer->lastInput == INPUT_MOUSE )
    {
        /// Check if mouse is at uiElement
        for ( int elementIdx = 0; elementIdx < LAYOUT_UI_ELEMENTS; ++elementIdx )

        {
            UIElement const* const pUIElement = &pMappings->uiElements[contextId][elementIdx];

            if (
                pInputBuffer->mousePosition[0] >= pUIElement->x
                && pInputBuffer->mousePosition[0] < pUIElement->x + pUIElement->width
                && pInputBuffer->mousePosition[1] >= pUIElement->y
                && pInputBuffer->mousePosition[1] < pUIElement->y + pUIElement->height
            )
            {
                return pUIElement->commandId;
            }
        }

        return COMMAND_NONE;
    }

    return pMappings->commands[contextId][pInputBuffer->lastInput];
}
