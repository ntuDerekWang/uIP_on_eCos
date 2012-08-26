/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32_dsp.h
* Author             : MCD Application Team
* Version            : V1.0.0
* Date               : 10/06/2008
* Description        : This source file contains prototypes of DSP functions
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DSP_H
#define __STM32F10x_DSP_H
#include "cyg/infra/cyg_type.h"
/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
/* for block FIR module */
typedef struct {
  cyg_uint16 *h;
  cyg_uint32 nh;
} COEFS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* FIR 16-bit filter in assembly */
void fir_16by16_stm32(void *y, void *x, COEFS *c, cyg_uint32 N);

/* PID controller in C, error computed outside the function */
cyg_uint16 DoPID(cyg_uint16 Error, cyg_uint16 *Coeff);

/* Full PID in C, error computed inside the function */
cyg_uint16 DoFullPID(cyg_uint16 In, cyg_uint16 Ref, cyg_uint16 *Coeff);

/* PID controller in assembly, error computed outside the function */
cyg_uint16 PID_stm32(cyg_uint16 Error, cyg_uint16 *Coeff);

/* Radix-4 complex FFT for STM32, in assembly  */
/* 64 points*/
void cr4_fft_64_stm32(void *pssOUT, void *pssIN, cyg_uint16 Nbin);
/* 256 points */
void cr4_fft_256_stm32(void *pssOUT, void *pssIN, cyg_uint16 Nbin);
/* 1024 points */
void cr4_fft_1024_stm32(void *pssOUT, void *pssIN, cyg_uint16 Nbin);

/* IIR filter in assembly */
void iirarma_stm32(void *y, void *x, cyg_uint16 *h2, cyg_uint16 *h1, cyg_uint32 ny );

/* IIR filter in C */
void iir_biquad_stm32(cyg_uint16 *y, cyg_uint16 *x, s16 *IIRCoeff, cyg_uint16 ny);

#endif /* __STM32F10x_DSP_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
