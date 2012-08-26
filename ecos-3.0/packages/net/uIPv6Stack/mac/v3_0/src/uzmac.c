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
 * This file is part of the Contiki operating system.
 *
 * $Id: uzmac.c,v 1.41 2010/11/02 11:00:08 adamdunkels Exp $
 */

/**
 * \file
 *         The Contiki power-saving MAC protocol (ContikiMAC)
 * \author
 *         Adam Dunkels <adam@sics.se>
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */ 
/*
#include "net/netstack.h"
            //#include "dev/leds.h"
#include "dev/radio.h"
            //#include "dev/watchdog.h"
#include "lib/random.h"
#include "net/mac/uzmac.h"
#include "net/rime.h"
           //#include "sys/compower.h"
           //#include "sys/pt.h"
           //#include "sys/rtimer.h"
*/
/*#include "cooja-debug.h"*/
#include <cyg/kernel/kapi.h>   
#include "cyg/net/uIPv6Stack/uIPv6/netstack.h"
#include "cyg/net/uIPv6Stack/uIPv6/radio_dev.h"
#include "cyg/net/uIPv6Stack/uIPv6/random_lib.h"
#include "cyg/net/uIPv6Stack/mac/uzmac.h"   
#include "cyg/net/uIPv6Stack/rime/rimeaddr.h"

//===
 #include "cyg/net/uIPv6Stack/uIPv6/packetbuf.h"
//===

/*
#include "contiki-conf.h"
*/
#include "cyg/net/uIPv6Stack/uIPv6/contiki-conf.h"


#ifdef EXPERIMENT_SETUP
#include "experiment-setup.h"
#endif

#include <string.h>

#ifndef WITH_UZMAC_HEADER
#define WITH_UZMAC_HEADER       1
#endif

/* The maximum number of announcements in a single announcement
   message - may need to be increased in the future. */

#if WITH_UZMAC_HEADER
#define UZMAC_ID 0x00

struct hdr {
  cyg_uint8 id;
  cyg_uint8 len;
};
#endif /* WITH_UZMAC_HEADER */

#define MAX_PHASE_STROBE_TIME              RTIMER_ARCH_SECOND / 20

#define SHORTEST_PACKET_SIZE               43

#define ACK_LEN 3

#include <stdio.h>

static volatile cyg_uint8 uzmac_is_on = 0;

