#ifndef DW_CONFIG_H
#define DW_CONFIG_H
#include <stdio.h>
#include "cyg/infra/cyg_type.h"
#include <cyg/hal/var_io.h>   
#include <cyg/hal/hal_io.h>       
//===============================   
#include <cyg/io/__uz2400.h>
#include <cyg/io/__uz_type.h>
#include <cyg/io/__uz_srf.h>
#include <cyg/io/rf.h>
//================================
#include"cyg/kernel/kapi.h"
/****************************************************************************/
//  Usage : #include <cyg/DW_config.h> 
//
/****************************************************************************/
//----------------------self #define--------------------
/* IRQ Channels --------------------------------------------------------------*/
#define WWDG_IRQChannel              ((cyg_uint8)0x00)  /* Window WatchDog Interrupt */
#define PVD_IRQChannel               ((cyg_uint8)0x01)  /* PVD through EXTI Line detection Interrupt */
#define TAMPER_IRQChannel            ((cyg_uint8)0x02)  /* Tamper Interrupt */
#define RTC_IRQChannel               ((cyg_uint8)0x03)  /* RTC global Interrupt */
#define FLASH_IRQChannel             ((cyg_uint8)0x04)  /* FLASH global Interrupt */
#define RCC_IRQChannel               ((cyg_uint8)0x05)  /* RCC global Interrupt */
#define EXTI0_IRQChannel             ((cyg_uint8)0x06)  /* EXTI Line0 Interrupt */
#define EXTI1_IRQChannel             ((cyg_uint8)0x07)  /* EXTI Line1 Interrupt */
#define EXTI2_IRQChannel             ((cyg_uint8)0x08)  /* EXTI Line2 Interrupt */
#define EXTI3_IRQChannel             ((cyg_uint8)0x09)  /* EXTI Line3 Interrupt */
#define EXTI4_IRQChannel             ((cyg_uint8)0x0A)  /* EXTI Line4 Interrupt */
#define DMA1_Channel1_IRQChannel     ((cyg_uint8)0x0B)  /* DMA1 Channel 1 global Interrupt */
#define DMA1_Channel2_IRQChannel     ((cyg_uint8)0x0C)  /* DMA1 Channel 2 global Interrupt */
#define DMA1_Channel3_IRQChannel     ((cyg_uint8)0x0D)  /* DMA1 Channel 3 global Interrupt */
#define DMA1_Channel4_IRQChannel     ((cyg_uint8)0x0E)  /* DMA1 Channel 4 global Interrupt */
#define DMA1_Channel5_IRQChannel     ((cyg_uint8)0x0F)  /* DMA1 Channel 5 global Interrupt */
#define DMA1_Channel6_IRQChannel     ((cyg_uint8)0x10)  /* DMA1 Channel 6 global Interrupt */
#define DMA1_Channel7_IRQChannel     ((cyg_uint8)0x11)  /* DMA1 Channel 7 global Interrupt */
#define ADC1_2_IRQChannel            ((cyg_uint8)0x12)  /* ADC1 et ADC2 global Interrupt */
#define USB_HP_CAN_TX_IRQChannel     ((cyg_uint8)0x13)  /* USB High Priority or CAN TX Interrupts */
#define USB_LP_CAN_RX0_IRQChannel    ((cyg_uint8)0x14)  /* USB Low Priority or CAN RX0 Interrupts */
#define CAN_RX1_IRQChannel           ((cyg_uint8)0x15)  /* CAN RX1 Interrupt */
#define CAN_SCE_IRQChannel           ((cyg_uint8)0x16)  /* CAN SCE Interrupt */
#define EXTI9_5_IRQChannel           ((cyg_uint8)0x17)  /* External Line[9:5] Interrupts */
#define TIM1_BRK_IRQChannel          ((cyg_uint8)0x18)  /* TIM1 Break Interrupt */
#define TIM1_UP_IRQChannel           ((cyg_uint8)0x19)  /* TIM1 Update Interrupt */
#define TIM1_TRG_COM_IRQChannel      ((cyg_uint8)0x1A)  /* TIM1 Trigger and Commutation Interrupt */
#define TIM1_CC_IRQChannel           ((cyg_uint8)0x1B)  /* TIM1 Capture Compare Interrupt */
#define TIM2_IRQChannel              ((cyg_uint8)0x1C)  /* TIM2 global Interrupt */
#define TIM3_IRQChannel              ((cyg_uint8)0x1D)  /* TIM3 global Interrupt */
#define TIM4_IRQChannel              ((cyg_uint8)0x1E)  /* TIM4 global Interrupt */
#define I2C1_EV_IRQChannel           ((cyg_uint8)0x1F)  /* I2C1 Event Interrupt */
#define I2C1_ER_IRQChannel           ((cyg_uint8)0x20)  /* I2C1 Error Interrupt */
#define I2C2_EV_IRQChannel           ((cyg_uint8)0x21)  /* I2C2 Event Interrupt */
#define I2C2_ER_IRQChannel           ((cyg_uint8)0x22)  /* I2C2 Error Interrupt */
#define SPI1_IRQChannel              ((cyg_uint8)0x23)  /* SPI1 global Interrupt */
#define SPI2_IRQChannel              ((cyg_uint8)0x24)  /* SPI2 global Interrupt */
#define USART1_IRQChannel            ((cyg_uint8)0x25)  /* USART1 global Interrupt */
#define USART2_IRQChannel            ((cyg_uint8)0x26)  /* USART2 global Interrupt */
#define USART3_IRQChannel            ((cyg_uint8)0x27)  /* USART3 global Interrupt */
#define EXTI15_10_IRQChannel         ((cyg_uint8)0x28)  /* External Line[15:10] Interrupts */
#define RTCAlarm_IRQChannel          ((cyg_uint8)0x29)  /* RTC Alarm through EXTI Line Interrupt */
#define USBWakeUp_IRQChannel         ((cyg_uint8)0x2A)  /* USB WakeUp from suspend through EXTI Line Interrupt */
#define TIM8_BRK_IRQChannel          ((cyg_uint8)0x2B)  /* TIM8 Break Interrupt */
#define TIM8_UP_IRQChannel           ((cyg_uint8)0x2C)  /* TIM8 Update Interrupt */
#define TIM8_TRG_COM_IRQChannel      ((cyg_uint8)0x2D)  /* TIM8 Trigger and Commutation Interrupt */
#define TIM8_CC_IRQChannel           ((cyg_uint8)0x2E)  /* TIM8 Capture Compare Interrupt */
#define ADC3_IRQChannel              ((cyg_uint8)0x2F)  /* ADC3 global Interrupt */
#define FSMC_IRQChannel              ((cyg_uint8)0x30)  /* FSMC global Interrupt */
#define SDIO_IRQChannel              ((cyg_uint8)0x31)  /* SDIO global Interrupt */
#define TIM5_IRQChannel              ((cyg_uint8)0x32)  /* TIM5 global Interrupt */
#define SPI3_IRQChannel              ((cyg_uint8)0x33)  /* SPI3 global Interrupt */
#define UART4_IRQChannel             ((cyg_uint8)0x34)  /* UART4 global Interrupt */
#define UART5_IRQChannel             ((cyg_uint8)0x35)  /* UART5 global Interrupt */
#define TIM6_IRQChannel              ((cyg_uint8)0x36)  /* TIM6 global Interrupt */
#define TIM7_IRQChannel              ((cyg_uint8)0x37)  /* TIM7 global Interrupt */
#define DMA2_Channel1_IRQChannel     ((cyg_uint8)0x38)  /* DMA2 Channel 1 global Interrupt */
#define DMA2_Channel2_IRQChannel     ((cyg_uint8)0x39)  /* DMA2 Channel 2 global Interrupt */
#define DMA2_Channel3_IRQChannel     ((cyg_uint8)0x3A)  /* DMA2 Channel 3 global Interrupt */
#define DMA2_Channel4_5_IRQChannel   ((cyg_uint8)0x3B)  /* DMA2 Channel 4 and DMA2 Channel 5 global Interrupt */

