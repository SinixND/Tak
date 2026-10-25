#ifndef IG20260728124832
#define IG20260728124832

#include "CommandId.h"
#include "UIElementId.h"

/// Links position with command
typedef struct UIElement
{
    float x;
    float y;
    float width;
    float height;
    UIElementId uiElementId;
    CommandId commandId;
} UIElement;

#endif

