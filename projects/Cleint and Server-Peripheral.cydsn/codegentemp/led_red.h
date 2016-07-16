/*******************************************************************************
* File Name: led_red.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_led_red_H) /* Pins led_red_H */
#define CY_PINS_led_red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "led_red_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    led_red_Write(uint8 value) ;
void    led_red_SetDriveMode(uint8 mode) ;
uint8   led_red_ReadDataReg(void) ;
uint8   led_red_Read(void) ;
uint8   led_red_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define led_red_DRIVE_MODE_BITS        (3)
#define led_red_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - led_red_DRIVE_MODE_BITS))

#define led_red_DM_ALG_HIZ         (0x00u)
#define led_red_DM_DIG_HIZ         (0x01u)
#define led_red_DM_RES_UP          (0x02u)
#define led_red_DM_RES_DWN         (0x03u)
#define led_red_DM_OD_LO           (0x04u)
#define led_red_DM_OD_HI           (0x05u)
#define led_red_DM_STRONG          (0x06u)
#define led_red_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define led_red_MASK               led_red__MASK
#define led_red_SHIFT              led_red__SHIFT
#define led_red_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define led_red_PS                     (* (reg32 *) led_red__PS)
/* Port Configuration */
#define led_red_PC                     (* (reg32 *) led_red__PC)
/* Data Register */
#define led_red_DR                     (* (reg32 *) led_red__DR)
/* Input Buffer Disable Override */
#define led_red_INP_DIS                (* (reg32 *) led_red__PC2)


#if defined(led_red__INTSTAT)  /* Interrupt Registers */

    #define led_red_INTSTAT                (* (reg32 *) led_red__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define led_red_DRIVE_MODE_SHIFT       (0x00u)
#define led_red_DRIVE_MODE_MASK        (0x07u << led_red_DRIVE_MODE_SHIFT)


#endif /* End Pins led_red_H */


/* [] END OF FILE */
