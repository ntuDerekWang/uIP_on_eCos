#include <cyg/kernel/kapi.h>
#include <cyg/hal/plf_io.h>
#include <stdio.h>
#include <cyg/DW_config.h>     
#include <stdlib.h>
#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"
#include "cyg/net/uIPv6Stack/uIPv6/contiki-lib.h"
#include "cyg/net/uIPv6Stack/uIPv6/contiki-net.h"
#include "cyg/net/uIPv6Stack/uIPv6/uip.h"
#include "cyg/net/uIPv6Stack/rpl/rpl.h"
#include "cyg/net/uIPv6Stack/uIPv6/netstack.h"
#include <cyg/hal/var_io.h>
//#include "cyg/net/uIPv6Stack/mac/frame802154.h"

#include "cyg/net/uIPv6Stack/uIPv6/uz2400_dev.h"
//#include "cyg/net/uIPv6Stack/uIPv6/tcpip.h"

//#define DEBUG DEBUG_PRINT
#define DEBUG DEBUG_NONE

#include "cyg/net/uIPv6Stack/uIPv6/uip-debug.h"

#if WITH_UIP6
#include "cyg/net/uIPv6Stack/uIPv6/uip-ds6.h"
#endif /* WITH_UIP6 */

/*------------------------------------*/
#ifndef RF_CHANNEL
#define RF_CHANNEL              26
#endif
/*--------------------------------------*/
 unsigned char ds2411_id[8];
extern cyg_handle_t mbox_out_tcpip_handle;
/*----------------------------------------*/
static void
set_rime_addr(void)
{
  rimeaddr_t addr;
  int i;

  memset(&addr, 0, sizeof(rimeaddr_t));
#if UIP_CONF_IPV6
  memcpy(addr.u8, ds2411_id, sizeof(addr.u8));
#else
  if(node_id == 0) {
    for(i = 0; i < sizeof(rimeaddr_t); ++i) {
      addr.u8[i] = ds2411_id[7 - i];
    }
  } else {
    addr.u8[0] = node_id & 0xff;
    addr.u8[1] = node_id >> 8;
  }
#endif
  rimeaddr_set_node_addr(&addr);
  printf("Rime started with address ");
  for(i = 0; i < sizeof(addr.u8) - 1; i++) {
    printf("%d.", addr.u8[i]);
  }
  printf("%d\n", addr.u8[i]);
}
/*------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*
static void
print_processes(struct process * const processes[])
{
  //  const struct process * const * p = processes; 
  printf("Starting");
  while(*processes != NULL) {
    printf(" '%s'", (*processes)->name);
    processes++;
  }
  putchar('\n');
}
*/
/*--------------------------------------------------------------------------*/


/********* udp-client.c **********/
#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678

#define UDP_EXAMPLE_ID  190
//=========
#define START_INTERVAL		(15 * CLOCK_CONF_SECOND)
#define SEND_INTERVAL		(5 * CLOCK_CONF_SECOND)
#define SEND_TIME		(0.1 * CLOCK_CONF_SECOND)//(random_rand() % (SEND_INTERVAL))
#define MAX_PAYLOAD_LEN		30

//===========

static struct uip_udp_conn *client_conn;
static uip_ipaddr_t server_ipaddr;
/*--------------------------------------------------------------*/
static void
tcpip_handler(void)
{
  char *appdata;
  
  PRINTF("  uip_flags = %i\n", uip_flags); 
  if(uip_newdata()) {
    appdata = (char *)uip_appdata;
    appdata[uip_datalen()] = 0;
    PRINTF("DATA recv '%s' from ", appdata);
    PRINTF("%d", UIP_IP_BUF->srcipaddr.u8[15]);
    PRINTF("\n");
#if SERVER_REPLY
    uip_ipaddr_copy(&client_conn->ripaddr, &UIP_IP_BUF->srcipaddr);
    uip_udp_packet_send(client_conn, "Reply", sizeof("Reply"));
    uip_create_unspecified(&client_conn->ripaddr);
#endif
  }
 
}
/*---------------------------------------------------------------------------*/



