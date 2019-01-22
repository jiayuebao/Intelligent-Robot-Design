/*******************************************************************************
* File Name: trigger.h  
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

#if !defined(CY_PINS_trigger_H) /* Pins trigger_H */
#define CY_PINS_trigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "trigger_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    trigger_Write(uint8 value) ;
void    trigger_SetDriveMode(uint8 mode) ;
uint8   trigger_ReadDataReg(void) ;
uint8   trigger_Read(void) ;
uint8   trigger_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define trigger_DRIVE_MODE_BITS        (3)
#define trigger_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - trigger_DRIVE_MODE_BITS))

#define trigger_DM_ALG_HIZ         (0x00u)
#define trigger_DM_DIG_HIZ         (0x01u)
#define trigger_DM_RES_UP          (0x02u)
#define trigger_DM_RES_DWN         (0x03u)
#define trigger_DM_OD_LO           (0x04u)
#define trigger_DM_OD_HI           (0x05u)
#define trigger_DM_STRONG          (0x06u)
#define trigger_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define trigger_MASK               trigger__MASK
#define trigger_SHIFT              trigger__SHIFT
#define trigger_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define trigger_PS                     (* (reg32 *) trigger__PS)
/* Port Configuration */
#define trigger_PC                     (* (reg32 *) trigger__PC)
/* Data Register */
#define trigger_DR                     (* (reg32 *) trigger__DR)
/* Input Buffer Disable Override */
#define trigger_INP_DIS                (* (reg32 *) trigger__PC2)


#if defined(trigger__INTSTAT)  /* Interrupt Registers */

    #define trigger_INTSTAT                (* (reg32 *) trigger__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define trigger_DRIVE_MODE_SHIFT       (0x00u)
#define trigger_DRIVE_MODE_MASK        (0x07u << trigger_DRIVE_MODE_SHIFT)


#endif /* End Pins trigger_H */


/* [] END OF FILE */
