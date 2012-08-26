/**
  ******************************************************************************
  * @file    stm32f10x_tim.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the TIM firmware 
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
  *  Usage:       #include <cyg/io/stm32f10x_tim.h>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_TIM_H
#define __STM32F10x_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cyg/DW_config.h>
//#include <cyg/io/stm32f10x_rcc.h>
/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/** @defgroup TIM_Exported_Types
  * @{
  */ 

/** 
  * @brief  TIM Time Base Init structure definition
  * @note   This sturcture is used with all TIMx except for TIM6 and TIM7.    
  */

typedef struct
{
  cyg_uint16 TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  cyg_uint16 TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  cyg_uint16 TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  cyg_uint16 TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  cyg_uint8 TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1 and TIM8. */
} TIM_TimeBaseInitTypeDef;       

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  cyg_uint16 TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  cyg_uint16 TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

  cyg_uint16 TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1 and TIM8. */

  cyg_uint16 TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  cyg_uint16 TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  cyg_uint16 TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

  cyg_uint16 TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  cyg_uint16 TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} TIM_OCInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

typedef struct
{

  cyg_uint16 TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  cyg_uint16 TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  cyg_uint16 TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  cyg_uint16 TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  cyg_uint16 TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

/** 
  * @brief  BDTR structure definition 
  * @note   This sturcture is used only with TIM1 and TIM8.    
  */

typedef struct
{

  cyg_uint16 TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */

  cyg_uint16 TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */

  cyg_uint16 TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref Lock_level */ 

  cyg_uint16 TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  cyg_uint16 TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not. 
                                      This parameter can be a value of @ref Break_Input_enable_disable */

  cyg_uint16 TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref Break_Polarity */

  cyg_uint16 TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef;

/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM4) || \
                                   ((PERIPH) == TIM5) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM8))

#define IS_TIM_18_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                  ((PERIPH) == TIM8))