#define SENSOR_I2C				I2C2

//----------------EXTI------------------
#define EXTI_Line0       ((cyg_uint32)0x00001)  /*!< External interrupt line 0 */
#define EXTI_Line1       ((cyg_uint32)0x00002)  /*!< External interrupt line 1 */
#define EXTI_Line2       ((cyg_uint32)0x00004)  /*!< External interrupt line 2 */
#define EXTI_Line3       ((cyg_uint32)0x00008)  /*!< External interrupt line 3 */
#define EXTI_Line4       ((cyg_uint32)0x00010)  /*!< External interrupt line 4 */
#define EXTI_Line5       ((cyg_uint32)0x00020)  /*!< External interrupt line 5 */
#define EXTI_Line6       ((cyg_uint32)0x00040)  /*!< External interrupt line 6 */
#define EXTI_Line7       ((cyg_uint32)0x00080)  /*!< External interrupt line 7 */
#define EXTI_Line8       ((cyg_uint32)0x00100)  /*!< External interrupt line 8 */
#define EXTI_Line9       ((cyg_uint32)0x00200)  /*!< External interrupt line 9 */
#define EXTI_Line10      ((cyg_uint32)0x00400)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((cyg_uint32)0x00800)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((cyg_uint32)0x01000)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((cyg_uint32)0x02000)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((cyg_uint32)0x04000)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((cyg_uint32)0x08000)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((cyg_uint32)0x10000)  /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17      ((cyg_uint32)0x20000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18      ((cyg_uint32)0x40000)  /*!< External interrupt line 18 Connected to the USB Device/USB OTG FS
                                                   Wakeup from suspend event */
