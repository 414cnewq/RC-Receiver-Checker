/*******************************************************************************
* File Name: ANALOG_INT.h
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
#if !defined(CY_ISR_ANALOG_INT_H)
#define CY_ISR_ANALOG_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ANALOG_INT_Start(void);
void ANALOG_INT_StartEx(cyisraddress address);
void ANALOG_INT_Stop(void);

CY_ISR_PROTO(ANALOG_INT_Interrupt);

void ANALOG_INT_SetVector(cyisraddress address);
cyisraddress ANALOG_INT_GetVector(void);

void ANALOG_INT_SetPriority(uint8 priority);
uint8 ANALOG_INT_GetPriority(void);

void ANALOG_INT_Enable(void);
uint8 ANALOG_INT_GetState(void);
void ANALOG_INT_Disable(void);

void ANALOG_INT_SetPending(void);
void ANALOG_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ANALOG_INT ISR. */
#define ANALOG_INT_INTC_VECTOR            ((reg32 *) ANALOG_INT__INTC_VECT)

/* Address of the ANALOG_INT ISR priority. */
#define ANALOG_INT_INTC_PRIOR             ((reg32 *) ANALOG_INT__INTC_PRIOR_REG)

/* Priority of the ANALOG_INT interrupt. */
#define ANALOG_INT_INTC_PRIOR_NUMBER      ANALOG_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ANALOG_INT interrupt. */
#define ANALOG_INT_INTC_SET_EN            ((reg32 *) ANALOG_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ANALOG_INT interrupt. */
#define ANALOG_INT_INTC_CLR_EN            ((reg32 *) ANALOG_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ANALOG_INT interrupt state to pending. */
#define ANALOG_INT_INTC_SET_PD            ((reg32 *) ANALOG_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ANALOG_INT interrupt. */
#define ANALOG_INT_INTC_CLR_PD            ((reg32 *) ANALOG_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_ANALOG_INT_H */


/* [] END OF FILE */
