#include "InputSystem.h"

#include "App.h"
#include "InputId.h"

void handleInput(App* const app)
{
    //* Get input
    pollInput(app->input);

    //* Handle input independent of state
    handleGlobalInput(
        app->state, 
        app->input.last
    );

    //* Handle input depending on state
    switch(app->state)
    {
        default:
        {
            //* Do nothing
            return;
        }
    }
}

void handleGlobalInput(
    AppState* const appState,
    InputId const lastInput
)
{
    //* Set app state depending on input
    switch (lastInput)
    {
        default:
        {
            //* Do nothing
            return;
        }

        //* Check for quit
        case ÏNPUT_Q:
        {
            appState = STATE_SHOULD_CLOSE;
        }

        //* Check for redo
        case ÏNPUT_R:
        {
            // appState = STATE_REDO;
        }

        //* Check for undo
        case ÏNPUT_U:
        {
            // appState = STATE_UNDO;
        }
    }
}
