/*******************************************************************************
* File Name: UDB_TIMER_ADC.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_UDB_TIMER_ADC_H)
#define CY_TIMER_UDB_TIMER_ADC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 UDB_TIMER_ADC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define UDB_TIMER_ADC_Resolution                 8u
#define UDB_TIMER_ADC_UsingFixedFunction         0u
#define UDB_TIMER_ADC_UsingHWCaptureCounter      0u
#define UDB_TIMER_ADC_SoftwareCaptureMode        0u
#define UDB_TIMER_ADC_SoftwareTriggerMode        0u
#define UDB_TIMER_ADC_UsingHWEnable              1u
#define UDB_TIMER_ADC_EnableTriggerMode          0u
#define UDB_TIMER_ADC_InterruptOnCaptureCount    0u
#define UDB_TIMER_ADC_RunModeUsed                0u
#define UDB_TIMER_ADC_ControlRegRemoved          1u

#if defined(UDB_TIMER_ADC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (UDB_TIMER_ADC_UsingFixedFunction)
    #define UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End UDB_TIMER_ADC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!UDB_TIMER_ADC_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (UDB_TIMER_ADC_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}UDB_TIMER_ADC_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    UDB_TIMER_ADC_Start(void) ;
void    UDB_TIMER_ADC_Stop(void) ;

void    UDB_TIMER_ADC_SetInterruptMode(uint8 interruptMode) ;
uint8   UDB_TIMER_ADC_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define UDB_TIMER_ADC_GetInterruptSource() UDB_TIMER_ADC_ReadStatusRegister()

#if(!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED)
    uint8   UDB_TIMER_ADC_ReadControlRegister(void) ;
    void    UDB_TIMER_ADC_WriteControlRegister(uint8 control) ;
#endif /* (!UDB_TIMER_ADC_UDB_CONTROL_REG_REMOVED) */

uint8  UDB_TIMER_ADC_ReadPeriod(void) ;
void    UDB_TIMER_ADC_WritePeriod(uint8 period) ;
uint8  UDB_TIMER_ADC_ReadCounter(void) ;
void    UDB_TIMER_ADC_WriteCounter(uint8 counter) ;
uint8  UDB_TIMER_ADC_ReadCapture(void) ;
void    UDB_TIMER_ADC_SoftwareCapture(void) ;

#if(!UDB_TIMER_ADC_UsingFixedFunction) /* UDB Prototypes */
    #if (UDB_TIMER_ADC_SoftwareCaptureMode)
        void    UDB_TIMER_ADC_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!UDB_TIMER_ADC_UsingFixedFunction) */

    #if (UDB_TIMER_ADC_SoftwareTriggerMode)
        void    UDB_TIMER_ADC_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (UDB_TIMER_ADC_SoftwareTriggerMode) */

    #if (UDB_TIMER_ADC_EnableTriggerMode)
        void    UDB_TIMER_ADC_EnableTrigger(void) ;
        void    UDB_TIMER_ADC_DisableTrigger(void) ;
    #endif /* (UDB_TIMER_ADC_EnableTriggerMode) */


    #if(UDB_TIMER_ADC_InterruptOnCaptureCount)
        void    UDB_TIMER_ADC_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (UDB_TIMER_ADC_InterruptOnCaptureCount) */

    #if (UDB_TIMER_ADC_UsingHWCaptureCounter)
        void    UDB_TIMER_ADC_SetCaptureCount(uint8 captureCount) ;
        uint8   UDB_TIMER_ADC_ReadCaptureCount(void) ;
    #endif /* (UDB_TIMER_ADC_UsingHWCaptureCounter) */

    void UDB_TIMER_ADC_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void UDB_TIMER_ADC_Init(void)          ;
