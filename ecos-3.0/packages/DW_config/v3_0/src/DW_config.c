#include<cyg/DW_config.h>


cyg_handle_t isr_handle;
cyg_handle_t isr_handle_buttom;
cyg_interrupt isr_intr;
cyg_interrupt isr_intr_buttom;

static EXTI_InitTypeDef RF_EXTI_InitStructure;
static EXTI_InitTypeDef EXTI_InitStructure;

void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  cyg_uint32 tmp = 0;
  EXTI_TypeDef * EXTI = (EXTI_TypeDef *) CYGHWR_HAL_STM32_EXTI ;

  /* Check the parameters */
/*
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));  
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));
*/
  tmp = (cyg_uint32)CYGHWR_HAL_STM32_EXTI;
     
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
   
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
    
    tmp += EXTI_InitStruct->EXTI_Mode;
    
   
    *(volatile cyg_uint32 *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;
    
    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else 
    {
      tmp = (cyg_uint32)CYGHWR_HAL_STM32_EXTI;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(volatile cyg_uint32 *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(volatile cyg_uint32 *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }

  // printf("Hello, eCos world!\n");

}
    



void GPIO_EXTILineConfig(cyg_uint8 GPIO_PortSource, cyg_uint8 GPIO_PinSource)
{
  cyg_uint32 tmp = 0x00;
  AFIO_TypeDef * AFIO = (AFIO_TypeDef * ) CYGHWR_HAL_STM32_AFIO;
  /* Check the parameters */
/*
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
*/  
  tmp = ((cyg_uint32)0x0F) << (0x04 * (GPIO_PinSource & (cyg_uint8)0x03));
  //printf ("%x\n",tmp); 
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((cyg_uint32)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (cyg_uint8)0x03)));
}



// -------------------------------------------------------------------------
/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *   parameters in the SPI_InitStruct.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *   contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  cyg_uint16 tmpreg = 0;
  
  /* check the parameters */
/*
  assert_param(IS_SPI_ALL_PERIPH(SPIx));   
  
  //* Check the SPI parameters 

  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));
*/
/*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Get the SPIx CR1 value */
  tmpreg = SPIx->CR1;
  /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
  /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
  /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
  /* Set LSBFirst bit according to SPI_FirstBit value */
  /* Set BR bits according to SPI_BaudRatePrescaler value */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */
  tmpreg |= (cyg_uint16)((cyg_uint32)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                  SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |  
                  SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |  
                  SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
  /* Write to SPIx CR1 */
  SPIx->CR1 = tmpreg;
   
  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCFGR &= SPI_Mode_Select;		

/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}
//-------------------
/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
/*
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
*/  
  if (NewState != DISABLE)
  {    
    /* Enable the selected SPI peripheral */
    SPIx->CR1 |= CR1_SPE_Set;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR1 &= CR1_SPE_Reset;
  }
}
//===========

/**
  * @brief  Checks whether the specified SPI/I2S flag is set or not.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode 
  *   - 2 or 3 in I2S mode
  * @param  SPI_I2S_FLAG: specifies the SPI/I2S flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *     @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *     @arg SPI_I2S_FLAG_BSY: Busy flag.
  *     @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *     @arg SPI_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_FLAG_CRCERR: CRC Error flag.
  *     @arg I2S_FLAG_UDR: Underrun Error flag.
  *     @arg I2S_FLAG_CHSIDE: Channel Side flag.
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, cyg_uint16 SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
/*
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
  // Check the status of the specified SPI/I2S flag 
*/
  if ((SPIx->SR & SPI_I2S_FLAG) != (cyg_uint16)RESET)
  {
    /* SPI_I2S_FLAG is set */   
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_FLAG status */
  return  bitstatus;
}


/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode 
  *   - 2 or 3 in I2S mode
  * @param  Data : Data to be transmitted.
  * @retval None
  */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, cyg_uint16 Data)
{
  /* Check the parameters */
  //assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Write in the DR register the data to be sent */
  SPIx->DR = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral. 
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode 
  *   - 2 or 3 in I2S mode
  * @retval The value of the received data.
  */
cyg_uint16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)
{
  // Check the parameters          
/* 
 assert_param(IS_SPI_ALL_PERIPH(SPIx));
*/  
  /* Return the data in the DR register */
  return SPIx->DR;
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *   This parameter can be:
  *     @arg EXTI_Linex: External interrupt line x where x(0..19)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus(cyg_uint32 EXTI_Line)
{
  EXTI_TypeDef * EXTI = (EXTI_TypeDef *) CYGHWR_HAL_STM32_EXTI ;
  ITStatus bitstatus = RESET;
  cyg_uint32 enablestatus = 0;
  /* Check the parameters */
//  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (cyg_uint32)RESET) && (enablestatus != (cyg_uint32)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the EXTI line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */
void EXTI_ClearITPendingBit(cyg_uint32 EXTI_Line)
{
EXTI_TypeDef * EXTI = (EXTI_TypeDef *) CYGHWR_HAL_STM32_EXTI ;
  /* Check the parameters */
//  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
}

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *   parameters in the NVIC_InitStruct.
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *   the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  cyg_uint32 tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  SCB_Type* SCB = (SCB_Type*)(CYGARC_REG_NVIC_BASE+0x0D00) ;
  NVIC_Type* NVIC = (NVIC_Type*)(CYGARC_REG_NVIC_BASE + 0x100); // referenced to core_cm3.h file in ST firmware          
   // printf ("%x\n",(NVIC));
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (cyg_uint32)0x700))>> 0x08;
    
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (cyg_uint32)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;

    if (NVIC_InitStruct->NVIC_IRQChannel == 0x08){
  

    }

    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (cyg_uint32)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (cyg_uint8)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (cyg_uint32)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (cyg_uint8)0x1F);
  }
}


