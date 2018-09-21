/*******************************************************************************
* File Name: PinSelect_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PinSelect.h"

/* Check for removal by optimization */
#if !defined(PinSelect_Sync_ctrl_reg__REMOVED)

static PinSelect_BACKUP_STRUCT  PinSelect_backup = {0u};

    
/*******************************************************************************
* Function Name: PinSelect_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PinSelect_SaveConfig(void) 
{
    PinSelect_backup.controlState = PinSelect_Control;
}


/*******************************************************************************
* Function Name: PinSelect_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void PinSelect_RestoreConfig(void) 
{
     PinSelect_Control = PinSelect_backup.controlState;
}


/*******************************************************************************
* Function Name: PinSelect_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PinSelect_Sleep(void) 
{
    PinSelect_SaveConfig();
}


/*******************************************************************************
* Function Name: PinSelect_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PinSelect_Wakeup(void)  
{
    PinSelect_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
