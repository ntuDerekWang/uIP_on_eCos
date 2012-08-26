/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
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
 *
 * $Id: tcpip.c,v 1.30 2010/10/29 05:36:07 adamdunkels Exp $
 */
/**
 * \file
 *         Code for tunnelling uIP packets over the Rime mesh routing module
 *
 * \author  Adam Dunkels <adam@sics.se>\author
 * \author  Mathilde Durvy <mdurvy@cisco.com> (IPv6 related code)
 * \author  Julien Abeille <jabeille@cisco.com> (IPv6 related code)
 */
 
 /**     tcpip.c       **/
 
/*********待處理********/
// etimer_expired     etimer_restart   未處理

/*********好像可以不用************/
//#include "contiki-net.h"
#include "cyg/net/uIPv6Stack/uIPv6/tcpip.h"


//#include "net/uip-split.h"
//#include "net/uip-packetqueue.h"

//=========
#include "cyg/infra/cyg_type.h"
#include <cyg/kernel/kapi.h>
#include <cyg/DW_config.h> 
//=======

#include <string.h>

#if UIP_CONF_IPV6
#include "cyg/net/uIPv6Stack/uIPv6/uip-nd6.h"
#include "cyg/net/uIPv6Stack/uIPv6/uip-ds6.h"
#endif

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) cyg_scheduler_lock();printf(__VA_ARGS__);cyg_scheduler_unlock()
#define PRINT6ADDR(addr) PRINTF(" %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x ", ((cyg_uint8 *)addr)[0], ((cyg_uint8 *)addr)[1], ((cyg_uint8 *)addr)[2], ((cyg_uint8 *)addr)[3], ((cyg_uint8 *)addr)[4], ((cyg_uint8 *)addr)[5], ((cyg_uint8 *)addr)[6], ((cyg_uint8 *)addr)[7], ((cyg_uint8 *)addr)[8], ((cyg_uint8 *)addr)[9], ((cyg_uint8 *)addr)[10], ((cyg_uint8 *)addr)[11], ((cyg_uint8 *)addr)[12], ((cyg_uint8 *)addr)[13], ((cyg_uint8 *)addr)[14], ((cyg_uint8 *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF(" %02x:%02x:%02x:%02x:%02x:%02x ",lladdr->addr[0], lladdr->addr[1], lladdr->addr[2], lladdr->addr[3],lladdr->addr[4], lladdr->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#endif

#if UIP_LOGGING
#include <stdio.h>
void uip_log(char *msg);
#define UIP_LOG(m) uip_log(m)
#else
#define UIP_LOG(m)
#endif

#define UIP_ICMP_BUF ((struct uip_icmp_hdr *)&uip_buf[UIP_LLIPH_LEN + uip_ext_len])
#define UIP_IP_BUF ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UIP_TCP_BUF ((struct uip_tcpip_hdr *)&uip_buf[UIP_LLH_LEN])

#ifdef UIP_FALLBACK_INTERFACE
extern struct uip_fallback_interface UIP_FALLBACK_INTERFACE;
#endif
#if UIP_CONF_IPV6_RPL
void rpl_init(void);
#endif
///////process_event_t tcpip_event; 改過的地方
/********************* global variables ***********/
extern cyg_handle_t mbox_into_tcpip_handle;
extern cyg_handle_t mbox_out_tcpip_handle;
extern cyg_mbox mbox_into_tcpip_obj;
extern cyg_mbox mbox_out_tcpip_obj;
extern MyEvent_t into_tcpip_event;
extern MyEvent_t out_tcpip_event;
/********************end of global variables *********/

/********************* My static variables ***********/
static MyEvent_t message_tcpip;

/********************end of My static variables *********/
#if UIP_CONF_ICMP6
process_event_t tcpip_icmp6_event;
#endif /* UIP_CONF_ICMP6 */

/*static struct tcpip_event_args ev_args;*/

/*periodic check of active connections*/
static struct timer periodic;

#if UIP_CONF_IPV6 && UIP_CONF_IPV6_REASSEMBLY
/*timer for reassembly*/
extern struct timer uip_reass_timer;
#endif

