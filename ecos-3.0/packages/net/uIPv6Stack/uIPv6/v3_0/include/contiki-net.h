/*
 * Copyright (c) 2005, Swedish Institute of Computer Science.
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: contiki-net.h,v 1.8 2010/03/15 16:54:35 nifi Exp $
 */

/***************
Usage:#include "cyg/net/uIPv6Stack/uIPv6/contiki-net.h"
***************/



#ifndef __CONTIKI_NET_H__
#define __CONTIKI_NET_H__

#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"

#include "cyg/net/uIPv6Stack/uIPv6/tcpip.h"
#include "cyg/net/uIPv6Stack/uIPv6/uip.h"
//#include "net/uip-fw.h"
//#include "net/uip-fw-drv.h"
//#include "net/uip_arp.h"
//#include "net/uiplib.h"
#include "cyg/net/uIPv6Stack/uIPv6/uip-udp-packet.h"

#if UIP_CONF_IPV6
#include "cyg/net/uIPv6Stack/uIPv6/uip-icmp6.h"
#include "cyg/net/uIPv6Stack/uIPv6/uip-ds6.h"
#endif /* UIP_CONF_IPV6 */

//#include "net/resolv.h"

#include "cyg/net/uIPv6Stack/uIPv6/psock.h"
/*
#include "cyg/net/uIPv6Stack/uIPv6/rime.h"
*/
#include "cyg/net/uIPv6Stack/rime/rimeaddr.h"
#include "cyg/net/uIPv6Stack/uIPv6/queuebuf.h"


#include "cyg/net/uIPv6Stack/uIPv6/netstack.h"

#endif /* __CONTIKI_NET_H__ */
