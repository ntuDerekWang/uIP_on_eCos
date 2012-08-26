/**
  ******************************************************************************
  * @file    stm32f10x_rcc.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the RCC firmware 
  *          library.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_RCC_H
#define __STM32F10x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cyg/DW_config.h>

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types
  * @{
  */

typedef struct
{
  cyg_uint32 SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
  cyg_uint32 HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
  cyg_uint32 PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
  cyg_uint32 PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
  cyg_uint32 ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup HSE_configuration 
  * @{
  */

#define RCC_HSE_OFF                      ((cyg_uint32)0x00000000)
#define RCC_HSE_ON                       ((cyg_uint32)0x00010000)
#define RCC_HSE_Bypass                   ((cyg_uint32)0x00040000)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @}
  */ 

/** @defgroup PLL_entry_clock_source 
  * @{
  */

#define RCC_PLLSource_HSI_Div2           ((cyg_uint32)0x00000000)

#ifndef STM32F10X_CL
 #define RCC_PLLSource_HSE_Div1           ((cyg_uint32)0x00010000)
 #define RCC_PLLSource_HSE_Div2           ((cyg_uint32)0x00030000)
 #define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div1) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div2))
#else
 #define RCC_PLLSource_PREDIV1            ((cyg_uint32)0x00010000)
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_PREDIV1))
#endif /* STM32F10X_CL */ 

/**
  * @}
  */ 

/** @defgroup PLL_multiplication_factor 
  * @{
  */
#ifndef STM32F10X_CL
 #define RCC_PLLMul_2                    ((cyg_uint32)0x00000000)
 #define RCC_PLLMul_3                    ((cyg_uint32)0x00040000)
 #define RCC_PLLMul_4                    ((cyg_uint32)0x00080000)
 #define RCC_PLLMul_5                    ((cyg_uint32)0x000C0000)
 #define RCC_PLLMul_6                    ((cyg_uint32)0x00100000)
 #define RCC_PLLMul_7                    ((cyg_uint32)0x00140000)
 #define RCC_PLLMul_8                    ((cyg_uint32)0x00180000)
 #define RCC_PLLMul_9                    ((cyg_uint32)0x001C0000)
 #define RCC_PLLMul_10                   ((cyg_uint32)0x00200000)
 #define RCC_PLLMul_11                   ((cyg_uint32)0x00240000)
 #define RCC_PLLMul_12                   ((cyg_uint32)0x00280000)
 #define RCC_PLLMul_13                   ((cyg_uint32)0x002C0000)
 #define RCC_PLLMul_14                   ((cyg_uint32)0x00300000)
 #define RCC_PLLMul_15                   ((cyg_uint32)0x00340000)
 #define RCC_PLLMul_16                   ((cyg_uint32)0x00380000)
 #define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                              ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                              ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                              ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                              ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                              ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                              ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                              ((MUL) == RCC_PLLMul_16))

#else
 #define RCC_PLLMul_4                    ((cyg_uint32)0x00080000)
 #define RCC_PLLMul_5                    ((cyg_uint32)0x000C0000)
 #define RCC_PLLMul_6                    ((cyg_uint32)0x00100000)
 #define RCC_PLLMul_7                    ((cyg_uint32)0x00140000)
 #define RCC_PLLMul_8                    ((cyg_uint32)0x00180000)
 #define RCC_PLLMul_9                    ((cyg_uint32)0x001C0000)
 #define RCC_PLLMul_6_5                  ((cyg_uint32)0x00340000)

 #define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5) || \
                              ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7) || \
                              ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9) || \
                              ((MUL) == RCC_PLLMul_6_5))
#endif /* STM32F10X_CL */                              
/**
  * @}
  */

