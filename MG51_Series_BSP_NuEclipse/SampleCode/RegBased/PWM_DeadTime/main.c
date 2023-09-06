/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 PWM insert dead time demo code                                                      */
/************************************************************************************************************/
#include "mg51_sdcc.h"

/************************************************************************************************************/
/*    Main function                                                                                         */
/*     PWM4 P0.5 simple output a 2.7KHz 1/4high duty signal                                                 */
/************************************************************************************************************/
void main(void)
{
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (16MHz/8)/(0x7CF+1) = 1KHz (1ms)
  PWM4 high duty  = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty  = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/24000000 = 21.3 us (max value)
-----------------------------------------------------------------------------------------------------------------*/
    P12_QUASI_MODE;
    P11_QUASI_MODE;
    P01_QUASI_MODE;
    P15_QUASI_MODE;

	PWM0_P12_OUTPUT_ENABLE;
    PWM1_P11_OUTPUT_ENABLE;
    PWM4_P01_OUTPUT_ENABLE;
    PWM5_P15_OUTPUT_ENABLE;
  
    PWM_COMPLEMENTARY_MODE;          //Only this mode support deat time function
    PWM_CLOCK_DIV_8;
    PWMPH = 0x07;
    PWMPL = 0xCF;

    PWM0H = 0x03;
    PWM0L = 0xCF;
    ENABLE_SFR_PAGE1;                    // PWM4 and PWM5 duty value need set SFPPAGE 1
    PWM4H = 0x01;
    PWM4L = 0xCF;
    ENABLE_SFR_PAGE0;
    
    PWM01_DEADTIME_ENABLE;
    PWM45_DEADTIME_ENABLE;
    PWM0_DeadZoneEnable(PWM0_CH01,0x100);      //value never over 0x1FF
    
//Please always setting Dead time if needed before PWM run.    
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);    
}
