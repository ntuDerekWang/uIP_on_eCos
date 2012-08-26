/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
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
 * $Id: platform-conf.h,v 1.1 2010/06/23 10:18:05 joxe Exp $
 */

/**
 * \file
 *         A brief description of what this file is
 * \author
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */
/*
  Usage :#include "cyg/net/uIPv6Stack/uIPv6/platform-conf.h"

*/
#ifndef __PLATFORM_CONF_H__
#define __PLATFORM_CONF_H__

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */
/* Platform TMOTE_SKY */
#define TMOTE_SKY 1

/* CPU target speed in Hz */
#define F_CPU 3900000uL /*2457600uL*/

/* Our clock resolution, this is the same as Unix HZ. */
#define CLOCK_CONF_SECOND 10000UL

#define BAUD2UBR(baud) ((F_CPU/baud))

#define CCIF
#define CLIF

#define CC_CONF_INLINE inline

#define HAVE_STDINT_H
#define MSP430_MEMCPY_WORKAROUND 1
//#include "msp430def.h"


/* Types for clocks and uip_stats */
typedef unsigned short uip_stats_t;
typedef unsigned long clock_time_t;
typedef unsigned long off_t;

/* the low-level radio driver */
#define NETSTACK_CONF_RADIO   uz2400_driver

/* LED ports */
#define LEDS_PxDIR P5DIR
#define LEDS_PxOUT P5OUT
#define LEDS_CONF_RED    0x10
#define LEDS_CONF_GREEN  0x20
#define LEDS_CONF_YELLOW 0x40

/* DCO speed resynchronization for more robust UART, etc. */
#define DCOSYNCH_CONF_ENABLED 1
#define DCOSYNCH_CONF_PERIOD 30

#define ROM_ERASE_UNIT_SIZE  512
#define XMEM_ERASE_UNIT_SIZE (64*1024L)


#define CFS_CONF_OFFSET_TYPE    long


/* Use the first 64k of external flash for node configuration */
#define NODE_ID_XMEM_OFFSET     (0 * XMEM_ERASE_UNIT_SIZE)

/* Use the second 64k of external flash for codeprop. */
#define EEPROMFS_ADDR_CODEPROP  (1 * XMEM_ERASE_UNIT_SIZE)

#define CFS_XMEM_CONF_OFFSET    (2 * XMEM_ERASE_UNIT_SIZE)
#define CFS_XMEM_CONF_SIZE      (1 * XMEM_ERASE_UNIT_SIZE)

#define CFS_RAM_CONF_SIZE 4096

/*
 * SPI bus configuration for the TMote Sky.
 */

/* SPI input/output registers. */
#define SPI_TXBUF U0TXBUF
#define SPI_RXBUF U0RXBUF

                                /* USART0 Tx ready? */
#define SPI_WAITFOREOTx() while ((U0TCTL & TXEPT) == 0)
                                /* USART0 Rx ready? */
#define SPI_WAITFOREORx() while ((IFG1 & URXIFG0) == 0)
                                /* USART0 Tx buffer ready? */
#define SPI_WAITFORTxREADY() while ((IFG1 & UTXIFG0) == 0)

#define SCK            1  /* P3.1 - Output: SPI Serial Clock (SCLK) */
#define MOSI           2  /* P3.2 - Output: SPI Master out - slave in (MOSI) */
#define MISO           3  /* P3.3 - Input:  SPI Master in - slave out (MISO) */

/*
 * SPI bus - M25P80 external flash configuration.
 */

#define FLASH_PWR       3       /* P4.3 Output */
#define FLASH_CS        4       /* P4.4 Output */
#define FLASH_HOLD      7       /* P4.7 Output */

/* Enable/disable flash access to the SPI bus (active low). */

#define SPI_FLASH_ENABLE()  ( P4OUT &= ~BV(FLASH_CS) )
#define SPI_FLASH_DISABLE() ( P4OUT |=  BV(FLASH_CS) )

#define SPI_FLASH_HOLD()                ( P4OUT &= ~BV(FLASH_HOLD) )
#define SPI_FLASH_UNHOLD()              ( P4OUT |=  BV(FLASH_HOLD) )

/*
 * SPI bus - UZ2400 pin configuration.
 */

#define UZ2400_CONF_SYMBOL_LOOP_COUNT 800

