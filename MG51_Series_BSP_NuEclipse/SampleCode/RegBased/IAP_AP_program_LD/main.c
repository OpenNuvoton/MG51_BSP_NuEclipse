/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP program LDROM demo code
//***********************************************************************************************************
#include "mg51_sdcc.h"


/*---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------*/
#define     DATA_SIZE           1024   
#define     DATA_START_ADDR     0x0000           


void main (void) 
{
    unsigned char i;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Toggle P12 to low to start test ...");

    P12_QUASI_MODE;
    
    for (i=0;i<128;i++)
        IAPDataBuf[i]=i;

    while(P12);

    Erase_LDROM(DATA_START_ADDR,128);
    Erase_Verify_LDROM(DATA_START_ADDR,128);
    Program_LDROM(DATA_START_ADDR,128);
    Program_Verify_LDROM(DATA_START_ADDR,128);
    while(1);
}
//-----------------------------------------------------------------------------------------------------------
