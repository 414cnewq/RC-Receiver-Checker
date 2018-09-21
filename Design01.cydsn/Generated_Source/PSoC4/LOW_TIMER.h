/*******************************************************************************
* File Name: LOW_TIMER.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the LOW_TIMER
*  component.
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

#if !defined(CY_TCPWM_LOW_TIMER_H)
#define CY_TCPWM_LOW_TIMER_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} LOW_TIMER_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  LOW_TIMER_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define LOW_TIMER_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define LOW_TIMER_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define LOW_TIMER_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define LOW_TIMER_QUAD_ENCODING_MODES            (0lu)
#define LOW_TIMER_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define LOW_TIMER_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define LOW_TIMER_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define LOW_TIMER_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define LOW_TIMER_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define LOW_TIMER_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define LOW_TIMER_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define LOW_TIMER_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define LOW_TIMER_TC_RUN_MODE                    (0lu)
#define LOW_TIMER_TC_COUNTER_MODE                (0lu)
#define LOW_TIMER_TC_COMP_CAP_MODE               (2lu)
#define LOW_TIMER_TC_PRESCALER                   (0lu)

/* Signal modes */
#define LOW_TIMER_TC_RELOAD_SIGNAL_MODE          (1lu)
#define LOW_TIMER_TC_COUNT_SIGNAL_MODE           (3lu)
#define LOW_TIMER_TC_START_SIGNAL_MODE           (1lu)
#define LOW_TIMER_TC_STOP_SIGNAL_MODE            (0lu)
#define LOW_TIMER_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define LOW_TIMER_TC_RELOAD_SIGNAL_PRESENT       (1lu)
#define LOW_TIMER_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define LOW_TIMER_TC_START_SIGNAL_PRESENT        (1lu)
#define LOW_TIMER_TC_STOP_SIGNAL_PRESENT         (1lu)
#define LOW_TIMER_TC_CAPTURE_SIGNAL_PRESENT      (1lu)

/* Interrupt Mask */
#define LOW_TIMER_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define LOW_TIMER_PWM_KILL_EVENT                 (0lu)
#define LOW_TIMER_PWM_STOP_EVENT                 (0lu)
#define LOW_TIMER_PWM_MODE                       (4lu)
#define LOW_TIMER_PWM_OUT_N_INVERT               (0lu)
#define LOW_TIMER_PWM_OUT_INVERT                 (0lu)
#define LOW_TIMER_PWM_ALIGN                      (0lu)
#define LOW_TIMER_PWM_RUN_MODE                   (0lu)
#define LOW_TIMER_PWM_DEAD_TIME_CYCLE            (0lu)
#define LOW_TIMER_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define LOW_TIMER_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define LOW_TIMER_PWM_COUNT_SIGNAL_MODE          (3lu)
#define LOW_TIMER_PWM_START_SIGNAL_MODE          (0lu)
#define LOW_TIMER_PWM_STOP_SIGNAL_MODE           (0lu)
#define LOW_TIMER_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define LOW_TIMER_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define LOW_TIMER_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define LOW_TIMER_PWM_START_SIGNAL_PRESENT       (0lu)
#define LOW_TIMER_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define LOW_TIMER_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define LOW_TIMER_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define LOW_TIMER_TC_PERIOD_VALUE                (65535lu)
#define LOW_TIMER_TC_COMPARE_VALUE               (65535lu)
#define LOW_TIMER_TC_COMPARE_BUF_VALUE           (65535lu)
#define LOW_TIMER_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define LOW_TIMER_PWM_PERIOD_VALUE               (65535lu)
#define LOW_TIMER_PWM_PERIOD_BUF_VALUE           (65535lu)
#define LOW_TIMER_PWM_PERIOD_SWAP                (0lu)
#define LOW_TIMER_PWM_COMPARE_VALUE              (65535lu)
#define LOW_TIMER_PWM_COMPARE_BUF_VALUE          (65535lu)
#define LOW_TIMER_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define LOW_TIMER__LEFT 0
#define LOW_TIMER__RIGHT 1
#define LOW_TIMER__CENTER 2
#define LOW_TIMER__ASYMMETRIC 3

