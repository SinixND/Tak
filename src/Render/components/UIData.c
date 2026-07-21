#include "UIData.h"

#ifdef BACKEND_RAYLIB
#include <raygui.h>
#endif

UIData newUIData( void )
{
    return (UIData){
        .fontSize = 20,
#ifdef BACKEND_RAYLIB
        .spacing = GuiGetStyle( DEFAULT, TEXT_SPACING ),
#endif
    };
}