#ifdef STM32F10X_CL
/** @defgroup PREDIV1_division_factor
  * @{
  */
 #define  RCC_PREDIV1_Div1               ((cyg_uint32)0x00000000)
 #define  RCC_PREDIV1_Div2               ((cyg_uint32)0x00000001)
 #define  RCC_PREDIV1_Div3               ((cyg_uint32)0x00000002)
 #define  RCC_PREDIV1_Div4               ((cyg_uint32)0x00000003)
 #define  RCC_PREDIV1_Div5               ((cyg_uint32)0x00000004)
 #define  RCC_PREDIV1_Div6               ((cyg_uint32)0x00000005)
 #define  RCC_PREDIV1_Div7               ((cyg_uint32)0x00000006)
 #define  RCC_PREDIV1_Div8               ((cyg_uint32)0x00000007)
 #define  RCC_PREDIV1_Div9               ((cyg_uint32)0x00000008)
 #define  RCC_PREDIV1_Div10              ((cyg_uint32)0x00000009)
 #define  RCC_PREDIV1_Div11              ((cyg_uint32)0x0000000A)
 #define  RCC_PREDIV1_Div12              ((cyg_uint32)0x0000000B)
 #define  RCC_PREDIV1_Div13              ((cyg_uint32)0x0000000C)
 #define  RCC_PREDIV1_Div14              ((cyg_uint32)0x0000000D)
 #define  RCC_PREDIV1_Div15              ((cyg_uint32)0x0000000E)
 #define  RCC_PREDIV1_Div16              ((cyg_uint32)0x0000000F)

 #define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
/**
  * @}
  */


/** @defgroup PREDIV1_clock_source
  * @{
  */
/* PREDIV1 clock source (only for STM32 connectivity line devices) */
 #define  RCC_PREDIV1_Source_HSE         ((cyg_uint32)0x00000000) 
 #define  RCC_PREDIV1_Source_PLL2        ((cyg_uint32)0x00010000) 

 #define IS_RCC_PREDIV1_SOURCE(SOURCE) (((SOURCE) == RCC_PREDIV1_Source_HSE) || \
                                        ((SOURCE) == RCC_PREDIV1_Source_PLL2)) 
/**
  * @}
  */


/** @defgroup PREDIV2_division_factor
  * @{
  */
  
 #define  RCC_PREDIV2_Div1               ((cyg_uint32)0x00000000)
 #define  RCC_PREDIV2_Div2               ((cyg_uint32)0x00000010)
 #define  RCC_PREDIV2_Div3               ((cyg_uint32)0x00000020)
 #define  RCC_PREDIV2_Div4               ((cyg_uint32)0x00000030)
 #define  RCC_PREDIV2_Div5               ((cyg_uint32)0x00000040)
 #define  RCC_PREDIV2_Div6               ((cyg_uint32)0x00000050)
 #define  RCC_PREDIV2_Div7               ((cyg_uint32)0x00000060)
 #define  RCC_PREDIV2_Div8               ((cyg_uint32)0x00000070)
 #define  RCC_PREDIV2_Div9               ((cyg_uint32)0x00000080)
 #define  RCC_PREDIV2_Div10              ((cyg_uint32)0x00000090)
 #define  RCC_PREDIV2_Div11              ((cyg_uint32)0x000000A0)
 #define  RCC_PREDIV2_Div12              ((cyg_uint32)0x000000B0)
 #define  RCC_PREDIV2_Div13              ((cyg_uint32)0x000000C0)
 #define  RCC_PREDIV2_Div14              ((cyg_uint32)0x000000D0)
 #define  RCC_PREDIV2_Div15              ((cyg_uint32)0x000000E0)
 #define  RCC_PREDIV2_Div16              ((cyg_uint32)0x000000F0)

 #define IS_RCC_PREDIV2(PREDIV2) (((PREDIV2) == RCC_PREDIV2_Div1) || ((PREDIV2) == RCC_PREDIV2_Div2) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div3) || ((PREDIV2) == RCC_PREDIV2_Div4) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div5) || ((PREDIV2) == RCC_PREDIV2_Div6) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div7) || ((PREDIV2) == RCC_PREDIV2_Div8) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div9) || ((PREDIV2) == RCC_PREDIV2_Div10) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div11) || ((PREDIV2) == RCC_PREDIV2_Div12) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div13) || ((PREDIV2) == RCC_PREDIV2_Div14) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div15) || ((PREDIV2) == RCC_PREDIV2_Div16))