#define LOW_TIMER__X1 0
#define LOW_TIMER__X2 1
#define LOW_TIMER__X4 2

#define LOW_TIMER__PWM 4
#define LOW_TIMER__PWM_DT 5
#define LOW_TIMER__PWM_PR 6

#define LOW_TIMER__INVERSE 1
#define LOW_TIMER__DIRECT 0

#define LOW_TIMER__CAPTURE 2
#define LOW_TIMER__COMPARE 0

#define LOW_TIMER__TRIG_LEVEL 3
#define LOW_TIMER__TRIG_RISING 0
#define LOW_TIMER__TRIG_FALLING 1
#define LOW_TIMER__TRIG_BOTH 2

#define LOW_TIMER__INTR_MASK_TC 1
#define LOW_TIMER__INTR_MASK_CC_MATCH 2
#define LOW_TIMER__INTR_MASK_NONE 0
#define LOW_TIMER__INTR_MASK_TC_CC 3

#define LOW_TIMER__UNCONFIG 8
#define LOW_TIMER__TIMER 1
#define LOW_TIMER__QUAD 3
#define LOW_TIMER__PWM_SEL 7

#define LOW_TIMER__COUNT_UP 0
#define LOW_TIMER__COUNT_DOWN 1
#define LOW_TIMER__COUNT_UPDOWN0 2
#define LOW_TIMER__COUNT_UPDOWN1 3


/* Prescaler */
#define LOW_TIMER_PRESCALE_DIVBY1                ((uint32)(0u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY2                ((uint32)(1u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY4                ((uint32)(2u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY8                ((uint32)(3u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY16               ((uint32)(4u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY32               ((uint32)(5u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY64               ((uint32)(6u << LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_PRESCALE_DIVBY128              ((uint32)(7u << LOW_TIMER_PRESCALER_SHIFT))

/* TCPWM set modes */
#define LOW_TIMER_MODE_TIMER_COMPARE             ((uint32)(LOW_TIMER__COMPARE         <<  \
                                                                  LOW_TIMER_MODE_SHIFT))
#define LOW_TIMER_MODE_TIMER_CAPTURE             ((uint32)(LOW_TIMER__CAPTURE         <<  \
                                                                  LOW_TIMER_MODE_SHIFT))
#define LOW_TIMER_MODE_QUAD                      ((uint32)(LOW_TIMER__QUAD            <<  \
                                                                  LOW_TIMER_MODE_SHIFT))
#define LOW_TIMER_MODE_PWM                       ((uint32)(LOW_TIMER__PWM             <<  \
                                                                  LOW_TIMER_MODE_SHIFT))
#define LOW_TIMER_MODE_PWM_DT                    ((uint32)(LOW_TIMER__PWM_DT          <<  \
                                                                  LOW_TIMER_MODE_SHIFT))
#define LOW_TIMER_MODE_PWM_PR                    ((uint32)(LOW_TIMER__PWM_PR          <<  \
                                                                  LOW_TIMER_MODE_SHIFT))

/* Quad Modes */
#define LOW_TIMER_MODE_X1                        ((uint32)(LOW_TIMER__X1              <<  \
                                                                  LOW_TIMER_QUAD_MODE_SHIFT))
#define LOW_TIMER_MODE_X2                        ((uint32)(LOW_TIMER__X2              <<  \
                                                                  LOW_TIMER_QUAD_MODE_SHIFT))
#define LOW_TIMER_MODE_X4                        ((uint32)(LOW_TIMER__X4              <<  \
                                                                  LOW_TIMER_QUAD_MODE_SHIFT))

/* Counter modes */
#define LOW_TIMER_COUNT_UP                       ((uint32)(LOW_TIMER__COUNT_UP        <<  \
                                                                  LOW_TIMER_UPDOWN_SHIFT))
