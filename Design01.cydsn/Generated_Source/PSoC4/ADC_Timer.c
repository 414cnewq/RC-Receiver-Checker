/*******************************************************************************
* File Name: ADC_Timer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the ADC_Timer
*  component
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

#include "ADC_Timer.h"

uint8 ADC_Timer_initVar = 0u;


/*******************************************************************************
* Function Name: ADC_Timer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default ADC_Timer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (ADC_Timer__QUAD == ADC_Timer_CONFIG)
        ADC_Timer_CONTROL_REG = ADC_Timer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ADC_Timer_TRIG_CONTROL1_REG  = ADC_Timer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        ADC_Timer_SetInterruptMode(ADC_Timer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        ADC_Timer_SetCounterMode(ADC_Timer_COUNT_DOWN);
        ADC_Timer_WritePeriod(ADC_Timer_QUAD_PERIOD_INIT_VALUE);
        ADC_Timer_WriteCounter(ADC_Timer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (ADC_Timer__QUAD == ADC_Timer_CONFIG) */

    #if (ADC_Timer__TIMER == ADC_Timer_CONFIG)
        ADC_Timer_CONTROL_REG = ADC_Timer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ADC_Timer_TRIG_CONTROL1_REG  = ADC_Timer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ADC_Timer_SetInterruptMode(ADC_Timer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        ADC_Timer_WritePeriod(ADC_Timer_TC_PERIOD_VALUE );

        #if (ADC_Timer__COMPARE == ADC_Timer_TC_COMP_CAP_MODE)
            ADC_Timer_WriteCompare(ADC_Timer_TC_COMPARE_VALUE);

            #if (1u == ADC_Timer_TC_COMPARE_SWAP)
                ADC_Timer_SetCompareSwap(1u);
                ADC_Timer_WriteCompareBuf(ADC_Timer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == ADC_Timer_TC_COMPARE_SWAP) */
        #endif  /* (ADC_Timer__COMPARE == ADC_Timer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (ADC_Timer_CY_TCPWM_V2 && ADC_Timer_TIMER_UPDOWN_CNT_USED && !ADC_Timer_CY_TCPWM_4000)
            ADC_Timer_WriteCounter(1u);
        #elif(ADC_Timer__COUNT_DOWN == ADC_Timer_TC_COUNTER_MODE)
            ADC_Timer_WriteCounter(ADC_Timer_TC_PERIOD_VALUE);
        #else
            ADC_Timer_WriteCounter(0u);
        #endif /* (ADC_Timer_CY_TCPWM_V2 && ADC_Timer_TIMER_UPDOWN_CNT_USED && !ADC_Timer_CY_TCPWM_4000) */
    #endif  /* (ADC_Timer__TIMER == ADC_Timer_CONFIG) */

    #if (ADC_Timer__PWM_SEL == ADC_Timer_CONFIG)
        ADC_Timer_CONTROL_REG = ADC_Timer_CTRL_PWM_BASE_CONFIG;

        #if (ADC_Timer__PWM_PR == ADC_Timer_PWM_MODE)
            ADC_Timer_CONTROL_REG |= ADC_Timer_CTRL_PWM_RUN_MODE;
            ADC_Timer_WriteCounter(ADC_Timer_PWM_PR_INIT_VALUE);
        #else
            ADC_Timer_CONTROL_REG |= ADC_Timer_CTRL_PWM_ALIGN | ADC_Timer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (ADC_Timer_CY_TCPWM_V2 && ADC_Timer_PWM_UPDOWN_CNT_USED && !ADC_Timer_CY_TCPWM_4000)
                ADC_Timer_WriteCounter(1u);
            #elif (ADC_Timer__RIGHT == ADC_Timer_PWM_ALIGN)
                ADC_Timer_WriteCounter(ADC_Timer_PWM_PERIOD_VALUE);
            #else 
                ADC_Timer_WriteCounter(0u);
            #endif  /* (ADC_Timer_CY_TCPWM_V2 && ADC_Timer_PWM_UPDOWN_CNT_USED && !ADC_Timer_CY_TCPWM_4000) */
        #endif  /* (ADC_Timer__PWM_PR == ADC_Timer_PWM_MODE) */

        #if (ADC_Timer__PWM_DT == ADC_Timer_PWM_MODE)
            ADC_Timer_CONTROL_REG |= ADC_Timer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (ADC_Timer__PWM_DT == ADC_Timer_PWM_MODE) */

        #if (ADC_Timer__PWM == ADC_Timer_PWM_MODE)
            ADC_Timer_CONTROL_REG |= ADC_Timer_CTRL_PWM_PRESCALER;
        #endif  /* (ADC_Timer__PWM == ADC_Timer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        ADC_Timer_TRIG_CONTROL1_REG  = ADC_Timer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ADC_Timer_SetInterruptMode(ADC_Timer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (ADC_Timer__PWM_PR == ADC_Timer_PWM_MODE)
            ADC_Timer_TRIG_CONTROL2_REG =
                    (ADC_Timer_CC_MATCH_NO_CHANGE    |
                    ADC_Timer_OVERLOW_NO_CHANGE      |
                    ADC_Timer_UNDERFLOW_NO_CHANGE);
        #else
            #if (ADC_Timer__LEFT == ADC_Timer_PWM_ALIGN)
                ADC_Timer_TRIG_CONTROL2_REG = ADC_Timer_PWM_MODE_LEFT;
            #endif  /* ( ADC_Timer_PWM_LEFT == ADC_Timer_PWM_ALIGN) */

            #if (ADC_Timer__RIGHT == ADC_Timer_PWM_ALIGN)
                ADC_Timer_TRIG_CONTROL2_REG = ADC_Timer_PWM_MODE_RIGHT;
            #endif  /* ( ADC_Timer_PWM_RIGHT == ADC_Timer_PWM_ALIGN) */

            #if (ADC_Timer__CENTER == ADC_Timer_PWM_ALIGN)
                ADC_Timer_TRIG_CONTROL2_REG = ADC_Timer_PWM_MODE_CENTER;
            #endif  /* ( ADC_Timer_PWM_CENTER == ADC_Timer_PWM_ALIGN) */

            #if (ADC_Timer__ASYMMETRIC == ADC_Timer_PWM_ALIGN)
                ADC_Timer_TRIG_CONTROL2_REG = ADC_Timer_PWM_MODE_ASYM;
            #endif  /* (ADC_Timer__ASYMMETRIC == ADC_Timer_PWM_ALIGN) */
        #endif  /* (ADC_Timer__PWM_PR == ADC_Timer_PWM_MODE) */

        /* Set other values from customizer */
        ADC_Timer_WritePeriod(ADC_Timer_PWM_PERIOD_VALUE );
        ADC_Timer_WriteCompare(ADC_Timer_PWM_COMPARE_VALUE);

        #if (1u == ADC_Timer_PWM_COMPARE_SWAP)
            ADC_Timer_SetCompareSwap(1u);
            ADC_Timer_WriteCompareBuf(ADC_Timer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == ADC_Timer_PWM_COMPARE_SWAP) */

        #if (1u == ADC_Timer_PWM_PERIOD_SWAP)
            ADC_Timer_SetPeriodSwap(1u);
            ADC_Timer_WritePeriodBuf(ADC_Timer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == ADC_Timer_PWM_PERIOD_SWAP) */
    #endif  /* (ADC_Timer__PWM_SEL == ADC_Timer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: ADC_Timer_Enable
********************************************************************************
*
* Summary:
*  Enables the ADC_Timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    ADC_Timer_BLOCK_CONTROL_REG |= ADC_Timer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (ADC_Timer__PWM_SEL == ADC_Timer_CONFIG)
        #if (0u == ADC_Timer_PWM_START_SIGNAL_PRESENT)
            ADC_Timer_TriggerCommand(ADC_Timer_MASK, ADC_Timer_CMD_START);
        #endif /* (0u == ADC_Timer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (ADC_Timer__PWM_SEL == ADC_Timer_CONFIG) */

    #if (ADC_Timer__TIMER == ADC_Timer_CONFIG)
        #if (0u == ADC_Timer_TC_START_SIGNAL_PRESENT)
            ADC_Timer_TriggerCommand(ADC_Timer_MASK, ADC_Timer_CMD_START);
        #endif /* (0u == ADC_Timer_TC_START_SIGNAL_PRESENT) */
    #endif /* (ADC_Timer__TIMER == ADC_Timer_CONFIG) */
    
    #if (ADC_Timer__QUAD == ADC_Timer_CONFIG)
        #if (0u != ADC_Timer_QUAD_AUTO_START)
            ADC_Timer_TriggerCommand(ADC_Timer_MASK, ADC_Timer_CMD_RELOAD);
        #endif /* (0u != ADC_Timer_QUAD_AUTO_START) */
    #endif  /* (ADC_Timer__QUAD == ADC_Timer_CONFIG) */
}