/**
  * @}
  */


/** @defgroup PLL2_multiplication_factor
  * @{
  */
  
 #define  RCC_PLL2Mul_8                  ((cyg_uint32)0x00000600)
 #define  RCC_PLL2Mul_9                  ((cyg_uint32)0x00000700)
 #define  RCC_PLL2Mul_10                 ((cyg_uint32)0x00000800)
 #define  RCC_PLL2Mul_11                 ((cyg_uint32)0x00000900)
 #define  RCC_PLL2Mul_12                 ((cyg_uint32)0x00000A00)
 #define  RCC_PLL2Mul_13                 ((cyg_uint32)0x00000B00)
 #define  RCC_PLL2Mul_14                 ((cyg_uint32)0x00000C00)
 #define  RCC_PLL2Mul_16                 ((cyg_uint32)0x00000E00)
 #define  RCC_PLL2Mul_20                 ((cyg_uint32)0x00000F00)

 #define IS_RCC_PLL2_MUL(MUL) (((MUL) == RCC_PLL2Mul_8) || ((MUL) == RCC_PLL2Mul_9)  || \
                               ((MUL) == RCC_PLL2Mul_10) || ((MUL) == RCC_PLL2Mul_11) || \
                               ((MUL) == RCC_PLL2Mul_12) || ((MUL) == RCC_PLL2Mul_13) || \
                               ((MUL) == RCC_PLL2Mul_14) || ((MUL) == RCC_PLL2Mul_16) || \
                               ((MUL) == RCC_PLL2Mul_20))
/**
  * @}
  */


/** @defgroup PLL3_multiplication_factor
  * @{
  */

 #define  RCC_PLL3Mul_8                  ((cyg_uint32)0x00006000)
 #define  RCC_PLL3Mul_9                  ((cyg_uint32)0x00007000)
 #define  RCC_PLL3Mul_10                 ((cyg_uint32)0x00008000)
 #define  RCC_PLL3Mul_11                 ((cyg_uint32)0x00009000)
 #define  RCC_PLL3Mul_12                 ((cyg_uint32)0x0000A000)
 #define  RCC_PLL3Mul_13                 ((cyg_uint32)0x0000B000)
 #define  RCC_PLL3Mul_14                 ((cyg_uint32)0x0000C000)
 #define  RCC_PLL3Mul_16                 ((cyg_uint32)0x0000E000)
 #define  RCC_PLL3Mul_20                 ((cyg_uint32)0x0000F000)

 #define IS_RCC_PLL3_MUL(MUL) (((MUL) == RCC_PLL3Mul_8) || ((MUL) == RCC_PLL3Mul_9)  || \
                               ((MUL) == RCC_PLL3Mul_10) || ((MUL) == RCC_PLL3Mul_11) || \
                               ((MUL) == RCC_PLL3Mul_12) || ((MUL) == RCC_PLL3Mul_13) || \
                               ((MUL) == RCC_PLL3Mul_14) || ((MUL) == RCC_PLL3Mul_16) || \
                               ((MUL) == RCC_PLL3Mul_20))
/**
  * @}
  */

#endif /* STM32F10X_CL */


/** @defgroup System_clock_source 
  * @{
  */

#define RCC_SYSCLKSource_HSI             ((cyg_uint32)0x00000000)
#define RCC_SYSCLKSource_HSE             ((cyg_uint32)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((cyg_uint32)0x00000002)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
/**
  * @}
  */

/** @defgroup AHB_clock_source 
  * @{
  */

#define RCC_SYSCLK_Div1                  ((cyg_uint32)0x00000000)
#define RCC_SYSCLK_Div2                  ((cyg_uint32)0x00000080)
#define RCC_SYSCLK_Div4                  ((cyg_uint32)0x00000090)
#define RCC_SYSCLK_Div8                  ((cyg_uint32)0x000000A0)
#define RCC_SYSCLK_Div16                 ((cyg_uint32)0x000000B0)
#define RCC_SYSCLK_Div64                 ((cyg_uint32)0x000000C0)
#define RCC_SYSCLK_Div128                ((cyg_uint32)0x000000D0)
#define RCC_SYSCLK_Div256                ((cyg_uint32)0x000000E0)
#define RCC_SYSCLK_Div512                ((cyg_uint32)0x000000F0)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */ 

