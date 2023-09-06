/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo code                                                  */
//**********************************************************************************************************/

#include "mg51_sdcc.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
float  Bandgap_Voltage,VDD_Voltage;      //please always use "double" mode for this

unsigned int READ_BANDGAP(void);
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    UINT16 ADC_BG_Result;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

/* ADC sampling timing setting for Bandgap*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(ADCF == 0);
/* ADC convert current Bandgap value */
    ADC_BG_Result = ADCRH<<4 ;
    ADC_BG_Result = ADC_BG_Result|(ADCRL&0x0F);
    DISABLE_ADC;              /*Disable ADCEN each time after ADC trig */

/*                  VDD  Now                         READ_BANDGAP() VALUE              */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)      NOW ADC Bandgap convert reuslt         */
      VDD_Voltage = READ_BANDGAP()/ADC_BG_Result*3.072;

/*            Bandgap real voltage                    READ_BANDGAP() VALUE             */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)              4096(12bit ADC)                */
      Bandgap_Voltage = READ_BANDGAP()*3/4/1000;

/*printf result value */
      /*printf result value */
          printf_fast_f ("\n BG Voltage = %f", Bandgap_Voltage);
          printf_tiny (" V");
          printf_fast_f ("\n VDD voltage = %f", VDD_Voltage);
          printf_tiny (" V");

    while(1);

}



