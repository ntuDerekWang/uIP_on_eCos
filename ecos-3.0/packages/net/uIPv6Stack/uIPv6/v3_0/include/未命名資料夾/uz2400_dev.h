/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: uz2400.h,v 1.13 2010/09/23 08:26:06 nifi Exp $
 */

/**
 * \file
 *         UZ2400 driver header file
 * \author
 *         Adam Dunkels <adam@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */
/*********************
  Usage:    #include "cyg/net/uIPv6Stack/uIPv6/uz2400_dev.h"

#ifndef __UZ2400_H__
#define __UZ2400_H__
/*
#include "contiki.h"
#include "dev/spi.h"///////////////更改
#include "dev/radio.h"
#include "dev/uz2400_const.h"

#include "dev/uz2400_rf_package.h"
#include "dev/uz2400_srf.h"
*/
#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"
#include "cyg/net/uIPv6Stack/uIPv6/radio_dev.h"

int uz2400_init(void);

#define UZ2400_MAX_PACKET_LEN      127

int uz2400_set_channel(int channel);
int uz2400_get_channel(void);

void uz2400_set_pan_addr(unsigned pan,
                                unsigned addr,
                                const cyg_uint8 *ieee_addr);

extern signed char uz2400_last_rssi;
extern cyg_uint8 uz2400_last_correlation;

int uz2400_rssi(void);

extern const struct radio_driver uz2400_driver;

/**
 * \param power Between 1 and 31.
 */
void uz2400_set_txpower(cyg_uint8 power);
int uz2400_get_txpower(void);
#define UZ2400_TXPOWER_MAX  31
#define UZ2400_TXPOWER_MIN   0

/**
 * Interrupt function, called from the simple-uz2400-arch driver.
 *
 */
int uz2400_interrupt(void);

/* XXX hack: these will be made as Chameleon packet attributes */
////////////////////////////extern rtimer_clock_t uz2400_time_of_arrival,      // from uz2400.c
//////////////////////////////////////////////  uz2400_time_of_departure;///改過的地方
extern int uz2400_authority_level_of_sender;

int uz2400_on(void);
int uz2400_off(void);

void uz2400_set_cca_threshold(int value);

/************************************************************************/
/* Additional SPI Macros for the UZ2400 */
/************************************************************************/
/* Send a strobe to the UZ2400 */
#define UZ2400_STROBE(s)                                   \
  do {                                                  \
    UZ2400_SPI_ENABLE();                                \
    SPI_WRITE(s);                                       \
    UZ2400_SPI_DISABLE();                               \
  } while (0)

/* Write to a register in the UZ2400                         */
/* Note: the SPI_WRITE(0) seems to be needed for getting the */
/* write reg working on the Z1 / MSP430X platform            */
#define UZ2400_WRITE_REG(adr,data)                              \
  do {                                                       \
    UZ2400_SPI_ENABLE();                                     \
    SPI_WRITE_FAST(adr);                                     \
    SPI_WRITE_FAST((cyg_uint8)((data) >> 8));                  \
    SPI_WRITE_FAST((cyg_uint8)(data & 0xff));                  \
    SPI_WAITFORTx_ENDED();                                   \
    SPI_WRITE(0);                                            \
    UZ2400_SPI_DISABLE();                                    \
  } while(0)

/* Read a register in the UZ2400 */
#define UZ2400_READ_REG(adr,data)                          \
  do {                                                  \
    UZ2400_SPI_ENABLE();                                \
    SPI_WRITE(adr | 0x40);                              \
    data = (cyg_uint8)SPI_RXBUF;                          \
    SPI_TXBUF = 0;                                      \
    SPI_WAITFOREORx();                                  \
    data = SPI_RXBUF << 8;                              \
    SPI_TXBUF = 0;                                      \
    SPI_WAITFOREORx();                                  \
    data |= SPI_RXBUF;                                  \
    UZ2400_SPI_DISABLE();                               \
  } while(0)

#define UZ2400_READ_FIFO_BYTE(data)                        \
  do {                                                  \
    UZ2400_SPI_ENABLE();                                \
    SPI_WRITE(UZ2400_RXFIFO | 0x40);                    \
    (void)SPI_RXBUF;                                    \
    SPI_READ(data);                                     \
    clock_delay(1);                                     \
    UZ2400_SPI_DISABLE();                               \
  } while(0)

#define UZ2400_READ_FIFO_BUF(buffer,count)                                 \
  do {                                                                  \
    cyg_uint8 i;                                                          \
    UZ2400_SPI_ENABLE();                                                \
    SPI_WRITE(UZ2400_RXFIFO | 0x40);                                    \
    (void)SPI_RXBUF;                                                    \
    for(i = 0; i < (count); i++) {                                      \
      SPI_READ(((cyg_uint8 *)(buffer))[i]);                               \
    }                                                                   \
    clock_delay(1);                                                     \
    UZ2400_SPI_DISABLE();                                               \
  } while(0)

#define UZ2400_WRITE_FIFO_BUF(buffer,count)                                \
  do {                                                                  \
    cyg_uint8 i;                                                          \
    UZ2400_SPI_ENABLE();                                                \
    SPI_WRITE_FAST(UZ2400_TXFIFO);                                           \
    for(i = 0; i < (count); i++) {                                      \
      SPI_WRITE_FAST(((cyg_uint8 *)(buffer))[i]);                              \
    }                                                                   \
    SPI_WAITFORTx_ENDED();                                              \
    UZ2400_SPI_DISABLE();                                               \
  } while(0)

/* Write to RAM in the UZ2400 */
#define UZ2400_WRITE_RAM(buffer,adr,count)                 \
  do {                                                       \
    cyg_uint8 i;                                               \
    UZ2400_SPI_ENABLE();                                     \
    SPI_WRITE_FAST(0x80 | (adr & 0x7f));                     \
    SPI_WRITE_FAST((adr >> 1) & 0xc0);                       \
    for(i = 0; i < (count); i++) {                           \
      SPI_WRITE_FAST(((cyg_uint8*)(buffer))[i]);               \
    }                                                        \
    SPI_WAITFORTx_ENDED();                                   \
    UZ2400_SPI_DISABLE();                                    \
  } while(0)

/* Read from RAM in the UZ2400 */
#define UZ2400_READ_RAM(buffer,adr,count)                    \
  do {                                                       \
    cyg_uint8 i;                                               \
    UZ2400_SPI_ENABLE();                                     \
    SPI_WRITE(0x80 | (adr & 0x7f));                          \
    SPI_WRITE(((adr >> 1) & 0xc0) | 0x20);                   \
    SPI_RXBUF;                                               \
    for(i = 0; i < (count); i++) {                           \
      SPI_READ(((cyg_uint8*)(buffer))[i]);                     \
    }                                                        \
    UZ2400_SPI_DISABLE();                                    \
  } while(0)

/* Read status of the UZ2400 */
#define UZ2400_GET_STATUS(s)                       \
  do {                                          \
    UZ2400_SPI_ENABLE();                        \
    SPI_WRITE(UZ2400_SNOP);                     \
    s = SPI_RXBUF;                              \
    UZ2400_SPI_DISABLE();                       \
  } while (0)

#endif /* __UZ2400_H__ */
