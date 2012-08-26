/*
 * Copyright (c) 2007, Swedish Institute of Computer Science
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
 * @(#)$Id: uz2400.c,v 1.60 2010/09/23 08:26:06 nifi Exp $
 */
/*
 * This code is almost device independent and should be easy to port.
 */

#include <string.h>
/*
#include "contiki.h"

#if defined(__AVR__)
#include <avr/io.h>
#elif defined(__MSP430__)
#include <io.h>
#endif

#include "dev/leds.h"
#include "dev/spi.h"
#include "dev/uz2400.h"
#include "dev/uz2400_const.h"

#include "net/packetbuf.h"
#include "net/rime/rimestats.h"
#include "net/netstack.h"

#include "sys/timetable.h"/////////////看似不用
*/
//////////////////////放著,可能會出問題

 
#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"
#include "cyg/net/uIPv6Stack/uIPv6/uz2400_dev.h"
#include "cyg/net/uIPv6Stack/uIPv6/packetbuf.h"
#include "cyg/net/uIPv6Stack/rime/rimestats.h"
#include "cyg/net/uIPv6Stack/uIPv6/netstack.h" 
//==========================
#include <cyg/DW_config.h> 
#include"cyg/io/rf.h"
//==========================
#define WITH_SEND_CCA 1

#define FOOTER_LEN 2

#ifndef UZ2400_CONF_CHECKSUM
#define UZ2400_CONF_CHECKSUM 0
#endif /* UZ2400_CONF_CHECKSUM */

#ifndef UZ2400_CONF_AUTOACK
#define UZ2400_CONF_AUTOACK 0
#endif /* UZ2400_CONF_AUTOACK */

#if UZ2400_CONF_CHECKSUM
#include "lib/crc16.h"
#define CHECKSUM_LEN 2
#else
#define CHECKSUM_LEN 0
#endif /* UZ2400_CONF_CHECKSUM */

#define AUX_LEN (CHECKSUM_LEN + FOOTER_LEN)


#define FOOTER1_CRC_OK      0x80
#define FOOTER1_CORRELATION 0x7f

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) do {} while (0)
#endif

#define DEBUG_LEDS DEBUG
#undef LEDS_ON
#undef LEDS_OFF
#if DEBUG_LEDS
#define LEDS_ON(x) leds_on(x)
#define LEDS_OFF(x) leds_off(x)
#else
#define LEDS_ON(x)
#define LEDS_OFF(x)
#endif

void uz2400_arch_init(void);

/* XXX hack: these will be made as Chameleon packet attributes */
//rtimer_clock_t uz2400_time_of_arrival, uz2400_time_of_departure;

int uz2400_authority_level_of_sender;

int uz2400_packets_seen, uz2400_packets_read;

static cyg_uint8 volatile pending;

/***在cc2420用的到,在uz2400用不到***/
/*
#define BUSYWAIT_UNTIL(cond, max_time)                                  \
  do {                                                                  \
    rtimer_clock_t t0;                                                  \
    t0 = RTIMER_NOW();                                                  \
    while(!(cond) && RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + (max_time)));   \
  } while(0)
*/
/*---------------------------------------------------------------------------*/
//PROCESS(uz2400_process, "UZ2400 driver");
/*---------------------------------------------------------------------------*/

int uz2400_on(void);
int uz2400_off(void);

static int uz2400_read(void *buf, unsigned short bufsize);

static int uz2400_prepare(const void *data, unsigned short len);
static int uz2400_transmit(unsigned short len);
static int uz2400_send(const void *data, unsigned short len);

static int uz2400_receiving_packet(void);
static int pending_packet(void);
static int uz2400_cca(void);
static int detected_energy(void);

signed char uz2400_last_rssi;
cyg_uint8 uz2400_last_correlation;

/*
struct radio_driver {

  int (* init)(void);
  
   
  int (* prepare)(const void *payload, unsigned short payload_len);

   
  int (* transmit)(unsigned short transmit_len);

   
  int (* send)(const void *payload, unsigned short payload_len);

  
  int (* read)(void *buf, unsigned short buf_len);

   
  int (* channel_clear)(void);

  
  int (* receiving_packet)(void);

   
  int (* pending_packet)(void);

  
  int (* on)(void);

   
  int (* off)(void);
};

*/



