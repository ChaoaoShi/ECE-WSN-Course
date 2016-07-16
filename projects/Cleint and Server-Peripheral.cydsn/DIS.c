

#include <project.h>
#include <common.h>
#include  "stdio.h"


void DisEventHandler(uint32 event,void * eventParam)
{
    CYBLE_DIS_CHAR_VALUE_T                disCharValue;
    CYBLE_GATTC_ERR_RSP_PARAM_T           ErrResponse;
    uint8 i;
    switch(event)
    {
        case CYBLE_EVT_DISC_READ_CHAR_RESPONSE:
                disCharValue=*(CYBLE_DIS_CHAR_VALUE_T*) eventParam;                
                for(i=0;i<disCharValue.value->len;i++)
                {
                    printf("%c",disCharValue.value->val[i]);  
                }
                printf("\r\n");
            break;
        case CYBLE_EVT_GATTC_ERROR_RSP:
                ErrResponse=*(CYBLE_GATTC_ERR_RSP_PARAM_T*) eventParam;
                printf("CYBLE_EVT_GATTC_ERROR_RSP:\r\n");
                printf("GATT PDU:%x\r\n",ErrResponse.opCode);
                printf("ERR_CODE_T:%x\r\n",ErrResponse.errorCode);
            break;
    }
}
/* [] END OF FILE */
