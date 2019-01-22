/*******************************************************************************
* File Name: receiver.c  
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
#include "receiver.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        receiver_PC =   (receiver_PC & \
                                (uint32)(~(uint32)(receiver_DRIVE_MODE_IND_MASK << (receiver_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (receiver_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: receiver_Write
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
void receiver_Write(uint8 value) 
{
    uint8 drVal = (uint8)(receiver_DR & (uint8)(~receiver_MASK));
    drVal = (drVal | ((uint8)(value << receiver_SHIFT) & receiver_MASK));
    receiver_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: receiver_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  receiver_DM_STRONG     Strong Drive 
*  receiver_DM_OD_HI      Open Drain, Drives High 
*  receiver_DM_OD_LO      Open Drain, Drives Low 
*  receiver_DM_RES_UP     Resistive Pull Up 
*  receiver_DM_RES_DWN    Resistive Pull Down 
*  receiver_DM_RES_UPDWN  Resistive Pull Up/Down 
*  receiver_DM_DIG_HIZ    High Impedance Digital 
*  receiver_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void receiver_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(receiver__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: receiver_Read
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
*  Macro receiver_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 receiver_Read(void) 
{
    return (uint8)((receiver_PS & receiver_MASK) >> receiver_SHIFT);
}


/*******************************************************************************
* Function Name: receiver_ReadDataReg
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
uint8 receiver_ReadDataReg(void) 
{
    return (uint8)((receiver_DR & receiver_MASK) >> receiver_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(receiver_INTSTAT) 

    /*******************************************************************************
    * Function Name: receiver_ClearInterrupt
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
    uint8 receiver_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(receiver_INTSTAT & receiver_MASK);
		receiver_INTSTAT = maskedStatus;
        return maskedStatus >> receiver_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
