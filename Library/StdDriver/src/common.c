/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "MG51_SDCC.H"

BIT BIT_TMP;
unsigned char __data SFRTEMP;
//unsigned short int __code *u16_addr_apread;
/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
unsigned char Read_APROM_BYTE(const uint16_t __code *u16_addr_apread)
{
    unsigned char rdata;
    rdata = *u16_addr_apread;
    return rdata;
}


/**
 * @brief       Software reset API
 * @param       Run in APROM/LDROM after reset
 *                       - \ref BOOT_APROM: Run in APROM after reset .
 *                       - \ref BOOT_LDROM: Run in LDROM after reset.
 * @return      None
 * @details     None
 */
void Software_Reset(unsigned char u8Bootarea)
{
    SFRTEMP = (0x80|u8Bootarea);
    TA = 0xAA;
    TA = 0x55;
    CHPCON = SFRTEMP;                   //software reset enable
}


void _delay_(void)
{
  unsigned char __data i,j;

    for (j=0;j<20;j++)
    {
       for (i=0;i<99;i++)
       {
          NOP;
       }
    }
}