#define LOW_TIMER_COUNT_DOWN                     ((uint32)(LOW_TIMER__COUNT_DOWN      <<  \
                                                                  LOW_TIMER_UPDOWN_SHIFT))
#define LOW_TIMER_COUNT_UPDOWN0                  ((uint32)(LOW_TIMER__COUNT_UPDOWN0   <<  \
                                                                  LOW_TIMER_UPDOWN_SHIFT))
#define LOW_TIMER_COUNT_UPDOWN1                  ((uint32)(LOW_TIMER__COUNT_UPDOWN1   <<  \
                                                                  LOW_TIMER_UPDOWN_SHIFT))

/* PWM output invert */
#define LOW_TIMER_INVERT_LINE                    ((uint32)(LOW_TIMER__INVERSE         <<  \
                                                                  LOW_TIMER_INV_OUT_SHIFT))
#define LOW_TIMER_INVERT_LINE_N                  ((uint32)(LOW_TIMER__INVERSE         <<  \
                                                                  LOW_TIMER_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define LOW_TIMER_TRIG_RISING                    ((uint32)LOW_TIMER__TRIG_RISING)
#define LOW_TIMER_TRIG_FALLING                   ((uint32)LOW_TIMER__TRIG_FALLING)
#define LOW_TIMER_TRIG_BOTH                      ((uint32)LOW_TIMER__TRIG_BOTH)
#define LOW_TIMER_TRIG_LEVEL                     ((uint32)LOW_TIMER__TRIG_LEVEL)

/* Interrupt mask */
#define LOW_TIMER_INTR_MASK_TC                   ((uint32)LOW_TIMER__INTR_MASK_TC)
#define LOW_TIMER_INTR_MASK_CC_MATCH             ((uint32)LOW_TIMER__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define LOW_TIMER_CC_MATCH_SET                   (0x00u)
#define LOW_TIMER_CC_MATCH_CLEAR                 (0x01u)
#define LOW_TIMER_CC_MATCH_INVERT                (0x02u)
#define LOW_TIMER_CC_MATCH_NO_CHANGE             (0x03u)
#define LOW_TIMER_OVERLOW_SET                    (0x00u)
#define LOW_TIMER_OVERLOW_CLEAR                  (0x04u)
#define LOW_TIMER_OVERLOW_INVERT                 (0x08u)
#define LOW_TIMER_OVERLOW_NO_CHANGE              (0x0Cu)
#define LOW_TIMER_UNDERFLOW_SET                  (0x00u)
#define LOW_TIMER_UNDERFLOW_CLEAR                (0x10u)
#define LOW_TIMER_UNDERFLOW_INVERT               (0x20u)
#define LOW_TIMER_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define LOW_TIMER_PWM_MODE_LEFT                  (LOW_TIMER_CC_MATCH_CLEAR        |   \
                                                         LOW_TIMER_OVERLOW_SET           |   \
                                                         LOW_TIMER_UNDERFLOW_NO_CHANGE)
#define LOW_TIMER_PWM_MODE_RIGHT                 (LOW_TIMER_CC_MATCH_SET          |   \
                                                         LOW_TIMER_OVERLOW_NO_CHANGE     |   \
                                                         LOW_TIMER_UNDERFLOW_CLEAR)
#define LOW_TIMER_PWM_MODE_ASYM                  (LOW_TIMER_CC_MATCH_INVERT       |   \
                                                         LOW_TIMER_OVERLOW_SET           |   \
                                                         LOW_TIMER_UNDERFLOW_CLEAR)

