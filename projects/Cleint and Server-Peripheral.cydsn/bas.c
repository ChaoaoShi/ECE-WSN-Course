

#include <common.h>
#include <stdio.h>



void BasServiceAppEventHandler(uint32 event, void *eventParam)
{
    switch(event)
    {
        /***************************************
        *        BAS Server events
        ***************************************/
        case CYBLE_EVT_BASS_NOTIFICATION_ENABLED:
            printf("BAS notification enabled\r\n");
            break;
        case CYBLE_EVT_BASS_NOTIFICATION_DISABLED:
            printf("BAS notification disabled\r\n");
            break;
        default:
            break;
    }
}
