/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "mg51_sdcc.h"

//***********************************************************************************************************
//  File Function: MS51 ADC trig by GPIO demo
//***********************************************************************************************************

BIT  adcintflag;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) __interrupt (11)
{
	PUSH_SFRS;
  
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    adcintflag=1;

    POP_SFRS;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    UINT16 ADCResult12bit;

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

/*---------------------------------------------------------------
  ADC port trig initial setting toggle P0.4 to start ADC 
----------------------------------------------------------------*/
    ENABLE_ADC_AIN0;                              // Enable AIN0 P1.7 as ADC pin
    P04_QUASI_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                     // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    ENABLE_ADC_INTERRUPT;                         // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
/* Trig P12 falling edge to start adc, no need set ADCS bit   */
    while(1)                                      // Wait ADC interrupt
    {
      if (adcintflag)
      {
            ADCResult12bit = ADCRH<<4;
            ADCResult12bit|= ADCRL&0x0F;
            printf ("\n Value = 0x%x",ADCResult12bit);
            adcintflag =0;
      }
      Timer0_Delay(24000000,500,1000);
    }


}
