/**
 * \addtogroup ctimer
 * @{
 */

/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
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
 * $Id: ctimer.c,v 1.1 2010/06/14 07:34:36 adamdunkels Exp $
 */

/**
 * \file
 *         Callback timer implementation
 * \author
 *         Adam Dunkels <adam@sics.se>
 */
/*
#include "sys/ctimer.h"
#include "contiki.h"
#include "lib/list.h"
*/

#include "cyg/net/uIPv6Stack/uIPv6/ctimer_sys.h"
#include "cyg/net/uIPv6Stack/uIPv6/contiki.h"
#include "cyg/net/uIPv6Stack/uIPv6/list_lib.h"

LIST(ctimer_list);

//static char initialized;

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


/*---------------------------------------------------------------------------*/
void
ctimer_set(struct ctimer *c, cyg_tick_count_t t,
	   void (*f)(cyg_handle_t , cyg_addrword_t), void *ptr)
{
  PRINTF("ctimer_set %p %u\n", c, (unsigned)t);
/*
  c->p = PROCESS_CURRENT();
  c->f = f;
  c->ptr = ptr;
  if(initialized) {
    PROCESS_CONTEXT_BEGIN(&ctimer_process);
    etimer_set(&c->etimer, t);
    PROCESS_CONTEXT_END(&ctimer_process);
  } else {
    c->etimer.timer.interval = t;
  }

  list_remove(ctimer_list, c);
  list_add(ctimer_list, c);
*/
   

       MyeCosAlarm(  &(c->MyeCosAlramObj),
                                        t,
                                      ptr,
	                                f);
}
/*---------------------------------------------------------------------------*/
void
ctimer_reset(struct ctimer *c)
{
/*
  if(initialized) {
    PROCESS_CONTEXT_BEGIN(&ctimer_process);
    etimer_reset(&c->etimer);
    PROCESS_CONTEXT_END(&ctimer_process);
  }

  list_remove(ctimer_list, c);
  list_add(ctimer_list, c);
  
*/  if (c->MyeCosAlramObj.initialized == 0){
        cyg_alarm_enable((c->MyeCosAlramObj).alarm_handle);  
        c->MyeCosAlramObj.initialized = 1;
    }

}
/*---------------------------------------------------------------------------*/
void
ctimer_restart(struct ctimer *c)
{
/*
  if(initialized) {
    PROCESS_CONTEXT_BEGIN(&ctimer_process);
    etimer_restart(&c->etimer);
    PROCESS_CONTEXT_END(&ctimer_process);
  }

  list_remove(ctimer_list, c);
  list_add(ctimer_list, c);
  */
  cyg_alarm_enable((c->MyeCosAlramObj).alarm_handle);  

} 
/*---------------------------------------------------------------------------*/
void
ctimer_stop(struct ctimer *c)
{
/* 
 if(initialized) {
    etimer_stop(&c->etimer);
  } else {
    c->etimer.next = NULL;
    c->etimer.p = PROCESS_NONE;
  }
  list_remove(ctimer_list, c);
*/

if (c->MyeCosAlramObj.initialized){
    cyg_alarm_delete((c->MyeCosAlramObj).alarm_handle);
    c->MyeCosAlramObj.initialized =0;
   }
  
}
/*---------------------------------------------------------------------------*/
int
ctimer_expired(struct ctimer *c)
{/*
  struct ctimer *t;
  if(initialized) {
    return etimer_expired(&c->etimer);
  }
  for(t = list_head(ctimer_list); t != NULL; t = t->next) {
    if(t == c) {
      return 0;
    }
  }
  return 1;
*/
  }
/*---------------------------------------------------------------------------*/
/** @} */