#if (LOW_TIMER_CY_TCPWM_V2)
    #if(LOW_TIMER_CY_TCPWM_4000)
        #define LOW_TIMER_PWM_MODE_CENTER                (LOW_TIMER_CC_MATCH_INVERT       |   \
                                                                 LOW_TIMER_OVERLOW_NO_CHANGE     |   \
                                                                 LOW_TIMER_UNDERFLOW_CLEAR)
    #else
        #define LOW_TIMER_PWM_MODE_CENTER                (LOW_TIMER_CC_MATCH_INVERT       |   \
                                                                 LOW_TIMER_OVERLOW_SET           |   \
                                                                 LOW_TIMER_UNDERFLOW_CLEAR)
    #endif /* (LOW_TIMER_CY_TCPWM_4000) */
#else
    #define LOW_TIMER_PWM_MODE_CENTER                (LOW_TIMER_CC_MATCH_INVERT       |   \
                                                             LOW_TIMER_OVERLOW_NO_CHANGE     |   \
                                                             LOW_TIMER_UNDERFLOW_CLEAR)
#endif /* (LOW_TIMER_CY_TCPWM_NEW) */

/* Command operations without condition */
#define LOW_TIMER_CMD_CAPTURE                    (0u)
#define LOW_TIMER_CMD_RELOAD                     (8u)
#define LOW_TIMER_CMD_STOP                       (16u)
#define LOW_TIMER_CMD_START                      (24u)

/* Status */
#define LOW_TIMER_STATUS_DOWN                    (1u)
#define LOW_TIMER_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   LOW_TIMER_Init(void);
void   LOW_TIMER_Enable(void);
void   LOW_TIMER_Start(void);
void   LOW_TIMER_Stop(void);

void   LOW_TIMER_SetMode(uint32 mode);
void   LOW_TIMER_SetCounterMode(uint32 counterMode);
void   LOW_TIMER_SetPWMMode(uint32 modeMask);
void   LOW_TIMER_SetQDMode(uint32 qdMode);

void   LOW_TIMER_SetPrescaler(uint32 prescaler);
void   LOW_TIMER_TriggerCommand(uint32 mask, uint32 command);
void   LOW_TIMER_SetOneShot(uint32 oneShotEnable);
uint32 LOW_TIMER_ReadStatus(void);

void   LOW_TIMER_SetPWMSyncKill(uint32 syncKillEnable);
void   LOW_TIMER_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   LOW_TIMER_SetPWMDeadTime(uint32 deadTime);
void   LOW_TIMER_SetPWMInvert(uint32 mask);

void   LOW_TIMER_SetInterruptMode(uint32 interruptMask);
uint32 LOW_TIMER_GetInterruptSourceMasked(void);
uint32 LOW_TIMER_GetInterruptSource(void);
void   LOW_TIMER_ClearInterrupt(uint32 interruptMask);
void   LOW_TIMER_SetInterrupt(uint32 interruptMask);

void   LOW_TIMER_WriteCounter(uint32 count);
uint32 LOW_TIMER_ReadCounter(void);

uint32 LOW_TIMER_ReadCapture(void);
uint32 LOW_TIMER_ReadCaptureBuf(void);

void   LOW_TIMER_WritePeriod(uint32 period);
uint32 LOW_TIMER_ReadPeriod(void);
void   LOW_TIMER_WritePeriodBuf(uint32 periodBuf);
uint32 LOW_TIMER_ReadPeriodBuf(void);

void   LOW_TIMER_WriteCompare(uint32 compare);
uint32 LOW_TIMER_ReadCompare(void);
void   LOW_TIMER_WriteCompareBuf(uint32 compareBuf);
uint32 LOW_TIMER_ReadCompareBuf(void);

void   LOW_TIMER_SetPeriodSwap(uint32 swapEnable);
void   LOW_TIMER_SetCompareSwap(uint32 swapEnable);

void   LOW_TIMER_SetCaptureMode(uint32 triggerMode);
void   LOW_TIMER_SetReloadMode(uint32 triggerMode);
void   LOW_TIMER_SetStartMode(uint32 triggerMode);
void   LOW_TIMER_SetStopMode(uint32 triggerMode);
void   LOW_TIMER_SetCountMode(uint32 triggerMode);

