/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdbool.h>
#include <stdio.h>

volatile uint16 PulseLength=0;  // The PWM pulse length of the video switching signal
int q=0;
float vbat = 5;
uint16 prevPulse=0, ppPulse;      // last two pulses
float dPulse, ddPulse;

uint32 tAccrued=0;
bool flatline=true;


uint16 low_time = 0;
uint16 nthTime=0;
uint16 override;



CY_ISR(ADC_ISR)
{
    
    int x=0,y =0;
    ADC_StartConvert(); 
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    x = ADC_GetResult16(0);
    y = ADC_CountsTo_Volts(0,x);
    vbat = y * 5/3.3;
    nthTime++;
    Analog_Timer_ClearInterrupt(Analog_Timer_INTR_MASK_TC);
}

CY_ISR(PWM_Int)
{   
    
    static bool firstTime = true; //Whether an instance is the first time the PWM int is called
    static int t0;
    override=6;

    q++;
    PulseLength = PWM_Timer_ReadCapture()-t0 ; // This will give the total time that the pulse has been high
    firstTime = true; //Next call will be first of new cycle
    PWM_Timer_Stop(); //Stop the timer
    PWM_Timer_WriteCounter(0); //reset it
    PWM_Timer_Start(); //restart the timer

    PWM_Timer_ClearInterrupt(PWM_Timer_INTR_MASK_CC_MATCH); //clear the interrupt on the timer
}

int wdtIsrCnt = 0;
int nResets;
int timeRemain;


//ISR CALLED upon PSOC reset
//On second ISR Call: stop ISR and ensure 3 unhandled ISRS for reset
CY_ISR(wdtISR)
{
    if(wdtIsrCnt == 0)
        WDT_ISR_ClearPending();
    else
    {
        WDT_ISR_Stop();
    }
    wdtIsrCnt++;
}

int main(void)
{
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_INT_RESET);         // put WDT on Reset on unhandled int mode
    
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, ( (uint32) (5000*32000) / 1000) ); //1 second delay before reset
    CySysWdtWriteClearOnMatch( CY_SYS_WDT_COUNTER0, 1u );                      // Clear the counter on match
    //enable counter
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK); // Enable the watchdog counter
    
    while(!CySysWdtReadEnabledStatus(CY_SYS_WDT_COUNTER0));  // pause until it is enabled
    PWM_Timer_Int_StartEx(PWM_Int);
   // ANALOG_INT_StartEx(ADC_ISR);
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Timer_Start();
    //Analog_Timer_Start();
    PWM_Timer_Pulse_Start();
    UART_Start();
        
    char data[20];
  //  PinSelect_Write(0);
    int i = 0;
    for(;; i++)
    {
        /*
        PinSelect_Write(i%6);
        for(int q=0; q< (i%6 +1); q++)
        {
            Red_Write(1);
            Green_Write(1);
            Blue_Write(0);
            CyDelay(500);
            Blue_Write(1);
            CyDelay(500);
        }*/
        
        int Red_Val, Green_Val;
        int Blue_Val = 0;
        if(PulseLength < 4920 && PulseLength > 0) 
        {
            Red_Val = 1;
            Green_Val = 1;
        }
        else
        {
            Red_Val = 0;
            Green_Val = 1;
        }
        

        //Write out the camera feed to the Video Switch board
        //feedNo = 0; //DEBUG WITH THIS FEED
        snprintf(data,35,"DATA  %5d %5d %3d %4d\n    " , PulseLength, low_time, override ,i);
        UART_UartPutString(data);
        if(override-- <=0)
        {
            override = 0;
            Red_Val =1;
            Green_Val=0;
        }
        Red_Write(!Red_Val);  
        Green_Write(!Green_Val);
        Blue_Write(!Blue_Val);
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
        CyDelay(300);

    }
}

/* [] END OF FILE */
