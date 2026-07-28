#ifndef IG20260728124832
#define IG20260728124832

#include "CommandId.h"

/// Links position with command
typedef struct UIElement
{
    float x;
    float y;
    float width;
    float height;
    CommandId commandId;
} UIElement;

UIElement newUIElement( void );

#endif