void   LOW_TIMER_SaveConfig(void);
void   LOW_TIMER_RestoreConfig(void);
void   LOW_TIMER_Sleep(void);
void   LOW_TIMER_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define LOW_TIMER_BLOCK_CONTROL_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define LOW_TIMER_BLOCK_CONTROL_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define LOW_TIMER_COMMAND_REG                    (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define LOW_TIMER_COMMAND_PTR                    ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define LOW_TIMER_INTRRUPT_CAUSE_REG             (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define LOW_TIMER_INTRRUPT_CAUSE_PTR             ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define LOW_TIMER_CONTROL_REG                    (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CTRL )
#define LOW_TIMER_CONTROL_PTR                    ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CTRL )
#define LOW_TIMER_STATUS_REG                     (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__STATUS )
#define LOW_TIMER_STATUS_PTR                     ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__STATUS )
#define LOW_TIMER_COUNTER_REG                    (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__COUNTER )
#define LOW_TIMER_COUNTER_PTR                    ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__COUNTER )
#define LOW_TIMER_COMP_CAP_REG                   (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CC )
#define LOW_TIMER_COMP_CAP_PTR                   ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CC )
#define LOW_TIMER_COMP_CAP_BUF_REG               (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CC_BUFF )
#define LOW_TIMER_COMP_CAP_BUF_PTR               ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__CC_BUFF )
#define LOW_TIMER_PERIOD_REG                     (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__PERIOD )
#define LOW_TIMER_PERIOD_PTR                     ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__PERIOD )
#define LOW_TIMER_PERIOD_BUF_REG                 (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define LOW_TIMER_PERIOD_BUF_PTR                 ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define LOW_TIMER_TRIG_CONTROL0_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define LOW_TIMER_TRIG_CONTROL0_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define LOW_TIMER_TRIG_CONTROL1_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define LOW_TIMER_TRIG_CONTROL1_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define LOW_TIMER_TRIG_CONTROL2_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define LOW_TIMER_TRIG_CONTROL2_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define LOW_TIMER_INTERRUPT_REQ_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR )
#define LOW_TIMER_INTERRUPT_REQ_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR )
#define LOW_TIMER_INTERRUPT_SET_REG              (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_SET )
#define LOW_TIMER_INTERRUPT_SET_PTR              ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_SET )
#define LOW_TIMER_INTERRUPT_MASK_REG             (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_MASK )
#define LOW_TIMER_INTERRUPT_MASK_PTR             ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_MASK )
#define LOW_TIMER_INTERRUPT_MASKED_REG           (*(reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_MASKED )
#define LOW_TIMER_INTERRUPT_MASKED_PTR           ( (reg32 *) LOW_TIMER_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define LOW_TIMER_MASK                           ((uint32)LOW_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define LOW_TIMER_RELOAD_CC_SHIFT                (0u)
#define LOW_TIMER_RELOAD_PERIOD_SHIFT            (1u)
#define LOW_TIMER_PWM_SYNC_KILL_SHIFT            (2u)
#define LOW_TIMER_PWM_STOP_KILL_SHIFT            (3u)
#define LOW_TIMER_PRESCALER_SHIFT                (8u)
#define LOW_TIMER_UPDOWN_SHIFT                   (16u)
#define LOW_TIMER_ONESHOT_SHIFT                  (18u)
#define LOW_TIMER_QUAD_MODE_SHIFT                (20u)
#define LOW_TIMER_INV_OUT_SHIFT                  (20u)
#define LOW_TIMER_INV_COMPL_OUT_SHIFT            (21u)
#define LOW_TIMER_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define LOW_TIMER_RELOAD_CC_MASK                 ((uint32)(LOW_TIMER_1BIT_MASK        <<  \
                                                                            LOW_TIMER_RELOAD_CC_SHIFT))
#define LOW_TIMER_RELOAD_PERIOD_MASK             ((uint32)(LOW_TIMER_1BIT_MASK        <<  \
                                                                            LOW_TIMER_RELOAD_PERIOD_SHIFT))
