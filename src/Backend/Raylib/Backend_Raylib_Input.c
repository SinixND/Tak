#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include "Backend_Raylib_Layout.h"
#include "InputBuffer.h"
#include "InputId.h"
#include <assert.h>
#include <raylib.h>

UIPosition getUIPosition(
    float mouseX,
    float mouseY,
    UIData const* const pUIData
)
{
    assert(
        pUIData
        && "Invalid pointer"
    );

    return (UIPosition){
        (int)( mouseX * pUIData->fontSize ),
        (int)( mouseY * pUIData->fontSize )
    };
}

Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize,
    UIData const* const pUIData
)
{
    assert(
        pUIData
        && "Invalid pointer"
    );

    Tile tile = { FILE_NONE, RANK_NONE };

    if (
        ( ( (int)( mouseX * pUIData->fontSize ) - ( BOARD_POS_X + 1 ) ) % 4 )
        && ( (int)( mouseY * pUIData->fontSize ) - BOARD_POS_Y ) % 4
    )
    {
        tile.fileX
            = ( (int)( mouseX * pUIData->fontSize ) - ( BOARD_POS_X + 1 ) ) / 4;

        tile.rankY
            = ( boardSize - 1 ) - ( ( (int)( mouseY * pUIData->fontSize ) - 1 ) / 4 );
    }

    return tile;
}

void getInputFromUser( InputBuffer* const pInput )
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    switch ( GetKeyPressed() )
    {
        case KEY_ZERO:
        {
            pInput->lastInput = INPUT_0;
            return;
        }

        case KEY_ONE:
        {
            pInput->lastInput = INPUT_1;
            return;
        }

        case KEY_TWO:
        {
            pInput->lastInput = INPUT_2;
            return;
        }

        case KEY_THREE:
        {
            pInput->lastInput = INPUT_3;
            return;
        }

        case KEY_FOUR:
        {
            pInput->lastInput = INPUT_4;
            return;
        }

        case KEY_FIVE:
        {
            pInput->lastInput = INPUT_5;
            return;
        }

        case KEY_SIX:
        {
            pInput->lastInput = INPUT_6;
            return;
        }

        case KEY_SEVEN:
        {
            pInput->lastInput = INPUT_7;
            return;
        }

        case KEY_EIGHT:
        {
            pInput->lastInput = INPUT_8;
            return;
        }

        case KEY_A:
        {
            pInput->lastInput = INPUT_A;
            return;
        }

        case KEY_B:
        {
            pInput->lastInput = INPUT_B;
            return;
        }

        case KEY_C:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_C;
                return;
            }

            pInput->lastInput = INPUT_C;
            return;
        }

        case KEY_D:
        {
            pInput->lastInput = INPUT_D;
            return;
        }

        case KEY_E:
        {
            pInput->lastInput = INPUT_E;
            return;
        }

        case KEY_F:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_F;
                return;
            }

            pInput->lastInput = INPUT_F;
            return;
        }

        case KEY_G:
        {
            pInput->lastInput = INPUT_G;
            return;
        }

        case KEY_H:
        {
            pInput->lastInput = INPUT_H;
            return;
        }

        case KEY_L:
        {
            pInput->lastInput = INPUT_L;
            return;
        }

        case KEY_M:
        {
            pInput->lastInput = INPUT_M;
            return;
        }

        case KEY_P:
        {
            pInput->lastInput = INPUT_P;
            return;
        }

        case KEY_R:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_R;
                return;
            }

            pInput->lastInput = INPUT_R;
            return;
        }

        case KEY_T:
        {
            pInput->lastInput = INPUT_T;
            return;
        }

        case KEY_U:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_U;
                return;
            }

            pInput->lastInput = INPUT_U;
            return;
        }

        case KEY_SPACE:
        {
            pInput->lastInput = INPUT_SPACE;
            return;
        }

        case KEY_Q:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_Q;
            }
            return;
        }

        case KEY_S:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_S;
            }
            return;
        }

        case KEY_X:
        {
            if ( IsKeyDown( KEY_LEFT_SHIFT ) )
            {
                pInput->lastInput = INPUT_CAP_X;
            }
            return;
        }

        default:
        {
            if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
            {
                pInput->lastInput = INPUT_MOUSE;

                Vector2 mousePosition = GetMousePosition();
                pInput->mousePosition[0] = mousePosition.x;
                pInput->mousePosition[1] = mousePosition.y;

                return;
            }

            pInput->lastInput = INPUT_NONE;
            return;
        }
    }
}

#endif
