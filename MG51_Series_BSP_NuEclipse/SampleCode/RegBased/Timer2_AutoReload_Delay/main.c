/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Timer 2 delay with interrupt demo                                                   */
/************************************************************************************************************/
#include "mg51_sdcc.h"

/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
void Timer2_ISR (void) __interrupt (5)
{
    PUSH_SFRS;

    clr_T2CON_TF2;                                //Clear Timer2 Interrupt Flag

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
	MODIFY_HIRC(HIRC_24);;
  
    TIMER2_DIV_128;
    TIMER2_Auto_Reload_Delay_Mode;
  
    RCMP2H = 0x60;
    RCMP2L = 0xFF;

    TL2 = 0x60;
    TH2 =0xFF;

    ENABLE_TIMER2_INTERRUPT;                                    // Enable Timer2 interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_T2CON_TR2;                                    // Timer2 run

    while(1)
    {
      CALL_NOP;
    }

}