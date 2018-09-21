/*******************************************************************************
* File Name: LOW_TIMER.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the LOW_TIMER
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

#include "LOW_TIMER.h"

uint8 LOW_TIMER_initVar = 0u;


/*******************************************************************************
* Function Name: LOW_TIMER_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default LOW_TIMER configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (LOW_TIMER__QUAD == LOW_TIMER_CONFIG)
        LOW_TIMER_CONTROL_REG = LOW_TIMER_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        LOW_TIMER_TRIG_CONTROL1_REG  = LOW_TIMER_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        LOW_TIMER_SetInterruptMode(LOW_TIMER_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        LOW_TIMER_SetCounterMode(LOW_TIMER_COUNT_DOWN);
        LOW_TIMER_WritePeriod(LOW_TIMER_QUAD_PERIOD_INIT_VALUE);
        LOW_TIMER_WriteCounter(LOW_TIMER_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (LOW_TIMER__QUAD == LOW_TIMER_CONFIG) */

    #if (LOW_TIMER__TIMER == LOW_TIMER_CONFIG)
        LOW_TIMER_CONTROL_REG = LOW_TIMER_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        LOW_TIMER_TRIG_CONTROL1_REG  = LOW_TIMER_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        LOW_TIMER_SetInterruptMode(LOW_TIMER_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        LOW_TIMER_WritePeriod(LOW_TIMER_TC_PERIOD_VALUE );

        #if (LOW_TIMER__COMPARE == LOW_TIMER_TC_COMP_CAP_MODE)
            LOW_TIMER_WriteCompare(LOW_TIMER_TC_COMPARE_VALUE);

            #if (1u == LOW_TIMER_TC_COMPARE_SWAP)
                LOW_TIMER_SetCompareSwap(1u);
                LOW_TIMER_WriteCompareBuf(LOW_TIMER_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == LOW_TIMER_TC_COMPARE_SWAP) */
        #endif  /* (LOW_TIMER__COMPARE == LOW_TIMER_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (LOW_TIMER_CY_TCPWM_V2 && LOW_TIMER_TIMER_UPDOWN_CNT_USED && !LOW_TIMER_CY_TCPWM_4000)
            LOW_TIMER_WriteCounter(1u);
        #elif(LOW_TIMER__COUNT_DOWN == LOW_TIMER_TC_COUNTER_MODE)
            LOW_TIMER_WriteCounter(LOW_TIMER_TC_PERIOD_VALUE);
        #else
            LOW_TIMER_WriteCounter(0u);
        #endif /* (LOW_TIMER_CY_TCPWM_V2 && LOW_TIMER_TIMER_UPDOWN_CNT_USED && !LOW_TIMER_CY_TCPWM_4000) */
    #endif  /* (LOW_TIMER__TIMER == LOW_TIMER_CONFIG) */

    #if (LOW_TIMER__PWM_SEL == LOW_TIMER_CONFIG)
        LOW_TIMER_CONTROL_REG = LOW_TIMER_CTRL_PWM_BASE_CONFIG;

        #if (LOW_TIMER__PWM_PR == LOW_TIMER_PWM_MODE)
            LOW_TIMER_CONTROL_REG |= LOW_TIMER_CTRL_PWM_RUN_MODE;
            LOW_TIMER_WriteCounter(LOW_TIMER_PWM_PR_INIT_VALUE);
        #else
            LOW_TIMER_CONTROL_REG |= LOW_TIMER_CTRL_PWM_ALIGN | LOW_TIMER_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (LOW_TIMER_CY_TCPWM_V2 && LOW_TIMER_PWM_UPDOWN_CNT_USED && !LOW_TIMER_CY_TCPWM_4000)
                LOW_TIMER_WriteCounter(1u);
            #elif (LOW_TIMER__RIGHT == LOW_TIMER_PWM_ALIGN)
                LOW_TIMER_WriteCounter(LOW_TIMER_PWM_PERIOD_VALUE);
            #else 
                LOW_TIMER_WriteCounter(0u);
            #endif  /* (LOW_TIMER_CY_TCPWM_V2 && LOW_TIMER_PWM_UPDOWN_CNT_USED && !LOW_TIMER_CY_TCPWM_4000) */
        #endif  /* (LOW_TIMER__PWM_PR == LOW_TIMER_PWM_MODE) */

        #if (LOW_TIMER__PWM_DT == LOW_TIMER_PWM_MODE)
            LOW_TIMER_CONTROL_REG |= LOW_TIMER_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (LOW_TIMER__PWM_DT == LOW_TIMER_PWM_MODE) */

        #if (LOW_TIMER__PWM == LOW_TIMER_PWM_MODE)
            LOW_TIMER_CONTROL_REG |= LOW_TIMER_CTRL_PWM_PRESCALER;
        #endif  /* (LOW_TIMER__PWM == LOW_TIMER_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        LOW_TIMER_TRIG_CONTROL1_REG  = LOW_TIMER_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        LOW_TIMER_SetInterruptMode(LOW_TIMER_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (LOW_TIMER__PWM_PR == LOW_TIMER_PWM_MODE)
            LOW_TIMER_TRIG_CONTROL2_REG =
                    (LOW_TIMER_CC_MATCH_NO_CHANGE    |
                    LOW_TIMER_OVERLOW_NO_CHANGE      |
                    LOW_TIMER_UNDERFLOW_NO_CHANGE);
        #else
            #if (LOW_TIMER__LEFT == LOW_TIMER_PWM_ALIGN)
                LOW_TIMER_TRIG_CONTROL2_REG = LOW_TIMER_PWM_MODE_LEFT;
            #endif  /* ( LOW_TIMER_PWM_LEFT == LOW_TIMER_PWM_ALIGN) */

            #if (LOW_TIMER__RIGHT == LOW_TIMER_PWM_ALIGN)
                LOW_TIMER_TRIG_CONTROL2_REG = LOW_TIMER_PWM_MODE_RIGHT;
            #endif  /* ( LOW_TIMER_PWM_RIGHT == LOW_TIMER_PWM_ALIGN) */

            #if (LOW_TIMER__CENTER == LOW_TIMER_PWM_ALIGN)
                LOW_TIMER_TRIG_CONTROL2_REG = LOW_TIMER_PWM_MODE_CENTER;
            #endif  /* ( LOW_TIMER_PWM_CENTER == LOW_TIMER_PWM_ALIGN) */

            #if (LOW_TIMER__ASYMMETRIC == LOW_TIMER_PWM_ALIGN)
                LOW_TIMER_TRIG_CONTROL2_REG = LOW_TIMER_PWM_MODE_ASYM;
            #endif  /* (LOW_TIMER__ASYMMETRIC == LOW_TIMER_PWM_ALIGN) */
        #endif  /* (LOW_TIMER__PWM_PR == LOW_TIMER_PWM_MODE) */

        /* Set other values from customizer */
        LOW_TIMER_WritePeriod(LOW_TIMER_PWM_PERIOD_VALUE );
        LOW_TIMER_WriteCompare(LOW_TIMER_PWM_COMPARE_VALUE);

        #if (1u == LOW_TIMER_PWM_COMPARE_SWAP)
            LOW_TIMER_SetCompareSwap(1u);
            LOW_TIMER_WriteCompareBuf(LOW_TIMER_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == LOW_TIMER_PWM_COMPARE_SWAP) */

        #if (1u == LOW_TIMER_PWM_PERIOD_SWAP)
            LOW_TIMER_SetPeriodSwap(1u);
            LOW_TIMER_WritePeriodBuf(LOW_TIMER_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == LOW_TIMER_PWM_PERIOD_SWAP) */
    #endif  /* (LOW_TIMER__PWM_SEL == LOW_TIMER_CONFIG) */
    
}


