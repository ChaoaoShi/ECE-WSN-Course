

#include <common.h>
#include <stdio.h>



void BasServiceAppEventHandler(uint32 event, void *eventParam)

{
    
    CYBLE_BAS_CHAR_VALUE_T CharValue;
   
    switch(event)
    {
    
    /***************************************
    *        BAS Client events
    ***************************************/
    case CYBLE_EVT_BASC_NOTIFICATION:
            CharValue=*(CYBLE_BAS_CHAR_VALUE_T*)eventParam;
            printf("Notification received. Battery Level:%d \r\n",(int8)(CharValue.value->val[0]));
        break;
            
    case CYBLE_EVT_BASC_READ_CHAR_RESPONSE:
            CharValue=*(CYBLE_BAS_CHAR_VALUE_T*)eventParam;
            printf("Read Char Response. Battery Level: %d \r\n",(int8)(CharValue.value->val[0]));
        break;
                      
    case CYBLE_EVT_BASC_WRITE_DESCR_RESPONSE:
             printf("Write Descr Response\r\n");
        break;
            
     case CYBLE_EVT_GATTC_ERROR_RSP:
             printf("Error Rsp\r\n");
        break;
     
    default:                 
             printf("default:\r\n");            
        break;
    }
}

/* [] END OF FILE */
