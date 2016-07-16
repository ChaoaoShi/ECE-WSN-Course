/*******************************************************************************
* File Name: led_green.h  
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

#if !defined(CY_PINS_led_green_H) /* Pins led_green_H */
#define CY_PINS_led_green_H

#include "cytypes.h"
#include "cyfitter.h"
#include "led_green_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    led_green_Write(uint8 value) ;
void    led_green_SetDriveMode(uint8 mode) ;
uint8   led_green_ReadDataReg(void) ;
uint8   led_green_Read(void) ;
uint8   led_green_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define led_green_DRIVE_MODE_BITS        (3)
#define led_green_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - led_green_DRIVE_MODE_BITS))

#define led_green_DM_ALG_HIZ         (0x00u)
#define led_green_DM_DIG_HIZ         (0x01u)
#define led_green_DM_RES_UP          (0x02u)
#define led_green_DM_RES_DWN         (0x03u)
#define led_green_DM_OD_LO           (0x04u)
#define led_green_DM_OD_HI           (0x05u)
#define led_green_DM_STRONG          (0x06u)
#define led_green_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define led_green_MASK               led_green__MASK
#define led_green_SHIFT              led_green__SHIFT
#define led_green_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define led_green_PS                     (* (reg32 *) led_green__PS)
/* Port Configuration */
#define led_green_PC                     (* (reg32 *) led_green__PC)
/* Data Register */
#define led_green_DR                     (* (reg32 *) led_green__DR)
/* Input Buffer Disable Override */
#define led_green_INP_DIS                (* (reg32 *) led_green__PC2)


#if defined(led_green__INTSTAT)  /* Interrupt Registers */

    #define led_green_INTSTAT                (* (reg32 *) led_green__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define led_green_DRIVE_MODE_SHIFT       (0x00u)
#define led_green_DRIVE_MODE_MASK        (0x07u << led_green_DRIVE_MODE_SHIFT)


#endif /* End Pins led_green_H */


/* [] END OF FILE */