const struct radio_driver uz2400_driver =
  {
    uz2400_init,
    uz2400_prepare,
    uz2400_transmit,
    uz2400_send,
    uz2400_read,
    /* uz2400_set_channel, */
    /* detected_energy, */
    uz2400_cca,
    uz2400_receiving_packet,
    pending_packet,
    uz2400_on,
    uz2400_off,
  };

static cyg_uint8 receive_on;

static int channel;

/*---------------------------------------------------------------------------*/
/*////////////////好像用不到
static void
getrxdata(void *buf, int len)
{
  UZ2400_READ_FIFO_BUF(buf, len);
}
*/
/*////////////////好像用不到
static void
getrxbyte(cyg_uint8 *byte)
{
  UZ2400_READ_FIFO_BYTE(*byte);
}
*/
/*---------------------------------------------------------------------------*/
/*////////////////好像用不到
static void
strobe(enum uz2400_register regname)
{
  UZ2400_STROBE(regname);
}
*/

/*---------------------------------------------------------------------------*/
static unsigned int////////放著,可能會出問題
status(void)
{
/* 
  cyg_uint8 status;
  UZ2400_GET_STATUS(status);
  return status;
*/return 0;
}
/*---------------------------------------------------------------------------*/
static cyg_uint8 locked, lock_on, lock_off;

static void
on(void)
{                           
}
static void
off(void)
{
}
/*---------------------------------------------------------------------------*/
#define GET_LOCK() locked++
static void RELEASE_LOCK(void) {
  if(locked == 1) {
    if(lock_on) {
      on();
      lock_on = 0;
    }
    if(lock_off) {
   /* 
      LEDS_OFF(LEDS_BLUE);
   */  
      off();
      lock_off = 0;
    }
  }
  locked--;
}
/*---------------------------------------------------------------------------*/
/*
static unsigned////////放著,可能會出問題
getreg(enum uz2400_register regname)
{
  unsigned reg;
  UZ2400_READ_REG(regname, reg);
  return reg;
}
*/
/*---------------------------------------------------------------------------*/
/*
static void
setreg(enum uz2400_register regname, unsigned value)
{
  UZ2400_WRITE_REG(regname, value);
}
*/
/*---------------------------------------------------------------------------*/
static void
set_txpower(cyg_uint8 power)
{   
  // now stub
/*
  UzSetTxPower(0);
*/
uz_set_tx_power(power);  
  }