/*******************************************************************************
* Function Name: LOW_TIMER_Enable
********************************************************************************
*
* Summary:
*  Enables the LOW_TIMER.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    LOW_TIMER_BLOCK_CONTROL_REG |= LOW_TIMER_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (LOW_TIMER__PWM_SEL == LOW_TIMER_CONFIG)
        #if (0u == LOW_TIMER_PWM_START_SIGNAL_PRESENT)
            LOW_TIMER_TriggerCommand(LOW_TIMER_MASK, LOW_TIMER_CMD_START);
        #endif /* (0u == LOW_TIMER_PWM_START_SIGNAL_PRESENT) */
    #endif /* (LOW_TIMER__PWM_SEL == LOW_TIMER_CONFIG) */

    #if (LOW_TIMER__TIMER == LOW_TIMER_CONFIG)
        #if (0u == LOW_TIMER_TC_START_SIGNAL_PRESENT)
            LOW_TIMER_TriggerCommand(LOW_TIMER_MASK, LOW_TIMER_CMD_START);
        #endif /* (0u == LOW_TIMER_TC_START_SIGNAL_PRESENT) */
    #endif /* (LOW_TIMER__TIMER == LOW_TIMER_CONFIG) */
    
    #if (LOW_TIMER__QUAD == LOW_TIMER_CONFIG)
        #if (0u != LOW_TIMER_QUAD_AUTO_START)
            LOW_TIMER_TriggerCommand(LOW_TIMER_MASK, LOW_TIMER_CMD_RELOAD);
        #endif /* (0u != LOW_TIMER_QUAD_AUTO_START) */
    #endif  /* (LOW_TIMER__QUAD == LOW_TIMER_CONFIG) */
}


