/*******************************************************************************
* File Name: Pin_R.h  
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

#if !defined(CY_PINS_Pin_R_H) /* Pins Pin_R_H */
#define CY_PINS_Pin_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_R_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_R_Write(uint8 value) ;
void    Pin_R_SetDriveMode(uint8 mode) ;
uint8   Pin_R_ReadDataReg(void) ;
uint8   Pin_R_Read(void) ;
uint8   Pin_R_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_R_DRIVE_MODE_BITS        (3)
#define Pin_R_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_R_DRIVE_MODE_BITS))

#define Pin_R_DM_ALG_HIZ         (0x00u)
#define Pin_R_DM_DIG_HIZ         (0x01u)
#define Pin_R_DM_RES_UP          (0x02u)
#define Pin_R_DM_RES_DWN         (0x03u)
#define Pin_R_DM_OD_LO           (0x04u)
#define Pin_R_DM_OD_HI           (0x05u)
#define Pin_R_DM_STRONG          (0x06u)
#define Pin_R_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin_R_MASK               Pin_R__MASK
#define Pin_R_SHIFT              Pin_R__SHIFT
#define Pin_R_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_R_PS                     (* (reg32 *) Pin_R__PS)
/* Port Configuration */
#define Pin_R_PC                     (* (reg32 *) Pin_R__PC)
/* Data Register */
#define Pin_R_DR                     (* (reg32 *) Pin_R__DR)
/* Input Buffer Disable Override */
#define Pin_R_INP_DIS                (* (reg32 *) Pin_R__PC2)


#if defined(Pin_R__INTSTAT)  /* Interrupt Registers */

    #define Pin_R_INTSTAT                (* (reg32 *) Pin_R__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin_R_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_R_DRIVE_MODE_MASK        (0x07u << Pin_R_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin_R_H */


/* [] END OF FILE */