#if UIP_TCP
/**
 * \internal Structure for holding a TCP port and a process ID.
 */
struct listenport {
  cyg_uint16 port;
  struct process *p;
};

static struct internal_state {
  struct listenport listenports[UIP_LISTENPORTS];
  struct process *p;
} s;
#endif

enum {
  NO_EVENT,
  TCP_POLL,
  UDP_POLL,
  PACKET_INPUT
};

/* Called on IP packet output. */
#if UIP_CONF_IPV6

static cyg_uint8 (* outputfunc)(uip_lladdr_t *a);

cyg_uint8
tcpip_output(uip_lladdr_t *a)
{
  int ret;
  if(outputfunc != NULL) {    //PRINTF(" in   if(outputfunc != NULL)\n");////////////////////////////////////
    ret = outputfunc(a);
    return ret;
  }
  UIP_LOG("tcpip_output: Use tcpip_set_outputfunc() to set an output function");
   
  return 0;
}

void
tcpip_set_outputfunc(cyg_uint8 (*f)(uip_lladdr_t *))
{ PRINTF(" in  tcpip_set_outputfunc\n");////////////////////////////////////
  outputfunc = f;
}
#else

static cyg_uint8 (* outputfunc)(void);
cyg_uint8
tcpip_output(void)
{
  if(outputfunc != NULL) {
    return outputfunc();
  }
  UIP_LOG("tcpip_output: Use tcpip_set_outputfunc() to set an output function");
  return 0;
}

void
tcpip_set_outputfunc(cyg_uint8 (*f)(void))
{
  outputfunc = f;
}
#endif

#if UIP_CONF_IP_FORWARD
unsigned char tcpip_is_forwarding; /* Forwarding right now? */
#endif /* UIP_CONF_IP_FORWARD */

//PROCESS(tcpip_process, "TCP/IP stack"); 待處理

/*---------------------------------------------------------------------------*/
static void
start_periodic_tcp_timer(void)
{
  if(timer_expired(&periodic)) {
    timer_restart(&periodic);
  }
}
/*---------------------------------------------------------------------------*/
static void
check_for_tcp_syn(void)
{
  /* This is a hack that is needed to start the periodic TCP timer if
     an incoming packet contains a SYN: since uIP does not inform the
     application if a SYN arrives, we have no other way of starting
     this timer.  This function is called for every incoming IP packet
     to check for such SYNs. */
#define TCP_SYN 0x02
  if(UIP_IP_BUF->proto == UIP_PROTO_TCP &&
     (UIP_TCP_BUF->flags & TCP_SYN) == TCP_SYN) {
    start_periodic_tcp_timer();
  }
}
/*---------------------------------------------------------------------------*/
static void 
packet_input(void)
{ 

 // printf(" uip_len = %i\n", uip_len);
#if UIP_CONF_IP_FORWARD
  if(uip_len > 0) {
    tcpip_is_forwarding = 1;
    if(uip_fw_forward() == UIP_FW_LOCAL) {
      tcpip_is_forwarding = 0;
      check_for_tcp_syn();
      uip_input();
      if(uip_len > 0) {
#if UIP_CONF_TCP_SPLIT
        uip_split_output(); 
#else /* UIP_CONF_TCP_SPLIT */
#if UIP_CONF_IPV6
        tcpip_ipv6_output();
#else
	PRINTF("tcpip packet_input forward output len %d\n", uip_len);
        tcpip_output();
#endif
#endif /* UIP_CONF_TCP_SPLIT */
      }
    }
    tcpip_is_forwarding = 0;
  } 
#else /* UIP_CONF_IP_FORWARD */
   // printf("in uip_process, BEFORE BEFORE if(uip_len > 0)!!\n");
  if(uip_len > 0) {
    check_for_tcp_syn();
 //   printf("in uip_process, BEFORE uip_input!!\n");
    uip_input();
  //  printf("in uip_process, AFTER uip_input!!\n");
    if(uip_len > 0) {
#if UIP_CONF_TCP_SPLIT
      uip_split_output();
#else /* UIP_CONF_TCP_SPLIT */
#if UIP_CONF_IPV6
      tcpip_ipv6_output();
#else
      PRINTF("tcpip packet_input output len %d\n", uip_len);
      tcpip_output();
#endif
#endif /* UIP_CONF_TCP_SPLIT */
    }
  }
#endif /* UIP_CONF_IP_FORWARD */
 
 //uip_len = 0;///////////////////////////////////改過的地方
}
/*---------------------------------------------------------------------------*/
#if UIP_TCP