/*---------------------------------------------------------------------------*/
#define AUTOACK (1 << 4)
#define ADR_DECODE (1 << 11)
#define RXFIFO_PROTECTION (1 << 9)
#define CORR_THR(n) (((n) & 0x1f) << 6)
#define FIFOP_THR(n) ((n) & 0x7f)
#define RXBPF_LOCUR (1 << 13);
/*---------------------------------------------------------------------------*/
int
inline uz2400_init(void)
{
/************************原本育正的 code******************
  init_rf_pin();
  InitSPI();
  UzInit();
  UzEnablePA();
  UzSetTxPower(15);
  UzSetChannel(26);
  UzRxNormalMode();

  uz2400_set_pan_addr(0xffff, 0x0000, NULL);
  uz2400_set_channel(26);
  
  UzRxFlush();
***********************************************************/

/*     
    SetupIO();
    SetupIsr();///////記得把 interrupt_create放進來
    SetupRfSpi(); 

 //   uz_rx_normal_mode();
    uz_init(); 
    uz_enable_pa(PA500M); 
    uz_set_tx_power(15);
    uz_set_channel(26);
   
    uz2400_set_pan_addr(0xffff, 0x0000, NULL);
    uz_rx_normal_mode();
	
    uz_rx_flush();
**********************************************/
        uz_init();
	
	uz_enable_ext_wakeup();
      
	uz_set_channel(26);
//	uz_set_panId(0x1234);//////////////////////////////////
//	uz_set_nwk_addr(0x5678);/////////////////////////////
         uz2400_set_pan_addr(0xffff, 0x0000, NULL);
//	init_package(0x1234,0x5678);
//	set_tx_dst_panid(0xffff);
//	set_tx_dst_nwk_addr(0xffff);
	uz_set_tx_power(0);
        uz_rx_normal_mode();
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
uz2400_transmit(unsigned short payload_len)
{
 
  GET_LOCK();
//  printf("Before uz2400_transmit    !\n"); 
  int ret = UzTransmit(payload_len);////////modified for contiki mac layer
 // printf("After uz2400_transmit    !\n");
  PRINTF("uz2400_transmit    !\n"); 
  RELEASE_LOCK();

 
  return ret;
}
/*---------------------------------------------------------------------------*/
static int
uz2400_prepare(const void *payload, unsigned short payload_len)
{
  GET_LOCK();

  PRINTF("uz2400: sending %d bytes\n", payload_len);
  UzPrepare(payload, payload_len);

  RELEASE_LOCK();
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
uz2400_send(const void *payload, unsigned short payload_len)
{
  int ret = uz_tx((UINT8 *)payload, payload_len);
  return ret;
}
/*---------------------------------------------------------------------------*/
int
uz2400_off(void)
{
  /* Don't do anything if we are already turned off. */
  if(receive_on == 0) {
    return 1;
  }

  /* If we are called when the driver is locked, we indicate that the
     radio should be turned off when the lock is unlocked. */
  if(locked) {
    /*    printf("Off when locked (%d)\n", locked);*/
/*   
    LEDS_ON(LEDS_GREEN + LEDS_BLUE);
*/
    lock_off = 1;
    return 1;
  }

  GET_LOCK();
  /* If we are currently receiving a packet (indicated by SFD == 1),
     we don't actually switch the radio off now, but signal that the
     driver should switch off the radio once the packet has been
     received and processed, by setting the 'lock_off' variable. */
/*	 
  if(status() & BV(UZ2400_TX_ACTIVE)) {
    lock_off = 1;
  } else {
    off();
  }
*/  
  RELEASE_LOCK();
  return 1;
}
/*---------------------------------------------------------------------------*/
int
uz2400_on(void)
{
  if(receive_on) {
    return 1;
  }
  if(locked) {
/*
    LEDS_ON(LEDS_GREEN + LEDS_RED);
*/
    lock_on = 1;
    return 1;
  }

  GET_LOCK();
  on();  //空的
  RELEASE_LOCK();
  return 1;
}
/*---------------------------------------------------------------------------*/
int
uz2400_get_channel(void)
{
  return channel;
}
/*---------------------------------------------------------------------------*/
int
uz2400_set_channel(int c)
{
	uz_set_channel(c);
	return 1;
}
/*---------------------------------------------------------------------------*/
void
uz2400_set_pan_addr(unsigned pan,
                    unsigned addr,
                    const cyg_uint8 *ieee_addr)
{
    cyg_uint16 f = 0;
  
    GET_LOCK();
/*  
  UzSetPanId(pan);
*/  uz_set_panId(pan);

/* 
  UzSetNwkAddr(addr);  
*/  uz_set_nwk_addr(addr);

  if(ieee_addr != NULL) {
       cyg_uint8 addr[8];
    /* LSB first, MSB last for 802.15.4 addresses in UZ2400 */
      for (f = 0; f < 8; f++) {
          addr[7-f] = ieee_addr[f];
        }
/*	
      UzSetMacAddress(addr);
*/    uz_set_mac_address(addr);  
    }
  
  RELEASE_LOCK();
}
/*---------------------------------------------------------------------------*/
/*
 * Interrupt leaves frame intact in FIFO.
 */
#if UZ2400_TIMETABLE_PROFILING
#define uz2400_timetable_size 16
TIMETABLE(uz2400_timetable);
TIMETABLE_AGGREGATE(aggregate_time, 10);
#endif /* UZ2400_TIMETABLE_PROFILING */
/*
int
uz2400_interrupt(void)
{
  process_poll(&uz2400_process);

  pending++;
  uz2400_packets_seen++;
  return 1;
}
*/
/*---------------------------------------------------------------------------*/

volatile static  cyg_uint8 blink; 
void alarm_func(cyg_handle_t alarm_handle, cyg_addrword_t data)
{
   // coming=1;printf("Alarm!\n");
   cyg_uint32 RLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 9, OUT_50MHZ , OUT_PUSHPULL     );
   blink=~blink;
   CYGHWR_HAL_STM32_GPIO_OUT(RLedPinspec,blink);  
} 
/*--------------------------------------------------------------------------*/

extern inline void check_rpl_timer_timeout(void);
extern void  check_timer_expired(void);

/*------------------------------------------------------------------------*/
 


/*************************************************************************/
void uz2400_process(void)
{
  int len;
   

  PRINTF("uz2400_process: started\n\r");
  cyg_addrword_t data;
   
  MyeCosAlram_t MyAlarmtest;
 // MyeCosAlarm(&MyAlarmtest,500,0,alarm_func);

/*
  static cyg_uint32 RLedPinspec; 
  RLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 9, OUT_50MHZ , OUT_PUSHPULL     );
    
  
              blink=~blink;
              CYGHWR_HAL_STM32_GPIO_OUT(RLedPinspec,blink);  
*/
  
cyg_thread_delay(20); 
  while(1) {
   // cyg_thread_delay(1);   
  
 //   check_timer_expired( );///////////////////////////////////
 
 //    check_rpl_timer_timeout();
 
   if(is_rf_incoming()){ 
     //   PRINTF("uz2400_process: calling receiver callback\n");
        
        packetbuf_clear();
     //   cyg_thread_delay(1);   
        len = uz2400_read(packetbuf_dataptr(), PACKETBUF_SIZE);
     //   cyg_thread_delay(1);   
        uz_rx_flush();
         
        
        cyg_uint8 tmp = uz_read_rssi();  
        printf("uz_read_rssi = %i\n", tmp);


     //  if ( tmp<100) ////////////////         
/* 
        if ( tmp<80)    
            continue;
*/   
        if(len > 0) {
              packetbuf_set_datalen(len);
 
               NETSTACK_RDC.input(tmp);
            //   cyg_thread_delay(10);   
          }
         
        // IntStatus.Rx =0; 
        // cyg_thread_delay(10);   




    }
	check_timer_expired( );///////////////////////////////////
 
     check_rpl_timer_timeout();
         
  }







}
/*---------------------------------------------------------------------------*/
static int
uz2400_read(void *buf, unsigned short bufsize)
{
  cyg_uint8 len;
  
  len = uz_rx(buf);
  
  if(len > UZ2400_MAX_PACKET_LEN) {
    /* Oops, we must be out of sync. */
    return 0;
  }
  
  if(len <= AUX_LEN) {
    return 0;
  }

  if(len - AUX_LEN > bufsize) {
    return 0;
  }
  
  if(len < AUX_LEN) {
    return 0;
  }

  // still bug here, check the datasheet
  uz2400_last_rssi = buf+(len-1);
  uz2400_last_correlation = buf+(len-2); // LQI
  
  if(len < AUX_LEN) {
    return 0;
  }

  return len - AUX_LEN;
}
/*---------------------------------------------------------------------------*/
void
uz2400_set_txpower(cyg_uint8 power)
{
  GET_LOCK();
/*  
   UzSetTxPower(power);
*/ uz_set_tx_power(power); 
  RELEASE_LOCK();
}
/*---------------------------------------------------------------------------*/
int
uz2400_get_txpower(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
/*
int
uz2400_rssi(void)
{
  int rssi;
  int radio_was_off = 0;

  if(!receive_on) {
    radio_was_off = 1;
    uz2400_on();
  }
  while(!(status() & BV(UZ2400_RSSI_VALID))) {
       printf("uz2400_rssi: RSSI not valid.\n"); 
  }

  rssi = (int)((signed char)getreg(UZ2400_RSSI));

  if(radio_was_off) {
    uz2400_off();
  }
  return rssi;
}
*/
/*---------------------------------------------------------------------------*/
int
uz2400_cca_valid(void)
{
  int valid;
  if(locked) {
    return 1;
  }
  GET_LOCK();
/*  
  valid = !!(status() & BV(UZ2400_RSSI_VALID));
*/  
  RELEASE_LOCK();
  return valid;
}
/*---------------------------------------------------------------------------*/
static int
uz2400_cca(void)
{
	return 1;
}
/*---------------------------------------------------------------------------*/
int
uz2400_receiving_packet(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
pending_packet(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
void
uz2400_set_cca_threshold(int value)
{
  cyg_uint16 shifted = value << 8;
  GET_LOCK();
/* 
  setreg(UZ2400_RSSI, shifted);
*/  
  RELEASE_LOCK();
}
/*---------------------------------------------------------------------------*/
