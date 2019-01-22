/*******************************************************************************
* File Name: IR_L.c  
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
#include "IR_L.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        IR_L_PC =   (IR_L_PC & \
                                (uint32)(~(uint32)(IR_L_DRIVE_MODE_IND_MASK << (IR_L_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (IR_L_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: IR_L_Write
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
void IR_L_Write(uint8 value) 
{
    uint8 drVal = (uint8)(IR_L_DR & (uint8)(~IR_L_MASK));
    drVal = (drVal | ((uint8)(value << IR_L_SHIFT) & IR_L_MASK));
    IR_L_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: IR_L_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  IR_L_DM_STRONG     Strong Drive 
*  IR_L_DM_OD_HI      Open Drain, Drives High 
*  IR_L_DM_OD_LO      Open Drain, Drives Low 
*  IR_L_DM_RES_UP     Resistive Pull Up 
*  IR_L_DM_RES_DWN    Resistive Pull Down 
*  IR_L_DM_RES_UPDWN  Resistive Pull Up/Down 
*  IR_L_DM_DIG_HIZ    High Impedance Digital 
*  IR_L_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void IR_L_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(IR_L__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: IR_L_Read
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
*  Macro IR_L_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 IR_L_Read(void) 
{
    return (uint8)((IR_L_PS & IR_L_MASK) >> IR_L_SHIFT);
}


/*******************************************************************************
* Function Name: IR_L_ReadDataReg
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
uint8 IR_L_ReadDataReg(void) 
{
    return (uint8)((IR_L_DR & IR_L_MASK) >> IR_L_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(IR_L_INTSTAT) 

    /*******************************************************************************
    * Function Name: IR_L_ClearInterrupt
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
    uint8 IR_L_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(IR_L_INTSTAT & IR_L_MASK);
		IR_L_INTSTAT = maskedStatus;
        return maskedStatus >> IR_L_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
