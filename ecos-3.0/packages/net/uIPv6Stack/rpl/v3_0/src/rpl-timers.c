/**
 * \addtogroup uip6
 * @{
 */
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
 * $Id: rpl-timers.c,v 1.13 2010/11/03 15:41:23 adamdunkels Exp $
 */
/**
 * \file
 *         RPL timer management.
 *
 * \author Joakim Eriksson <joakime@sics.se>, Nicolas Tsiftes <nvt@sics.se>
 */
/*
#include "contiki-conf.h"
#include "net/rpl/rpl.h"
#include "lib/random.h"
#include "sys/ctimer.h"
*/
 /////////////////改過的地方
#include "cyg/net/uIPv6Stack/uIPv6/contiki-conf.h"
#include "cyg/net/uIPv6Stack/rpl/rpl.h"
#include "cyg/net/uIPv6Stack/uIPv6/random_lib.h"
#include "cyg/net/uIPv6Stack/uIPv6/ctimer_sys.h"


#define DEBUG DEBUG_NONE
//#define DEBUG DEBUG_PRINT
/*
#include "net/uip-debug.h"
*/
#include "cyg/net/uIPv6Stack/uIPv6/uip-debug.h"



/************************************************************************/
static struct ctimer periodic_timer;

static void new_dio_interval(rpl_dag_t *dag);

static inline void handle_periodic_timer_modified( cyg_handle_t,cyg_addrword_t);
static void handle_periodic_timer( cyg_addrword_t);

static inline void handle_dio_timer_modified(cyg_handle_t alarm_handle, cyg_addrword_t data);
static void handle_dio_timer( cyg_addrword_t data);

static inline void handle_dao_timer_modified(cyg_handle_t alarm_handle, cyg_addrword_t data);
static void handle_dao_timer( cyg_addrword_t data);


static cyg_uint16 next_dis;

/* dio_send_ok is true if the node is ready to send DIOs */
static cyg_uint8 dio_send_ok;
//===================================
static cyg_uint8 handle_periodic_timer_flag;// = 0;
static cyg_addrword_t handle_periodic_timer_data;// = NULL;

static cyg_uint8 handle_dio_timer_flag ;//= 0;
static cyg_addrword_t handle_dio_timer_data;// = NULL;

static cyg_uint8 handle_dao_timer_flag ;//= 0;
static cyg_addrword_t handle_dao_timer_data ;//= NULL;
/************************************************************************/
inline void check_rpl_timer_timeout(void){
             /******************** lock the Scheduler ************************/
 //     cyg_scheduler_lock();
/****************************************************************/
      

           if (handle_periodic_timer_flag){
               handle_periodic_timer(  handle_periodic_timer_data);
			   handle_periodic_timer_flag = 0;
                          // return;   
            }
			
		 	/////
                  
		  if (handle_dio_timer_flag ){
 
                       handle_dio_timer(handle_dio_timer_data );
		       handle_dio_timer_flag = 0; 
		        // return;
                            
                     }  
                    

			
		cyg_thread_delay(1);   /////	
		  if (handle_dao_timer_flag)	{
		      handle_dao_timer(handle_dao_timer_data );
			  handle_dao_timer_flag = 0;
		  
		  }


                          /******************** unlock the Scheduler ************************/
    //  cyg_scheduler_unlock();
/****************************************************************/
			
}
/************************************************************************/
void
rpl_reset_periodic_timer(void)
{
  next_dis = RPL_DIS_INTERVAL - RPL_DIS_START_DELAY;
  ctimer_set(&periodic_timer, CLOCK_CONF_SECOND, handle_periodic_timer, NULL);
  PRINTF("RPL: rpl_reset_periodic_timer\n");
}
/************************************************************************/
static inline void
handle_periodic_timer_modified(cyg_handle_t alarm_handle, cyg_addrword_t data)
{
    if(!handle_periodic_timer_flag){
        handle_periodic_timer_flag = 1 ;
        handle_periodic_timer_data = data;
     }else
            return;
}		
/////////////////////////////////////////////////////
static void
handle_periodic_timer(  cyg_addrword_t data)
//handle_periodic_timer(void *ptr)
{
  rpl_purge_routes();
  rpl_recalculate_ranks();

  /* handle DIS */
#ifdef RPL_DIS_SEND
  next_dis++;
  if(rpl_get_dag(RPL_ANY_INSTANCE) == NULL && next_dis >= RPL_DIS_INTERVAL) {
    next_dis = 0;
    dis_output(NULL);
  }
#endif
 // ctimer_reset(&periodic_timer);
}
/************************************************************************/
static void
new_dio_interval(rpl_dag_t *dag)
{PRINTF("Hello, in new_dio_interval #%i\n", dag );
  unsigned long time;

  /* TODO: too small timer intervals for many cases */
  time = 1UL << dag->dio_intcurrent;
  PRINTF("Hello, dag->dio_intcurrent #%i\n", dag->dio_intcurrent);
  /* need to convert from milliseconds to CLOCK_TICKS */
  time = (time * CLOCK_CONF_SECOND) / 1000;
  dag->dio_next_delay = time;

  /* random number between I/2 and I */
  time = time >> 1;
  time += (time * random_rand()) / RANDOM_MAX;

  dag->dio_next_delay -= time;
  dag->dio_send = 1;

#if RPL_CONF_STATS
  /* keep some stats */
  dag->dio_totint++;
  dag->dio_totrecv += dag->dio_counter;
  ANNOTATE("#A rank=%u.%u(%u),stats=%d %d %d %d,color=%s\n",
	   DAG_RANK(dag->rank, dag),
           (10 * (dag->rank % dag->min_hoprankinc)) / dag->min_hoprankinc,
           dag->version,
           dag->dio_totint, dag->dio_totsend,
           dag->dio_totrecv,dag->dio_intcurrent,
	   dag->rank == ROOT_RANK ? "BLUE" : "ORANGE");
#endif /* RPL_CONF_STATS */

  /* reset the redundancy counter */
  dag->dio_counter = 0;

  /* schedule the timer */
  PRINTF("RPL: Scheduling DIO timer %lu ticks in future (Interval)\n", time);
  ctimer_set(&dag->dio_timer, time & 0xffff, handle_dio_timer_modified, dag);
  
}
/************************************************************************/
static inline void
handle_dio_timer_modified(cyg_handle_t alarm_handle, cyg_addrword_t data){

    if (!handle_dio_timer_flag){
         handle_dio_timer_flag = 1;
         handle_dio_timer_data = data ;
        }else
            return;

}
///////////////////////////////////////
static void
handle_dio_timer(cyg_addrword_t data)//cyg_handle_t alarm_handle, cyg_addrword_t data
{
  rpl_dag_t *dag;

  dag = (rpl_dag_t *)data;

  PRINTF("RPL: DIO Timer triggered\n");
  if(!dio_send_ok) {
    if(uip_ds6_get_link_local(ADDR_PREFERRED) != NULL) {
      dio_send_ok = 1;
    } else {
      PRINTF("RPL: Postponing DIO transmission since link local address is not ok\n");
      ctimer_set(&dag->dio_timer, CLOCK_CONF_SECOND, handle_dio_timer_modified, dag);
      return;
    }
  }

  if(dag->dio_send) {PRINTF("RPL: handle_dio_timer in dag->dio_send\n");
    /* send DIO if counter is less than desired redundancy */
    if(dag->dio_counter < dag->dio_redundancy) {
#if RPL_CONF_STATS
      dag->dio_totsend++;
#endif /* RPL_CONF_STATS */
      dio_output(dag, NULL);
    } else {
      PRINTF("RPL: Supressing DIO transmission (%d >= %d)\n",
             dag->dio_counter, dag->dio_redundancy);
    }
    dag->dio_send = 0;
    PRINTF("RPL: Scheduling DIO timer %u ticks in future (sent)\n",
           dag->dio_next_delay);
    ctimer_set(&dag->dio_timer, dag->dio_next_delay, handle_dio_timer_modified, dag);
  } else {
    /* check if we need to double interval */
    if(dag->dio_intcurrent < dag->dio_intmin + dag->dio_intdoubl) {
      dag->dio_intcurrent++;
      PRINTF("RPL: DIO Timer interval doubled %d\n", dag->dio_intcurrent);
    }
    new_dio_interval(dag);PRINTF("Hello, in handle_dio_timer_modified #%i\n", dag );
  }
}

