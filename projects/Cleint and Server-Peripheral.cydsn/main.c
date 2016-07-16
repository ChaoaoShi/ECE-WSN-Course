
#include <project.h>
#include  "common.h"
#include <stdio.h>

#define BAS_SERVICE_INDEX                (0)
/***************************************
*        Global Variables
***************************************/
uint8 discoverServer=0;
uint8 disSupport=0;
uint8 bval=40;
 char8 Led_Satus=0;
 char8 Led_colour=0;
char8 blinking_flag=0;
//char8 command;



void StackEventHandler(uint32 event,void * eventParam)
{
    /*Local avriables*/
    uint8 i;
    CYBLE_GAP_BD_ADDR_T localAddr;
        
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
        
                printf("BLE Stack ON: \r\n");
                /*Get local device address*/
                CyBle_GetDeviceAddress(&localAddr);

                for(i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
                {
                    printf("%2.2x", localAddr.bdAddr[i-1]);
                }
                
                printf("\r\n");
                 
                /*Start to advertise*/
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            
            break;                
       
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
                
            if(CyBle_GetState()==CYBLE_STATE_DISCONNECTED)
            {
                printf("Advertising stopped\r\n");
            }
            else if(CyBle_GetState()==CYBLE_STATE_ADVERTISING)
            {
                printf("Started to Advertise\r\n");
            }
            break;
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:             
                printf("Device Connected\r\n)");                                               
            break;
            
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
                disSupport=0;
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
                
         case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
                printf("\r\n");
                printf("Discovery complete.\r\n");
                printf("Discovered services: \r\n");
                
                for(i = 0u; i < CYBLE_SRVI_COUNT; i++)
                {          /*Check for DIS service*/
                    if(cyBle_serverInfo[i].uuid == CYBLE_UUID_DEVICE_INFO_SERVICE)
                    {
                        if(cyBle_serverInfo[i].range.startHandle < cyBle_serverInfo[i].range.endHandle)
                        {
                            printf("Peer device supports Device Information Service \r\n");
                            disSupport=1;
                        }
                        else
                        {
                            printf("Peer device doesn't supports Device Information Service \r\n");
                        }
                    }

                }                
                printf("\r\n");
            break; 
          
        default:
            break;
        
    }
}


void HandleLeds()
{

    if(CyBle_GetState()==CYBLE_STATE_DISCONNECTED)
    {
         Advertising_Led_Write(LED_OFF);
        Disconnect_Led_Write(LED_ON);
        Connect_Led_Write(LED_OFF);
        Led_Satus=0;
    }

    else if(CyBle_GetState()==CYBLE_STATE_ADVERTISING)
    {
        Advertising_Led_Write(LED_ON);
        Disconnect_Led_Write(LED_OFF);
        Connect_Led_Write(LED_OFF);
        Led_Satus=1;
        
    }
  
    else if(CyBle_GetState()==CYBLE_STATE_CONNECTED)
    {
        
        Advertising_Led_Write(LED_OFF);
        Disconnect_Led_Write(LED_OFF);
        Connect_Led_Write(LED_ON);
     Led_Satus=2;
    
     }
}

void Ledcolour()
{
   
   
   
    if(Led_Satus==0)
    {
           led_blue_Write(LED_OFF);
         led_green_Write(LED_OFF);
         led_red_Write(LED_OFF);
    }
    else if (Led_Satus==1)
    {
       led_blue_Write(LED_ON);
         led_green_Write(LED_ON);
         led_red_Write(LED_ON);
    }
    else if (Led_Satus==2)
    {
     if(Led_colour==1)////Blue
    {
       if (blinking_flag==1)
        {
          led_green_Write(LED_OFF);
         led_blue_Write(~led_blue_Read());
         led_red_Write(LED_OFF);
        }
        else 
        {
           led_blue_Write(LED_ON);
         led_green_Write(LED_OFF);
         led_red_Write(LED_OFF); 
        }
       
    }
       
           
    else if(Led_colour==0)////green
    {
        if (blinking_flag==1)
        {
          led_blue_Write(LED_OFF);
         led_green_Write(~led_green_Read());
         led_red_Write(LED_OFF);
        }
        else 
        {
          led_blue_Write(LED_OFF);
         led_green_Write(LED_ON);
         led_red_Write(LED_OFF);   
        }
    }
      
    
    
    else if(Led_colour==2) ///REd
    {
     if (blinking_flag==1)
        {
          led_blue_Write(LED_OFF);
         led_green_Write(LED_OFF);
         led_red_Write(~led_red_Read());
        }
        else 
        {
          led_blue_Write(LED_OFF);
         led_green_Write(LED_OFF);
         led_red_Write(LED_ON);   
        }
    }
    /*if Advertising TURN ON BLUE LED*/
       
    }
    /*If Connected TURN ON GREEN LED*/
   
}


CY_ISR(DIS_Interrupt)
{
    discoverServer=1;
    SW2_ClearInterrupt();/*Clear the interrupt*/
}
          