/*

#if UIP_ACTIVE_OPEN
struct uip_conn *
tcp_connect(uip_ipaddr_t *ripaddr, cyg_uint16 port, void *appstate)
{
  struct uip_conn *c;
  
  c = uip_connect(ripaddr, port);
  if(c == NULL) {
    return NULL;
  }

  c->appstate.threadHandle = &cyg_thread_self();
  c->appstate.state = appstate;
  
  tcpip_poll_tcp(c);
  
  return c;
}
#endif //================= UIP_ACTIVE_OPEN ===================//
//------------------------------------------------------------------------- 
void
tcp_unlisten(cyg_uint16 port)
{
  static unsigned char i;
  struct listenport *l;

  l = s.listenports;
  for(i = 0; i < UIP_LISTENPORTS; ++i) {
    if(l->port == port &&
       l->p == PROCESS_CURRENT()) {
      l->port = 0;
      uip_unlisten(port);
      break;
    }
    ++l;
  }
}
//---------------------------------------------------------------------------
void
tcp_listen(cyg_uint16 port)
{
  static unsigned char i;
  struct listenport *l;

  l = s.listenports;
  for(i = 0; i < UIP_LISTENPORTS; ++i) {
    if(l->port == 0) {
      l->port = port;
      l->p = PROCESS_CURRENT();
      uip_listen(port);
      break;
    }
    ++l;
  }
}
//---------------------------------------------------------------------------
void
tcp_attach(struct uip_conn *conn,
	   void *appstate)
{
  register uip_tcp_appstate_t *s;

  s = &conn->appstate;
  s->threadHandle = &cyg_thread_self();
  s->state = appstate;
}
*/
#endif /* UIP_TCP */
/*---------------------------------------------------------------------------*/
#if UIP_UDP
/*              ////////原本的code   改過的地方
void
udp_attach(struct uip_udp_conn *conn,
	   void *appstate)
{
  register uip_udp_appstate_t *s;

  s = &conn->appstate;
  s->p = PROCESS_CURRENT();
  s->state = appstate;
}

*/

void
udp_attach(struct uip_udp_conn *conn,
	   void *appstate)
{
  register uip_udp_appstate_t *s;

  s = &conn->appstate;
  
  s->threadHandle  =    cyg_thread_self() ;
  s->state = appstate;
}
/*---------------------------------------------------------------------------*/
struct uip_udp_conn* //////    改過的地方
udp_new(const uip_ipaddr_t *ripaddr, cyg_uint16 port, void *appstate)
{
  struct uip_udp_conn *c;
  uip_udp_appstate_t *s;
  
  c = uip_udp_new(ripaddr, port);
  if(c == NULL) {
    return NULL;
  }

  s = &c->appstate;
  s->threadHandle =   cyg_thread_self();
  s->state = appstate;

  return c;
}
/*---------------------------------------------------------------------------*/
struct uip_udp_conn *
udp_broadcast_new(cyg_uint16 port, void *appstate)
{
  uip_ipaddr_t addr;
  struct uip_udp_conn *conn;

#if UIP_CONF_IPV6
  uip_create_linklocal_allnodes_mcast(&addr);
#else
  uip_ipaddr(&addr, 255,255,255,255);
#endif /* UIP_CONF_IPV6 */
  conn = udp_new(&addr, port, appstate);
  if(conn != NULL) {
    udp_bind(conn, port);
  }
  return conn;
}
#endif /* UIP_UDP */
/*---------------------------------------------------------------------------*/
#if UIP_CONF_ICMP6
cyg_uint8
icmp6_new(void *appstate) {
  if(uip_icmp6_conns.appstate.p == PROCESS_NONE) {
    uip_icmp6_conns.appstate.p = PROCESS_CURRENT();
    uip_icmp6_conns.appstate.state = appstate;
    return 0;
  }
  return 1;
}