#define IS_TIM_123458_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM8))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_and_PWM_modes 
  * @{
  */

#define TIM_OCMode_Timing                  ((cyg_uint16)0x0000)
#define TIM_OCMode_Active                  ((cyg_uint16)0x0010)
#define TIM_OCMode_Inactive                ((cyg_uint16)0x0020)
#define TIM_OCMode_Toggle                  ((cyg_uint16)0x0030)
#define TIM_OCMode_PWM1                    ((cyg_uint16)0x0060)
#define TIM_OCMode_PWM2                    ((cyg_uint16)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode 
  * @{
  */

#define TIM_OPMode_Single                  ((cyg_uint16)0x0008)
#define TIM_OPMode_Repetitive              ((cyg_uint16)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */ 

/** @defgroup TIM_Channel 
  * @{
  */

#define TIM_Channel_1                      ((cyg_uint16)0x0000)
#define TIM_Channel_2                      ((cyg_uint16)0x0004)
#define TIM_Channel_3                      ((cyg_uint16)0x0008)
#define TIM_Channel_4                      ((cyg_uint16)0x000C)
#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
/**
  * @}
  */ 

/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */

#define TIM_CKD_DIV1                       ((cyg_uint16)0x0000)
#define TIM_CKD_DIV2                       ((cyg_uint16)0x0100)
#define TIM_CKD_DIV4                       ((cyg_uint16)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode 
  * @{
  */

#define TIM_CounterMode_Up                 ((cyg_uint16)0x0000)
#define TIM_CounterMode_Down               ((cyg_uint16)0x0010)
#define TIM_CounterMode_CenterAligned1     ((cyg_uint16)0x0020)
#define TIM_CounterMode_CenterAligned2     ((cyg_uint16)0x0040)
#define TIM_CounterMode_CenterAligned3     ((cyg_uint16)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Polarity 
  * @{
  */

#define TIM_OCPolarity_High                ((cyg_uint16)0x0000)
#define TIM_OCPolarity_Low                 ((cyg_uint16)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity 
  * @{
  */
  
#define TIM_OCNPolarity_High               ((cyg_uint16)0x0000)
#define TIM_OCNPolarity_Low                ((cyg_uint16)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state 
  * @{
  */

#define TIM_OutputState_Disable            ((cyg_uint16)0x0000)
#define TIM_OutputState_Enable             ((cyg_uint16)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_state 
  * @{
  */

#define TIM_OutputNState_Disable           ((cyg_uint16)0x0000)
#define TIM_OutputNState_Enable            ((cyg_uint16)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_state 
  * @{
  */

#define TIM_CCx_Enable                      ((cyg_uint16)0x0001)
#define TIM_CCx_Disable                     ((cyg_uint16)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_N_state 
  * @{
  */

#define TIM_CCxN_Enable                     ((cyg_uint16)0x0004)
#define TIM_CCxN_Disable                    ((cyg_uint16)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
  * @}
  */ 

/** @defgroup Break_Input_enable_disable 
  * @{
  */

#define TIM_Break_Enable                   ((cyg_uint16)0x1000)
#define TIM_Break_Disable                  ((cyg_uint16)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))
/**
  * @}
  */ 

/** @defgroup Break_Polarity 
  * @{
  */

#define TIM_BreakPolarity_Low              ((cyg_uint16)0x0000)
#define TIM_BreakPolarity_High             ((cyg_uint16)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
  * @}
  */ 

/** @defgroup TIM_AOE_Bit_Set_Reset 
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((cyg_uint16)0x4000)
#define TIM_AutomaticOutput_Disable        ((cyg_uint16)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */ 

/** @defgroup Lock_level 
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((cyg_uint16)0x0000)
#define TIM_LOCKLevel_1                    ((cyg_uint16)0x0100)
#define TIM_LOCKLevel_2                    ((cyg_uint16)0x0200)
#define TIM_LOCKLevel_3                    ((cyg_uint16)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
  * @}
  */ 

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TIM_OSSIState_Enable               ((cyg_uint16)0x0400)
#define TIM_OSSIState_Disable              ((cyg_uint16)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */

#define TIM_OSSRState_Enable               ((cyg_uint16)0x0800)
#define TIM_OSSRState_Disable              ((cyg_uint16)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Idle_State 
  * @{
  */

#define TIM_OCIdleState_Set                ((cyg_uint16)0x0100)
#define TIM_OCIdleState_Reset              ((cyg_uint16)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_Idle_State 
  * @{
  */

#define TIM_OCNIdleState_Set               ((cyg_uint16)0x0200)
#define TIM_OCNIdleState_Reset             ((cyg_uint16)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Polarity 
  * @{
  */

#define  TIM_ICPolarity_Rising             ((cyg_uint16)0x0000)
#define  TIM_ICPolarity_Falling            ((cyg_uint16)0x0002)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Selection 
  * @{
  */

#define TIM_ICSelection_DirectTI           ((cyg_uint16)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI         ((cyg_uint16)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC                ((cyg_uint16)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Prescaler 
  * @{
  */

#define TIM_ICPSC_DIV1                     ((cyg_uint16)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2                     ((cyg_uint16)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4                     ((cyg_uint16)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8                     ((cyg_uint16)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
  * @}
  */ 

/** @defgroup TIM_interrupt_sources 
  * @{
  */

#define TIM_IT_Update                      ((cyg_uint16)0x0001)
#define TIM_IT_CC1                         ((cyg_uint16)0x0002)
#define TIM_IT_CC2                         ((cyg_uint16)0x0004)
#define TIM_IT_CC3                         ((cyg_uint16)0x0008)
#define TIM_IT_CC4                         ((cyg_uint16)0x0010)
#define TIM_IT_COM                         ((cyg_uint16)0x0020)
#define TIM_IT_Trigger                     ((cyg_uint16)0x0040)
#define TIM_IT_Break                       ((cyg_uint16)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (cyg_uint16)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Base_address 
  * @{
  */

#define TIM_DMABase_CR1                    ((cyg_uint16)0x0000)
#define TIM_DMABase_CR2                    ((cyg_uint16)0x0001)
#define TIM_DMABase_SMCR                   ((cyg_uint16)0x0002)
#define TIM_DMABase_DIER                   ((cyg_uint16)0x0003)
#define TIM_DMABase_SR                     ((cyg_uint16)0x0004)
#define TIM_DMABase_EGR                    ((cyg_uint16)0x0005)
#define TIM_DMABase_CCMR1                  ((cyg_uint16)0x0006)
#define TIM_DMABase_CCMR2                  ((cyg_uint16)0x0007)
#define TIM_DMABase_CCER                   ((cyg_uint16)0x0008)
#define TIM_DMABase_CNT                    ((cyg_uint16)0x0009)
#define TIM_DMABase_PSC                    ((cyg_uint16)0x000A)
#define TIM_DMABase_ARR                    ((cyg_uint16)0x000B)
#define TIM_DMABase_RCR                    ((cyg_uint16)0x000C)
#define TIM_DMABase_CCR1                   ((cyg_uint16)0x000D)
#define TIM_DMABase_CCR2                   ((cyg_uint16)0x000E)
#define TIM_DMABase_CCR3                   ((cyg_uint16)0x000F)
#define TIM_DMABase_CCR4                   ((cyg_uint16)0x0010)
#define TIM_DMABase_BDTR                   ((cyg_uint16)0x0011)
#define TIM_DMABase_DCR                    ((cyg_uint16)0x0012)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
                               ((BASE) == TIM_DMABase_DCR))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Burst_Length 
  * @{
  */

#define TIM_DMABurstLength_1Byte           ((cyg_uint16)0x0000)
#define TIM_DMABurstLength_2Bytes          ((cyg_uint16)0x0100)
#define TIM_DMABurstLength_3Bytes          ((cyg_uint16)0x0200)
#define TIM_DMABurstLength_4Bytes          ((cyg_uint16)0x0300)
#define TIM_DMABurstLength_5Bytes          ((cyg_uint16)0x0400)
#define TIM_DMABurstLength_6Bytes          ((cyg_uint16)0x0500)
#define TIM_DMABurstLength_7Bytes          ((cyg_uint16)0x0600)
#define TIM_DMABurstLength_8Bytes          ((cyg_uint16)0x0700)
#define TIM_DMABurstLength_9Bytes          ((cyg_uint16)0x0800)
#define TIM_DMABurstLength_10Bytes         ((cyg_uint16)0x0900)
#define TIM_DMABurstLength_11Bytes         ((cyg_uint16)0x0A00)
#define TIM_DMABurstLength_12Bytes         ((cyg_uint16)0x0B00)
#define TIM_DMABurstLength_13Bytes         ((cyg_uint16)0x0C00)
#define TIM_DMABurstLength_14Bytes         ((cyg_uint16)0x0D00)
#define TIM_DMABurstLength_15Bytes         ((cyg_uint16)0x0E00)
#define TIM_DMABurstLength_16Bytes         ((cyg_uint16)0x0F00)
#define TIM_DMABurstLength_17Bytes         ((cyg_uint16)0x1000)
#define TIM_DMABurstLength_18Bytes         ((cyg_uint16)0x1100)
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Byte) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Bytes))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_sources 
  * @{
  */

#define TIM_DMA_Update                     ((cyg_uint16)0x0100)
#define TIM_DMA_CC1                        ((cyg_uint16)0x0200)
#define TIM_DMA_CC2                        ((cyg_uint16)0x0400)
#define TIM_DMA_CC3                        ((cyg_uint16)0x0800)
#define TIM_DMA_CC4                        ((cyg_uint16)0x1000)
#define TIM_DMA_COM                        ((cyg_uint16)0x2000)
#define TIM_DMA_Trigger                    ((cyg_uint16)0x4000)
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (cyg_uint16)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Prescaler 
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((cyg_uint16)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((cyg_uint16)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((cyg_uint16)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((cyg_uint16)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */ 

/** @defgroup TIM_Internal_Trigger_Selection 
  * @{
  */

#define TIM_TS_ITR0                        ((cyg_uint16)0x0000)
#define TIM_TS_ITR1                        ((cyg_uint16)0x0010)
#define TIM_TS_ITR2                        ((cyg_uint16)0x0020)
#define TIM_TS_ITR3                        ((cyg_uint16)0x0030)
#define TIM_TS_TI1F_ED                     ((cyg_uint16)0x0040)
#define TIM_TS_TI1FP1                      ((cyg_uint16)0x0050)
#define TIM_TS_TI2FP2                      ((cyg_uint16)0x0060)
#define TIM_TS_ETRF                        ((cyg_uint16)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
  * @}
  */ 

/** @defgroup TIM_TIx_External_Clock_Source 
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((cyg_uint16)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((cyg_uint16)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((cyg_uint16)0x0040)
#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */ 
#define TIM_ExtTRGPolarity_Inverted        ((cyg_uint16)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((cyg_uint16)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode 
  * @{
  */

#define TIM_PSCReloadMode_Update           ((cyg_uint16)0x0000)
#define TIM_PSCReloadMode_Immediate        ((cyg_uint16)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
  * @}
  */ 

/** @defgroup TIM_Forced_Action 
  * @{
  */

#define TIM_ForcedAction_Active            ((cyg_uint16)0x0050)
#define TIM_ForcedAction_InActive          ((cyg_uint16)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */ 

/** @defgroup TIM_Encoder_Mode 
  * @{
  */

#define TIM_EncoderMode_TI1                ((cyg_uint16)0x0001)
#define TIM_EncoderMode_TI2                ((cyg_uint16)0x0002)
#define TIM_EncoderMode_TI12               ((cyg_uint16)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */ 


/** @defgroup TIM_Event_Source 
  * @{
  */

#define TIM_EventSource_Update             ((cyg_uint16)0x0001)
#define TIM_EventSource_CC1                ((cyg_uint16)0x0002)
#define TIM_EventSource_CC2                ((cyg_uint16)0x0004)
#define TIM_EventSource_CC3                ((cyg_uint16)0x0008)
#define TIM_EventSource_CC4                ((cyg_uint16)0x0010)
#define TIM_EventSource_COM                ((cyg_uint16)0x0020)
#define TIM_EventSource_Trigger            ((cyg_uint16)0x0040)
#define TIM_EventSource_Break              ((cyg_uint16)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (cyg_uint16)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TIM_Update_Source 
  * @{
  */

#define TIM_UpdateSource_Global            ((cyg_uint16)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TIM_UpdateSource_Regular           ((cyg_uint16)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
  * @}
  */ 

/** @defgroup TIM_Ouput_Compare_Preload_State 
  * @{
  */

#define TIM_OCPreload_Enable               ((cyg_uint16)0x0008)
#define TIM_OCPreload_Disable              ((cyg_uint16)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Ouput_Compare_Fast_State 
  * @{
  */

#define TIM_OCFast_Enable                  ((cyg_uint16)0x0004)
#define TIM_OCFast_Disable                 ((cyg_uint16)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))
                                     
/**
  * @}
  */ 

/** @defgroup TIM_Ouput_Compare_Clear_State 
  * @{
  */

#define TIM_OCClear_Enable                 ((cyg_uint16)0x0080)
#define TIM_OCClear_Disable                ((cyg_uint16)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Trigger_Output_Source 
  * @{
  */

#define TIM_TRGOSource_Reset               ((cyg_uint16)0x0000)
#define TIM_TRGOSource_Enable              ((cyg_uint16)0x0010)
#define TIM_TRGOSource_Update              ((cyg_uint16)0x0020)
#define TIM_TRGOSource_OC1                 ((cyg_uint16)0x0030)
#define TIM_TRGOSource_OC1Ref              ((cyg_uint16)0x0040)
#define TIM_TRGOSource_OC2Ref              ((cyg_uint16)0x0050)
#define TIM_TRGOSource_OC3Ref              ((cyg_uint16)0x0060)
#define TIM_TRGOSource_OC4Ref              ((cyg_uint16)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
  * @}
  */ 

/** @defgroup TIM_Slave_Mode 
  * @{
  */

#define TIM_SlaveMode_Reset                ((cyg_uint16)0x0004)
#define TIM_SlaveMode_Gated                ((cyg_uint16)0x0005)
#define TIM_SlaveMode_Trigger              ((cyg_uint16)0x0006)
#define TIM_SlaveMode_External1            ((cyg_uint16)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
  * @}
  */ 

/** @defgroup TIM_Master_Slave_Mode 
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((cyg_uint16)0x0080)
#define TIM_MasterSlaveMode_Disable        ((cyg_uint16)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update                    ((cyg_uint16)0x0001)
#define TIM_FLAG_CC1                       ((cyg_uint16)0x0002)
#define TIM_FLAG_CC2                       ((cyg_uint16)0x0004)
#define TIM_FLAG_CC3                       ((cyg_uint16)0x0008)
#define TIM_FLAG_CC4                       ((cyg_uint16)0x0010)
#define TIM_FLAG_COM                       ((cyg_uint16)0x0020)
#define TIM_FLAG_Trigger                   ((cyg_uint16)0x0040)
#define TIM_FLAG_Break                     ((cyg_uint16)0x0080)
#define TIM_FLAG_CC1OF                     ((cyg_uint16)0x0200)
#define TIM_FLAG_CC2OF                     ((cyg_uint16)0x0400)
#define TIM_FLAG_CC3OF                     ((cyg_uint16)0x0800)
#define TIM_FLAG_CC4OF                     ((cyg_uint16)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))
                               
                               
#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (cyg_uint16)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Filer_Value 
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF) 
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Filter 
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)
/**
  * @}
  */ 

/**
  * @}
  */

/** @defgroup TIM_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup TIM_Exported_Functions
  * @{
  */
/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((cyg_uint16)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((cyg_uint16)0x0002)            /*!<Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((cyg_uint16)0x0004)            /*!<Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((cyg_uint16)0x0008)            /*!<Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((cyg_uint16)0x0010)            /*!<Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((cyg_uint16)0x0020)            /*!<COM interrupt enable */
#define  TIM_DIER_TIE                        ((cyg_uint16)0x0040)            /*!<Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((cyg_uint16)0x0080)            /*!<Break interrupt enable */
#define  TIM_DIER_UDE                        ((cyg_uint16)0x0100)            /*!<Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((cyg_uint16)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((cyg_uint16)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((cyg_uint16)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((cyg_uint16)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((cyg_uint16)0x2000)            /*!<COM DMA request enable */
#define  TIM_DIER_TDE                        ((cyg_uint16)0x4000)            /*!<Trigger DMA request enable */


void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, cyg_uint16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_DMABase, cyg_uint16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, cyg_uint16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_TIxExternalCLKSource,
                                cyg_uint16 TIM_ICPolarity, cyg_uint16 ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ExtTRGPrescaler, cyg_uint16 TIM_ExtTRGPolarity,
                             cyg_uint16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ExtTRGPrescaler, 
                             cyg_uint16 TIM_ExtTRGPolarity, cyg_uint16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_ExtTRGPrescaler, cyg_uint16 TIM_ExtTRGPolarity,
                   cyg_uint16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, cyg_uint16 Prescaler, cyg_uint16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, cyg_uint16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_EncoderMode,
                                cyg_uint16 TIM_IC1Polarity, cyg_uint16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, cyg_uint16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, cyg_uint16 TIM_Channel, cyg_uint16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, cyg_uint16 TIM_Channel, cyg_uint16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, cyg_uint16 TIM_Channel, cyg_uint16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, cyg_uint16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, cyg_uint16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, cyg_uint16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, cyg_uint16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, cyg_uint16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, cyg_uint16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, cyg_uint16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, cyg_uint16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, cyg_uint16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, cyg_uint16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, cyg_uint16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, cyg_uint16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, cyg_uint16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, cyg_uint16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, cyg_uint16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, cyg_uint16 TIM_CKD);
cyg_uint16 TIM_GetCapture1(TIM_TypeDef* TIMx);
cyg_uint16 TIM_GetCapture2(TIM_TypeDef* TIMx);
cyg_uint16 TIM_GetCapture3(TIM_TypeDef* TIMx);
cyg_uint16 TIM_GetCapture4(TIM_TypeDef* TIMx);
cyg_uint16 TIM_GetCounter(TIM_TypeDef* TIMx);
cyg_uint16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, cyg_uint16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, cyg_uint16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, cyg_uint16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, cyg_uint16 TIM_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_TIM_H */
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