/*******************************************************************************
* Function Name: ADC_Timer_Start
********************************************************************************
*
* Summary:
*  Initializes the ADC_Timer with default customizer
*  values when called the first time and enables the ADC_Timer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ADC_Timer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time ADC_Timer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the ADC_Timer_Start() routine.
*
*******************************************************************************/
void ADC_Timer_Start(void)
{
    if (0u == ADC_Timer_initVar)
    {
        ADC_Timer_Init();
        ADC_Timer_initVar = 1u;
    }

    ADC_Timer_Enable();
}


/*******************************************************************************
* Function Name: ADC_Timer_Stop
********************************************************************************
*
* Summary:
*  Disables the ADC_Timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_BLOCK_CONTROL_REG &= (uint32)~ADC_Timer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the ADC_Timer. This function is used when
*  configured as a generic ADC_Timer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the ADC_Timer to operate in
*   Values:
*   - ADC_Timer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - ADC_Timer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - ADC_Timer_MODE_QUAD - Quadrature decoder
*         - ADC_Timer_MODE_PWM - PWM
*         - ADC_Timer_MODE_PWM_DT - PWM with dead time
*         - ADC_Timer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_MODE_MASK;
    ADC_Timer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - ADC_Timer_MODE_X1 - Counts on phi 1 rising
*         - ADC_Timer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - ADC_Timer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_QUAD_MODE_MASK;
    ADC_Timer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - ADC_Timer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - ADC_Timer_PRESCALE_DIVBY2    - Divide by 2
*         - ADC_Timer_PRESCALE_DIVBY4    - Divide by 4
*         - ADC_Timer_PRESCALE_DIVBY8    - Divide by 8
*         - ADC_Timer_PRESCALE_DIVBY16   - Divide by 16
*         - ADC_Timer_PRESCALE_DIVBY32   - Divide by 32
*         - ADC_Timer_PRESCALE_DIVBY64   - Divide by 64
*         - ADC_Timer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_PRESCALER_MASK;
    ADC_Timer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the ADC_Timer runs
*  continuously or stops when terminal count is reached.  By default the
*  ADC_Timer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_ONESHOT_MASK;
    ADC_Timer_CONTROL_REG |= ((uint32)((oneShotEnable & ADC_Timer_1BIT_MASK) <<
                                                               ADC_Timer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPWMMode(uint32 modeMask)
{
    ADC_Timer_TRIG_CONTROL2_REG = (modeMask & ADC_Timer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: ADC_Timer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_PWM_SYNC_KILL_MASK;
    ADC_Timer_CONTROL_REG |= ((uint32)((syncKillEnable & ADC_Timer_1BIT_MASK)  <<
                                               ADC_Timer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_PWM_STOP_KILL_MASK;
    ADC_Timer_CONTROL_REG |= ((uint32)((stopOnKillEnable & ADC_Timer_1BIT_MASK)  <<
                                                         ADC_Timer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_PRESCALER_MASK;
    ADC_Timer_CONTROL_REG |= ((uint32)((deadTime & ADC_Timer_8BIT_MASK) <<
                                                          ADC_Timer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - ADC_Timer_INVERT_LINE   - Inverts the line output
*         - ADC_Timer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_INV_OUT_MASK;
    ADC_Timer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: ADC_Timer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_WriteCounter(uint32 count)
{
    ADC_Timer_COUNTER_REG = (count & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 ADC_Timer_ReadCounter(void)
{
    return (ADC_Timer_COUNTER_REG & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - ADC_Timer_COUNT_UP       - Counts up
*     - ADC_Timer_COUNT_DOWN     - Counts down
*     - ADC_Timer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - ADC_Timer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_UPDOWN_MASK;
    ADC_Timer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_WritePeriod(uint32 period)
{
    ADC_Timer_PERIOD_REG = (period & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ADC_Timer_ReadPeriod(void)
{
    return (ADC_Timer_PERIOD_REG & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_RELOAD_CC_MASK;
    ADC_Timer_CONTROL_REG |= (swapEnable & ADC_Timer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_WritePeriodBuf(uint32 periodBuf)
{
    ADC_Timer_PERIOD_BUF_REG = (periodBuf & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ADC_Timer_ReadPeriodBuf(void)
{
    return (ADC_Timer_PERIOD_BUF_REG & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_CONTROL_REG &= (uint32)~ADC_Timer_RELOAD_PERIOD_MASK;
    ADC_Timer_CONTROL_REG |= ((uint32)((swapEnable & ADC_Timer_1BIT_MASK) <<
                                                            ADC_Timer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void ADC_Timer_WriteCompare(uint32 compare)
{
    #if (ADC_Timer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ADC_Timer_CY_TCPWM_4000) */

    #if (ADC_Timer_CY_TCPWM_4000)
        currentMode = ((ADC_Timer_CONTROL_REG & ADC_Timer_UPDOWN_MASK) >> ADC_Timer_UPDOWN_SHIFT);

        if (((uint32)ADC_Timer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)ADC_Timer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (ADC_Timer_CY_TCPWM_4000) */
    
    ADC_Timer_COMP_CAP_REG = (compare & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 ADC_Timer_ReadCompare(void)
{
    #if (ADC_Timer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ADC_Timer_CY_TCPWM_4000) */

    #if (ADC_Timer_CY_TCPWM_4000)
        currentMode = ((ADC_Timer_CONTROL_REG & ADC_Timer_UPDOWN_MASK) >> ADC_Timer_UPDOWN_SHIFT);
        
        regVal = ADC_Timer_COMP_CAP_REG;
        
        if (((uint32)ADC_Timer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ADC_Timer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ADC_Timer_16BIT_MASK);
    #else
        return (ADC_Timer_COMP_CAP_REG & ADC_Timer_16BIT_MASK);
    #endif /* (ADC_Timer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ADC_Timer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void ADC_Timer_WriteCompareBuf(uint32 compareBuf)
{
    #if (ADC_Timer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ADC_Timer_CY_TCPWM_4000) */

    #if (ADC_Timer_CY_TCPWM_4000)
        currentMode = ((ADC_Timer_CONTROL_REG & ADC_Timer_UPDOWN_MASK) >> ADC_Timer_UPDOWN_SHIFT);

        if (((uint32)ADC_Timer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)ADC_Timer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (ADC_Timer_CY_TCPWM_4000) */
    
    ADC_Timer_COMP_CAP_BUF_REG = (compareBuf & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 ADC_Timer_ReadCompareBuf(void)
{
    #if (ADC_Timer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ADC_Timer_CY_TCPWM_4000) */

    #if (ADC_Timer_CY_TCPWM_4000)
        currentMode = ((ADC_Timer_CONTROL_REG & ADC_Timer_UPDOWN_MASK) >> ADC_Timer_UPDOWN_SHIFT);

        regVal = ADC_Timer_COMP_CAP_BUF_REG;
        
        if (((uint32)ADC_Timer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ADC_Timer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ADC_Timer_16BIT_MASK);
    #else
        return (ADC_Timer_COMP_CAP_BUF_REG & ADC_Timer_16BIT_MASK);
    #endif /* (ADC_Timer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 ADC_Timer_ReadCapture(void)
{
    return (ADC_Timer_COMP_CAP_REG & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 ADC_Timer_ReadCaptureBuf(void)
{
    return (ADC_Timer_COMP_CAP_BUF_REG & ADC_Timer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ADC_Timer_TRIG_LEVEL     - Level
*     - ADC_Timer_TRIG_RISING    - Rising edge
*     - ADC_Timer_TRIG_FALLING   - Falling edge
*     - ADC_Timer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_TRIG_CONTROL1_REG &= (uint32)~ADC_Timer_CAPTURE_MASK;
    ADC_Timer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ADC_Timer_TRIG_LEVEL     - Level
*     - ADC_Timer_TRIG_RISING    - Rising edge
*     - ADC_Timer_TRIG_FALLING   - Falling edge
*     - ADC_Timer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_TRIG_CONTROL1_REG &= (uint32)~ADC_Timer_RELOAD_MASK;
    ADC_Timer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ADC_Timer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ADC_Timer_TRIG_LEVEL     - Level
*     - ADC_Timer_TRIG_RISING    - Rising edge
*     - ADC_Timer_TRIG_FALLING   - Falling edge
*     - ADC_Timer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_TRIG_CONTROL1_REG &= (uint32)~ADC_Timer_START_MASK;
    ADC_Timer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ADC_Timer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ADC_Timer_TRIG_LEVEL     - Level
*     - ADC_Timer_TRIG_RISING    - Rising edge
*     - ADC_Timer_TRIG_FALLING   - Falling edge
*     - ADC_Timer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_TRIG_CONTROL1_REG &= (uint32)~ADC_Timer_STOP_MASK;
    ADC_Timer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ADC_Timer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ADC_Timer_TRIG_LEVEL     - Level
*     - ADC_Timer_TRIG_RISING    - Rising edge
*     - ADC_Timer_TRIG_FALLING   - Falling edge
*     - ADC_Timer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_TRIG_CONTROL1_REG &= (uint32)~ADC_Timer_COUNT_MASK;
    ADC_Timer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ADC_Timer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - ADC_Timer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - ADC_Timer_CMD_RELOAD     - Trigger Reload/Index command
*     - ADC_Timer_CMD_STOP       - Trigger Stop/Kill command
*     - ADC_Timer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ADC_Timer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ADC_Timer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the ADC_Timer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - ADC_Timer_STATUS_DOWN    - Set if counting down
*     - ADC_Timer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 ADC_Timer_ReadStatus(void)
{
    return ((ADC_Timer_STATUS_REG >> ADC_Timer_RUNNING_STATUS_SHIFT) |
            (ADC_Timer_STATUS_REG & ADC_Timer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: ADC_Timer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - ADC_Timer_INTR_MASK_TC       - Terminal count mask
*     - ADC_Timer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetInterruptMode(uint32 interruptMask)
{
    ADC_Timer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: ADC_Timer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - ADC_Timer_INTR_MASK_TC       - Terminal count mask
*     - ADC_Timer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ADC_Timer_GetInterruptSourceMasked(void)
{
    return (ADC_Timer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - ADC_Timer_INTR_MASK_TC       - Terminal count mask
*     - ADC_Timer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ADC_Timer_GetInterruptSource(void)
{
    return (ADC_Timer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: ADC_Timer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - ADC_Timer_INTR_MASK_TC       - Terminal count mask
*     - ADC_Timer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_ClearInterrupt(uint32 interruptMask)
{
    ADC_Timer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: ADC_Timer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - ADC_Timer_INTR_MASK_TC       - Terminal count mask
*     - ADC_Timer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ADC_Timer_SetInterrupt(uint32 interruptMask)
{
    ADC_Timer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