/** @defgroup APB1_APB2_clock_source 
  * @{
  */

#define RCC_HCLK_Div1                    ((cyg_uint32)0x00000000)
#define RCC_HCLK_Div2                    ((cyg_uint32)0x00000400)
#define RCC_HCLK_Div4                    ((cyg_uint32)0x00000500)
#define RCC_HCLK_Div8                    ((cyg_uint32)0x00000600)
#define RCC_HCLK_Div16                   ((cyg_uint32)0x00000700)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */

/** @defgroup RCC_Interrupt_source 
  * @{
  */

#define RCC_IT_LSIRDY                    ((cyg_uint8)0x01)
#define RCC_IT_LSERDY                    ((cyg_uint8)0x02)
#define RCC_IT_HSIRDY                    ((cyg_uint8)0x04)
#define RCC_IT_HSERDY                    ((cyg_uint8)0x08)
#define RCC_IT_PLLRDY                    ((cyg_uint8)0x10)
#define RCC_IT_CSS                       ((cyg_uint8)0x80)

#ifndef STM32F10X_CL
 #define IS_RCC_IT(IT) ((((IT) & (cyg_uint8)0xE0) == 0x00) && ((IT) != 0x00))
 #define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                            ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                            ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
 #define IS_RCC_CLEAR_IT(IT) ((((IT) & (cyg_uint8)0x60) == 0x00) && ((IT) != 0x00))
#else
 #define RCC_IT_PLL2RDY                  ((cyg_uint8)0x20)
 #define RCC_IT_PLL3RDY                  ((cyg_uint8)0x40)
 #define IS_RCC_IT(IT) ((((IT) & (cyg_uint8)0x80) == 0x00) && ((IT) != 0x00))
 #define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                            ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                            ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS) || \
                            ((IT) == RCC_IT_PLL2RDY) || ((IT) == RCC_IT_PLL3RDY))
 #define IS_RCC_CLEAR_IT(IT) ((IT) != 0x00)
#endif /* STM32F10X_CL */ 


/**
  * @}
  */

#ifndef STM32F10X_CL
/** @defgroup USB_Device_clock_source 
  * @{
  */

 #define RCC_USBCLKSource_PLLCLK_1Div5   ((cyg_uint8)0x00)
 #define RCC_USBCLKSource_PLLCLK_Div1    ((cyg_uint8)0x01)

 #define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))
#else
/** @defgroup USB_OTG_FS_clock_source 
  * @{
  */
 #define RCC_OTGFSCLKSource_PLLVCO_Div3    ((cyg_uint8)0x00)
 #define RCC_OTGFSCLKSource_PLLVCO_Div2    ((cyg_uint8)0x01)

 #define IS_RCC_OTGFSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_OTGFSCLKSource_PLLVCO_Div3) || \
                                         ((SOURCE) == RCC_OTGFSCLKSource_PLLVCO_Div2))
#endif /* STM32F10X_CL */ 
/**
  * @}
  */

#ifdef STM32F10X_CL
/** @defgroup I2S2_clock_source 
  * @{
  */
 #define RCC_I2S2CLKSource_SYSCLK        ((cyg_uint8)0x00)
 #define RCC_I2S2CLKSource_PLL3_VCO      ((cyg_uint8)0x01)

 #define IS_RCC_I2S2CLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_SYSCLK) || \
                                        ((SOURCE) == RCC_I2S2CLKSource_PLL3_VCO))
/**
  * @}
  */

/** @defgroup I2S3_clock_source 
  * @{
  */
 #define RCC_I2S3CLKSource_SYSCLK        ((cyg_uint8)0x00)
 #define RCC_I2S3CLKSource_PLL3_VCO      ((cyg_uint8)0x01)

 #define IS_RCC_I2S3CLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S3CLKSource_SYSCLK) || \
                                        ((SOURCE) == RCC_I2S3CLKSource_PLL3_VCO))    