static volatile unsigned char we_are_sending = 0;
static volatile unsigned char radio_is_on = 0;

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINTDEBUG(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#define PRINTDEBUG(...)
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

#ifndef MIN
#define MIN(a, b) ((a) < (b)? (a) : (b))
#endif /* MIN */

struct seqno {
  rimeaddr_t sender;
  cyg_uint8 seqno;
};

#define MAX_SEQNOS 8
static struct seqno received_seqnos[MAX_SEQNOS];

/*---------------------------------------------------------------------------*/
static void
on(void)
{
    NETSTACK_RADIO.on();
}
/*---------------------------------------------------------------------------*/
static void
off(void)
{
    NETSTACK_RADIO.off();
}
/*---------------------------------------------------------------------------*/
static int
send_packet(mac_callback_t mac_callback, void *mac_callback_ptr)
{
/* 
 rtimer_clock_t t0;
  rtimer_clock_t t;
  rtimer_clock_t encounter_time = 0, last_transmission_time = 0;
*/  
  cyg_uint8 first_transmission = 1;
  int strobes;
  cyg_uint8 got_strobe_ack = 0;
  int hdrlen, len;
  cyg_uint8 is_broadcast = 0;
  cyg_uint8 is_reliable = 0;
  cyg_uint8 is_known_receiver = 0;
  cyg_uint8 collisions;
  int transmit_len;
  int i;
  int ret;
#if WITH_UZMAC_HEADER
  struct hdr *chdr;
#endif /* WITH_UZMAC_HEADER */

  if(packetbuf_totlen() == 0) {
        PRINTF("uzmac: send_packet data len 0\n");
        return MAC_TX_ERR_FATAL;
  }

  
  packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &rimeaddr_node_addr);
  if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER), &rimeaddr_null)) {
        is_broadcast = 1;
        PRINTDEBUG("uzmac: send broadcast\n");

  } else {
#if UIP_CONF_IPV6
    PRINTDEBUG("uzmac: send unicast to %02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[1],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[2],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[3],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[4],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[5],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[6],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[7]);
#else /* UIP_CONF_IPV6 */
    PRINTDEBUG("uzmac: send unicast to %u.%u\n",
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[1]);
#endif /* UIP_CONF_IPV6 */
  }
    is_reliable = packetbuf_attr(PACKETBUF_ATTR_RELIABLE) ||
    packetbuf_attr(PACKETBUF_ATTR_ERELIABLE);
  
    packetbuf_set_attr(PACKETBUF_ATTR_MAC_ACK, 1);

#if WITH_UZMAC_HEADER
  hdrlen = packetbuf_totlen(); 
  if(packetbuf_hdralloc(sizeof(struct hdr)) == 0) {
    /* Failed to allocate space for uzmac header */
    PRINTF("uzmac: send failed, too large header\n");
    return MAC_TX_ERR_FATAL;
  }
  
  chdr = packetbuf_hdrptr();
  chdr->id = UZMAC_ID;
  chdr->len = hdrlen;

  /* Create the MAC header for the data packet. */

/******************** lock the Scheduler ************************/
//      cyg_scheduler_lock();
/****************************************************************/

  hdrlen = NETSTACK_FRAMER.create();
/******************** unlock the Scheduler ************************/
 //       cyg_scheduler_unlock();
/****************************************************************/
  if(hdrlen == 0) {
    /* Failed to send */
    PRINTF("uzmac: send failed, too large header\n");
    packetbuf_hdr_remove(sizeof(struct hdr));
    return MAC_TX_ERR_FATAL;
  }   
  hdrlen += sizeof(struct hdr);
#else /* WITH_UZMAC_HEADER */
  /* Create the MAC header for the data packet. */

/******************** lock the Scheduler ************************/
//      cyg_scheduler_lock();
/****************************************************************/

  hdrlen = NETSTACK_FRAMER.create();
/******************** unlock the Scheduler ************************/
//        cyg_scheduler_unlock();
/****************************************************************/
  if(hdrlen == 0) {
    /* Failed to send */
    PRINTF("uzmac: send failed, too large header\n");
    return MAC_TX_ERR_FATAL;
  }
#endif /* WITH_UZMAC_HEADER */

  /* Make sure that the packet is longer or equal to the shortest
     packet length. */
  transmit_len = packetbuf_totlen();
  
  if(transmit_len < SHORTEST_PACKET_SIZE) {
#if 0
    /* Pad with zeroes */
    cyg_uint8 *ptr;
    ptr = packetbuf_dataptr();
    memset(ptr + packetbuf_datalen(), 0, SHORTEST_PACKET_SIZE - packetbuf_totlen());
#endif

    PRINTF("uzmac: shorter than shortest (%d)\n", packetbuf_totlen());
    //transmit_len = SHORTEST_PACKET_SIZE;
  }


  packetbuf_compact();

  NETSTACK_RADIO.prepare(packetbuf_hdrptr(), transmit_len);
 // printf("Hello, uzmac!\n");  
  return NETSTACK_RADIO.transmit(transmit_len);
  /* Remove the MAC-layer header since it will be recreated next time around. */
  packetbuf_hdr_remove(hdrlen);
 
}
/*---------------------------------------------------------------------------*/
static void
qsend_packet(mac_callback_t sent, void *ptr)
{
 /******************** lock the Scheduler ************************/
//      cyg_scheduler_lock();
/****************************************************************/
   int ret = send_packet(sent, ptr);
//   printf("End of send_packet\n");
   if(ret != MAC_TX_DEFERRED) {
    //    printf("uzmac qsend_packet %p\n", ptr);
    mac_call_sent_callback(sent, ptr, ret, 1);
   }
/******************** unlock the Scheduler ************************/
//        cyg_scheduler_unlock();
/****************************************************************/
 

}
/*---------------------------------------------------------------------------*/
static inline void
input_packet(cyg_uint8 rssi)
{
  /* We have received the packet, so we can go back to being
     asleep. */
  off();

  /*  printf("cycle_start 0x%02x 0x%02x\n", cycle_start, cycle_start % CYCLE_TIME);*/
  
  
  if(packetbuf_totlen() > 0 && NETSTACK_FRAMER.parse()) {

#if WITH_UZMAC_HEADER
    struct hdr *chdr;
    chdr = packetbuf_dataptr();
    if(chdr->id != UZMAC_ID) {
      PRINTF("uzmac: failed to parse hdr (%u)\n", packetbuf_totlen());
      return;
    }
    packetbuf_hdrreduce(sizeof(struct hdr));
    packetbuf_set_datalen(chdr->len);
#endif /* WITH_UZMAC_HEADER */

    if(packetbuf_datalen() > 0 &&
       packetbuf_totlen() > 0 &&
       (rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                     &rimeaddr_node_addr) ||
        rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                     &rimeaddr_null))) {
      /* This is a regular packet that is destined to us or to the
         broadcast address. */

      /* Check for duplicate packet by comparing the sequence number
         of the incoming packet with the last few ones we saw. */
      /*{
        int i;
        for(i = 0; i < MAX_SEQNOS; ++i) {
          if(packetbuf_attr(PACKETBUF_ATTR_PACKET_ID) == received_seqnos[i].seqno &&
             rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_SENDER),
                          &received_seqnos[i].sender)) {
            // Drop the packet.
            //        printf("Drop duplicate UZMAC layer packet\n");
            return;
          }
        }
        for(i = MAX_SEQNOS - 1; i > 0; --i) {
          memcpy(&received_seqnos[i], &received_seqnos[i - 1],
                 sizeof(struct seqno));
        }
        received_seqnos[0].seqno = packetbuf_attr(PACKETBUF_ATTR_PACKET_ID);
        rimeaddr_copy(&received_seqnos[0].sender,
                      packetbuf_addr(PACKETBUF_ADDR_SENDER));
      }*/

      PRINTDEBUG("uzmac: data (%u)\n", packetbuf_datalen());
      NETSTACK_MAC.input(rssi);
      return;
    } else {
      PRINTDEBUG("uzmac: data not for us\n");
    }
  } else {
    PRINTF("uzmac: failed to parse (%u)\n", packetbuf_totlen());
  }
}
/*---------------------------------------------------------------------------*/
static void
init(void)
{
}
/*---------------------------------------------------------------------------*/
static int
turn_on(void)
{
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
turn_off(int keep_radio_on)
{
  return 1;
}
/*---------------------------------------------------------------------------*/
static  cyg_tick_count_t
channel_check_interval(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct rdc_driver uzmac_driver = {
  "UZMAC",
  init,
  qsend_packet,
  input_packet,
  turn_on,
  turn_off,
  channel_check_interval,
};
/*---------------------------------------------------------------------------*/
/*
struct rdc_driver {
  char *name;

  //Initialize the RDC driver  
  void (* init)(void);

  //Send a packet from the Rime buffer  
  void (* send)(mac_callback_t sent_callback, void *ptr);

  // Callback for getting notified of incoming packet.  
  void (* input)(void);

  // Turn the MAC layer on. 
  int (* on)(void);

  //Turn the MAC layer off. 
  int (* off)(int keep_radio_on);

  // Returns the channel check interval, expressed in clock_time_t ticks. 
  unsigned short (* channel_check_interval)(void);
};
*/