void UDB_TIMER_ADC_Enable(void)        ;
void UDB_TIMER_ADC_SaveConfig(void)    ;
void UDB_TIMER_ADC_RestoreConfig(void) ;
void UDB_TIMER_ADC_Sleep(void)         ;
void UDB_TIMER_ADC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define UDB_TIMER_ADC__B_TIMER__CM_NONE 0
#define UDB_TIMER_ADC__B_TIMER__CM_RISINGEDGE 1
#define UDB_TIMER_ADC__B_TIMER__CM_FALLINGEDGE 2
#define UDB_TIMER_ADC__B_TIMER__CM_EITHEREDGE 3
#define UDB_TIMER_ADC__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define UDB_TIMER_ADC__B_TIMER__TM_NONE 0x00u
#define UDB_TIMER_ADC__B_TIMER__TM_RISINGEDGE 0x04u
#define UDB_TIMER_ADC__B_TIMER__TM_FALLINGEDGE 0x08u
#define UDB_TIMER_ADC__B_TIMER__TM_EITHEREDGE 0x0Cu
#define UDB_TIMER_ADC__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define UDB_TIMER_ADC_INIT_PERIOD             215u
#define UDB_TIMER_ADC_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << UDB_TIMER_ADC_CTRL_CAP_MODE_SHIFT))
#define UDB_TIMER_ADC_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << UDB_TIMER_ADC_CTRL_TRIG_MODE_SHIFT))
#if (UDB_TIMER_ADC_UsingFixedFunction)
    #define UDB_TIMER_ADC_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << UDB_TIMER_ADC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define UDB_TIMER_ADC_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << UDB_TIMER_ADC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UDB_TIMER_ADC_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (UDB_TIMER_ADC_UsingFixedFunction) */