/************************************************************************/
/* Resets the DIO timer in the DAG to its minimal interval. */
void
rpl_reset_dio_timer(rpl_dag_t *dag, cyg_uint8 force)
{
  /* only reset if not just reset or started */
  if(force || dag->dio_intcurrent > dag->dio_intmin) {
    dag->dio_counter = 0;
    dag->dio_intcurrent = dag->dio_intmin;
    new_dio_interval(dag);
    PRINTF("RPL: rpl_reset_dio_timer in new_dio_interval\n");
  }
#if RPL_CONF_STATS
  rpl_stats.resets++;
#endif
}
/************************************************************************/
static inline void
handle_dao_timer_modified(cyg_handle_t alarm_handle, cyg_addrword_t data){
          
	  if (!handle_dao_timer_flag){
            handle_dao_timer_flag = 1;
            handle_dao_timer_data = data ;
        }else
            return;

}
//////////////////////////////
static void
handle_dao_timer(cyg_addrword_t data)//cyg_handle_t alarm_handle, cyg_addrword_t data
{
  rpl_dag_t *dag;

  dag = (rpl_dag_t *)data;

  if (!dio_send_ok && uip_ds6_get_link_local(ADDR_PREFERRED) == NULL) {
    PRINTF("RPL: Postpone DAO transmission... \n");
    ctimer_set(&dag->dao_timer, CLOCK_CONF_SECOND, handle_dao_timer_modified, dag);
    return;
  }

  /* Send the DAO to the best parent. rpl-07 section C.2 lists the
     fan-out as being under investigation. */
  if(dag->preferred_parent != NULL) {
    PRINTF("RPL: handle_dao_timer - sending DAO\n");
    dao_output(dag->preferred_parent, DEFAULT_ROUTE_LIFETIME);
  } else {
    PRINTF("RPL: Could not find a parent to send a DAO to \n");
  }
  ctimer_stop(&dag->dao_timer);
}
/************************************************************************/
void
rpl_schedule_dao(rpl_dag_t *dag)
{ /*     /////////////////沒用到
         /////////////////改過的地方 
  cyg_tick_count_t expiration_time;
  expiration_time = etimer_expiration_time(&dag->dao_timer.etimer);
  */
  if(!ctimer_expired(&dag->dao_timer )) {/////////////////改過的地方 
    PRINTF("RPL: DAO timer already scheduled\n");
  } else {
    PRINTF("RPL: Scheduling DAO timer %u ticks in the future (%u %u)\n",
           (unsigned)DEFAULT_DAO_LATENCY / dag->rank,
           (unsigned)DEFAULT_DAO_LATENCY, (unsigned)dag->rank);
    ctimer_set(&dag->dao_timer, DEFAULT_DAO_LATENCY,
               handle_dao_timer_modified, dag);
  }
}
/************************************************************************/

