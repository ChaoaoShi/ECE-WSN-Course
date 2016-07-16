/*******************************************************************************
* File Name: Disconnect_Led.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Disconnect_Led.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Disconnect_Led_PC =   (Disconnect_Led_PC & \
                                (uint32)(~(uint32)(Disconnect_Led_DRIVE_MODE_IND_MASK << (Disconnect_Led_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Disconnect_Led_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Disconnect_Led_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Disconnect_Led_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Disconnect_Led_DR & (uint8)(~Disconnect_Led_MASK));
    drVal = (drVal | ((uint8)(value << Disconnect_Led_SHIFT) & Disconnect_Led_MASK));
    Disconnect_Led_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Disconnect_Led_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Disconnect_Led_DM_STRONG     Strong Drive 
*  Disconnect_Led_DM_OD_HI      Open Drain, Drives High 
*  Disconnect_Led_DM_OD_LO      Open Drain, Drives Low 
*  Disconnect_Led_DM_RES_UP     Resistive Pull Up 
*  Disconnect_Led_DM_RES_DWN    Resistive Pull Down 
*  Disconnect_Led_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Disconnect_Led_DM_DIG_HIZ    High Impedance Digital 
*  Disconnect_Led_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Disconnect_Led_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Disconnect_Led__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Disconnect_Led_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Disconnect_Led_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Disconnect_Led_Read(void) 
{
    return (uint8)((Disconnect_Led_PS & Disconnect_Led_MASK) >> Disconnect_Led_SHIFT);
}


/*******************************************************************************
* Function Name: Disconnect_Led_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Disconnect_Led_ReadDataReg(void) 
{
    return (uint8)((Disconnect_Led_DR & Disconnect_Led_MASK) >> Disconnect_Led_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Disconnect_Led_INTSTAT) 

    /*******************************************************************************
    * Function Name: Disconnect_Led_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Disconnect_Led_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Disconnect_Led_INTSTAT & Disconnect_Led_MASK);
		Disconnect_Led_INTSTAT = maskedStatus;
        return maskedStatus >> Disconnect_Led_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