void EnableRfIsr(void){
	RF_EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&RF_EXTI_InitStructure);
}
void DisableRfIsr(void){
	RF_EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&RF_EXTI_InitStructure);
}


void SetupIsr(void){
/////////////////////////////////
        GPIO_EXTILineConfig(0x02,0x04);////////////////////////////////////////
	RF_EXTI_InitStructure.EXTI_Line = EXTI_Line4 ;/////////////////////////
	RF_EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	RF_EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EnableRfIsr();  

       //?建句柄
         cyg_interrupt_create(
            CYGNUM_HAL_INTERRUPT_EXTI4,
            0,                         // Priority - unused
           (cyg_addrword_t)CYGNUM_HAL_INTERRUPT_EXTI4, // Data item passed to ISR & DSR
            yy_isr,                    // ISR
            yy_dsr,                    // DSR
            &isr_handle,                   // handle to intr obj
            &isr_intr );                   // space for int obj

    //?中?挂接到中?句柄上
        cyg_interrupt_attach(isr_handle);
    
    //使能中?
       cyg_interrupt_unmask(CYGNUM_HAL_INTERRUPT_EXTI4);
///////////////////////////////////////////////////////////

       GPIO_EXTILineConfig(0x02,0x02);
		EXTI_InitStructure.EXTI_Line = EXTI_Line2;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

      cyg_interrupt_create(
            CYGNUM_HAL_INTERRUPT_EXTI2,
            0,                         // Priority - unused
           (cyg_addrword_t)CYGNUM_HAL_INTERRUPT_EXTI2, // Data item passed to ISR & DSR
            buttom_isr,                    // ISR
            buttom_dsr,                    // DSR
            &isr_handle_buttom,                   // handle to intr obj
            &isr_intr_buttom);                   // space for int obj

    //?中?挂接到中?句柄上
        cyg_interrupt_attach(isr_handle_buttom);
    
    //使能中?
       cyg_interrupt_unmask(CYGNUM_HAL_INTERRUPT_EXTI2);



}
void SetupRfSpi(void){
        SPI_TypeDef* SPI1 = (SPI_TypeDef *) CYGHWR_HAL_STM32_SPI1;
        SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low ;
	SPI_InitStructure.SPI_CRCPolynomial=0;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;

	SPI_Init(SPI1,&SPI_InitStructure);
        SPI_Cmd(SPI1,ENABLE);
}

void SetupIO(void){
    
   CYGHWR_HAL_STM32_GPIO_SET(RF_SEL_PinSpec);              // RF_SEL
   CYGHWR_HAL_STM32_GPIO_OUT(RF_SEL_PinSpec,Bit_SET);       
                                                            
   CYGHWR_HAL_STM32_GPIO_SET(RF_RESETN_PinSpec);           // RF_RESETN 
   CYGHWR_HAL_STM32_GPIO_OUT(RF_RESETN_PinSpec,Bit_SET);   
                                                            
   CYGHWR_HAL_STM32_GPIO_SET(PERIPH_POWER_PinSpec);        // periph power
   CYGHWR_HAL_STM32_GPIO_OUT(PERIPH_POWER_PinSpec,Bit_SET);
   
   CYGHWR_HAL_STM32_GPIO_SET(RF_WAKEUP_PinSpec);           // RF wakeup
   CYGHWR_HAL_STM32_GPIO_OUT(RF_WAKEUP_PinSpec,Bit_SET);   
    
   CYGHWR_HAL_STM32_GPIO_SET(RF_SCK_PinSpec);              //RF SCK
   CYGHWR_HAL_STM32_GPIO_SET(RF_MISO_PinSpec);             //RF MISO
   CYGHWR_HAL_STM32_GPIO_SET(RF_MOSI_PinSpec);             //RF MOSI

   CYGHWR_HAL_STM32_GPIO_SET(RF_INT_PinSpec);              //RF INT

   /*--------------- LED -------------------*/
   CYGHWR_HAL_STM32_GPIO_SET (LED_G_PinSpec);
   CYGHWR_HAL_STM32_GPIO_SET (LED_B_PinSpec);
   CYGHWR_HAL_STM32_GPIO_SET (LED_R_PinSpec); 
   CYGHWR_HAL_STM32_GPIO_SET (LED_Y_PinSpec);               //Yello LED

   /*------------ User Buttom-------------*/
    CYGHWR_HAL_STM32_GPIO_SET(UseButtomPinSpec);
}
//=====================
extern cyg_handle_t uz2400_handle;


 void