/**
  * @}
  */
#endif /* STM32F10X_CL */  
  

/** @defgroup ADC_clock_source 
  * @{
  */

#define RCC_PCLK2_Div2                   ((cyg_uint32)0x00000000)
#define RCC_PCLK2_Div4                   ((cyg_uint32)0x00004000)
#define RCC_PCLK2_Div6                   ((cyg_uint32)0x00008000)
#define RCC_PCLK2_Div8                   ((cyg_uint32)0x0000C000)
#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_PCLK2_Div2) || ((ADCCLK) == RCC_PCLK2_Div4) || \
                               ((ADCCLK) == RCC_PCLK2_Div6) || ((ADCCLK) == RCC_PCLK2_Div8))
/**
  * @}
  */

/** @defgroup LSE_configuration 
  * @{
  */

#define RCC_LSE_OFF                      ((cyg_uint8)0x00)
#define RCC_LSE_ON                       ((cyg_uint8)0x01)
#define RCC_LSE_Bypass                   ((cyg_uint8)0x04)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RTC_clock_source 
  * @{
  */

#define RCC_RTCCLKSource_LSE             ((cyg_uint32)0x00000100)
#define RCC_RTCCLKSource_LSI             ((cyg_uint32)0x00000200)
#define RCC_RTCCLKSource_HSE_Div128      ((cyg_uint32)0x00000300)
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div128))
/**
  * @}
  */

/** @defgroup AHB_peripheral 
  * @{
  */

#define RCC_AHBPeriph_DMA1               ((cyg_uint32)0x00000001)
#define RCC_AHBPeriph_DMA2               ((cyg_uint32)0x00000002)
#define RCC_AHBPeriph_SRAM               ((cyg_uint32)0x00000004)
#define RCC_AHBPeriph_FLITF              ((cyg_uint32)0x00000010)
#define RCC_AHBPeriph_CRC                ((cyg_uint32)0x00000040)

#ifndef STM32F10X_CL
 #define RCC_AHBPeriph_FSMC              ((cyg_uint32)0x00000100)
 #define RCC_AHBPeriph_SDIO              ((cyg_uint32)0x00000400)
 #define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFAA8) == 0x00) && ((PERIPH) != 0x00))
#else
 #define RCC_AHBPeriph_OTG_FS            ((cyg_uint32)0x00001000)
 #define RCC_AHBPeriph_ETH_MAC           ((cyg_uint32)0x00004000)
 #define RCC_AHBPeriph_ETH_MAC_Tx        ((cyg_uint32)0x00008000)
 #define RCC_AHBPeriph_ETH_MAC_Rx        ((cyg_uint32)0x00010000)

 #define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFE2FA8) == 0x00) && ((PERIPH) != 0x00))
 #define IS_RCC_AHB_PERIPH_RESET(PERIPH) ((((PERIPH) & 0xFFFFAFFF) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F10X_CL */
/**
  * @}
  */

/** @defgroup APB2_peripheral 
  * @{
  */

#define RCC_APB2Periph_AFIO              ((cyg_uint32)0x00000001)
#define RCC_APB2Periph_GPIOA             ((cyg_uint32)0x00000004)
#define RCC_APB2Periph_GPIOB             ((cyg_uint32)0x00000008)
#define RCC_APB2Periph_GPIOC             ((cyg_uint32)0x00000010)
#define RCC_APB2Periph_GPIOD             ((cyg_uint32)0x00000020)
#define RCC_APB2Periph_GPIOE             ((cyg_uint32)0x00000040)
#define RCC_APB2Periph_GPIOF             ((cyg_uint32)0x00000080)
#define RCC_APB2Periph_GPIOG             ((cyg_uint32)0x00000100)
#define RCC_APB2Periph_ADC1              ((cyg_uint32)0x00000200)
#define RCC_APB2Periph_ADC2              ((cyg_uint32)0x00000400)
#define RCC_APB2Periph_TIM1              ((cyg_uint32)0x00000800)
#define RCC_APB2Periph_SPI1              ((cyg_uint32)0x00001000)
#define RCC_APB2Periph_TIM8              ((cyg_uint32)0x00002000)
#define RCC_APB2Periph_USART1            ((cyg_uint32)0x00004000)
#define RCC_APB2Periph_ADC3              ((cyg_uint32)0x00008000)

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFF0002) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 