void
tcpip_icmp6_call(cyg_uint8 type)
{
  if(uip_icmp6_conns.appstate.p != PROCESS_NONE) {
    /* XXX: This is a hack that needs to be updated. Passing a pointer (&type)
       like this only works with process_post_synch. */
    process_post_synch(uip_icmp6_conns.appstate.p, tcpip_icmp6_event, &type);
  }
  return;
}
#endif /* UIP_CONF_ICMP6 */
/*---------------------------------------------------------------------------*/

static void
eventhandler(MyEvent_t message_tcpip)
{   
#if UIP_TCP
  static unsigned char i;
  register struct listenport *l;
#endif /*UIP_TCP*/
    cyg_uint32 flag = message_tcpip.EventFlag;
//    PRINTF("in eventhandler, flag=%i\n", flag);
  switch(flag) {   
    case PROCESS_EVENT_EXITED:
      /* This is the event we get if a process has exited. 
         We go through the TCP/IP tables to see if this process had any open
         connections or listening TCP ports. If so, we'll close those connections. */
       
     {   /************************  begin 1{   ************************/    
         cyg_handle_t* conn_thread_handle_ptr;
         conn_thread_handle_ptr  = (cyg_handle_t*)message_tcpip.dataPtr;
#if UIP_TCP
      l = s.listenports;
      for(i = 0; i < UIP_LISTENPORTS; ++i) {
            if(l->p == p) {
                 uip_unlisten(l->port);
                 l->port = 0;
                 l->p = PROCESS_NONE;
             }
           ++l;
       }
	 
      {  /************************  begin 2{   ************************/ 
        register struct uip_conn *cptr;
	    
        for(cptr = &uip_conns[0]; cptr < &uip_conns[UIP_CONNS]; ++cptr) {
          if(cptr->appstate.p == p) {
            cptr->appstate.p = PROCESS_NONE;
            cptr->tcpstateflags = UIP_CLOSED;
          }
	       
        }
	    
      }/************************  end 2{   ************************/    
#endif /* UIP_TCP */
#if UIP_UDP
      {  /************************  begin 3{   ************************/ 
        register struct uip_udp_conn *cptr;
        for(cptr = &uip_udp_conns[0];
            cptr < &uip_udp_conns[UIP_UDP_CONNS]; ++cptr) {
           if(cptr->appstate.threadHandle == *conn_thread_handle_ptr) {
            cptr->lport = 0;
          }
        }
      
      }/************************  end 3{   ************************/    
#endif /* UIP_UDP */
}   /************************  end 1{   ************************/    
       message_tcpip.EventFlag=NO_EVENT;///////////////////////////////////////////////////////// modified
      break;

    
	 
#if UIP_TCP
    case TCP_POLL:
{/************************  begin 5{   ************************/ 
 struct uip_conn* conn_tcp;
 conn_tcp = (struct uip_conn*)message_tcpip.dataPtr;
      if( conn_tcp= !NULL) {
        uip_poll_conn(conn_tcp);
#if UIP_CONF_IPV6
        tcpip_ipv6_output();
#else /* UIP_CONF_IPV6 */
        if(uip_len > 0) {
	  PRINTF("tcpip_output from tcp poll len %d\n", uip_len);
          tcpip_output();
        }
#endif /* UIP_CONF_IPV6 */
        /* Start the periodic polling, if it isn't already active. */
        start_periodic_tcp_timer();
      }
}/************************  end 5{   ************************/
       message_tcpip.EventFlag=NO_EVENT;///////////////////////////////////////////////////////// modified
      break;
#endif /* UIP_TCP */
#if UIP_UDP
    case UDP_POLL:
{/************************  begin 6{   ************************/ 

   struct uip_udp_conn * conn_udp;
   conn_udp = (struct uip_udp_conn*) message_tcpip.dataPtr;
      if(conn_udp != NULL) {
        uip_udp_periodic_conn(conn_udp);
#if UIP_CONF_IPV6
        tcpip_ipv6_output();
#else
        if(uip_len > 0) {
          tcpip_output();
        }
#endif /* UIP_UDP */
      }
}/************************  end 6{   ************************/ 
      message_tcpip.EventFlag=NO_EVENT;///////////////////////////////////////////////////////// modified
      break;
#endif /* UIP_UDP */

    case PACKET_INPUT:
     
      packet_input(); 
  //    printf("in tcpip.c,packet_input  AFTER  \n");
    message_tcpip.EventFlag=NO_EVENT;///////////////////////////////////////////////////////// modified   
   break;

    case NO_EVENT:

    break;
 };


 message_tcpip.EventFlag=NO_EVENT;
}
/*---------------------------------------------------------------------------*/
void
tcpip_input(void)
{
  //process_post_synch(&tcpip_process, PACKET_INPUT, NULL);///改過的地方
  // 可以用改 priority 來作到 synch   
/*
   into_tcpip_event.EventFlag =PACKET_INPUT;
   cyg_mbox_put( mbox_into_tcpip_handle, &into_tcpip_event);
*/
    message_tcpip.EventFlag=PACKET_INPUT;
    eventhandler(message_tcpip);

  uip_len = 0;////////////////////////////////////////////出問題/////////////////////////////////改過的地方
#if UIP_CONF_IPV6
  uip_ext_len = 0;////////////////////////////////////////////出問題
#endif /*UIP_CONF_IPV6*/
}
/*---------------------------------------------------------------------------*/
#if UIP_CONF_IPV6
void
tcpip_ipv6_output(void)
{//PRINTF(" Enter into tcpip_ipv6_output \n");////////////////////////
  uip_ds6_nbr_t *nbr = NULL;
  uip_ipaddr_t* nexthop;
  
  if(uip_len == 0) {
   // PRINTF("   tcpip_ipv6_output uip_len == 0 return \n");/////////
    return;
  }
  
  if(uip_len > UIP_LINK_MTU) {
    PRINTF("   tcpip_ipv6_output: Packet too big \n");/////////
    UIP_LOG("tcpip_ipv6_output: Packet too big");
    uip_len = 0;
    return;
  }
  if(uip_is_addr_unspecified(&UIP_IP_BUF->destipaddr)){
    PRINTF("  tcpip_ipv6_output: Destination address unspecified \n");/////////
    UIP_LOG("tcpip_ipv6_output: Destination address unspecified");
    uip_len = 0;
    return;
  }

  //PRINTF(" Before !uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) \n");////////////////////////////////   

  if(!uip_is_addr_mcast(&UIP_IP_BUF->destipaddr)) {
    /* Next hop determination */
   // PRINTF(" !uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) \n");///////////////////////////////////////////////////
    nbr = NULL;
    if(uip_ds6_is_addr_onlink(&UIP_IP_BUF->destipaddr)){
      nexthop = &UIP_IP_BUF->destipaddr;
    } else {
      uip_ds6_route_t* locrt;
      locrt = uip_ds6_route_lookup(&UIP_IP_BUF->destipaddr);
      if(locrt == NULL) {
        if((nexthop = uip_ds6_defrt_choose()) == NULL) {
#ifdef UIP_FALLBACK_INTERFACE
	  UIP_FALLBACK_INTERFACE.output();
#else
          PRINTF("tcpip_ipv6_output: Destination off-link but no route\n");
#endif
          uip_len = 0;
          return;
        }
      } else {
	nexthop = &locrt->nexthop;
      }
    }
    /* end of next hop determination */
    if((nbr = uip_ds6_nbr_lookup(nexthop)) == NULL) {
      //      printf("add1 %d\n", nexthop->u8[15]);
      if((nbr = uip_ds6_nbr_add(nexthop, NULL, 0, NBR_INCOMPLETE)) == NULL) {
        //        printf("add n\n");
        uip_len = 0;
        return;
      } else {
#if UIP_CONF_IPV6_QUEUE_PKT
        /* copy outgoing pkt in the queuing buffer for later transmmit */
        if(uip_packetqueue_alloc(&nbr->packethandle, UIP_DS6_NBR_PACKET_LIFETIME) != NULL) {
          memcpy(uip_packetqueue_buf(&nbr->packethandle), UIP_IP_BUF, uip_len);
          uip_packetqueue_set_buflen(&nbr->packethandle, uip_len);
        }
#endif
      /* RFC4861, 7.2.2:
       * "If the source address of the packet prompting the solicitation is the
       * same as one of the addresses assigned to the outgoing interface, that
       * address SHOULD be placed in the IP Source Address of the outgoing
       * solicitation.  Otherwise, any one of the addresses assigned to the
       * interface should be used."*/
       if(uip_ds6_is_my_addr(&UIP_IP_BUF->srcipaddr)){
          uip_nd6_ns_output(&UIP_IP_BUF->srcipaddr, NULL, &nbr->ipaddr);
        } else {
          uip_nd6_ns_output(NULL, NULL, &nbr->ipaddr);
        }

        stimer_set(&(nbr->sendns), uip_ds6_if.retrans_timer / 1000);
        nbr->nscount = 1;
      }
    } else {
      if(nbr->state == NBR_INCOMPLETE) {
        PRINTF("tcpip_ipv6_output: nbr cache entry incomplete\n");
#if UIP_CONF_IPV6_QUEUE_PKT
        /* copy outgoing pkt in the queuing buffer for later transmmit and set
           the destination nbr to nbr */
        if(uip_packetqueue_alloc(&nbr->packethandle, UIP_DS6_NBR_PACKET_LIFETIME) != NULL) {
          memcpy(uip_packetqueue_buf(&nbr->packethandle), UIP_IP_BUF, uip_len);
          uip_packetqueue_set_buflen(&nbr->packethandle, uip_len);
        }
        /*        memcpy(nbr->queue_buf, UIP_IP_BUF, uip_len);
                  nbr->queue_buf_len = uip_len;*/
        uip_len = 0;
#endif /*UIP_CONF_IPV6_QUEUE_PKT*/
        return;
      }
      /* if running NUD (nbc->state == STALE, DELAY, or PROBE ) keep
         sending in parallel see rfc 4861 Node behavior in section 7.7.3*/
	 
      if(nbr->state == NBR_STALE) {
        nbr->state = NBR_DELAY;
        stimer_set(&(nbr->reachable),
                  UIP_ND6_DELAY_FIRST_PROBE_TIME);
        nbr->nscount = 0;
        PRINTF("tcpip_ipv6_output: nbr cache entry stale moving to delay\n");
      }
      
      stimer_set(&(nbr->sendns),
                uip_ds6_if.retrans_timer / 1000);

      tcpip_output(&(nbr->lladdr));


#if UIP_CONF_IPV6_QUEUE_PKT
      /* Send the queued packets from here, may not be 100% perfect though.
       * This happens in a few cases, for example when instead of receiving a
       * NA after sendiong a NS, you receive a NS with SLLAO: the entry moves
       *to STALE, and you must both send a NA and the queued packet
       */
      /*      if(nbr->queue_buf_len != 0) {
        uip_len = nbr->queue_buf_len;
        memcpy(UIP_IP_BUF, nbr->queue_buf, uip_len);
        nbr->queue_buf_len = 0;
        tcpip_output(&(nbr->lladdr));
        }*/
      if(uip_packetqueue_buflen(&nbr->packethandle) != 0) {
        uip_len = uip_packetqueue_buflen(&nbr->packethandle);
        memcpy(UIP_IP_BUF, uip_packetqueue_buf(&nbr->packethandle), uip_len);
        uip_packetqueue_free(&nbr->packethandle);
        tcpip_output(&(nbr->lladdr));
      }
#endif /*UIP_CONF_IPV6_QUEUE_PKT*/

      uip_len = 0;
      return;
    }
  }
  // PRINTF(" not !uip_is_addr_mcast(&UIP_IP_BUF->destipaddr)\n");////////////////////////////////   

  
   
  /*multicast IP destination address */
  tcpip_output(NULL);
  uip_len = 0;
  uip_ext_len = 0;
   
}
#endif
/*---------------------------------------------------------------------------*/
#if UIP_UDP
void
tcpip_poll_udp(struct uip_udp_conn *conn)
{
  ////process_post(&tcpip_process, UDP_POLL, conn);////改過的地方
    MyEvent_t* tcpip_udp_poll_ptr;
    tcpip_udp_poll_ptr = &into_tcpip_event;

    tcpip_udp_poll_ptr->EventFlag = UDP_POLL;
    tcpip_udp_poll_ptr->dataPtr =  conn;
    cyg_mbox_put( mbox_into_tcpip_handle, tcpip_udp_poll_ptr);

}
#endif /* UIP_UDP */
/*---------------------------------------------------------------------------*/
#if UIP_TCP
void
tcpip_poll_tcp(struct uip_conn *conn)
{
  ////// process_post(&tcpip_process, TCP_POLL, conn);////改過的地方
  MyEvent_t* tcpip_poll_ptr;
  tcpip_poll_ptr = &into_tcpip_event;

  tcpip_poll_ptr->EventFlag = TCP_POLL ;
  tcpip_poll_ptr->dataPtr =  conn;
  cyg_mbox_put( mbox_into_tcpip_handle, tcpip_poll_ptr); 
}
#endif /* UIP_TCP */
/*---------------------------------------------------------------------------*/
void
tcpip_uipcall(void)
{
  register uip_udp_appstate_t *ts;
  
#if UIP_UDP
  if(uip_conn != NULL) {
    ts = &uip_conn->appstate;
  } else {
    ts = &uip_udp_conn->appstate;
  }
#else /* UIP_UDP */
  ts = &uip_conn->appstate;
#endif /* UIP_UDP */

#if UIP_TCP
 {
   static unsigned char i;
   register struct listenport *l;
   
   /* If this is a connection request for a listening port, we must
      mark the connection with the right process ID. */
   if(uip_connected()) {
     l = &s.listenports[0];
     for(i = 0; i < UIP_LISTENPORTS; ++i) {
       if(l->port == uip_conn->lport &&
	  l->p != PROCESS_NONE) {
	 ts->p = l->p;
	 ts->state = NULL;
	 break;
       }
       ++l;
     }
     
     /* Start the periodic polling, if it isn't already active. */
     start_periodic_tcp_timer();
   }
 }
#endif /* UIP_TCP */

	//printf("\ntcpip_uipcall\n\n");

  if(ts->threadHandle != 0) {  // ts is uip_upd_conn
        //process_post_synch(ts->p, tcpip_event, ts->state);/////改過的地方
	//	puts("\npost tcpip_event\n");

//    printf("tcpip_event, conn handle = %i\n", ts->threadHandle);
    MyEvent_t* tcpip_out_ptr;
    tcpip_out_ptr = &out_tcpip_event;

    tcpip_out_ptr->EventFlag = 0;
    tcpip_out_ptr->dataPtr = (void*) &(ts->threadHandle);////////可能會出事
    cyg_mbox_put( mbox_out_tcpip_handle, tcpip_out_ptr);

    
                
    cyg_thread_set_priority(ts->threadHandle,5); 
    
 
    cyg_thread_set_priority(ts->threadHandle,10); 
   PRINTF("End of set priority!!!\n");

  } 
}
/*---------------------------------------------------------------------------*/
void  check_timer_expired(void){
    /* We get this event if one of our timers have expired. */
            /* Check the clock so see if we should call the periodic uIP processing. */   
        if(timer_expired(&periodic)) {
     
        

#if UIP_TCP
          for(i = 0; i < UIP_CONNS; ++i) {
            if(uip_conn_active(i)) {
              /* Only restart the timer if there are active
                 connections. */
              timer_restart(&periodic);
              uip_periodic(i);
#if UIP_CONF_IPV6
            tcpip_ipv6_output(); // not used
#else
              if(uip_len > 0) {
		PRINTF("tcpip_output from periodic len %d\n", uip_len);
                tcpip_output();
		PRINTF("tcpip_output after periodic len %d\n", uip_len);
              }
#endif /* UIP_CONF_IPV6 */
            }
          }
#endif /* UIP_TCP */
#if UIP_CONF_IP_FORWARD
          uip_fw_periodic();
#endif /* UIP_CONF_IP_FORWARD */
        }
        
#if UIP_CONF_IPV6
#if UIP_CONF_IPV6_REASSEMBLY
        /*
         * check the timer for reassembly
         */
        if( timer_expired(&uip_reass_timer)) {
          uip_reass_over();
          tcpip_ipv6_output();
        }
#endif /* UIP_CONF_IPV6_REASSEMBLY */
        /*
         * check the different timers for neighbor discovery and
         * stateless autoconfiguration
         */
        /*if(data == &uip_nd6_timer_periodic &&
           etimer_expired(&uip_nd6_timer_periodic)) {
          uip_nd6_periodic();
          tcpip_ipv6_output();
        }*/
#if !UIP_CONF_ROUTER	    
        if(timer_expired(&uip_ds6_timer_rs)){
          uip_ds6_send_rs();
          tcpip_ipv6_output();
        }
#endif /* !UIP_CONF_ROUTER */
        if(timer_expired(&uip_ds6_timer_periodic)){
          uip_ds6_periodic();
        //  printf("uip_ds6_timer_periodic!\n");
          tcpip_ipv6_output();/////////////////////////////////////////////////////////
        }
#endif /* UIP_CONF_IPV6 */
}

