/*******************************************************************************
* File Name: BETWEEN_Timer_INT.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_BETWEEN_Timer_INT_H)
#define CY_ISR_BETWEEN_Timer_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BETWEEN_Timer_INT_Start(void);
void BETWEEN_Timer_INT_StartEx(cyisraddress address);
void BETWEEN_Timer_INT_Stop(void);

CY_ISR_PROTO(BETWEEN_Timer_INT_Interrupt);

void BETWEEN_Timer_INT_SetVector(cyisraddress address);
cyisraddress BETWEEN_Timer_INT_GetVector(void);

void BETWEEN_Timer_INT_SetPriority(uint8 priority);
uint8 BETWEEN_Timer_INT_GetPriority(void);

void BETWEEN_Timer_INT_Enable(void);
uint8 BETWEEN_Timer_INT_GetState(void);
void BETWEEN_Timer_INT_Disable(void);

void BETWEEN_Timer_INT_SetPending(void);
void BETWEEN_Timer_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BETWEEN_Timer_INT ISR. */
#define BETWEEN_Timer_INT_INTC_VECTOR            ((reg32 *) BETWEEN_Timer_INT__INTC_VECT)

/* Address of the BETWEEN_Timer_INT ISR priority. */
#define BETWEEN_Timer_INT_INTC_PRIOR             ((reg32 *) BETWEEN_Timer_INT__INTC_PRIOR_REG)

/* Priority of the BETWEEN_Timer_INT interrupt. */
#define BETWEEN_Timer_INT_INTC_PRIOR_NUMBER      BETWEEN_Timer_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BETWEEN_Timer_INT interrupt. */
#define BETWEEN_Timer_INT_INTC_SET_EN            ((reg32 *) BETWEEN_Timer_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BETWEEN_Timer_INT interrupt. */
#define BETWEEN_Timer_INT_INTC_CLR_EN            ((reg32 *) BETWEEN_Timer_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BETWEEN_Timer_INT interrupt state to pending. */
#define BETWEEN_Timer_INT_INTC_SET_PD            ((reg32 *) BETWEEN_Timer_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BETWEEN_Timer_INT interrupt. */
#define BETWEEN_Timer_INT_INTC_CLR_PD            ((reg32 *) BETWEEN_Timer_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_BETWEEN_Timer_INT_H */


/* [] END OF FILE */
