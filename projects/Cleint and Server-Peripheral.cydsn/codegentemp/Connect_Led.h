/*******************************************************************************
* File Name: Connect_Led.h  
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

#if !defined(CY_PINS_Connect_Led_H) /* Pins Connect_Led_H */
#define CY_PINS_Connect_Led_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Connect_Led_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Connect_Led_Write(uint8 value) ;
void    Connect_Led_SetDriveMode(uint8 mode) ;
uint8   Connect_Led_ReadDataReg(void) ;
uint8   Connect_Led_Read(void) ;
uint8   Connect_Led_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Connect_Led_DRIVE_MODE_BITS        (3)
#define Connect_Led_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Connect_Led_DRIVE_MODE_BITS))

#define Connect_Led_DM_ALG_HIZ         (0x00u)
#define Connect_Led_DM_DIG_HIZ         (0x01u)
#define Connect_Led_DM_RES_UP          (0x02u)
#define Connect_Led_DM_RES_DWN         (0x03u)
#define Connect_Led_DM_OD_LO           (0x04u)
#define Connect_Led_DM_OD_HI           (0x05u)
#define Connect_Led_DM_STRONG          (0x06u)
#define Connect_Led_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Connect_Led_MASK               Connect_Led__MASK
#define Connect_Led_SHIFT              Connect_Led__SHIFT
#define Connect_Led_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Connect_Led_PS                     (* (reg32 *) Connect_Led__PS)
/* Port Configuration */
#define Connect_Led_PC                     (* (reg32 *) Connect_Led__PC)
/* Data Register */
#define Connect_Led_DR                     (* (reg32 *) Connect_Led__DR)
/* Input Buffer Disable Override */
#define Connect_Led_INP_DIS                (* (reg32 *) Connect_Led__PC2)


#if defined(Connect_Led__INTSTAT)  /* Interrupt Registers */

    #define Connect_Led_INTSTAT                (* (reg32 *) Connect_Led__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Connect_Led_DRIVE_MODE_SHIFT       (0x00u)
#define Connect_Led_DRIVE_MODE_MASK        (0x07u << Connect_Led_DRIVE_MODE_SHIFT)


#endif /* End Pins Connect_Led_H */


/* [] END OF FILE */