static void
send_packet(void)
{

  static int seq_id;
  char buf[MAX_PAYLOAD_LEN];
  char buf2[MAX_PAYLOAD_LEN];

  seq_id++;
  PRINTF("DATA send to %d 'Hello %d'\n",
         client_conn->ripaddr.u8[15], seq_id);
  sprintf(buf, "Hello %d from ", seq_id);

sprintf(buf2, "Hello %d from %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x ", seq_id, ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[0], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[1], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[2], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[3], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[4], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[5], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[6], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[7], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[8], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[9], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[10], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[11], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[12], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[13], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[14], ((cyg_uint8 *)&uip_ds6_if.addr_list[1].ipaddr)[15]);
//=======
/*
char buf3[150];
uip_udp_packet_sendto(client_conn, buf3, 150,
                        &server_ipaddr, UIP_HTONS(UDP_SERVER_PORT));
*/
//========
 
    uip_udp_packet_sendto(client_conn, buf2, strlen(buf2),
                        &server_ipaddr, UIP_HTONS(UDP_SERVER_PORT));

}
/*---------------------------------------------------------------------------*/
static void
set_global_address(void)
{
  uip_ipaddr_t ipaddr;

  uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0 );
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

  /* set server address */
  uip_ip6addr(&server_ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 1);

}
/*---------------------------------------------------------------------------*/
static void
print_local_addresses(void)
{
  int i;
  cyg_uint8 state;

  PRINTF("Client IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(state == ADDR_TENTATIVE || state == ADDR_PREFERRED) {
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
      /* hack to make address "final" */
      if (state == ADDR_TENTATIVE) {
	uip_ds6_if.addr_list[i].state = ADDR_PREFERRED;
      }
    }
  }
}
/*--------------------------------------------------------*/
void udp_client_process(void){
     
/******************** lock the Scheduler ************************/
      cyg_scheduler_lock();
/****************************************************************/
        static struct ctimer backoff_timer;
 
	 PRINTF("UDP client started\n");
	 
         set_global_address();   
	 
	 
	 print_local_addresses();
	 
	  

     client_conn = udp_new(NULL, UIP_HTONS(UDP_SERVER_PORT), NULL);
 

     udp_bind(client_conn, UIP_HTONS(UDP_CLIENT_PORT));
     PRINTF("Created a connection with the server ");
     PRINT6ADDR(&client_conn->ripaddr);
     PRINTF(" local/remote port %u/%u\n",
	UIP_HTONS(client_conn->lport), UIP_HTONS(client_conn->rport));

     ctimer_set(&backoff_timer,SEND_TIME,send_packet,NULL);
	 
//      PRINTF(" local/remote port %u/%u\n", client_conn->lport, client_conn->rport);
	 
	        void* message = NULL;
                
                 
/******************** unlock the Scheduler ************************/
        cyg_scheduler_unlock();
/****************************************************************/
          while(1){
                    // cyg_thread_yield();

		     message = cyg_mbox_tryget (mbox_out_tcpip_handle);
		     MyEvent_t* msg_local = message ;
			 if (  message != NULL){ 
                              cyg_handle_t* event_handlePtr;
                              event_handlePtr = (cyg_handle_t*) msg_local-> dataPtr;

                              if( cyg_thread_self() == *event_handlePtr){
			 
			                            tcpip_handler();
			                    }
 
 
		
		
                             }

                     }
}

/********* EOF udp-client.c **********/


#define STACK_SIZE 4096
#define UZ_STACK_SIZE ((STACK_SIZE)*(2))
#define EVENT_STACK_SIZE 512
//==============================
char stack[STACK_SIZE];
cyg_thread main_thread;
cyg_handle_t main_handle;
//===============================
char udp_client_stack [STACK_SIZE];
cyg_thread udp_client_thread ;
cyg_handle_t udp_client_handle;
//================================
char tcpip_stack [STACK_SIZE];
cyg_thread tcpip_thread ;
cyg_handle_t tcpip_handle;
//==================================
char uz2400_stack [UZ_STACK_SIZE];
cyg_thread uz2400_thread;
cyg_handle_t uz2400_handle;