yy_dsr(cyg_vector_t vector, cyg_ucount32 count, cyg_addrword_t data)
{
    int priv_data = (int)data;
//printf("Hello, dsr\n");
    uz2400_isr_handler();
cyg_thread_set_priority(uz2400_handle,5);
//cyg_thread_delay(1);   
cyg_thread_set_priority(uz2400_handle,10);

//uz_rx_flush();////////
EXTI_ClearITPendingBit(EXTI_Line4);
    cyg_interrupt_unmask(priv_data);//解除中?屏蔽
}

cyg_uint32    
yy_isr(cyg_vector_t vector, cyg_addrword_t data)
{
    int priv_data = (int)data;
 //   printf("Hello, isr\n");
    cyg_interrupt_mask(priv_data);        
    cyg_interrupt_acknowledge(priv_data);

//uz2400_isr_handler(); 
    return (CYG_ISR_HANDLED|CYG_ISR_CALL_DSR);   
}
//===========================


static void(*buttom)(void);
static ButtomCallback(){
   if (buttom!=NULL){
         buttom();
   }
}

void SetupButtomCallback(void(*s)){
    buttom = s;

}

 void
buttom_dsr(cyg_vector_t vector, cyg_ucount32 count, cyg_addrword_t data)
{
    int priv_data = (int)data;
    printf("buttom_dsr\n");
    ButtomCallback();
//    SetupIsr();
  //SetupIO();
//uz2400_init();
//uz_init();
//uz_rx_flush();
//uz_rx_normal_mode();
/*
   uz_init();
	
	uz_enable_ext_wakeup();
      
	uz_set_channel(26);
        uz2400_set_pan_addr(0xffff, 0x0000, NULL);
 	uz_set_tx_power(0);
        uz_rx_normal_mode();

*/cyg_thread_delay(1);
    cyg_interrupt_unmask(priv_data);//解除中?屏蔽
}

cyg_uint32
buttom_isr(cyg_vector_t vector, cyg_addrword_t data)
{
    int priv_data = (int)data;
 //   printf("Hello, isr\n");
    cyg_interrupt_mask(priv_data);        
    cyg_interrupt_acknowledge(priv_data);

 
    return (CYG_ISR_HANDLED|CYG_ISR_CALL_DSR);   
}
//==================================================
void MyeCosAlarm( 
                  MyeCosAlram_t* MyAlarm,
		  cyg_tick_count_t alarm_period,
		  cyg_addrword_t data,
				  void* alarm_func ){


           if (!MyAlarm->initialized){
                   cyg_clock_to_counter(cyg_real_time_clock(), &(MyAlarm->counter_handle));
                   cyg_alarm_create((MyAlarm->counter_handle), alarm_func, data, &(MyAlarm->alarm_handle), &(MyAlarm->alarm_object));
                   cyg_alarm_initialize((MyAlarm->alarm_handle), cyg_current_time() + alarm_period, alarm_period);
		   cyg_alarm_enable((MyAlarm->alarm_handle));

              
                   MyAlarm->initialized = 1;
           }else{
                   cyg_alarm_delete((MyAlarm->alarm_handle)); 
                   cyg_alarm_create((MyAlarm->counter_handle), alarm_func, data, &(MyAlarm->alarm_handle), &(MyAlarm->alarm_object));/////////
                   cyg_alarm_initialize((MyAlarm->alarm_handle), cyg_current_time() + alarm_period, alarm_period);
                   cyg_alarm_enable((MyAlarm->alarm_handle));
            }


/*
            cyg_clock_to_counter(cyg_real_time_clock(), &(MyAlarm->counter_handle));
            cyg_alarm_create((MyAlarm->counter_handle), alarm_func, data, &(MyAlarm->alarm_handle), &(MyAlarm->alarm_object));
            cyg_alarm_initialize((MyAlarm->alarm_handle), cyg_current_time() + alarm_period, alarm_period);
            cyg_alarm_enable((MyAlarm->alarm_handle));	  
*/
}
//===================================================



void testfuc(void){
printf("Hello, testfunc!\n");
}
