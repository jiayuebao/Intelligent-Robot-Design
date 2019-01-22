/*******************************************************************************
* File Name: Pin_L.h  
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

#if !defined(CY_PINS_Pin_L_H) /* Pins Pin_L_H */
#define CY_PINS_Pin_L_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_L_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_L_Write(uint8 value) ;
void    Pin_L_SetDriveMode(uint8 mode) ;
uint8   Pin_L_ReadDataReg(void) ;
uint8   Pin_L_Read(void) ;
uint8   Pin_L_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_L_DRIVE_MODE_BITS        (3)
#define Pin_L_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_L_DRIVE_MODE_BITS))

#define Pin_L_DM_ALG_HIZ         (0x00u)
#define Pin_L_DM_DIG_HIZ         (0x01u)
#define Pin_L_DM_RES_UP          (0x02u)
#define Pin_L_DM_RES_DWN         (0x03u)
#define Pin_L_DM_OD_LO           (0x04u)
#define Pin_L_DM_OD_HI           (0x05u)
#define Pin_L_DM_STRONG          (0x06u)
#define Pin_L_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin_L_MASK               Pin_L__MASK
#define Pin_L_SHIFT              Pin_L__SHIFT
#define Pin_L_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_L_PS                     (* (reg32 *) Pin_L__PS)
/* Port Configuration */
#define Pin_L_PC                     (* (reg32 *) Pin_L__PC)
/* Data Register */
#define Pin_L_DR                     (* (reg32 *) Pin_L__DR)
/* Input Buffer Disable Override */
#define Pin_L_INP_DIS                (* (reg32 *) Pin_L__PC2)


#if defined(Pin_L__INTSTAT)  /* Interrupt Registers */

    #define Pin_L_INTSTAT                (* (reg32 *) Pin_L__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin_L_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_L_DRIVE_MODE_MASK        (0x07u << Pin_L_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin_L_H */


/* [] END OF FILE */
