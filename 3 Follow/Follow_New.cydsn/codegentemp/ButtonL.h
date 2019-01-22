/*******************************************************************************
* File Name: ButtonL.h  
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

#if !defined(CY_PINS_ButtonL_H) /* Pins ButtonL_H */
#define CY_PINS_ButtonL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ButtonL_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ButtonL_Write(uint8 value) ;
void    ButtonL_SetDriveMode(uint8 mode) ;
uint8   ButtonL_ReadDataReg(void) ;
uint8   ButtonL_Read(void) ;
uint8   ButtonL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ButtonL_DRIVE_MODE_BITS        (3)
#define ButtonL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ButtonL_DRIVE_MODE_BITS))

#define ButtonL_DM_ALG_HIZ         (0x00u)
#define ButtonL_DM_DIG_HIZ         (0x01u)
#define ButtonL_DM_RES_UP          (0x02u)
#define ButtonL_DM_RES_DWN         (0x03u)
#define ButtonL_DM_OD_LO           (0x04u)
#define ButtonL_DM_OD_HI           (0x05u)
#define ButtonL_DM_STRONG          (0x06u)
#define ButtonL_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ButtonL_MASK               ButtonL__MASK
#define ButtonL_SHIFT              ButtonL__SHIFT
#define ButtonL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ButtonL_PS                     (* (reg32 *) ButtonL__PS)
/* Port Configuration */
#define ButtonL_PC                     (* (reg32 *) ButtonL__PC)
/* Data Register */
#define ButtonL_DR                     (* (reg32 *) ButtonL__DR)
/* Input Buffer Disable Override */
#define ButtonL_INP_DIS                (* (reg32 *) ButtonL__PC2)


#if defined(ButtonL__INTSTAT)  /* Interrupt Registers */

    #define ButtonL_INTSTAT                (* (reg32 *) ButtonL__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ButtonL_DRIVE_MODE_SHIFT       (0x00u)
#define ButtonL_DRIVE_MODE_MASK        (0x07u << ButtonL_DRIVE_MODE_SHIFT)


#endif /* End Pins ButtonL_H */


/* [] END OF FILE */
