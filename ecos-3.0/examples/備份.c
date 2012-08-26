#include <cyg/kernel/kapi.h>
#include <cyg/hal/plf_io.h>
#include <stdio.h>
#include <cyg/io/spi_stm32.h>
#include <cyg/DW_config.h>     
#include <stdlib.h>
//==============================================
#include "cyg/net/uIPv6Stack/uIPv6/contiki-conf.h"
#include "cyg/net/uIPv6Stack/mac/frame802154.h"

//=============================================
#define STACK_SIZE 4096
#define ALARM_INTERVAL 2  //2 miliseconds
#define BEEPCON 0x0000080
#define LOOPNUM 0x800000

char stack[STACK_SIZE];
static cyg_thread thread_data;
static cyg_handle_t thread_handle;
static cyg_uint32 GLedPinspec; 
volatile static  cyg_uint8 blink;
volatile static cyg_uint8 coming ;

cyg_handle_t counter_handle;
cyg_handle_t alarm_handle;
cyg_alarm    alarm_object;

//register cyg_uint8 t;


void 
main_test(cyg_addrword_t data)
{ 
    printf("\n\n\n");
    printf("\t    *******************************\n");
    printf("\t    *     Hello! test.      *\n");
    printf("\t    *******************************\n\n\n");
    
    GLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 6, OUT_50MHZ , OUT_PUSHPULL     );
 // GLedPinspec =  CYGHWR_HAL_STM32_GPIO( B, 1, OUT_50MHZ , OUT_PUSHPULL     ); 
    CYGHWR_HAL_STM32_GPIO_SET(GLedPinspec);

   
  
     

    while(1)
        {
               
                
        }
}
void
cyg_start(void)
{
    // Create a main thread, so we can run the scheduler and have time 'pass'
    cyg_thread_create(10,                // Priority - just a number
                      main_test,              // entry
                      0,                 // entry parameter
                      "alarm",            // Name
                      &stack,         // Stack
                      STACK_SIZE,        // Size
                      &thread_handle, // Handle
                      &thread_data    // Thread data structure
            );
    cyg_thread_resume(thread_handle); // Start it
    cyg_scheduler_start();
}