/*******************************************************************************
* Function Name: LOW_TIMER_Start
********************************************************************************
*
* Summary:
*  Initializes the LOW_TIMER with default customizer
*  values when called the first time and enables the LOW_TIMER.
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
*  LOW_TIMER_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time LOW_TIMER_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the LOW_TIMER_Start() routine.
*
*******************************************************************************/
void LOW_TIMER_Start(void)
{
    if (0u == LOW_TIMER_initVar)
    {
        LOW_TIMER_Init();
        LOW_TIMER_initVar = 1u;
    }

    LOW_TIMER_Enable();
}


/*******************************************************************************
* Function Name: LOW_TIMER_Stop
********************************************************************************
*
* Summary:
*  Disables the LOW_TIMER.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_BLOCK_CONTROL_REG &= (uint32)~LOW_TIMER_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the LOW_TIMER. This function is used when
*  configured as a generic LOW_TIMER and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the LOW_TIMER to operate in
*   Values:
*   - LOW_TIMER_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - LOW_TIMER_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - LOW_TIMER_MODE_QUAD - Quadrature decoder
*         - LOW_TIMER_MODE_PWM - PWM
*         - LOW_TIMER_MODE_PWM_DT - PWM with dead time
*         - LOW_TIMER_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_MODE_MASK;
    LOW_TIMER_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - LOW_TIMER_MODE_X1 - Counts on phi 1 rising
*         - LOW_TIMER_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - LOW_TIMER_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_QUAD_MODE_MASK;
    LOW_TIMER_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - LOW_TIMER_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - LOW_TIMER_PRESCALE_DIVBY2    - Divide by 2
*         - LOW_TIMER_PRESCALE_DIVBY4    - Divide by 4
*         - LOW_TIMER_PRESCALE_DIVBY8    - Divide by 8
*         - LOW_TIMER_PRESCALE_DIVBY16   - Divide by 16
*         - LOW_TIMER_PRESCALE_DIVBY32   - Divide by 32
*         - LOW_TIMER_PRESCALE_DIVBY64   - Divide by 64
*         - LOW_TIMER_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_PRESCALER_MASK;
    LOW_TIMER_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the LOW_TIMER runs
*  continuously or stops when terminal count is reached.  By default the
*  LOW_TIMER operates in the continuous mode.
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
void LOW_TIMER_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_ONESHOT_MASK;
    LOW_TIMER_CONTROL_REG |= ((uint32)((oneShotEnable & LOW_TIMER_1BIT_MASK) <<
                                                               LOW_TIMER_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPWMMode
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
void LOW_TIMER_SetPWMMode(uint32 modeMask)
{
    LOW_TIMER_TRIG_CONTROL2_REG = (modeMask & LOW_TIMER_6BIT_MASK);
}



/*******************************************************************************
* Function Name: LOW_TIMER_SetPWMSyncKill
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
void LOW_TIMER_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_PWM_SYNC_KILL_MASK;
    LOW_TIMER_CONTROL_REG |= ((uint32)((syncKillEnable & LOW_TIMER_1BIT_MASK)  <<
                                               LOW_TIMER_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPWMStopOnKill
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
void LOW_TIMER_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_PWM_STOP_KILL_MASK;
    LOW_TIMER_CONTROL_REG |= ((uint32)((stopOnKillEnable & LOW_TIMER_1BIT_MASK)  <<
                                                         LOW_TIMER_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPWMDeadTime
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
void LOW_TIMER_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_PRESCALER_MASK;
    LOW_TIMER_CONTROL_REG |= ((uint32)((deadTime & LOW_TIMER_8BIT_MASK) <<
                                                          LOW_TIMER_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPWMInvert
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
*         - LOW_TIMER_INVERT_LINE   - Inverts the line output
*         - LOW_TIMER_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_INV_OUT_MASK;
    LOW_TIMER_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: LOW_TIMER_WriteCounter
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
void LOW_TIMER_WriteCounter(uint32 count)
{
    LOW_TIMER_COUNTER_REG = (count & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadCounter
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
uint32 LOW_TIMER_ReadCounter(void)
{
    return (LOW_TIMER_COUNTER_REG & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - LOW_TIMER_COUNT_UP       - Counts up
*     - LOW_TIMER_COUNT_DOWN     - Counts down
*     - LOW_TIMER_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - LOW_TIMER_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_UPDOWN_MASK;
    LOW_TIMER_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_WritePeriod
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
void LOW_TIMER_WritePeriod(uint32 period)
{
    LOW_TIMER_PERIOD_REG = (period & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadPeriod
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
uint32 LOW_TIMER_ReadPeriod(void)
{
    return (LOW_TIMER_PERIOD_REG & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetCompareSwap
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
void LOW_TIMER_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_RELOAD_CC_MASK;
    LOW_TIMER_CONTROL_REG |= (swapEnable & LOW_TIMER_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_WritePeriodBuf
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
void LOW_TIMER_WritePeriodBuf(uint32 periodBuf)
{
    LOW_TIMER_PERIOD_BUF_REG = (periodBuf & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadPeriodBuf
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
uint32 LOW_TIMER_ReadPeriodBuf(void)
{
    return (LOW_TIMER_PERIOD_BUF_REG & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetPeriodSwap
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
void LOW_TIMER_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_CONTROL_REG &= (uint32)~LOW_TIMER_RELOAD_PERIOD_MASK;
    LOW_TIMER_CONTROL_REG |= ((uint32)((swapEnable & LOW_TIMER_1BIT_MASK) <<
                                                            LOW_TIMER_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_WriteCompare
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
void LOW_TIMER_WriteCompare(uint32 compare)
{
    #if (LOW_TIMER_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */

    #if (LOW_TIMER_CY_TCPWM_4000)
        currentMode = ((LOW_TIMER_CONTROL_REG & LOW_TIMER_UPDOWN_MASK) >> LOW_TIMER_UPDOWN_SHIFT);

        if (((uint32)LOW_TIMER__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)LOW_TIMER__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */
    
    LOW_TIMER_COMP_CAP_REG = (compare & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadCompare
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
uint32 LOW_TIMER_ReadCompare(void)
{
    #if (LOW_TIMER_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */

    #if (LOW_TIMER_CY_TCPWM_4000)
        currentMode = ((LOW_TIMER_CONTROL_REG & LOW_TIMER_UPDOWN_MASK) >> LOW_TIMER_UPDOWN_SHIFT);
        
        regVal = LOW_TIMER_COMP_CAP_REG;
        
        if (((uint32)LOW_TIMER__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)LOW_TIMER__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & LOW_TIMER_16BIT_MASK);
    #else
        return (LOW_TIMER_COMP_CAP_REG & LOW_TIMER_16BIT_MASK);
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: LOW_TIMER_WriteCompareBuf
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
void LOW_TIMER_WriteCompareBuf(uint32 compareBuf)
{
    #if (LOW_TIMER_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */

    #if (LOW_TIMER_CY_TCPWM_4000)
        currentMode = ((LOW_TIMER_CONTROL_REG & LOW_TIMER_UPDOWN_MASK) >> LOW_TIMER_UPDOWN_SHIFT);

        if (((uint32)LOW_TIMER__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)LOW_TIMER__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */
    
    LOW_TIMER_COMP_CAP_BUF_REG = (compareBuf & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadCompareBuf
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
uint32 LOW_TIMER_ReadCompareBuf(void)
{
    #if (LOW_TIMER_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */

    #if (LOW_TIMER_CY_TCPWM_4000)
        currentMode = ((LOW_TIMER_CONTROL_REG & LOW_TIMER_UPDOWN_MASK) >> LOW_TIMER_UPDOWN_SHIFT);

        regVal = LOW_TIMER_COMP_CAP_BUF_REG;
        
        if (((uint32)LOW_TIMER__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)LOW_TIMER__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & LOW_TIMER_16BIT_MASK);
    #else
        return (LOW_TIMER_COMP_CAP_BUF_REG & LOW_TIMER_16BIT_MASK);
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadCapture
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
uint32 LOW_TIMER_ReadCapture(void)
{
    return (LOW_TIMER_COMP_CAP_REG & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadCaptureBuf
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
uint32 LOW_TIMER_ReadCaptureBuf(void)
{
    return (LOW_TIMER_COMP_CAP_BUF_REG & LOW_TIMER_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetCaptureMode
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
*     - LOW_TIMER_TRIG_LEVEL     - Level
*     - LOW_TIMER_TRIG_RISING    - Rising edge
*     - LOW_TIMER_TRIG_FALLING   - Falling edge
*     - LOW_TIMER_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_TRIG_CONTROL1_REG &= (uint32)~LOW_TIMER_CAPTURE_MASK;
    LOW_TIMER_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LOW_TIMER_TRIG_LEVEL     - Level
*     - LOW_TIMER_TRIG_RISING    - Rising edge
*     - LOW_TIMER_TRIG_FALLING   - Falling edge
*     - LOW_TIMER_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_TRIG_CONTROL1_REG &= (uint32)~LOW_TIMER_RELOAD_MASK;
    LOW_TIMER_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LOW_TIMER_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LOW_TIMER_TRIG_LEVEL     - Level
*     - LOW_TIMER_TRIG_RISING    - Rising edge
*     - LOW_TIMER_TRIG_FALLING   - Falling edge
*     - LOW_TIMER_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_TRIG_CONTROL1_REG &= (uint32)~LOW_TIMER_START_MASK;
    LOW_TIMER_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LOW_TIMER_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LOW_TIMER_TRIG_LEVEL     - Level
*     - LOW_TIMER_TRIG_RISING    - Rising edge
*     - LOW_TIMER_TRIG_FALLING   - Falling edge
*     - LOW_TIMER_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_TRIG_CONTROL1_REG &= (uint32)~LOW_TIMER_STOP_MASK;
    LOW_TIMER_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LOW_TIMER_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LOW_TIMER_TRIG_LEVEL     - Level
*     - LOW_TIMER_TRIG_RISING    - Rising edge
*     - LOW_TIMER_TRIG_FALLING   - Falling edge
*     - LOW_TIMER_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_TRIG_CONTROL1_REG &= (uint32)~LOW_TIMER_COUNT_MASK;
    LOW_TIMER_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LOW_TIMER_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_TriggerCommand
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
*     - LOW_TIMER_CMD_CAPTURE    - Trigger Capture/Switch command
*     - LOW_TIMER_CMD_RELOAD     - Trigger Reload/Index command
*     - LOW_TIMER_CMD_STOP       - Trigger Stop/Kill command
*     - LOW_TIMER_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LOW_TIMER_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the LOW_TIMER.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - LOW_TIMER_STATUS_DOWN    - Set if counting down
*     - LOW_TIMER_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 LOW_TIMER_ReadStatus(void)
{
    return ((LOW_TIMER_STATUS_REG >> LOW_TIMER_RUNNING_STATUS_SHIFT) |
            (LOW_TIMER_STATUS_REG & LOW_TIMER_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - LOW_TIMER_INTR_MASK_TC       - Terminal count mask
*     - LOW_TIMER_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetInterruptMode(uint32 interruptMask)
{
    LOW_TIMER_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: LOW_TIMER_GetInterruptSourceMasked
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
*     - LOW_TIMER_INTR_MASK_TC       - Terminal count mask
*     - LOW_TIMER_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 LOW_TIMER_GetInterruptSourceMasked(void)
{
    return (LOW_TIMER_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: LOW_TIMER_GetInterruptSource
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
*     - LOW_TIMER_INTR_MASK_TC       - Terminal count mask
*     - LOW_TIMER_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 LOW_TIMER_GetInterruptSource(void)
{
    return (LOW_TIMER_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: LOW_TIMER_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - LOW_TIMER_INTR_MASK_TC       - Terminal count mask
*     - LOW_TIMER_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_ClearInterrupt(uint32 interruptMask)
{
    LOW_TIMER_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: LOW_TIMER_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - LOW_TIMER_INTR_MASK_TC       - Terminal count mask
*     - LOW_TIMER_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LOW_TIMER_SetInterrupt(uint32 interruptMask)
{
    LOW_TIMER_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