#define EXTI_Line19      ((cyg_uint32)0x80000)  /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */ 



//------------------SPI_BaudRatePrescaler-------------------------
#define SPI_BaudRatePrescaler_2         ((cyg_uint16)0x0000)
#define SPI_BaudRatePrescaler_4         ((cyg_uint16)0x0008)
#define SPI_BaudRatePrescaler_8         ((cyg_uint16)0x0010)
#define SPI_BaudRatePrescaler_16        ((cyg_uint16)0x0018)
#define SPI_BaudRatePrescaler_32        ((cyg_uint16)0x0020)
#define SPI_BaudRatePrescaler_64        ((cyg_uint16)0x0028)
#define SPI_BaudRatePrescaler_128       ((cyg_uint16)0x0030)
#define SPI_BaudRatePrescaler_256       ((cyg_uint16)0x0038)


/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                  ((cyg_uint16)0x0000)
#define SPI_CPHA_2Edge                  ((cyg_uint16)0x0001)
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                    ((cyg_uint16)0x0000)
#define SPI_CPOL_High                   ((cyg_uint16)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_data_size 
  * @{
  */

#define SPI_DataSize_16b                ((cyg_uint16)0x0800)
#define SPI_DataSize_8b                 ((cyg_uint16)0x0000)

/**
  * @}
  */
/** @defgroup SPI_data_direction 
  * @{
  */
  
#define SPI_Direction_2Lines_FullDuplex ((cyg_uint16)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((cyg_uint16)0x0400)
#define SPI_Direction_1Line_Rx          ((cyg_uint16)0x8000)
#define SPI_Direction_1Line_Tx          ((cyg_uint16)0xC000)
/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */

#define SPI_FirstBit_MSB                ((cyg_uint16)0x0000)
#define SPI_FirstBit_LSB                ((cyg_uint16)0x0080)
/**
  * @}
  */

/** @defgroup SPI_mode 
  * @{
  */

#define SPI_Mode_Master                 ((cyg_uint16)0x0104)
#define SPI_Mode_Slave                  ((cyg_uint16)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */

#define SPI_NSS_Soft                    ((cyg_uint16)0x0200)
#define SPI_NSS_Hard                    ((cyg_uint16)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */ 
/* SPI registers Masks */
#define CR1_CLEAR_Mask       ((cyg_uint16)0x3040)
#define I2SCFGR_CLEAR_Mask   ((cyg_uint16)0xF040)


/* SPI or I2S mode selection masks */
#define SPI_Mode_Select      ((cyg_uint16)0xF7FF)
#define I2S_Mode_Select      ((cyg_uint16)0x0800) 

/* SPI SPE mask */
#define CR1_SPE_Set          ((cyg_uint16)0x0040)
#define CR1_SPE_Reset        ((cyg_uint16)0xFFBF)



/** @defgroup SPI_I2S_flags_definition 
  * @{
  */ 

#define SPI_I2S_FLAG_RXNE               ((cyg_uint16)0x0001)
#define SPI_I2S_FLAG_TXE                ((cyg_uint16)0x0002)
#define I2S_FLAG_CHSIDE                 ((cyg_uint16)0x0004)
#define I2S_FLAG_UDR                    ((cyg_uint16)0x0008)
#define SPI_FLAG_CRCERR                 ((cyg_uint16)0x0010)
#define SPI_FLAG_MODF                   ((cyg_uint16)0x0020)
#define SPI_I2S_FLAG_OVR                ((cyg_uint16)0x0040)
#define SPI_I2S_FLAG_BSY                ((cyg_uint16)0x0080)
#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE))

//-----------------------------------Chi-De's config.h--------------------------//


/*******RF PinSpec******/
#define RF_SPI				(SPI_TypeDef *)	 CYGHWR_HAL_STM32_SPI1
#define RF_SEL_PinSpec                  CYGHWR_HAL_STM32_GPIO( A, 4, OUT_50MHZ , OUT_PUSHPULL)
#define RF_SCK_PinSpec                  CYGHWR_HAL_STM32_GPIO( A, 5, OUT_50MHZ , ALT_PUSHPULL)
#define RF_MISO_PinSpec                 CYGHWR_HAL_STM32_GPIO( A, 6, OUT_50MHZ , ALT_OPENDRAIN)
#define RF_MOSI_PinSpec                 CYGHWR_HAL_STM32_GPIO( A, 7, OUT_50MHZ , ALT_PUSHPULL)
#define RF_RESETN_PinSpec               CYGHWR_HAL_STM32_GPIO( B, 2, OUT_50MHZ , OUT_PUSHPULL)
#define PERIPH_POWER_PinSpec            CYGHWR_HAL_STM32_GPIO( C, 1, OUT_50MHZ , OUT_PUSHPULL) /****** important, peripheral power **********/
#define RF_INT_PinSpec                  CYGHWR_HAL_STM32_GPIO( C, 4, IN , PULLUP )
#define RF_WAKEUP_PinSpec               CYGHWR_HAL_STM32_GPIO( C, 5, OUT_50MHZ , OUT_PUSHPULL)

/****User Buttom*************/
#define UseButtomPinSpec                CYGHWR_HAL_STM32_GPIO( C, 2, IN , PULLUP )    

/*******LED PinSpec******/
#define LED_G_PinSpec                   CYGHWR_HAL_STM32_GPIO( C, 6, OUT_50MHZ , OUT_PUSHPULL)
#define LED_Y_PinSpec                   CYGHWR_HAL_STM32_GPIO( C, 7, OUT_50MHZ , OUT_PUSHPULL)
#define LED_B_PinSpec                   CYGHWR_HAL_STM32_GPIO( C, 8, OUT_50MHZ , OUT_PUSHPULL)
#define LED_R_PinSpec                   CYGHWR_HAL_STM32_GPIO( C, 9, OUT_50MHZ , OUT_PUSHPULL)

//#define wait_uz2400()                   hal_delay_us(3)
#define uz2400_select()	                CYGHWR_HAL_STM32_GPIO_OUT(RF_SEL_PinSpec,Bit_RESET)
#define uz2400_deselect()	        CYGHWR_HAL_STM32_GPIO_OUT(RF_SEL_PinSpec,Bit_SET)
#define uz2400_wait_spi_w_ready()	while(SPI_I2S_GetFlagStatus(RF_SPI,SPI_I2S_FLAG_TXE)==RESET)
#define uz2400_wait_spi_r_ready()	while(SPI_I2S_GetFlagStatus(RF_SPI,SPI_I2S_FLAG_RXNE)==RESET)

 
#define uz2400_wakeup_set()		CYGHWR_HAL_STM32_GPIO_OUT(RF_WAKEUP_PinSpec ,Bit_SET) 
#define uz2400_wakeup_reset()           CYGHWR_HAL_STM32_GPIO_OUT(RF_WAKEUP_PinSpec ,Bit_RESET) 

#define RF_RESET_PinSpec                CYGHWR_HAL_STM32_GPIO( B, 2, OUT_50MHZ , OUT_PUSHPULL     )
#define uz2400_reset_set()              CYGHWR_HAL_STM32_GPIO_OUT(RF_RESET_PinSpec ,Bit_SET) 
#define uz2400_reset_reset()           CYGHWR_HAL_STM32_GPIO_OUT(RF_RESET_PinSpec ,Bit_RESET) 


//----------------------Contiki process #define-------------------------------------------------------
#define PROCESS_EVENT_NONE            0x80
#define PROCESS_EVENT_INIT            0x81
#define PROCESS_EVENT_POLL            0x82
#define PROCESS_EVENT_EXIT            0x83
#define PROCESS_EVENT_SERVICE_REMOVED 0x84
#define PROCESS_EVENT_CONTINUE        0x85
#define PROCESS_EVENT_MSG             0x86
#define PROCESS_EVENT_EXITED          0x87
#define PROCESS_EVENT_TIMER           0x88
#define PROCESS_EVENT_COM             0x89
#define PROCESS_EVENT_MAX             0x8a

//----------------------self typedef-------------------------------------------------------

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum { Bit_RESET = 0,  Bit_SET }BitAction;
typedef enum {ERROR = 0, NOT_ERROR = !ERROR} ErrorStatus;

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,        
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

/** 
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  volatile cyg_uint32 IMR;
  volatile cyg_uint32 EMR;
  volatile cyg_uint32 RTSR;
  volatile cyg_uint32 FTSR;
  volatile cyg_uint32 SWIER;
  volatile cyg_uint32 PR;
} EXTI_TypeDef;




typedef struct
{
  cyg_uint8 NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type 
                                                   (For the complete STM32 Devices IRQ Channels list, please
                                                    refer to stm32f10x.h file) */

  cyg_uint8 NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  cyg_uint8 NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled. 
                                                   This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;

/** @addtogroup CMSIS_CM3_NVIC CMSIS CM3 NVIC
  memory mapped structure for Nested Vectored Interrupt Controller (NVIC)
  @{
 */
typedef struct
{
  volatile cyg_uint32 ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
       cyg_uint32 RESERVED0[24];                                   
  volatile cyg_uint32 ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
       cyg_uint32 RSERVED1[24];                                    
  volatile cyg_uint32 ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
       cyg_uint32 RESERVED2[24];                                   
  volatile cyg_uint32 ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
       cyg_uint32 RESERVED3[24];                                   
  volatile cyg_uint32 IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
       cyg_uint32 RESERVED4[56];                                   
  volatile cyg_uint8  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
       cyg_uint32 RESERVED5[644];                                  
  volatile cyg_uint32 STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
}  NVIC_Type;                                               
/*@}*/ /* end of group CMSIS_CM3_NVIC */



      



typedef struct
{
  cyg_uint32 EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */
   
  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */ 
}EXTI_InitTypeDef;


typedef struct
{
  cyg_uint16 SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be any combination of @ref SPI_data_direction */

  cyg_uint16 SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be any combination of @ref SPI_mode */

  cyg_uint16 SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be any combination of @ref SPI_data_size */

  cyg_uint16 SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be any combination of @ref SPI_Clock_Polarity */

  cyg_uint16 SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be any combination of @ref SPI_Clock_Phase */

  cyg_uint16 SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be any combination of @ref SPI_Slave_Select_management */
 
  cyg_uint16 SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be any combination of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  cyg_uint16 SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be any combination of @ref SPI_MSB_LSB_transmission */

  cyg_uint16 SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;


/** 
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  volatile cyg_uint16 CR1;
  cyg_uint16  RESERVED0;
  volatile cyg_uint16 CR2;
  cyg_uint16  RESERVED1;
  volatile cyg_uint16 SR;
  cyg_uint16  RESERVED2;
  volatile cyg_uint16 DR;
  cyg_uint16  RESERVED3;
  volatile cyg_uint16 CRCPR;
  cyg_uint16  RESERVED4;
  volatile cyg_uint16 RXCRCR;
  cyg_uint16  RESERVED5;
  volatile cyg_uint16 TXCRCR;
  cyg_uint16  RESERVED6;
  volatile cyg_uint16 I2SCFGR;
  cyg_uint16  RESERVED7;
  volatile cyg_uint16 I2SPR;
  cyg_uint16  RESERVED8;  
} SPI_TypeDef;


/** 
  * @brief Alternate Function I/O
  */
 
typedef struct
{
  volatile cyg_uint32 EVCR;
  volatile cyg_uint32 MAPR;
  volatile cyg_uint32 EXTICR[4];
} AFIO_TypeDef;


/** 
  * @brief TIM
  */

typedef struct
{
  volatile cyg_uint16 CR1;
  cyg_uint16  RESERVED0;
  volatile cyg_uint16 CR2;
  cyg_uint16  RESERVED1;
  volatile cyg_uint16 SMCR;
  cyg_uint16  RESERVED2;
  volatile cyg_uint16 DIER;
  cyg_uint16  RESERVED3;
  volatile cyg_uint16 SR;
  cyg_uint16  RESERVED4;
  volatile cyg_uint16 EGR;
  cyg_uint16  RESERVED5;
  volatile cyg_uint16 CCMR1;
  cyg_uint16  RESERVED6;
  volatile cyg_uint16 CCMR2;
  cyg_uint16  RESERVED7;
  volatile cyg_uint16 CCER;
  cyg_uint16  RESERVED8;
  volatile cyg_uint16 CNT;
  cyg_uint16  RESERVED9;
  volatile cyg_uint16 PSC;
  cyg_uint16  RESERVED10;
  volatile cyg_uint16 ARR;
  cyg_uint16  RESERVED11;
  volatile cyg_uint16 RCR;
  cyg_uint16  RESERVED12;
  volatile cyg_uint16 CCR1;
  cyg_uint16  RESERVED13;
  volatile cyg_uint16 CCR2;
  cyg_uint16  RESERVED14;
  volatile cyg_uint16 CCR3;
  cyg_uint16  RESERVED15;
  volatile cyg_uint16 CCR4;
  cyg_uint16  RESERVED16;
  volatile cyg_uint16 BDTR;
  cyg_uint16  RESERVED17;
  volatile cyg_uint16 DCR;
  cyg_uint16  RESERVED18;
  volatile cyg_uint16 DMAR;
  cyg_uint16  RESERVED19;
} TIM_TypeDef;

typedef struct
{
  volatile cyg_uint32 CR;
  volatile cyg_uint32 CFGR;
  volatile cyg_uint32 CIR;
  volatile cyg_uint32 APB2RSTR;
  volatile cyg_uint32 APB1RSTR;
  volatile cyg_uint32 AHBENR;
  volatile cyg_uint32 APB2ENR;
  volatile cyg_uint32 APB1ENR;
  volatile cyg_uint32 BDCR;
  volatile cyg_uint32 CSR;
#ifdef STM32F10X_CL  
  volatile cyg_uint32 AHBRSTR;
  volatile cyg_uint32 CFGR2;
#endif /* STM32F10X_CL */ 
} RCC_TypeDef;

/** @addtogroup CMSIS_CM3_SCB CMSIS CM3 SCB
  memory mapped structure for System Control Block (SCB)
  @{
 */
typedef struct
{
  volatile  cyg_uint32 CPUID;                        /*!< Offset: 0x00  CPU ID Base Register                                  */
  volatile cyg_uint32 ICSR;                         /*!< Offset: 0x04  Interrupt Control State Register                      */
  volatile cyg_uint32 VTOR;                         /*!< Offset: 0x08  Vector Table Offset Register                          */
  volatile cyg_uint32 AIRCR;                        /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
  volatile cyg_uint32 SCR;                          /*!< Offset: 0x10  System Control Register                               */
  volatile cyg_uint32 CCR;                          /*!< Offset: 0x14  Configuration Control Register                        */
  volatile cyg_uint8  SHP[12];                      /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile cyg_uint32 SHCSR;                        /*!< Offset: 0x24  System Handler Control and State Register             */
  volatile cyg_uint32 CFSR;                         /*!< Offset: 0x28  Configurable Fault Status Register                    */
  volatile cyg_uint32 HFSR;                         /*!< Offset: 0x2C  Hard Fault Status Register                            */
  volatile cyg_uint32 DFSR;                         /*!< Offset: 0x30  Debug Fault Status Register                           */
  volatile cyg_uint32 MMFAR;                        /*!< Offset: 0x34  Mem Manage Address Register                           */
  volatile cyg_uint32 BFAR;                         /*!< Offset: 0x38  Bus Fault Address Register                            */
  volatile cyg_uint32 AFSR;                         /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
  volatile  cyg_uint32 PFR[2];                       /*!< Offset: 0x40  Processor Feature Register                            */
  volatile  cyg_uint32 DFR;                          /*!< Offset: 0x48  Debug Feature Register                                */
  volatile  cyg_uint32 ADR;                          /*!< Offset: 0x4C  Auxiliary Feature Register                            */
  volatile  cyg_uint32 MMFR[4];                      /*!< Offset: 0x50  Memory Model Feature Register                         */
  volatile  cyg_uint32 ISAR[5];                      /*!< Offset: 0x60  ISA Feature Register                                  */
} SCB_Type;        

//=====================================
 typedef struct{
          cyg_handle_t counter_handle;
          cyg_handle_t alarm_handle; 
          cyg_alarm    alarm_object;
          cyg_uint8    initialized;
}MyeCosAlram_t;

typedef struct{
    cyg_uint32 EventFlag;
    void* dataPtr;   


}MyEvent_t;
//===================================== 

//------------------ #define --------------
void SetupIsr(void);
void SetupIO(void);
void SetupRfSpi(void);

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void GPIO_EXTILineConfig(cyg_uint8 GPIO_PortSource, cyg_uint8 GPIO_PinSource);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void       SPI_I2S_SendData(SPI_TypeDef* SPIx, cyg_uint16 Data);
cyg_uint16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx) ;
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, cyg_uint16 SPI_I2S_FLAG);
      
void EnableRfIsr(void);
void DisableRfIsr(void);
void testfunc(void);
void MyeCosAlarm( 
                  MyeCosAlram_t* MyAlarm,
		  cyg_tick_count_t alarm_period,
		  cyg_addrword_t data,
		  void* alarm_func ); 

ITStatus EXTI_GetITStatus(cyg_uint32 EXTI_Line);
void EXTI_ClearITPendingBit(cyg_uint32 EXTI_Line);
//=========ISR & DSR=============//
void yy_dsr(cyg_vector_t vector, cyg_ucount32 count, cyg_addrword_t data);
cyg_uint32
yy_isr(cyg_vector_t vector, cyg_addrword_t data);
//-------------------------------
void SetupButtomCallback(void(*s));
void buttom_dsr(cyg_vector_t vector, cyg_ucount32 count, cyg_addrword_t data);
cyg_uint32
buttom_isr(cyg_vector_t vector, cyg_addrword_t data);
//===============================//
#endif /*DW_CONFIG_H*/