void 
tcpip_process(cyg_addrword_t data)
{

/******************** lock the Scheduler ************************/
      cyg_scheduler_lock();
/****************************************************************/

   
   PRINTF("Hello, eCos tcpip_process!\n");

#if UIP_TCP
 {
   static unsigned char i;
   
   for(i = 0; i < UIP_LISTENPORTS; ++i) {
     s.listenports[i].port = 0;
   }
   s.p = PROCESS_CURRENT();
 }
#endif

 //////// tcpip_event = process_alloc_event(); 改過的地方

    
   // cyg_mbox_create(&mbox_into_tcpip_handle, &mbox_into_tcpip_obj);
    cyg_mbox_create(&mbox_out_tcpip_handle, &mbox_out_tcpip_obj);

#if UIP_CONF_ICMP6
  tcpip_icmp6_event = process_alloc_event();
#endif /* UIP_CONF_ICMP6 */
  timer_set(&periodic, CLOCK_CONF_SECOND / 2); 
   
  //uip_init();
#ifdef UIP_FALLBACK_INTERFACE
  UIP_FALLBACK_INTERFACE.init();
#endif
/* initialize RPL if configured for using RPL */
#if UIP_CONF_IPV6_RPL
  //rpl_init();
#endif /* UIP_CONF_IPV6_RPL */
 
    
   cyg_mbox_create(&mbox_into_tcpip_handle, &mbox_into_tcpip_obj);
   
     
//=================================
   static cyg_uint32 YLedPinspec; 
  YLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 7, OUT_50MHZ , OUT_PUSHPULL     );
  volatile static  cyg_uint8 blinkY=0;
//==================================  
/******************** unlock the Scheduler ************************/
        cyg_scheduler_unlock();
/****************************************************************/

  extern void check_rpl_timer_timeout(void);

//  while(1) {
/*  
                blinkY=~blinkY;
                CYGHWR_HAL_STM32_GPIO_OUT(YLedPinspec,blinkY); 
               
		cyg_thread_delay(1500);
*/
cyg_thread_yield();


/*
 
cyg_scheduler_lock();////////////////////////
   check_timer_expired( );///////////////////////////////////
   check_rpl_timer_timeout();
cyg_scheduler_unlock();//////////////////////
 

*/


  // }   
}

/*---------------------------------------------------------------------------*/
 


