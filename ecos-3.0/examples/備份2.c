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
#define ALARM_INTERVAL 2000  //2 miliseconds
#define BEEPCON 0x0000080
#define LOOPNUM 0x800000

char stackA[STACK_SIZE];
char stackB[STACK_SIZE];
static cyg_thread thread_dataA,
                  thread_dataB;
static cyg_handle_t thread_handleA,
                    thread_handleB ;
static cyg_uint32 GLedPinspec; 
volatile static  cyg_uint8 blink;
volatile static cyg_uint8 coming ;

cyg_handle_t counter_handle;
cyg_handle_t alarm_handle;
cyg_alarm    alarm_object;

//register cyg_uint8 t;
void alarm_func(cyg_handle_t alarm_handle, cyg_addrword_t data)
{
    printf("Alarm!\n");
}

void 
main_testA(cyg_addrword_t data)
{ 
    printf("\n\n\n");
    printf("\t    *******************************\n");
    printf("\t    *     Hello! test.      *\n");
    printf("\t    *******************************\n\n\n");
    
    GLedPinspec =  CYGHWR_HAL_STM32_GPIO( C, 6, OUT_50MHZ , OUT_PUSHPULL     );
 // GLedPinspec =  CYGHWR_HAL_STM32_GPIO( B, 1, OUT_50MHZ , OUT_PUSHPULL     ); 
    CYGHWR_HAL_STM32_GPIO_SET(GLedPinspec);

   //將時鐘轉換為計數器。cyg_real_time_clock()函數獲取系統即時時鐘(RTC)。即時時鐘用於系統的延時、阻塞等待等操作。
    cyg_clock_to_counter(cyg_real_time_clock(), &counter_handle);
    
	//創建警告器
    cyg_alarm_create(counter_handle, alarm_func, 0, &alarm_handle, &alarm_object);
    
	//初始化警告器
    cyg_alarm_initialize(alarm_handle, cyg_current_time() + ALARM_INTERVAL, ALARM_INTERVAL);
    
	//使能警告器
    cyg_alarm_enable(alarm_handle);
  
     

    while(1)
        {
               
                
        }
}

void 
main_testB(cyg_addrword_t data){



while(1)
        {
               hal_delay_us(1600000);
               printf("threadB!\n");
                
        }


}


void
cyg_start(void)
{
    // Create a main thread, so we can run the scheduler and have time 'pass'
    cyg_thread_create(10,                // Priority - just a number
                      main_testA,              // entry
                      0,                 // entry parameter
                      "alarm",            // Name
                      &stackA,         // Stack
                      STACK_SIZE,        // Size
                      &thread_handleA, // Handle
                      &thread_dataA    // Thread data structure
            );

     cyg_thread_create(10,                // Priority - just a number
                      main_testB,              // entry
                      0,                 // entry parameter
                      "testB",            // Name
                      &stackB,         // Stack
                      STACK_SIZE,        // Size
                      &thread_handleB, // Handle
                      &thread_dataB    // Thread data structure
            ); 

    cyg_thread_resume(thread_handleA); // Start it


    cyg_thread_resume(thread_handleB);
    cyg_scheduler_start();
}