#define UDB_TIMER_ADC_INIT_CAPTURE_COUNT      (2u)
#define UDB_TIMER_ADC_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << UDB_TIMER_ADC_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (UDB_TIMER_ADC_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define UDB_TIMER_ADC_STATUS         (*(reg8 *) UDB_TIMER_ADC_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define UDB_TIMER_ADC_STATUS_MASK    (*(reg8 *) UDB_TIMER_ADC_TimerHW__SR0 )
    #define UDB_TIMER_ADC_CONTROL        (*(reg8 *) UDB_TIMER_ADC_TimerHW__CFG0)
    #define UDB_TIMER_ADC_CONTROL2       (*(reg8 *) UDB_TIMER_ADC_TimerHW__CFG1)
    #define UDB_TIMER_ADC_CONTROL2_PTR   ( (reg8 *) UDB_TIMER_ADC_TimerHW__CFG1)
    #define UDB_TIMER_ADC_RT1            (*(reg8 *) UDB_TIMER_ADC_TimerHW__RT1)
    #define UDB_TIMER_ADC_RT1_PTR        ( (reg8 *) UDB_TIMER_ADC_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define UDB_TIMER_ADC_CONTROL3       (*(reg8 *) UDB_TIMER_ADC_TimerHW__CFG2)
        #define UDB_TIMER_ADC_CONTROL3_PTR   ( (reg8 *) UDB_TIMER_ADC_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define UDB_TIMER_ADC_GLOBAL_ENABLE  (*(reg8 *) UDB_TIMER_ADC_TimerHW__PM_ACT_CFG)
    #define UDB_TIMER_ADC_GLOBAL_STBY_ENABLE  (*(reg8 *) UDB_TIMER_ADC_TimerHW__PM_STBY_CFG)

    #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerHW__CAP0 )
    #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerHW__CAP0 )
    #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg16 *) UDB_TIMER_ADC_TimerHW__PER0 )
    #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg16 *) UDB_TIMER_ADC_TimerHW__PER0 )
    #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerHW__CNT_CMP0 )
    #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define UDB_TIMER_ADC_BLOCK_EN_MASK                     UDB_TIMER_ADC_TimerHW__PM_ACT_MSK
    #define UDB_TIMER_ADC_BLOCK_STBY_EN_MASK                UDB_TIMER_ADC_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define UDB_TIMER_ADC_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define UDB_TIMER_ADC_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define UDB_TIMER_ADC_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define UDB_TIMER_ADC_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define UDB_TIMER_ADC_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define UDB_TIMER_ADC_CTRL_ENABLE                        ((uint8)((uint8)0x01u << UDB_TIMER_ADC_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define UDB_TIMER_ADC_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define UDB_TIMER_ADC_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << UDB_TIMER_ADC_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define UDB_TIMER_ADC_CTRL_MODE_SHIFT                 0x01u
        #define UDB_TIMER_ADC_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << UDB_TIMER_ADC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define UDB_TIMER_ADC_CTRL_RCOD_SHIFT        0x02u
        #define UDB_TIMER_ADC_CTRL_ENBL_SHIFT        0x00u
        #define UDB_TIMER_ADC_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define UDB_TIMER_ADC_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define UDB_TIMER_ADC_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << UDB_TIMER_ADC_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define UDB_TIMER_ADC_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define UDB_TIMER_ADC_CTRL_RCOD       ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_RCOD_SHIFT))
        #define UDB_TIMER_ADC_CTRL_ENBL       ((uint8)((uint8)0x80u << UDB_TIMER_ADC_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define UDB_TIMER_ADC_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define UDB_TIMER_ADC_RT1_MASK                        ((uint8)((uint8)0x03u << UDB_TIMER_ADC_RT1_SHIFT))
    #define UDB_TIMER_ADC_SYNC                            ((uint8)((uint8)0x03u << UDB_TIMER_ADC_RT1_SHIFT))
    #define UDB_TIMER_ADC_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define UDB_TIMER_ADC_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << UDB_TIMER_ADC_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define UDB_TIMER_ADC_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << UDB_TIMER_ADC_SYNCDSI_SHIFT))

    #define UDB_TIMER_ADC_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << UDB_TIMER_ADC_CTRL_MODE_SHIFT))
    #define UDB_TIMER_ADC_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << UDB_TIMER_ADC_CTRL_MODE_SHIFT))
    #define UDB_TIMER_ADC_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << UDB_TIMER_ADC_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UDB_TIMER_ADC_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UDB_TIMER_ADC_STATUS_TC_INT_MASK_SHIFT        (UDB_TIMER_ADC_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK_SHIFT   (UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define UDB_TIMER_ADC_STATUS_TC                       ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_TC_SHIFT))
    #define UDB_TIMER_ADC_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define UDB_TIMER_ADC_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define UDB_TIMER_ADC_STATUS              (* (reg8 *) UDB_TIMER_ADC_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define UDB_TIMER_ADC_STATUS_MASK         (* (reg8 *) UDB_TIMER_ADC_TimerUDB_rstSts_stsreg__MASK_REG)
    #define UDB_TIMER_ADC_STATUS_AUX_CTRL     (* (reg8 *) UDB_TIMER_ADC_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define UDB_TIMER_ADC_CONTROL             (* (reg8 *) UDB_TIMER_ADC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(UDB_TIMER_ADC_Resolution <= 8u) /* 8-bit Timer */
        #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(UDB_TIMER_ADC_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg16 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(UDB_TIMER_ADC_Resolution <= 24u)/* 24-bit Timer */
        #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define UDB_TIMER_ADC_CAPTURE_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define UDB_TIMER_ADC_CAPTURE_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB          (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define UDB_TIMER_ADC_PERIOD_LSB_PTR        ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB         (* (reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define UDB_TIMER_ADC_COUNTER_LSB_PTR       ((reg32 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define UDB_TIMER_ADC_COUNTER_LSB_PTR_8BIT       ((reg8 *) UDB_TIMER_ADC_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (UDB_TIMER_ADC_UsingHWCaptureCounter)
        #define UDB_TIMER_ADC_CAP_COUNT              (*(reg8 *) UDB_TIMER_ADC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UDB_TIMER_ADC_CAP_COUNT_PTR          ( (reg8 *) UDB_TIMER_ADC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UDB_TIMER_ADC_CAPTURE_COUNT_CTRL     (*(reg8 *) UDB_TIMER_ADC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define UDB_TIMER_ADC_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) UDB_TIMER_ADC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (UDB_TIMER_ADC_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define UDB_TIMER_ADC_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define UDB_TIMER_ADC_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_INTCNT_SHIFT))
    #define UDB_TIMER_ADC_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_TRIG_MODE_SHIFT))
    #define UDB_TIMER_ADC_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << UDB_TIMER_ADC_CTRL_TRIG_EN_SHIFT))
    #define UDB_TIMER_ADC_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << UDB_TIMER_ADC_CTRL_CAP_MODE_SHIFT))
    #define UDB_TIMER_ADC_CTRL_ENABLE                    ((uint8)((uint8)0x01u << UDB_TIMER_ADC_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define UDB_TIMER_ADC_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define UDB_TIMER_ADC_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_STATUS_TC_INT_MASK_SHIFT       UDB_TIMER_ADC_STATUS_TC_SHIFT
    #define UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK_SHIFT  UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT
    #define UDB_TIMER_ADC_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define UDB_TIMER_ADC_STATUS_FIFOFULL_INT_MASK_SHIFT UDB_TIMER_ADC_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_TC                      ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UDB_TIMER_ADC_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << UDB_TIMER_ADC_STATUS_FIFOFULL_SHIFT))

    #define UDB_TIMER_ADC_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define UDB_TIMER_ADC_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define UDB_TIMER_ADC_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define UDB_TIMER_ADC_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define UDB_TIMER_ADC_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define UDB_TIMER_ADC_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_UDB_TIMER_ADC_H */


/* [] END OF FILE */
