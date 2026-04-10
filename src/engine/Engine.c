
#include "Engine.h"

#include "Command.h"
#include "Event.h"

Engine newEngine( void )
{
    return (Engine){
        .event = newEvent(),
        .command = newCommand(),
    };
}
