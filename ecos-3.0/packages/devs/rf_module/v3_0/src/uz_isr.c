#include <cyg/DW_config.h> 
#include "cyg/io/__uz_srf.h"

/*******************************************************************************
 Function Name: disable_rf_int
 Parameters: None
 Return Data: None
 Description: Disable the external interrupt by CPU interrupt mask
********************************************************************************/

unsigned char isRfIsrEnable=0;
void disable_rf_int(void){
	DisableRfIsr();
}

void enable_rf_int(void){
	EnableRfIsr();
}

volatile INTERRUPT_STS IntStatus;
void uz2400_isr_handler(void){ 
	
        *((UINT8 *)&IntStatus) = spi_sr(ISRSTS);
        
	if(IntStatus.TxN){  //Transmit frame success
	}

	if(IntStatus.TxG1){  
	}

	if(IntStatus.TxG2){      
	}

	if(IntStatus.Rx){   //Received a frame 
           // printf("Hello, rf isr  RXrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n");         
	}

	if(IntStatus.Sec){   //Received a secure frame , need key to decrypt
	}

	if(IntStatus.Timer){   
	}

	if(IntStatus.Wakeup){   
	}

	if(IntStatus.Sleep){   

	}

}