/** @defgroup APB1_peripheral 
  * @{
  */

#define RCC_APB1Periph_TIM2              ((cyg_uint32)0x00000001)
#define RCC_APB1Periph_TIM3              ((cyg_uint32)0x00000002)
#define RCC_APB1Periph_TIM4              ((cyg_uint32)0x00000004)
#define RCC_APB1Periph_TIM5              ((cyg_uint32)0x00000008)
#define RCC_APB1Periph_TIM6              ((cyg_uint32)0x00000010)
#define RCC_APB1Periph_TIM7              ((cyg_uint32)0x00000020)
#define RCC_APB1Periph_WWDG              ((cyg_uint32)0x00000800)
#define RCC_APB1Periph_SPI2              ((cyg_uint32)0x00004000)
#define RCC_APB1Periph_SPI3              ((cyg_uint32)0x00008000)
#define RCC_APB1Periph_USART2            ((cyg_uint32)0x00020000)
#define RCC_APB1Periph_USART3            ((cyg_uint32)0x00040000)
#define RCC_APB1Periph_UART4             ((cyg_uint32)0x00080000)
#define RCC_APB1Periph_UART5             ((cyg_uint32)0x00100000)
#define RCC_APB1Periph_I2C1              ((cyg_uint32)0x00200000)
#define RCC_APB1Periph_I2C2              ((cyg_uint32)0x00400000)
#define RCC_APB1Periph_USB               ((cyg_uint32)0x00800000)
#define RCC_APB1Periph_CAN1              ((cyg_uint32)0x02000000)
#define RCC_APB1Periph_BKP               ((cyg_uint32)0x08000000)
#define RCC_APB1Periph_PWR               ((cyg_uint32)0x10000000)
#define RCC_APB1Periph_DAC               ((cyg_uint32)0x20000000)
#define RCC_APB1Periph_CAN2             ((cyg_uint32)0x04000000) 
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0xC10137C0) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup Clock_source_to_output_on_MCO_pin 
  * @{
  */

#define RCC_MCO_NoClock                  ((cyg_uint8)0x00)
#define RCC_MCO_SYSCLK                   ((cyg_uint8)0x04)
#define RCC_MCO_HSI                      ((cyg_uint8)0x05)
#define RCC_MCO_HSE                      ((cyg_uint8)0x06)
#define RCC_MCO_PLLCLK_Div2              ((cyg_uint8)0x07)

#ifndef STM32F10X_CL
 #define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) || \
                          ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                          ((MCO) == RCC_MCO_PLLCLK_Div2))
#else
 #define RCC_MCO_PLL2CLK                 ((cyg_uint8)0x08)
 #define RCC_MCO_PLL3CLK_Div2            ((cyg_uint8)0x09)
 #define RCC_MCO_XT1                     ((cyg_uint8)0x0A)
 #define RCC_MCO_PLL3CLK                 ((cyg_uint8)0x0B)

 #define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) || \
                          ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                          ((MCO) == RCC_MCO_PLLCLK_Div2) || ((MCO) == RCC_MCO_PLL2CLK) || \
                          ((MCO) == RCC_MCO_PLL3CLK_Div2) || ((MCO) == RCC_MCO_XT1) || \
                          ((MCO) == RCC_MCO_PLL3CLK))
#endif /* STM32F10X_CL */ 

/**
  * @}
  */

/** @defgroup RCC_Flag 
  * @{
  */