/* P1.0 - Input: FIFOP from UZ2400 */
#define UZ2400_FIFOP_PORT(type)   P1##type
#define UZ2400_FIFOP_PIN          0
/* P1.3 - Input: FIFO from UZ2400 */
#define UZ2400_FIFO_PORT(type)     P1##type
#define UZ2400_FIFO_PIN            3
/* P1.4 - Input: CCA from UZ2400 */
#define UZ2400_CCA_PORT(type)      P1##type
#define UZ2400_CCA_PIN             4
/* P4.1 - Input:  SFD from UZ2400 */
#define UZ2400_SFD_PORT(type)      P4##type
#define UZ2400_SFD_PIN             1
/* P4.2 - Output: SPI Chip Select (CS_N) */
#define UZ2400_CSN_PORT(type)      P4##type
#define UZ2400_CSN_PIN             2
/* P4.5 - Output: VREG_EN to UZ2400 */
#define UZ2400_VREG_PORT(type)     P4##type
#define UZ2400_VREG_PIN            5
/* P4.6 - Output: RESET_N to UZ2400 */
#define UZ2400_RESET_PORT(type)    P4##type
#define UZ2400_RESET_PIN           6

#define UZ2400_IRQ_VECTOR PORT1_VECTOR

/* Pin status. */
#define UZ2400_FIFOP_IS_1 (!!(UZ2400_FIFOP_PORT(IN) & BV(UZ2400_FIFOP_PIN)))
#define UZ2400_FIFO_IS_1  (!!(UZ2400_FIFO_PORT(IN) & BV(UZ2400_FIFO_PIN)))
#define UZ2400_CCA_IS_1   (!!(UZ2400_CCA_PORT(IN) & BV(UZ2400_CCA_PIN)))
#define UZ2400_SFD_IS_1   (!!(UZ2400_SFD_PORT(IN) & BV(UZ2400_SFD_PIN)))

/* The UZ2400 reset pin. */
#define SET_RESET_INACTIVE()   (UZ2400_RESET_PORT(OUT) |=  BV(UZ2400_RESET_PIN))
#define SET_RESET_ACTIVE()     (UZ2400_RESET_PORT(OUT) &= ~BV(UZ2400_RESET_PIN))

/* UZ2400 voltage regulator enable pin. */
#define SET_VREG_ACTIVE()       (UZ2400_VREG_PORT(OUT) |=  BV(UZ2400_VREG_PIN))
#define SET_VREG_INACTIVE()     (UZ2400_VREG_PORT(OUT) &= ~BV(UZ2400_VREG_PIN))

/* UZ2400 rising edge trigger for external interrupt 0 (FIFOP). */
#define UZ2400_FIFOP_INT_INIT() do {                  \
    UZ2400_FIFOP_PORT(IES) &= ~BV(UZ2400_FIFOP_PIN);  \
    UZ2400_CLEAR_FIFOP_INT();                         \
  } while(0)

/* FIFOP on external interrupt 0. */
#define UZ2400_ENABLE_FIFOP_INT()  do {UZ2400_FIFOP_PORT(IE) |= BV(UZ2400_FIFOP_PIN);} while(0)
#define UZ2400_DISABLE_FIFOP_INT() do {UZ2400_FIFOP_PORT(IE) &= ~BV(UZ2400_FIFOP_PIN);} while(0)
#define UZ2400_CLEAR_FIFOP_INT()   do {UZ2400_FIFOP_PORT(IFG) &= ~BV(UZ2400_FIFOP_PIN);} while(0)

/*
 * Enables/disables UZ2400 access to the SPI bus (not the bus).
 * (Chip Select)
 */

 /* ENABLE CSn (active low) */
#define UZ2400_SPI_ENABLE()     (UZ2400_CSN_PORT(OUT) &= ~BV(UZ2400_CSN_PIN))
 /* DISABLE CSn (active low) */
#define UZ2400_SPI_DISABLE()    (UZ2400_CSN_PORT(OUT) |=  BV(UZ2400_CSN_PIN))
#define UZ2400_SPI_IS_ENABLED() ((UZ2400_CSN_PORT(OUT) & BV(UZ2400_CSN_PIN)) != BV(UZ2400_CSN_PIN))

#endif /* __PLATFORM_CONF_H__ */
