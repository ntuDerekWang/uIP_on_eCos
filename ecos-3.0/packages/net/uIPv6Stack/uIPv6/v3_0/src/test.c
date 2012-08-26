//#include "cyg/net/uIPv6Stack/uIPv6/uip.h"

//#include "cyg/net/uIPv6Stack/uIPv6/uip-nd6.h"
#include "cyg/net/uIPv6Stack/uIPv6/tcpip.h"
//#include "cyg/net/uIPv6Stack/uIPv6/psock.h"
//#include "cyg/net/uIPv6Stack/mac/csma.h"
//#include "cyg/net/uIPv6Stack/uIPv6/sicslowpan.h"
#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"
//#include "cyg/net/uIPv6Stack/uIPv6/timer_sys.h"
//#include "cyg/net/uIPv6Stack/uIPv6/uip-ds6.h"
//#include "cyg/net/uIPv6Stack/uIPv6/contiki-net.h"
#include "cyg/net/uIPv6Stack/uIPv6/ctimer_sys.h"

 #include "cyg/net/uIPv6Stack/rpl/rpl.h"
#include <cyg/kernel/kapi.h>  
#include <cyg/DW_config.h> 
#include <limits.h>
 
#include "cyg/net/uIPv6Stack/uIPv6/uz2400_dev.h"
/***************global variable***************/
 
cyg_handle_t mbox_into_tcpip_handle;
cyg_handle_t mbox_out_tcpip_handle;
cyg_mbox mbox_into_tcpip_obj;
cyg_mbox mbox_out_tcpip_obj;
MyEvent_t into_tcpip_event;
MyEvent_t out_tcpip_event;
 
 