CY_ISR(Timer_ISR_Handler)
{
    CYBLE_GATT_HANDLE_VALUE_PAIR_T  locHandleValuePair;
    
    locHandleValuePair.attrHandle=cyBle_bass[0].batteryLevelHandle;
    
    locHandleValuePair.value.len = 1;
    
    locHandleValuePair.value.val=&bval;
    
    if(CYBLE_GATT_ERR_NONE==CyBle_GattsReadAttributeValue(&locHandleValuePair,NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))

        {
        // SW2_Write(TRUE);
            if(--bval<=1)
             {
               bval=1;
             
                blinking_flag=1;
     //    Amin_led_Write(~Amin_led_Read());
                
            }
            else
            {
              
                 blinking_flag=0;
            }
               Ledcolour(); 
        }
                      
    Timer_ClearInterrupt(Timer_INTR_MASK_TC);               
            
}


int main()
{
    /* Local variables */
    char8 command;

   
    
    CyGlobalIntEnable; 
    
    isr_DIS_StartEx(DIS_Interrupt);
    
    UART_Start();
    
    Timer_Start();
    Timer_ISR_StartEx(Timer_ISR_Handler);
    
    CyBle_Start(StackEventHandler); /*Start BLE*/
      
     /* Register the event handler for DIS specific events */
    CyBle_DisRegisterAttrCallback(DisEventHandler);
    
     /* Register the event handler for TPS specific events */
    CyBle_BasRegisterAttrCallback(BasServiceAppEventHandler);
    
    
    for(;;)
    {
        CyBle_ProcessEvents();
        HandleLeds();
    
        
   
        if(discoverServer==TRUE)
        {
          CyBle_GattcStartDiscovery(cyBle_connHandle);
          discoverServer=FALSE;
        }
        
        
        command = UART_UartGetChar();
        (void) CyBle_BassSetCharacteristicValue(BAS_SERVICE_INDEX, CYBLE_BAS_BATTERY_LEVEL,
                                                                    CYBLE_BAS_BATTERY_LEVEL_LEN,
                                                                    (uint8*)&bval); 
        if( command != 0u)
        {/*Client related functions*/
                       
            switch(command)
            {
                if(disSupport)
                {
                    case '1':   /*To read the Manufacturer Name */                
                            printf("Manufacturer Name:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_MANUFACTURER_NAME);            
                        break;
                            
                    case '2':   /*To read the Model number*/
                            printf("Model Number:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_MODEL_NUMBER);
                        break;
                        
                    case '3':   /*To read the serial number*/
                            printf("Serial Number:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_SERIAL_NUMBER);
                        break;
                            
                    case '4':  /*To read hardware Revision*/              
                            printf("Hardware Rev:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_HARDWARE_REV);
                        break;
                            
                    case '5':  /*To read Firmware Revision*/
                            printf("Firmware Rev:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_FIRMWARE_REV);
                        break;
                            
                    case '6':  /*To read Software Revision*/
                            printf("Software Rev:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_SOFTWARE_REV);
                        break;
                            
                    case '7':  /*To read System ID*/
                            printf("System ID:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_SYSTEM_ID);
                        break;
                            
                    case '8':  /*To read IEEE 11073 -20601 certifications details*/
                            printf("IEEE 11073-20601:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_REG_CERT_DATA);
                        break; 
                            
                    case '9':  /*To read PNP ID*/
                            printf("PNP ID:");
                            CyBle_DiscGetCharacteristicValue(cyBle_connHandle,CYBLE_DIS_PNP_ID);
                        break;
                   case 'q':  /*To read PNP ID*/
                            printf("The Counter has been Reset \r\n ");
                            bval=40;
                          //  blinking_flag = 0;
                   //        Amin_led_Write(LED_OFF);
                        break;
                   case '+':  /*To read PNP ID*/
                            printf("The colour of LED has been changed \r\n");
                            if (Led_colour == 0) 
                            {
                            Led_colour=1;
                            }
                            else if (Led_colour == 1) 
                            {
                            Led_colour=2;
                            }
                            else if (Led_colour == 2) 
                            {
                            Led_colour=0;
                            }
                            
                        break;
                }
                else
                {
                     printf("Client hasn't discovered the services of server or server doesn't support DIS service\r\n");
                }
                
 
 
                        
                case 'n': /*Send notification to the client about the battery level*/
//                       CyBle_TpssSendNotification(cyBle_connHandle,CYBLE_TPS_TX_POWER_LEVEL,CYBLE_TPS_TX_POWER_LEVEL_SIZE,&intTxPowerLevel); 
                       CyBle_BassSendNotification(cyBle_connHandle,BAS_SERVICE_INDEX,CYBLE_BAS_BATTERY_LEVEL,CYBLE_BAS_BATTERY_LEVEL_LEN, (uint8*)&bval); 
//                       CyBle_GattsWriteAttributeValue(&locHandleValuePair,0,NULL,CYBLE_GATT_DB_LOCALLY_INITIATED);
                    break;      
                                
            }
                        
        }                            
        
    }
}

/* [] END OF FILE */