#define LOW_TIMER_PWM_SYNC_KILL_MASK             ((uint32)(LOW_TIMER_1BIT_MASK        <<  \
                                                                            LOW_TIMER_PWM_SYNC_KILL_SHIFT))
#define LOW_TIMER_PWM_STOP_KILL_MASK             ((uint32)(LOW_TIMER_1BIT_MASK        <<  \
                                                                            LOW_TIMER_PWM_STOP_KILL_SHIFT))
#define LOW_TIMER_PRESCALER_MASK                 ((uint32)(LOW_TIMER_8BIT_MASK        <<  \
                                                                            LOW_TIMER_PRESCALER_SHIFT))
#define LOW_TIMER_UPDOWN_MASK                    ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                            LOW_TIMER_UPDOWN_SHIFT))
#define LOW_TIMER_ONESHOT_MASK                   ((uint32)(LOW_TIMER_1BIT_MASK        <<  \
                                                                            LOW_TIMER_ONESHOT_SHIFT))
#define LOW_TIMER_QUAD_MODE_MASK                 ((uint32)(LOW_TIMER_3BIT_MASK        <<  \
                                                                            LOW_TIMER_QUAD_MODE_SHIFT))
#define LOW_TIMER_INV_OUT_MASK                   ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                            LOW_TIMER_INV_OUT_SHIFT))
#define LOW_TIMER_MODE_MASK                      ((uint32)(LOW_TIMER_3BIT_MASK        <<  \
                                                                            LOW_TIMER_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define LOW_TIMER_CAPTURE_SHIFT                  (0u)
#define LOW_TIMER_COUNT_SHIFT                    (2u)
#define LOW_TIMER_RELOAD_SHIFT                   (4u)
#define LOW_TIMER_STOP_SHIFT                     (6u)
#define LOW_TIMER_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define LOW_TIMER_CAPTURE_MASK                   ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                  LOW_TIMER_CAPTURE_SHIFT))
#define LOW_TIMER_COUNT_MASK                     ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                  LOW_TIMER_COUNT_SHIFT))
#define LOW_TIMER_RELOAD_MASK                    ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                  LOW_TIMER_RELOAD_SHIFT))
#define LOW_TIMER_STOP_MASK                      ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                  LOW_TIMER_STOP_SHIFT))
#define LOW_TIMER_START_MASK                     ((uint32)(LOW_TIMER_2BIT_MASK        <<  \
                                                                  LOW_TIMER_START_SHIFT))

/* MASK */
#define LOW_TIMER_1BIT_MASK                      ((uint32)0x01u)
#define LOW_TIMER_2BIT_MASK                      ((uint32)0x03u)
#define LOW_TIMER_3BIT_MASK                      ((uint32)0x07u)
#define LOW_TIMER_6BIT_MASK                      ((uint32)0x3Fu)
#define LOW_TIMER_8BIT_MASK                      ((uint32)0xFFu)
#define LOW_TIMER_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define LOW_TIMER_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define LOW_TIMER_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(LOW_TIMER_QUAD_ENCODING_MODES     << LOW_TIMER_QUAD_MODE_SHIFT))       |\
         ((uint32)(LOW_TIMER_CONFIG                  << LOW_TIMER_MODE_SHIFT)))

#define LOW_TIMER_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(LOW_TIMER_PWM_STOP_EVENT          << LOW_TIMER_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(LOW_TIMER_PWM_OUT_INVERT          << LOW_TIMER_INV_OUT_SHIFT))         |\
         ((uint32)(LOW_TIMER_PWM_OUT_N_INVERT        << LOW_TIMER_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(LOW_TIMER_PWM_MODE                << LOW_TIMER_MODE_SHIFT)))

#define LOW_TIMER_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(LOW_TIMER_PWM_RUN_MODE         << LOW_TIMER_ONESHOT_SHIFT))
            
#define LOW_TIMER_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(LOW_TIMER_PWM_ALIGN            << LOW_TIMER_UPDOWN_SHIFT))