#define RCC_FLAG_HSIRDY                  ((cyg_uint8)0x21)
#define RCC_FLAG_HSERDY                  ((cyg_uint8)0x31)
#define RCC_FLAG_PLLRDY                  ((cyg_uint8)0x39)
#define RCC_FLAG_LSERDY                  ((cyg_uint8)0x41)
#define RCC_FLAG_LSIRDY                  ((cyg_uint8)0x61)
#define RCC_FLAG_PINRST                  ((cyg_uint8)0x7A)
#define RCC_FLAG_PORRST                  ((cyg_uint8)0x7B)
#define RCC_FLAG_SFTRST                  ((cyg_uint8)0x7C)
#define RCC_FLAG_IWDGRST                 ((cyg_uint8)0x7D)
#define RCC_FLAG_WWDGRST                 ((cyg_uint8)0x7E)
#define RCC_FLAG_LPWRRST                 ((cyg_uint8)0x7F)

#ifndef STM32F10X_CL
 #define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                            ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                            ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                            ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                            ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                            ((FLAG) == RCC_FLAG_LPWRRST))
#else
 #define RCC_FLAG_PLL2RDY                ((cyg_uint8)0x3B) 
 #define RCC_FLAG_PLL3RDY                ((cyg_uint8)0x3D) 
 #define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                            ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                            ((FLAG) == RCC_FLAG_PLL2RDY) || ((FLAG) == RCC_FLAG_PLL3RDY) || \
                            ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                            ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                            ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                            ((FLAG) == RCC_FLAG_LPWRRST))
#endif /* STM32F10X_CL */ 

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions
  * @{
  */

void RCC_DeInit(void);
void RCC_HSEConfig(cyg_uint32 RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(cyg_uint8 HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(cyg_uint32 RCC_PLLSource, cyg_uint32 RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);

#ifdef STM32F10X_CL
 void RCC_PREDIV1Config(cyg_uint32 RCC_PREDIV1_Source, cyg_uint32 RCC_PREDIV1_Div);
 void RCC_PREDIV2Config(cyg_uint32 RCC_PREDIV2_Div);
 void RCC_PLL2Config(cyg_uint32 RCC_PLL2Mul);
 void RCC_PLL2Cmd(FunctionalState NewState);
 void RCC_PLL3Config(cyg_uint32 RCC_PLL3Mul);
 void RCC_PLL3Cmd(FunctionalState NewState);
#endif /* STM32F10X_CL */ 

void RCC_SYSCLKConfig(cyg_uint32 RCC_SYSCLKSource);
cyg_uint8 RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(cyg_uint32 RCC_SYSCLK);
void RCC_PCLK1Config(cyg_uint32 RCC_HCLK);
void RCC_PCLK2Config(cyg_uint32 RCC_HCLK);
void RCC_ITConfig(cyg_uint8 RCC_IT, FunctionalState NewState);

#ifndef STM32F10X_CL
 void RCC_USBCLKConfig(cyg_uint32 RCC_USBCLKSource);
#else
 void RCC_OTGFSCLKConfig(cyg_uint32 RCC_OTGFSCLKSource);
#endif /* STM32F10X_CL */ 

void RCC_ADCCLKConfig(cyg_uint32 RCC_PCLK2);

#ifdef STM32F10X_CL
 void RCC_I2S2CLKConfig(cyg_uint32 RCC_I2S2CLKSource);                                  
 void RCC_I2S3CLKConfig(cyg_uint32 RCC_I2S3CLKSource);
#endif /* STM32F10X_CL */ 

void RCC_LSEConfig(cyg_uint8 RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(cyg_uint32 RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(cyg_uint32 RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(cyg_uint32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(cyg_uint32 RCC_APB1Periph, FunctionalState NewState);

#ifdef STM32F10X_CL
void RCC_AHBPeriphResetCmd(cyg_uint32 RCC_AHBPeriph, FunctionalState NewState);
#endif /* STM32F10X_CL */ 

void RCC_APB2PeriphResetCmd(cyg_uint32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(cyg_uint32 RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(cyg_uint8 RCC_MCO);
FlagStatus RCC_GetFlagStatus(cyg_uint8 RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(cyg_uint8 RCC_IT);
void RCC_ClearITPendingBit(cyg_uint8 RCC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_RCC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

