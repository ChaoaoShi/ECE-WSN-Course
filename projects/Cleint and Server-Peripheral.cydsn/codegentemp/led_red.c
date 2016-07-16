/*******************************************************************************
* File Name: led_red.c  
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
#include "led_red.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        led_red_PC =   (led_red_PC & \
                                (uint32)(~(uint32)(led_red_DRIVE_MODE_IND_MASK << (led_red_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (led_red_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: led_red_Write
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
void led_red_Write(uint8 value) 
{
    uint8 drVal = (uint8)(led_red_DR & (uint8)(~led_red_MASK));
    drVal = (drVal | ((uint8)(value << led_red_SHIFT) & led_red_MASK));
    led_red_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: led_red_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  led_red_DM_STRONG     Strong Drive 
*  led_red_DM_OD_HI      Open Drain, Drives High 
*  led_red_DM_OD_LO      Open Drain, Drives Low 
*  led_red_DM_RES_UP     Resistive Pull Up 
*  led_red_DM_RES_DWN    Resistive Pull Down 
*  led_red_DM_RES_UPDWN  Resistive Pull Up/Down 
*  led_red_DM_DIG_HIZ    High Impedance Digital 
*  led_red_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void led_red_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(led_red__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: led_red_Read
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
*  Macro led_red_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 led_red_Read(void) 
{
    return (uint8)((led_red_PS & led_red_MASK) >> led_red_SHIFT);
}


/*******************************************************************************
* Function Name: led_red_ReadDataReg
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
uint8 led_red_ReadDataReg(void) 
{
    return (uint8)((led_red_DR & led_red_MASK) >> led_red_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(led_red_INTSTAT) 

    /*******************************************************************************
    * Function Name: led_red_ClearInterrupt
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
    uint8 led_red_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(led_red_INTSTAT & led_red_MASK);
		led_red_INTSTAT = maskedStatus;
        return maskedStatus >> led_red_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
