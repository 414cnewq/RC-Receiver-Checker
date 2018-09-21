/*******************************************************************************
* File Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN.c
* Version 2.80
*
* Description:
*  The Timer component consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN.h"

uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_initVar = 0u;


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Init(void) 
{
    #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL2 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_MODE_MASK));
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_MODE_MASK));
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL2 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_RCOD_MASK));
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENBL_MASK));
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL3 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RT1 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RT1_MASK));
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RT1 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RT1 &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SYNCDSI_MASK));
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_RT1 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL2 |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WritePeriod(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_PERIOD);
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteCounter(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_PERIOD);

    #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWCaptureCounter)/* Capture counter is enabled */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAPTURE_COUNT_CTRL |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CNTR_ENABLE;
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureCount(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareCaptureMode)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureMode(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareTriggerMode)
            #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
                if (0u == (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL & I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_SOFTWARE))
                {
                    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetTriggerMode(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_TRIGGER_MODE);
                }
            #endif /* (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) */
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_AUX_CTRL |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_interruptState);

        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_EnableTriggerMode)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/
		
		
        #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_InterruptOnCaptureCount && !I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
            I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptCount(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_INT_CAPTURE_COUNT);
        #endif /* Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptMode(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_GLOBAL_ENABLE |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_BLOCK_EN_MASK;
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_GLOBAL_STBY_ENABLE |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED || I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Start(void) 
{
    if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_initVar == 0u)
    {
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Init();

        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Enable();
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_Stop(void) 
{
    /* Disable Timer */
    #if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED || I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_ENABLE));
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_GLOBAL_ENABLE &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_BLOCK_EN_MASK));
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_GLOBAL_STBY_ENABLE &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_BLOCK_STBY_EN_MASK));
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptMode(uint8 interruptMode) 
{
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        (void)CY_GET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR_8BIT);
    #endif/* (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) */
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
*******************************************************************************/
uint8   I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadStatusRegister(void) 
{
    return (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS);
}


#if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
*******************************************************************************/
uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadControlRegister(void) 
{
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) 
        return ((uint8)I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL);
    #else
        return (0);
    #endif /* (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteControlRegister(uint8 control) 
{
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) 
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL = control;
    #else
        control = 0u;
    #endif /* (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) */
}

#endif /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
*******************************************************************************/
uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadPeriod(void) 
{
   #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
       return ((uint8)CY_GET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_PERIOD_LSB_PTR));
   #else
       return (CY_GET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_PERIOD_LSB_PTR));
   #endif /* (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WritePeriod(uint8 period) 
{
    #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
*******************************************************************************/
uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCapture(void) 
{
   #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
       return ((uint8)CY_GET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAPTURE_LSB_PTR));
   #else
       return (CY_GET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAPTURE_LSB_PTR));
   #endif /* (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_WriteCounter(uint8 counter) 
{
   #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        CY_SET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR, (uint16)counter);
        
    #else
        CY_SET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
*******************************************************************************/
uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        (void)CY_GET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_COUNTER_LSB_PTR_8BIT);
    #endif/* (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) */

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAPTURE_LSB_PTR));
    #else
        return (CY_GET_REG8(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAPTURE_LSB_PTR));
    #endif /* (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) */
}


#if(!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingFixedFunction) /* UDB Specific Functions */

    
/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_NONE 0
#define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_RISINGEDGE 1
#define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_FALLINGEDGE 2
#define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_EITHEREDGE 3
#define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_NONE        - Set Capture mode to None
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = ((uint8)((uint8)captureMode << I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_CAP_MODE_SHIFT));
    captureMode &= (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_CAP_MODE_MASK);

    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_CAP_MODE_MASK));

        /* Write The New Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= captureMode;
    #endif /* (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_NONE 0x00u
    #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_RISINGEDGE 0x04u
    #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_FALLINGEDGE 0x08u
    #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_TRIG_MODE_MASK;

    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
    
        /* Clear the Current Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_TRIG_MODE_MASK));

        /* Write The New Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= (triggerMode | I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN__B_TIMER__TM_SOFTWARE);
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_EnableTriggerMode)


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_EnableTrigger(void) 
{
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_DisableTrigger(void) 
{
    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED )   /* Remove assignment if control register is removed */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_TRIG_EN));
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */

#if(I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_InterruptOnCaptureCount)


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_INTCNT_MASK;

    #if (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL &= ((uint8)(~I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CTRL_INTCNT_MASK));
        /* Write The New Setting */
        I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CONTROL |= interruptCount;
    #endif /* (!I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UDB_CONTROL_REG_REMOVED) */
}
#endif /* I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_InterruptOnCaptureCount */


#if (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_SetCaptureCount(uint8 captureCount) 
{
    I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCaptureCount(void) 
{
    return ((uint8)I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_CAP_COUNT);
}
#endif /* I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ClearFIFO
********************************************************************************
*
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ClearFIFO(void) 
{
    while(0u != (I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadStatusRegister() & I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_STATUS_FIFONEMP))
    {
        (void)I_REALLY_DONT_CARE_I_JUST_WANT_TO_GIVE_THIS_COMPONENT_THE_LONGEST_NAME_I_CAN_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */
