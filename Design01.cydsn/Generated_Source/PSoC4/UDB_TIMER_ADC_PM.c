/*******************************************************************************
* File Name: UDB_TIMER_ADC_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UDB_TIMER_ADC.h"

static UDB_TIMER_ADC_backupStruct UDB_TIMER_ADC_backup;


/*******************************************************************************
* Function Name: UDB_TIMER_ADC_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UDB_TIMER_ADC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UDB_TIMER_ADC_SaveConfig(void) 
{
    #if (!UDB_TIMER_ADC_UsingFixedFunction)
        UDB_TIMER_ADC_backup.TimerUdb = UDB_TIMER_ADC_ReadCounter();
        UDB_TIMER_ADC_backup.InterruptMaskValue = UDB_TIMER_ADC_STATUS_MASK;
        #if (UDB_TIMER_ADC_UsingHWCaptureCounter)
            UDB_TIMER_ADC_backup.TimerCaptureCounter = UDB_TIMER_ADC_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
            UDB_TIMER_ADC_backup.TimerControlRegister = UDB_TIMER_ADC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: UDB_TIMER_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UDB_TIMER_ADC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UDB_TIMER_ADC_RestoreConfig(void) 
{   
    #if (!UDB_TIMER_ADC_UsingFixedFunction)

        UDB_TIMER_ADC_WriteCounter(UDB_TIMER_ADC_backup.TimerUdb);
        UDB_TIMER_ADC_STATUS_MASK =UDB_TIMER_ADC_backup.InterruptMaskValue;
        #if (UDB_TIMER_ADC_UsingHWCaptureCounter)
            UDB_TIMER_ADC_SetCaptureCount(UDB_TIMER_ADC_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
            UDB_TIMER_ADC_WriteControlRegister(UDB_TIMER_ADC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: UDB_TIMER_ADC_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UDB_TIMER_ADC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void UDB_TIMER_ADC_Sleep(void) 
{
    #if(!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(UDB_TIMER_ADC_CTRL_ENABLE == (UDB_TIMER_ADC_CONTROL & UDB_TIMER_ADC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            UDB_TIMER_ADC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            UDB_TIMER_ADC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    UDB_TIMER_ADC_Stop();
    UDB_TIMER_ADC_SaveConfig();
}


/*******************************************************************************
* Function Name: UDB_TIMER_ADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UDB_TIMER_ADC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UDB_TIMER_ADC_Wakeup(void) 
{
    UDB_TIMER_ADC_RestoreConfig();
    #if(!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
        if(UDB_TIMER_ADC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                UDB_TIMER_ADC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
