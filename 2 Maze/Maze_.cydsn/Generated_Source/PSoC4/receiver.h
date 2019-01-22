/*******************************************************************************
* File Name: receiver.h  
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

#if !defined(CY_PINS_receiver_H) /* Pins receiver_H */
#define CY_PINS_receiver_H

#include "cytypes.h"
#include "cyfitter.h"
#include "receiver_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    receiver_Write(uint8 value) ;
void    receiver_SetDriveMode(uint8 mode) ;
uint8   receiver_ReadDataReg(void) ;
uint8   receiver_Read(void) ;
uint8   receiver_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define receiver_DRIVE_MODE_BITS        (3)
#define receiver_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - receiver_DRIVE_MODE_BITS))

#define receiver_DM_ALG_HIZ         (0x00u)
#define receiver_DM_DIG_HIZ         (0x01u)
#define receiver_DM_RES_UP          (0x02u)
#define receiver_DM_RES_DWN         (0x03u)
#define receiver_DM_OD_LO           (0x04u)
#define receiver_DM_OD_HI           (0x05u)
#define receiver_DM_STRONG          (0x06u)
#define receiver_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define receiver_MASK               receiver__MASK
#define receiver_SHIFT              receiver__SHIFT
#define receiver_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define receiver_PS                     (* (reg32 *) receiver__PS)
/* Port Configuration */
#define receiver_PC                     (* (reg32 *) receiver__PC)
/* Data Register */
#define receiver_DR                     (* (reg32 *) receiver__DR)
/* Input Buffer Disable Override */
#define receiver_INP_DIS                (* (reg32 *) receiver__PC2)


#if defined(receiver__INTSTAT)  /* Interrupt Registers */

    #define receiver_INTSTAT                (* (reg32 *) receiver__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define receiver_DRIVE_MODE_SHIFT       (0x00u)
#define receiver_DRIVE_MODE_MASK        (0x07u << receiver_DRIVE_MODE_SHIFT)


#endif /* End Pins receiver_H */


/* [] END OF FILE */
