/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "mg51_sdcc.h"


/***********************************************************************************************************/
/*  File Function: MS51 ADC simple convert demo code                                                        */
/***********************************************************************************************************/

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/

UINT16  ADCdataAIN;

void main (void) 
{
    P12_PUSHPULL_MODE;
/* Initial UART0 for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
  
    ENABLE_ADC_AIN4;
  /* ADC Sampling time setting*/
    ADC_ConvertTime(ADC_ADCDIV2,ADC_ADCAQT5);

    while(1)
    {
      Timer0_Delay(24000000,500,1000);
      ENABLE_ADC;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(!(ADCCON0&SET_BIT7));        // Wait ADC flag
      ADCdataAIN = ADCRH<<4;
      ADCdataAIN |= ADCRL&0x0F;
      DISABLE_ADC;
      printf ("\n ADC result = 0x%x", ADCdataAIN);
      P12 ^= 1;
    }
}


