#include "Input.h"

#include "CommandId.h"
#include "InputId.h"
#include "Mappings.h"
#include "UIElement.h"
#include <assert.h>

Input newInput( void )
{
    return (Input){
        .mappings = newMappings(),
        .lastInput = INPUT_NONE,
        .mousePosition = { 0, 0 },
    };
}

