#include "Record.h"

Record newRecord( void )
{
    return (Record){
        .actionType = ACTION_TYPE_NONE,
    };
}