#define LOW_TIMER_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(LOW_TIMER_PWM_KILL_EVENT      << LOW_TIMER_PWM_SYNC_KILL_SHIFT))

#define LOW_TIMER_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(LOW_TIMER_PWM_DEAD_TIME_CYCLE  << LOW_TIMER_PRESCALER_SHIFT))

#define LOW_TIMER_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(LOW_TIMER_PWM_PRESCALER        << LOW_TIMER_PRESCALER_SHIFT))

#define LOW_TIMER_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(LOW_TIMER_TC_PRESCALER            << LOW_TIMER_PRESCALER_SHIFT))       |\
         ((uint32)(LOW_TIMER_TC_COUNTER_MODE         << LOW_TIMER_UPDOWN_SHIFT))          |\
         ((uint32)(LOW_TIMER_TC_RUN_MODE             << LOW_TIMER_ONESHOT_SHIFT))         |\
         ((uint32)(LOW_TIMER_TC_COMP_CAP_MODE        << LOW_TIMER_MODE_SHIFT)))
        
#define LOW_TIMER_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(LOW_TIMER_QUAD_PHIA_SIGNAL_MODE   << LOW_TIMER_COUNT_SHIFT))           |\
         ((uint32)(LOW_TIMER_QUAD_INDEX_SIGNAL_MODE  << LOW_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(LOW_TIMER_QUAD_STOP_SIGNAL_MODE   << LOW_TIMER_STOP_SHIFT))            |\
         ((uint32)(LOW_TIMER_QUAD_PHIB_SIGNAL_MODE   << LOW_TIMER_START_SHIFT)))

#define LOW_TIMER_PWM_SIGNALS_MODES                                                              \
        (((uint32)(LOW_TIMER_PWM_SWITCH_SIGNAL_MODE  << LOW_TIMER_CAPTURE_SHIFT))         |\
         ((uint32)(LOW_TIMER_PWM_COUNT_SIGNAL_MODE   << LOW_TIMER_COUNT_SHIFT))           |\
         ((uint32)(LOW_TIMER_PWM_RELOAD_SIGNAL_MODE  << LOW_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(LOW_TIMER_PWM_STOP_SIGNAL_MODE    << LOW_TIMER_STOP_SHIFT))            |\
         ((uint32)(LOW_TIMER_PWM_START_SIGNAL_MODE   << LOW_TIMER_START_SHIFT)))

#define LOW_TIMER_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(LOW_TIMER_TC_CAPTURE_SIGNAL_MODE  << LOW_TIMER_CAPTURE_SHIFT))         |\
         ((uint32)(LOW_TIMER_TC_COUNT_SIGNAL_MODE    << LOW_TIMER_COUNT_SHIFT))           |\
         ((uint32)(LOW_TIMER_TC_RELOAD_SIGNAL_MODE   << LOW_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(LOW_TIMER_TC_STOP_SIGNAL_MODE     << LOW_TIMER_STOP_SHIFT))            |\
         ((uint32)(LOW_TIMER_TC_START_SIGNAL_MODE    << LOW_TIMER_START_SHIFT)))
        
#define LOW_TIMER_TIMER_UPDOWN_CNT_USED                                                          \
                ((LOW_TIMER__COUNT_UPDOWN0 == LOW_TIMER_TC_COUNTER_MODE)                  ||\
                 (LOW_TIMER__COUNT_UPDOWN1 == LOW_TIMER_TC_COUNTER_MODE))

#define LOW_TIMER_PWM_UPDOWN_CNT_USED                                                            \
                ((LOW_TIMER__CENTER == LOW_TIMER_PWM_ALIGN)                               ||\
                 (LOW_TIMER__ASYMMETRIC == LOW_TIMER_PWM_ALIGN))               
        
#define LOW_TIMER_PWM_PR_INIT_VALUE              (1u)
#define LOW_TIMER_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_LOW_TIMER_H */

/* [] END OF FILE */
