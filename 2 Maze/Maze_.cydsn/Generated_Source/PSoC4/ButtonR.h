/*******************************************************************************
* File Name: ButtonR.h  
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

#if !defined(CY_PINS_ButtonR_H) /* Pins ButtonR_H */
#define CY_PINS_ButtonR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ButtonR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ButtonR_Write(uint8 value) ;
void    ButtonR_SetDriveMode(uint8 mode) ;
uint8   ButtonR_ReadDataReg(void) ;
uint8   ButtonR_Read(void) ;
uint8   ButtonR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ButtonR_DRIVE_MODE_BITS        (3)
#define ButtonR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ButtonR_DRIVE_MODE_BITS))

#define ButtonR_DM_ALG_HIZ         (0x00u)
#define ButtonR_DM_DIG_HIZ         (0x01u)
#define ButtonR_DM_RES_UP          (0x02u)
#define ButtonR_DM_RES_DWN         (0x03u)
#define ButtonR_DM_OD_LO           (0x04u)
#define ButtonR_DM_OD_HI           (0x05u)
#define ButtonR_DM_STRONG          (0x06u)
#define ButtonR_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ButtonR_MASK               ButtonR__MASK
#define ButtonR_SHIFT              ButtonR__SHIFT
#define ButtonR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ButtonR_PS                     (* (reg32 *) ButtonR__PS)
/* Port Configuration */
#define ButtonR_PC                     (* (reg32 *) ButtonR__PC)
/* Data Register */
#define ButtonR_DR                     (* (reg32 *) ButtonR__DR)
/* Input Buffer Disable Override */
#define ButtonR_INP_DIS                (* (reg32 *) ButtonR__PC2)


#if defined(ButtonR__INTSTAT)  /* Interrupt Registers */

    #define ButtonR_INTSTAT                (* (reg32 *) ButtonR__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ButtonR_DRIVE_MODE_SHIFT       (0x00u)
#define ButtonR_DRIVE_MODE_MASK        (0x07u << ButtonR_DRIVE_MODE_SHIFT)


#endif /* End Pins ButtonR_H */


/* [] END OF FILE */
