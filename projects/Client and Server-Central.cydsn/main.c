
#include <project.h>
#include "common.h"
#include <stdio.h>

#define BAS_SERVICE_INDEX                   (0)
/***************************************
*        Global Variables
***************************************/
uint8 deviceDetected=0;
CYBLE_GAP_BD_ADDR_T  peerDeviceAddr;




void StackEventHandler(uint32 event,void* eventParam)
{
    
   /*Declaring Local variables*/
    uint8 i;
    CYBLE_GAPC_ADV_REPORT_T scanReport;
    CYBLE_API_RESULT_T apiResult;              
   
    switch(event)
    {
        
        case CYBLE_EVT_STACK_ON:
        
                printf("BLE Stack ON:\r\n");
                /*Start to Scan after Stack ON*/
                CyBle_GapcStartScan(CYBLE_SCANNING_FAST);
            break;                   
            
        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
                scanReport=  *(CYBLE_GAPC_ADV_REPORT_T*)eventParam;
                 
                /*Check for the Manufacturer specific data in scan response*/
                if(scanReport.data[1] == MANUFACTURER_SPECIFIC_DATA && scanReport.data[2] == COMPANY_LSB && scanReport.data[3] == COMPANY_MSB 
                && scanReport.data[4] == MAN_SPEC_DATA_LSB && scanReport.data[5] == MAN_SPEC_DATA_MSB)
                {
                    printf("peer address:\r\n");
                    
                    for(i=0;i<CYBLE_GAP_BD_ADDR_SIZE;i++)
                    {
                        peerDeviceAddr.bdAddr[i]=scanReport.peerBdAddr[i];
                        printf("%2.2x",scanReport.peerBdAddr[CYBLE_GAP_BD_ADDR_SIZE-1-i]);
                    }
                    
                    printf("\r\n");
                    deviceDetected=TRUE;
                    
                    /*Start to scan after disconnection*/
                    CyBle_GapcStopScan();
                }
                 
            break;
                
        case CYBLE_EVT_GAPC_SCAN_START_STOP:
                
                if(CyBle_GetState()==CYBLE_STATE_SCANNING)
                {
                    printf("Started to Scan\r\n");
                }
                else if(CyBle_GetState()==CYBLE_STATE_DISCONNECTED)
                {    
                    printf("Stop scanning:\r\n");
                    if(deviceDetected==TRUE)
                    {
                        apiResult=CyBle_GapcConnectDevice(&peerDeviceAddr);
                        if(apiResult==CYBLE_ERROR_OK)
                        {
                            printf("success\r\n");
                        }
                        else 
                        {
                            printf("connection failed:%x\r\n",apiResult);
                        }
                        deviceDetected=FALSE;   
                    }
                }
            break;
        
         case CYBLE_EVT_GAP_DEVICE_CONNECTED:
                /*Start to dicovery the servioes of the serve after connection*/
                CyBle_GattcStartDiscovery(cyBle_connHandle);  
            break;
                
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:           
                /*Start to scan after disconnection*/
                CyBle_GapcStartScan(CYBLE_SCANNING_FAST); 
            break;
                
        case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
                printf("\r\n");
                printf("Discovery complete.\r\n");
                
                for(i = 0u; i < CYBLE_SRVI_COUNT; i++)
                {          
                    /*Checking for the Tx power service*/
                    if(cyBle_serverInfo[i].uuid == CYBLE_UUID_BAS_SERVICE)
                    {
                        if(cyBle_serverInfo[i].range.startHandle < cyBle_serverInfo[i].range.endHandle)
                        {
                            printf("Peer device supports the Service \r\n");      
                        }
                        else
                        {
                            printf("Peer device doesn't supports the Service \r\n");
                        }
                    }

                }                
                printf("\r\n");
            break;                   
                
        default:               
             break;
                
    }
}



int main()
{
    /* Local variables*/
    uint8 value;
    char8 command;
    const char8 serialNumber[] = "123456";       
    
    CyGlobalIntEnable;  
    
    UART_Start();
    
    CyBle_Start(StackEventHandler);/*Start BLE*/
    
    /* Set Serial Number string not initialized in GUI */
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_SERIAL_NUMBER, sizeof(serialNumber), (uint8 *)serialNumber);
        
    
    /* Register the event handler for TPS specific events */
    CyBle_BasRegisterAttrCallback(BasServiceAppEventHandler);
   
    for(;;)
    {
        CyBle_ProcessEvents();
        
        command=UART_UartGetChar();
        if(command!=0u)
        {
            switch(command)
            {
                case 'r':    /*Read battery level*/           
                        CyBle_BascGetCharacteristicValue(cyBle_connHandle,BAS_SERVICE_INDEX,CYBLE_BAS_BATTERY_LEVEL);              
                    break;      
                        
                case 'e':   /*Enable the notification*/
                        value=1;
                        CyBle_BascSetCharacteristicDescriptor(cyBle_connHandle,BAS_SERVICE_INDEX,CYBLE_BAS_BATTERY_LEVEL,CYBLE_BAS_BATTERY_LEVEL_CCCD,
                            CYBLE_BAS_BATTERY_LEVEL_LEN*2,&value);            
                    break;
                        
                case 'd':   /*Disable the notification*/
                        value=0;
                        CyBle_BascSetCharacteristicDescriptor(cyBle_connHandle,BAS_SERVICE_INDEX,CYBLE_BAS_BATTERY_LEVEL,CYBLE_BAS_BATTERY_LEVEL_CCCD,
                            CYBLE_BAS_BATTERY_LEVEL_LEN*2,&value);
                    break;
            }
        }
    }
}

/* [] END OF FILE */
