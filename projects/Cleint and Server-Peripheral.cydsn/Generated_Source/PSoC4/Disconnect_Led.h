/*******************************************************************************
* File Name: Disconnect_Led.h  
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

#if !defined(CY_PINS_Disconnect_Led_H) /* Pins Disconnect_Led_H */
#define CY_PINS_Disconnect_Led_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Disconnect_Led_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Disconnect_Led_Write(uint8 value) ;
void    Disconnect_Led_SetDriveMode(uint8 mode) ;
uint8   Disconnect_Led_ReadDataReg(void) ;
uint8   Disconnect_Led_Read(void) ;
uint8   Disconnect_Led_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Disconnect_Led_DRIVE_MODE_BITS        (3)
#define Disconnect_Led_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Disconnect_Led_DRIVE_MODE_BITS))

#define Disconnect_Led_DM_ALG_HIZ         (0x00u)
#define Disconnect_Led_DM_DIG_HIZ         (0x01u)
#define Disconnect_Led_DM_RES_UP          (0x02u)
#define Disconnect_Led_DM_RES_DWN         (0x03u)
#define Disconnect_Led_DM_OD_LO           (0x04u)
#define Disconnect_Led_DM_OD_HI           (0x05u)
#define Disconnect_Led_DM_STRONG          (0x06u)
#define Disconnect_Led_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Disconnect_Led_MASK               Disconnect_Led__MASK
#define Disconnect_Led_SHIFT              Disconnect_Led__SHIFT
#define Disconnect_Led_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Disconnect_Led_PS                     (* (reg32 *) Disconnect_Led__PS)
/* Port Configuration */
#define Disconnect_Led_PC                     (* (reg32 *) Disconnect_Led__PC)
/* Data Register */
#define Disconnect_Led_DR                     (* (reg32 *) Disconnect_Led__DR)
/* Input Buffer Disable Override */
#define Disconnect_Led_INP_DIS                (* (reg32 *) Disconnect_Led__PC2)


#if defined(Disconnect_Led__INTSTAT)  /* Interrupt Registers */

    #define Disconnect_Led_INTSTAT                (* (reg32 *) Disconnect_Led__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Disconnect_Led_DRIVE_MODE_SHIFT       (0x00u)
#define Disconnect_Led_DRIVE_MODE_MASK        (0x07u << Disconnect_Led_DRIVE_MODE_SHIFT)


#endif /* End Pins Disconnect_Led_H */


/* [] END OF FILE */