void mainfunc(cyg_addrword_t data)
{
/******************** lock the Scheduler ************************/
      cyg_scheduler_lock();
/****************************************************************/
    printf("Hello, eCos mainfunc!\n");
    
    ds2411_id[0] = 0x00;
    ds2411_id[1] = 0x12;
    ds2411_id[2] = 0x75;
    ds2411_id[3] = 0x00;
    ds2411_id[4] = 0x0c;
    ds2411_id[5] = 0x59;
  //ds2411_id[6] = 0x57;
  //ds2411_id[7] = 0x3d;
    ds2411_id[6] = 0x09;
//    ds2411_id[7] = 0x08;
    ds2411_id[7] = 0x04;
    ds2411_id[2] &= 0xfe;
/*
    ds2411_id[0] = 0x02;
    ds2411_id[1] = 0x00;
    ds2411_id[2] = 0x00;
    ds2411_id[3] = 0x00;
    ds2411_id[4] = 0x00;
    ds2411_id[5] = 0x00;
  //ds2411_id[6] = 0x57;
  //ds2411_id[7] = 0x3d;
    ds2411_id[6] = 0x00;
    ds2411_id[7] = 0x00;
*/

     
  /* for setting "hardcoded" IEEE 802.15.4 MAC addresses */
#ifdef IEEE_802154_MAC_ADDRESS
  {
    uint8_t ieee[] = IEEE_802154_MAC_ADDRESS;
    memcpy(ds2411_id, ieee, sizeof(uip_lladdr.addr));
    ds2411_id[7] = node_id & 0xff;
  }
#endif
     random_init(5);

     set_rime_addr();
     NETSTACK_RADIO.init(); 
     
 
  {
    cyg_uint8 longaddr[8];
    cyg_uint16 shortaddr;
    
    shortaddr = (rimeaddr_node_addr.u8[0] << 8) +
    rimeaddr_node_addr.u8[1];
    memset(longaddr, 0, sizeof(longaddr));
    rimeaddr_copy((rimeaddr_t *)&longaddr, &rimeaddr_node_addr);
    printf("MAC %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x ",
           longaddr[0], longaddr[1], longaddr[2], longaddr[3],
           longaddr[4], longaddr[5], longaddr[6], longaddr[7]);
    
    uz2400_set_pan_addr(IEEE802154_PANID, shortaddr, longaddr);
  }
  uz2400_set_channel(RF_CHANNEL);///////////////////////////////////////////
 
 
 #if WITH_UIP6
  memcpy(&uip_lladdr.addr, ds2411_id, sizeof(uip_lladdr.addr)); 
  /* Setup nullmac-like MAC for 802.15.4 */
/*   sicslowpan_init(sicslowmac_init(&cc2420_driver)); */
/*   printf(" %s channel %u\n", sicslowmac_driver.name, RF_CHANNEL); */

  /* Setup X-MAC for 802.15.4 */
  queuebuf_init();
  //NETSTACK_RADIO.init();
  NETSTACK_RDC.init();
  NETSTACK_MAC.init();
  NETSTACK_NETWORK.init();

  printf("%s %s, channel check rate %lu Hz, radio channel %u\n",
         NETSTACK_MAC.name, NETSTACK_RDC.name,
         CLOCK_CONF_SECOND / (NETSTACK_RDC.channel_check_interval() == 0 ? 1:
                         NETSTACK_RDC.channel_check_interval()),
         RF_CHANNEL); 
//================
  uip_init(); 
  rpl_init(); 
//=============
  printf("Tentative link-local IPv6 address ");
  {
    uip_ds6_addr_t *lladdr=NULL;
    int i;
    lladdr = uip_ds6_get_link_local(-1);
    for(i = 0; i < 7; ++i) {
      printf("%02x%02x:", lladdr->ipaddr.u8[i * 2],
             lladdr->ipaddr.u8[i * 2 + 1]);
    }
    printf("%02x%02x\n", lladdr->ipaddr.u8[14], lladdr->ipaddr.u8[15]);
  } 

  if(!UIP_CONF_IPV6_RPL) {
    uip_ipaddr_t ipaddr;
    int i;
    uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
    uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
    uip_ds6_addr_add(&ipaddr, 0, ADDR_TENTATIVE);
    printf("Tentative global IPv6 address ");
    for(i = 0; i < 7; ++i) {
      printf("%02x%02x:",
             ipaddr.u8[i * 2], ipaddr.u8[i * 2 + 1]);
    }
    printf("%02x%02x\n",
           ipaddr.u8[7 * 2], ipaddr.u8[7 * 2 + 1]);
  }


#endif /* WITH_UIP6 */
  
  static cyg_uint32 GLedPinspec; 
  GLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 6, OUT_50MHZ , OUT_PUSHPULL     );
  volatile static  cyg_uint8 blink=0;  
/******************** unlock the Scheduler ************************/
        cyg_scheduler_unlock();
/****************************************************************/
  
	while(1){  
                
                blink=~blink;
                CYGHWR_HAL_STM32_GPIO_OUT(GLedPinspec,blink); 
               
		cyg_thread_delay(500);
             
               
                
       }
} 
      
void TestButtomCallback(void){
      printf("Hello, ButtomCallback!\n");


}

void
cyg_start(void)
{      

    //================
         SetupIsr();

         SetupRfSpi();
         SetupIO();
         SetupButtomCallback(send_packet);
   //================    
    cyg_thread_create(10,                // Priority - just a number
                      mainfunc,              // entry
                      0,                 // entry parameter
                      "mainfunc",            // Name
                      &stack[0],         // Stack
                      STACK_SIZE,        // Size
                      &main_handle, // Handle
                      &main_thread    // Thread data structure
                    ); 
				 
 
    cyg_thread_create(10,                // Priority - just a number
                      udp_client_process , // entry
                      0,                 // entry parameter
                      "udp_client_process",            // Name
                      &udp_client_stack[0],         // Stack
                      STACK_SIZE,        // Size
                      &udp_client_handle, // Handle
                      &udp_client_thread     // Thread data structure
                    );


   cyg_thread_create(10,                // Priority - just a number
                      uz2400_process, // entry
                      0,                 // entry parameter
                      "uz2400_process",            // Name
                      &uz2400_stack[0],         // Stack
                      UZ_STACK_SIZE,        // Sizeuz2400
                      &uz2400_handle, // Handle
                      &uz2400_thread     // Thread data structure
                    );   

 
    cyg_thread_create(10,                // Priority - just a number
                      tcpip_process, // entry
                      0,                 // entry parameter
                      "tcpip_process",            // Name
                      &tcpip_stack[0],         // Stack
                      STACK_SIZE,        // Size
                      &tcpip_handle, // Handle
                      &tcpip_thread     // Thread data structure
                    );
 
 



   
				
        cyg_thread_resume(main_handle); // Start it
	
        cyg_thread_resume(tcpip_handle);
        
        cyg_thread_resume(udp_client_handle);
         
   	cyg_thread_resume(uz2400_handle); 

        cyg_scheduler_start();
}
