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
 * $Id: neighbor-info.c,v 1.17 2010/10/28 08:54:54 joxe Exp $
 */
/**
 * \file
 *         A generic module for management of neighbor information.
 *
 * \author Nicolas Tsiftes <nvt@sics.se>
 */
/*
#include "net/neighbor-info.h"
#include "net/neighbor-attr.h"
*/

#include "cyg/net/uIPv6Stack/uIPv6/neighbor-attr.h"
#include "cyg/net/uIPv6Stack/uIPv6/neighbor-info.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif /* DEBUG */

#define ETX_LIMIT		15
#define ETX_SCALE		100
#define ETX_ALPHA		90
#define ETX_FIRST_GUESS		5

#define NOACK_PACKET_ETX        8
/*---------------------------------------------------------------------------*/
NEIGHBOR_ATTRIBUTE(cyg_uint8, etx, NULL);

static neighbor_info_subscriber_t subscriber_callback;
/*---------------------------------------------------------------------------*/
static void
update_etx(const rimeaddr_t *dest, int packet_etx)
{
/*
  cyg_uint8 *etxp;
  cyg_uint8 recorded_etx, new_etx;

  etxp = (cyg_uint8 *)neighbor_attr_get_data(&etx, dest);
  if(etxp == NULL || *etxp == 0) {
    recorded_etx = ETX2FIX(ETX_FIRST_GUESS);
  } else {
    recorded_etx = *etxp;
  }



  // Update the EWMA of the ETX for the neighbor. 
  packet_etx = ETX2FIX(packet_etx);
  new_etx = ((cyg_uint16)recorded_etx * ETX_ALPHA +
             (cyg_uint16)packet_etx * (ETX_SCALE - ETX_ALPHA)) / ETX_SCALE;
  PRINTF("neighbor-info: ETX changed from %d to %d (packet ETX = %d) %d\n",
         FIX2ETX(recorded_etx), FIX2ETX(new_etx), FIX2ETX(packet_etx),
         dest->u8[7]);
*/



/*
  if(neighbor_attr_has_neighbor(dest)) {
    neighbor_attr_set_data(&etx, dest, &new_etx);
    if(new_etx != recorded_etx && subscriber_callback != NULL) {
           PRINTF("Before subscriber_callback, new_etx = %i\n", new_etx);      
         subscriber_callback(dest, 1, new_etx);
    }
  }

*/

  cyg_uint8 *rssi_ptr;
  cyg_uint8 recorded_rssi ,packet_rssi;

  rssi_ptr = (cyg_uint8 *)neighbor_attr_get_data(&etx, dest);
  if(rssi_ptr == NULL || *rssi_ptr == 0) {
 
  } else {
    recorded_rssi = *rssi_ptr;
  }

 packet_rssi =   packet_etx;
  
  if(neighbor_attr_has_neighbor(dest)) {
    neighbor_attr_set_data(&etx, dest, &packet_rssi);
    if(packet_rssi != recorded_rssi && subscriber_callback != NULL) {
        //   PRINTF("Before subscriber_callback, packet_rssi = %i\n", packet_rssi);      
         subscriber_callback(dest, 1, packet_rssi);
    }
  }


}
/*---------------------------------------------------------------------------*/
static void
add_neighbor(const rimeaddr_t *addr)
{
  switch(neighbor_attr_add_neighbor(addr)) {
  case -1:
    PRINTF("neighbor-info: failed to add a node.\n");
    break;
  case 0:
    PRINTF("neighbor-info: The neighbor is already known\n");
    break;

  default:
/*
    if(subscriber_callback != NULL) {
      subscriber_callback(addr, 1, ETX_FIRST_GUESS);
    }
*/
    break;
  }
}
/*---------------------------------------------------------------------------*/
void
neighbor_info_packet_sent(int status, int numtx)
{
  const rimeaddr_t *dest;
  cyg_uint8 packet_etx;

  dest = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
  if(rimeaddr_cmp(dest, &rimeaddr_null)) {
    return;
  }

  PRINTF("neighbor-info: packet sent to %x.%x, status=%d, numtx=%d\n",
	dest->u8[sizeof(*dest) - 2], dest->u8[sizeof(*dest) - 1],
	status, numtx);

  switch(status) {
  case MAC_TX_OK:
    packet_etx = numtx;
//    add_neighbor(dest);
    break;
  case MAC_TX_COLLISION:
    packet_etx = numtx;
    break;
  case MAC_TX_NOACK:
    packet_etx = NOACK_PACKET_ETX;
  /* error and collissions will not cause high hits ??? */
    break;
  case MAC_TX_ERR:
  default:
    packet_etx = 0; 
    break;
  }

  //if (packet_etx > 0) update_etx(dest, packet_etx);
}
/*---------------------------------------------------------------------------*/
void
neighbor_info_packet_received(cyg_uint8 rssi)
{
  const rimeaddr_t *src;

  src = packetbuf_addr(PACKETBUF_ADDR_SENDER);
  if(rimeaddr_cmp(src, &rimeaddr_null)) { 
    return;
  }

  PRINTF("neighbor-info: packet received from %x.%x\n",
	src->u8[sizeof(*src) - 2], src->u8[sizeof(*src) - 1]);
/*
 if ( NULL != neighbor_attr_get_data(&etx, src)){ 

        if (rssi > 0)   ///// MODIFIED LATER
             update_etx(src, rssi);
     }
*/
/******************** lock the Scheduler ************************/
      cyg_scheduler_lock();
/****************************************************************/
  add_neighbor(src);
  update_etx(src, rssi);
/******************** unlock the Scheduler ************************/
      cyg_scheduler_unlock();
/****************************************************************/
  
}
/*---------------------------------------------------------------------------*/
int
neighbor_info_subscribe(neighbor_info_subscriber_t s)
{
  if(subscriber_callback == NULL) {
    neighbor_attr_register(&etx);
    subscriber_callback = s;
    return 1;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
cyg_uint8
neighbor_info_get_etx(const rimeaddr_t *addr)
{
  cyg_uint8 *etxp;

  etxp = (cyg_uint8 *)neighbor_attr_get_data(&etx, addr);
  return etxp == NULL ? 0 : *etxp;
}
/*---------------------------------------------------------------------------*/
