/*******************************************************************************
* File Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_PM.c
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

#include "I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN.h"

static I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backupStruct I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup;


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SaveConfig
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
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SaveConfig(void) 
{
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerUdb = I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCounter();
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.InterruptMaskValue = I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_MASK;
        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWCaptureCounter)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerCaptureCounter = I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerControlRegister = I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RestoreConfig
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
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RestoreConfig(void) 
{   
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)

        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteCounter(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerUdb);
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_MASK =I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.InterruptMaskValue;
        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWCaptureCounter)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureCount(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteControlRegister(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Sleep
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
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Sleep(void) 
{
    #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENABLE == (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL & I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENABLE))
        {
            /* Timer is enabled */
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Stop();
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SaveConfig();
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Wakeup
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
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Wakeup(void) 
{
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RestoreConfig();
    #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
        if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
