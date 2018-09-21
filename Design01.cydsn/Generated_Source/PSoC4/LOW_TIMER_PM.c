/*******************************************************************************
* File Name: LOW_TIMER_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LOW_TIMER.h"

static LOW_TIMER_BACKUP_STRUCT LOW_TIMER_backup;


/*******************************************************************************
* Function Name: LOW_TIMER_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: LOW_TIMER_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_Sleep(void)
{
    if(0u != (LOW_TIMER_BLOCK_CONTROL_REG & LOW_TIMER_MASK))
    {
        LOW_TIMER_backup.enableState = 1u;
    }
    else
    {
        LOW_TIMER_backup.enableState = 0u;
    }

    LOW_TIMER_Stop();
    LOW_TIMER_SaveConfig();
}


/*******************************************************************************
* Function Name: LOW_TIMER_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: LOW_TIMER_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_Wakeup(void)
{
    LOW_TIMER_RestoreConfig();

    if(0u != LOW_TIMER_backup.enableState)
    {
        LOW_TIMER_Enable();
    }
}


/* [] END OF FILE */
