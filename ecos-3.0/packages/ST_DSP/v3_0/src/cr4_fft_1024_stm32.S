/*;******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
;* File Name          : cr4_fft_1024_stm32.s
;* Author             : MCD Application Team
;* Version            : V1.0.0
;* Date               : 10/06/2008
;* Description        : Optimized 1024-point radix-4 complex FFT for Cortex-M3
;********************************************************************************
;* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
;* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
;* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
;* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
;* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
;* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
;*******************************************************************************/

.cpu cortex-m3
.fpu softvfp   
.syntax unified
.thumb
.text	

.global cr4_fft_1024_stm32
.extern TableFFT
  
.equ NPT, 64


/*;*******************************************************************************
;* Function Name  : cr4_fft_1024_stm32
;* Description    : complex radix-4 1024 points FFT
;* Input          : - R0 = pssOUT: Output array .
;*                  - R1 = pssIN: Input array 
;*                  - R2 = Nbin: =1024 number of points, this optimized FFT function  
;*                    can only convert 1024 points.
;* Output         : None 
;* Return         : None
;*********************************************************************************/
.thumb_func
cr4_fft_1024_stm32:

        STMFD   SP!, {R4-R11, LR}
        
        MOV r12, #0
        MOV r3, r0 
        MOV r0,#0
        
preloop_v7:
        ADD     r14, r1, r12, LSR#22 /*1024pts*/
       
        LDRSH r5, [r14, #2]
        LDRSH r4, [r14],#NPT
        LDRSH r9, [r14, #2]
        LDRSH r8, [r14],#NPT
        LDRSH r7, [r14, #2]
        LDRSH r6, [r14],#NPT
        LDRSH r11, [r14, #2]
        LDRSH r10, [r14],#NPT

        ADD     r8, r8, r10
        ADD     r9, r9, r11
        SUB     r10, r8, r10, LSL#1  
        SUB     r11, r9, r11, LSL#1  

        MOV     r4, r4, ASR#2
        MOV     r5, r5, ASR#2
        ADD     r4, r4, r6, ASR#2
        ADD     r5, r5, r7, ASR#2
        SUB     r6, r4, r6, ASR#1
        SUB     r7, r5, r7, ASR#1

        ADD     r4, r4, r8, ASR#2
        ADD     r5, r5, r9, ASR#2
        SUB     r8, r4, r8, ASR#1
        SUB     r9, r5, r9, ASR#1

        ADD     r6, r6, r11, ASR#2
        SUB     r7, r7, r10, ASR#2
        SUB     r11, r6, r11, ASR#1
        ADD     r10, r7, r10, ASR#1
   
        STRH    r5, [r3, #2]
        STRH    r4, [r3], #4
        STRH    r7, [r3, #2]
        STRH    r6, [r3], #4
        STRH    r9, [r3, #2]
        STRH    r8, [r3], #4
        STRH    r10, [r3, #2]  
        STRH    r11, [r3], #4
        
         ADD r0, r0, #1
         
         RBIT r12, r0 
         
         CMP r0,#256 /*1024pts*/  
         BNE  preloop_v7

         SUB     r1, r3, r2, LSL#2
         MOV     r0, #16
         MOVS    r2, r2, LSR#4   

/*;------------------------------------------------------------------------------
;   The FFT coefficients table can be stored into Flash or RAM. 
;   The following two lines of code allow selecting the method for coefficients 
;   storage. 
;   In the case of choosing coefficients in RAM, you have to:
;   1. Include the file table_fft.h, which is a part of the DSP library, 
;      in your main file.
;   2. Decomment the line LDR.W pssK, =TableFFT and comment the line 
;      ADRL    pssK, TableFFT_V7
;   3. Comment all the TableFFT_V7 data.
;------------------------------------------------------------------------------*/
         ADR    r3, TableFFT_V7    
         /*LDR.W r3, =TableFFT*/      


passloop_v7:
         STMFD   SP!, {r1,r2}
         ADD     r12, r0, r0, LSL#1
         ADD     r1, r1, r12
         SUB     r2, r2, #1<<16

grouploop_v7:
         ADD     r2,r2,r0,LSL#(16-2)

butterloop_v7:
        		
         LDRSH r5, [r1, #2]
         LDRSH r4, [r1]
         SUB r1, r1, r0

      	LDRSH r11, [r3, #2]
      	LDRSH r10, [r3]
      	ADD r3, r3, #4

         SUB  r14, r5, r4         
         MUL  r12, r14, r11        
         ADD  r14, r10, r11, LSL#1  
         MLA  r11, r5, r10, r12     
         MLA  r10, r4, r14, r12   

         LDRSH r5, [r1, #2]
         LDRSH r4, [r1]
         SUB r1, r1, r0
				
      	LDRSH r9, [r3, #2]
      	LDRSH r8, [r3]
      	ADD r3, r3, #4
        
         SUB  r14, r5, r4         
         MUL  r12, r14, r9        
         ADD  r14, r8, r9, LSL#1  
         MLA  r9, r5, r8, r12     
         MLA  r8, r4, r14, r12   
	
         LDRSH r5, [r1, #2]
         LDRSH r4, [r1]
         SUB r1, r1, r0
				
         LDRSH r7, [r3, #2]
      	LDRSH r6, [r3]
      	ADD r3, r3, #4
		
         SUB  r14, r5, r4        
         MUL  r12, r14, r7        
         ADD  r14, r6, r7, LSL#1  
         MLA  r7, r5, r6, r12     
         MLA  r6, r4, r14, r12   
		
         LDRSH r5, [r1, #2]
      	LDRSH r4, [r1]
    		
         ADD     r8, r8, r10
         ADD     r9, r9, r11
         SUB     r10, r8, r10, LSL#1
         SUB     r11, r9, r11, LSL#1

         MOV     r4, r4, ASR#2
         MOV     r5, r5, ASR#2
         ADD     r4, r4, r6, ASR#(2+14)
         ADD     r5, r5, r7, ASR#(2+14)
         SUB     r6, r4, r6, ASR#(1+14)
         SUB     r7, r5, r7, ASR#(1+14)

         ADD     r4, r4, r8, ASR#(2+14)
         ADD     r5, r5, r9, ASR#(2+14)
         SUB     r8, r4, r8, ASR#(1+14)
         SUB     r9, r5, r9, ASR#(1+14)

         ADD     r6, r6, r11, ASR#(2+14)
         SUB     r7, r7, r10, ASR#(2+14)
         SUB     r11, r6, r11, ASR#(1+14)
         ADD     r10, r7, r10, ASR#(1+14)      

         STRH    r5, [r1, #2]
         STRH    r4, [r1]
         ADD 	r1, r1, r0
         STRH    r7, [r1, #2]
         STRH    r6, [r1]
         ADD     r1, r1, r0
         STRH    r9, [r1, #2]
         STRH    r8, [r1]
         ADD     r1, r1, r0
         STRH    r10, [r1, #2]  
         STRH    r11, [r1], #4
         SUBS        r2,r2, #1<<16
         BGE     butterloop_v7
         ADD     r12, r0, r0, LSL#1
         ADD     r1, r1, r12

         SUB     r2, r2, #1
         MOVS    r14, r2, LSL#16
         IT      ne
         SUBNE   r3, r3, r12
         BNE     grouploop_v7

         LDMFD   sp!, {r1, r2}
         MOV  r0,r0,LSL#2		
         MOVS    r2, r2, LSR#2
       	BNE     passloop_v7
       	LDMFD   SP!, {R4-R11, PC}


TableFFT_V7:

        /*N=16*/
        .short 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000
        .short 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41
        .short 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000
        .short 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41
        /*N=64*/
        .short 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000
        .short 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c
        .short 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e
        .short 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e
        .short 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41
        .short 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537
        .short 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21
        .short 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5
        .short 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000
        .short 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5
        .short 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21
        .short 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537
        .short 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41
        .short 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e
        .short 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e
        .short 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c
        /*N=256*/
        .short 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000
        .short 0x3b1e,0x04b5, 0x3e69,0x0192, 0x3cc8,0x0324
        .short 0x35eb,0x0964, 0x3cc8,0x0324, 0x396b,0x0646
        .short 0x306c,0x0e06, 0x3b1e,0x04b5, 0x35eb,0x0964
        .short 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c
        .short 0x24ae,0x1709, 0x37af,0x07d6, 0x2e88,0x0f8d
        .short 0x1e7e,0x1b5d, 0x35eb,0x0964, 0x2aaa,0x1294
        .short 0x1824,0x1f8c, 0x341e,0x0af1, 0x26b3,0x1590
        .short 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e
        .short 0x0b14,0x2760, 0x306c,0x0e06, 0x1e7e,0x1b5d
        .short 0x0471,0x2afb, 0x2e88,0x0f8d, 0x1a46,0x1e2b
        .short 0xfdc7,0x2e5a, 0x2c9d,0x1112, 0x15fe,0x20e7
        .short 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e
        .short 0xf087,0x3453, 0x28b2,0x1413, 0x0d48,0x2620
        .short 0xea02,0x36e5, 0x26b3,0x1590, 0x08df,0x289a
        .short 0xe39c,0x392b, 0x24ae,0x1709, 0x0471,0x2afb
        .short 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41
        .short 0xd74e,0x3cc5, 0x2093,0x19ef, 0xfb8f,0x2f6c
        .short 0xd178,0x3e15, 0x1e7e,0x1b5d, 0xf721,0x3179
        .short 0xcbe2,0x3f0f, 0x1c64,0x1cc6, 0xf2b8,0x3368
        .short 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537
        .short 0xc197,0x3ffb, 0x1824,0x1f8c, 0xea02,0x36e5
        .short 0xbcf0,0x3fec, 0x15fe,0x20e7, 0xe5ba,0x3871
        .short 0xb8a6,0x3f85, 0x13d5,0x223d, 0xe182,0x39db
        .short 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21
        .short 0xb140,0x3daf, 0x0f79,0x24da, 0xd94d,0x3c42
        .short 0xae2e,0x3c42, 0x0d48,0x2620, 0xd556,0x3d3f
        .short 0xab8e,0x3a82, 0x0b14,0x2760, 0xd178,0x3e15
        .short 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5
        .short 0xa7b1,0x3612, 0x06a9,0x29ce, 0xca15,0x3f4f
        .short 0xa678,0x3368, 0x0471,0x2afb, 0xc695,0x3fb1
        .short 0xa5bc,0x3076, 0x0239,0x2c21, 0xc338,0x3fec
        .short 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000
        .short 0xa5bc,0x29ce, 0xfdc7,0x2e5a, 0xbcf0,0x3fec
        .short 0xa678,0x2620, 0xfb8f,0x2f6c, 0xba09,0x3fb1
        .short 0xa7b1,0x223d, 0xf957,0x3076, 0xb74d,0x3f4f
        .short 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5
        .short 0xab8e,0x19ef, 0xf4ec,0x3274, 0xb25e,0x3e15
        .short 0xae2e,0x1590, 0xf2b8,0x3368, 0xb02d,0x3d3f
        .short 0xb140,0x1112, 0xf087,0x3453, 0xae2e,0x3c42
        .short 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21
        .short 0xb8a6,0x07d6, 0xec2b,0x3612, 0xaac8,0x39db
        .short 0xbcf0,0x0324, 0xea02,0x36e5, 0xa963,0x3871
        .short 0xc197,0xfe6e, 0xe7dc,0x37b0, 0xa834,0x36e5
        .short 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537
        .short 0xcbe2,0xf50f, 0xe39c,0x392b, 0xa678,0x3368
        .short 0xd178,0xf073, 0xe182,0x39db, 0xa5ed,0x3179
        .short 0xd74e,0xebed, 0xdf6d,0x3a82, 0xa599,0x2f6c
        .short 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41
        .short 0xe39c,0xe33a, 0xdb52,0x3bb6, 0xa599,0x2afb
        .short 0xea02,0xdf19, 0xd94d,0x3c42, 0xa5ed,0x289a
        .short 0xf087,0xdb26, 0xd74e,0x3cc5, 0xa678,0x2620
        .short 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e
        .short 0xfdc7,0xd3df, 0xd363,0x3daf, 0xa834,0x20e7
        .short 0x0471,0xd094, 0xd178,0x3e15, 0xa963,0x1e2b
        .short 0x0b14,0xcd8c, 0xcf94,0x3e72, 0xaac8,0x1b5d
        .short 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e
        .short 0x1824,0xc850, 0xcbe2,0x3f0f, 0xae2e,0x1590
        .short 0x1e7e,0xc625, 0xca15,0x3f4f, 0xb02d,0x1294
        .short 0x24ae,0xc44a, 0xc851,0x3f85, 0xb25e,0x0f8d
        .short 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c
        .short 0x306c,0xc18e, 0xc4e2,0x3fd4, 0xb74d,0x0964
        .short 0x35eb,0xc0b1, 0xc338,0x3fec, 0xba09,0x0646
        .short 0x3b1e,0xc02c, 0xc197,0x3ffb, 0xbcf0,0x0324
        /*N=1024*/
        .short 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000
        .short 0x3ed0,0x012e, 0x3f9b,0x0065, 0x3f36,0x00c9
        .short 0x3d9a,0x025b, 0x3f36,0x00c9, 0x3e69,0x0192
        .short 0x3c5f,0x0388, 0x3ed0,0x012e, 0x3d9a,0x025b
        .short 0x3b1e,0x04b5, 0x3e69,0x0192, 0x3cc8,0x0324
        .short 0x39d9,0x05e2, 0x3e02,0x01f7, 0x3bf4,0x03ed
        .short 0x388e,0x070e, 0x3d9a,0x025b, 0x3b1e,0x04b5
        .short 0x373f,0x0839, 0x3d31,0x02c0, 0x3a46,0x057e
        .short 0x35eb,0x0964, 0x3cc8,0x0324, 0x396b,0x0646
        .short 0x3492,0x0a8e, 0x3c5f,0x0388, 0x388e,0x070e
        .short 0x3334,0x0bb7, 0x3bf4,0x03ed, 0x37af,0x07d6
        .short 0x31d2,0x0cdf, 0x3b8a,0x0451, 0x36ce,0x089d
        .short 0x306c,0x0e06, 0x3b1e,0x04b5, 0x35eb,0x0964
        .short 0x2f02,0x0f2b, 0x3ab2,0x051a, 0x3505,0x0a2b
        .short 0x2d93,0x1050, 0x3a46,0x057e, 0x341e,0x0af1
        .short 0x2c21,0x1173, 0x39d9,0x05e2, 0x3334,0x0bb7
        .short 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c
        .short 0x2931,0x13b4, 0x38fd,0x06aa, 0x315b,0x0d41
        .short 0x27b3,0x14d2, 0x388e,0x070e, 0x306c,0x0e06
        .short 0x2632,0x15ee, 0x381f,0x0772, 0x2f7b,0x0eca
        .short 0x24ae,0x1709, 0x37af,0x07d6, 0x2e88,0x0f8d
        .short 0x2326,0x1821, 0x373f,0x0839, 0x2d93,0x1050
        .short 0x219c,0x1937, 0x36ce,0x089d, 0x2c9d,0x1112
        .short 0x200e,0x1a4b, 0x365d,0x0901, 0x2ba4,0x11d3
        .short 0x1e7e,0x1b5d, 0x35eb,0x0964, 0x2aaa,0x1294
        .short 0x1ceb,0x1c6c, 0x3578,0x09c7, 0x29af,0x1354
        .short 0x1b56,0x1d79, 0x3505,0x0a2b, 0x28b2,0x1413
        .short 0x19be,0x1e84, 0x3492,0x0a8e, 0x27b3,0x14d2
        .short 0x1824,0x1f8c, 0x341e,0x0af1, 0x26b3,0x1590
        .short 0x1688,0x2091, 0x33a9,0x0b54, 0x25b1,0x164c
        .short 0x14ea,0x2193, 0x3334,0x0bb7, 0x24ae,0x1709
        .short 0x134a,0x2292, 0x32bf,0x0c1a, 0x23a9,0x17c4
        .short 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e
        .short 0x1005,0x2488, 0x31d2,0x0cdf, 0x219c,0x1937
        .short 0x0e61,0x257e, 0x315b,0x0d41, 0x2093,0x19ef
        .short 0x0cbb,0x2671, 0x30e4,0x0da4, 0x1f89,0x1aa7
        .short 0x0b14,0x2760, 0x306c,0x0e06, 0x1e7e,0x1b5d
        .short 0x096d,0x284c, 0x2ff4,0x0e68, 0x1d72,0x1c12
        .short 0x07c4,0x2935, 0x2f7b,0x0eca, 0x1c64,0x1cc6
        .short 0x061b,0x2a1a, 0x2f02,0x0f2b, 0x1b56,0x1d79
        .short 0x0471,0x2afb, 0x2e88,0x0f8d, 0x1a46,0x1e2b
        .short 0x02c7,0x2bd8, 0x2e0e,0x0fee, 0x1935,0x1edc
        .short 0x011c,0x2cb2, 0x2d93,0x1050, 0x1824,0x1f8c
        .short 0xff72,0x2d88, 0x2d18,0x10b1, 0x1711,0x203a
        .short 0xfdc7,0x2e5a, 0x2c9d,0x1112, 0x15fe,0x20e7
        .short 0xfc1d,0x2f28, 0x2c21,0x1173, 0x14ea,0x2193
        .short 0xfa73,0x2ff2, 0x2ba4,0x11d3, 0x13d5,0x223d
        .short 0xf8ca,0x30b8, 0x2b28,0x1234, 0x12bf,0x22e7
        .short 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e
        .short 0xf579,0x3236, 0x2a2d,0x12f4, 0x1091,0x2435
        .short 0xf3d2,0x32ef, 0x29af,0x1354, 0x0f79,0x24da
        .short 0xf22c,0x33a3, 0x2931,0x13b4, 0x0e61,0x257e
        .short 0xf087,0x3453, 0x28b2,0x1413, 0x0d48,0x2620
        .short 0xeee3,0x34ff, 0x2833,0x1473, 0x0c2e,0x26c1
        .short 0xed41,0x35a5, 0x27b3,0x14d2, 0x0b14,0x2760
        .short 0xeba1,0x3648, 0x2733,0x1531, 0x09fa,0x27fe
        .short 0xea02,0x36e5, 0x26b3,0x1590, 0x08df,0x289a
        .short 0xe865,0x377e, 0x2632,0x15ee, 0x07c4,0x2935
        .short 0xe6cb,0x3812, 0x25b1,0x164c, 0x06a9,0x29ce
        .short 0xe532,0x38a1, 0x252f,0x16ab, 0x058d,0x2a65
        .short 0xe39c,0x392b, 0x24ae,0x1709, 0x0471,0x2afb
        .short 0xe208,0x39b0, 0x242b,0x1766, 0x0355,0x2b8f
        .short 0xe077,0x3a30, 0x23a9,0x17c4, 0x0239,0x2c21
        .short 0xdee9,0x3aab, 0x2326,0x1821, 0x011c,0x2cb2
        .short 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41
        .short 0xdbd5,0x3b92, 0x221f,0x18db, 0xfee4,0x2dcf
        .short 0xda4f,0x3bfd, 0x219c,0x1937, 0xfdc7,0x2e5a
        .short 0xd8cd,0x3c64, 0x2117,0x1993, 0xfcab,0x2ee4
        .short 0xd74e,0x3cc5, 0x2093,0x19ef, 0xfb8f,0x2f6c
        .short 0xd5d3,0x3d21, 0x200e,0x1a4b, 0xfa73,0x2ff2
        .short 0xd45c,0x3d78, 0x1f89,0x1aa7, 0xf957,0x3076
        .short 0xd2e8,0x3dc9, 0x1f04,0x1b02, 0xf83c,0x30f9
        .short 0xd178,0x3e15, 0x1e7e,0x1b5d, 0xf721,0x3179
        .short 0xd00c,0x3e5c, 0x1df8,0x1bb8, 0xf606,0x31f8
        .short 0xcea5,0x3e9d, 0x1d72,0x1c12, 0xf4ec,0x3274
        .short 0xcd41,0x3ed8, 0x1ceb,0x1c6c, 0xf3d2,0x32ef
        .short 0xcbe2,0x3f0f, 0x1c64,0x1cc6, 0xf2b8,0x3368
        .short 0xca88,0x3f40, 0x1bdd,0x1d20, 0xf19f,0x33df
        .short 0xc932,0x3f6b, 0x1b56,0x1d79, 0xf087,0x3453
        .short 0xc7e1,0x3f91, 0x1ace,0x1dd3, 0xef6f,0x34c6
        .short 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537
        .short 0xc54e,0x3fcc, 0x19be,0x1e84, 0xed41,0x35a5
        .short 0xc40c,0x3fe1, 0x1935,0x1edc, 0xec2b,0x3612
        .short 0xc2cf,0x3ff1, 0x18ad,0x1f34, 0xeb16,0x367d
        .short 0xc197,0x3ffb, 0x1824,0x1f8c, 0xea02,0x36e5
        .short 0xc065,0x4000, 0x179b,0x1fe3, 0xe8ef,0x374b
        .short 0xbf38,0x3fff, 0x1711,0x203a, 0xe7dc,0x37b0
        .short 0xbe11,0x3ff8, 0x1688,0x2091, 0xe6cb,0x3812
        .short 0xbcf0,0x3fec, 0x15fe,0x20e7, 0xe5ba,0x3871
        .short 0xbbd4,0x3fdb, 0x1574,0x213d, 0xe4aa,0x38cf
        .short 0xbabf,0x3fc4, 0x14ea,0x2193, 0xe39c,0x392b
        .short 0xb9af,0x3fa7, 0x145f,0x21e8, 0xe28e,0x3984
        .short 0xb8a6,0x3f85, 0x13d5,0x223d, 0xe182,0x39db
        .short 0xb7a2,0x3f5d, 0x134a,0x2292, 0xe077,0x3a30
        .short 0xb6a5,0x3f30, 0x12bf,0x22e7, 0xdf6d,0x3a82
        .short 0xb5af,0x3efd, 0x1234,0x233b, 0xde64,0x3ad3
        .short 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21
        .short 0xb3d5,0x3e88, 0x111d,0x23e2, 0xdc57,0x3b6d
        .short 0xb2f2,0x3e45, 0x1091,0x2435, 0xdb52,0x3bb6
        .short 0xb215,0x3dfc, 0x1005,0x2488, 0xda4f,0x3bfd
        .short 0xb140,0x3daf, 0x0f79,0x24da, 0xd94d,0x3c42
        .short 0xb071,0x3d5b, 0x0eed,0x252c, 0xd84d,0x3c85
        .short 0xafa9,0x3d03, 0x0e61,0x257e, 0xd74e,0x3cc5
        .short 0xaee8,0x3ca5, 0x0dd4,0x25cf, 0xd651,0x3d03
        .short 0xae2e,0x3c42, 0x0d48,0x2620, 0xd556,0x3d3f
        .short 0xad7b,0x3bda, 0x0cbb,0x2671, 0xd45c,0x3d78
        .short 0xacd0,0x3b6d, 0x0c2e,0x26c1, 0xd363,0x3daf
        .short 0xac2b,0x3afa, 0x0ba1,0x2711, 0xd26d,0x3de3
        .short 0xab8e,0x3a82, 0x0b14,0x2760, 0xd178,0x3e15
        .short 0xaaf8,0x3a06, 0x0a87,0x27af, 0xd085,0x3e45
        .short 0xaa6a,0x3984, 0x09fa,0x27fe, 0xcf94,0x3e72
        .short 0xa9e3,0x38fd, 0x096d,0x284c, 0xcea5,0x3e9d
        .short 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5
        .short 0xa8eb,0x37e1, 0x0852,0x28e7, 0xcccc,0x3eeb
        .short 0xa87b,0x374b, 0x07c4,0x2935, 0xcbe2,0x3f0f
        .short 0xa812,0x36b1, 0x0736,0x2981, 0xcafb,0x3f30
        .short 0xa7b1,0x3612, 0x06a9,0x29ce, 0xca15,0x3f4f
        .short 0xa757,0x356e, 0x061b,0x2a1a, 0xc932,0x3f6b
        .short 0xa705,0x34c6, 0x058d,0x2a65, 0xc851,0x3f85
        .short 0xa6bb,0x3419, 0x04ff,0x2ab0, 0xc772,0x3f9c
        .short 0xa678,0x3368, 0x0471,0x2afb, 0xc695,0x3fb1
        .short 0xa63e,0x32b2, 0x03e3,0x2b45, 0xc5ba,0x3fc4
        .short 0xa60b,0x31f8, 0x0355,0x2b8f, 0xc4e2,0x3fd4
        .short 0xa5e0,0x3139, 0x02c7,0x2bd8, 0xc40c,0x3fe1
        .short 0xa5bc,0x3076, 0x0239,0x2c21, 0xc338,0x3fec
        .short 0xa5a1,0x2faf, 0x01aa,0x2c6a, 0xc266,0x3ff5
        .short 0xa58d,0x2ee4, 0x011c,0x2cb2, 0xc197,0x3ffb
        .short 0xa581,0x2e15, 0x008e,0x2cfa, 0xc0ca,0x3fff
        .short 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000
        .short 0xa581,0x2c6a, 0xff72,0x2d88, 0xbf38,0x3fff
        .short 0xa58d,0x2b8f, 0xfee4,0x2dcf, 0xbe73,0x3ffb
        .short 0xa5a1,0x2ab0, 0xfe56,0x2e15, 0xbdb0,0x3ff5
        .short 0xa5bc,0x29ce, 0xfdc7,0x2e5a, 0xbcf0,0x3fec
        .short 0xa5e0,0x28e7, 0xfd39,0x2e9f, 0xbc32,0x3fe1
        .short 0xa60b,0x27fe, 0xfcab,0x2ee4, 0xbb77,0x3fd4
        .short 0xa63e,0x2711, 0xfc1d,0x2f28, 0xbabf,0x3fc4
        .short 0xa678,0x2620, 0xfb8f,0x2f6c, 0xba09,0x3fb1
        .short 0xa6bb,0x252c, 0xfb01,0x2faf, 0xb956,0x3f9c
        .short 0xa705,0x2435, 0xfa73,0x2ff2, 0xb8a6,0x3f85
        .short 0xa757,0x233b, 0xf9e5,0x3034, 0xb7f8,0x3f6b
        .short 0xa7b1,0x223d, 0xf957,0x3076, 0xb74d,0x3f4f
        .short 0xa812,0x213d, 0xf8ca,0x30b8, 0xb6a5,0x3f30
        .short 0xa87b,0x203a, 0xf83c,0x30f9, 0xb600,0x3f0f
        .short 0xa8eb,0x1f34, 0xf7ae,0x3139, 0xb55e,0x3eeb
        .short 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5
        .short 0xa9e3,0x1d20, 0xf693,0x31b9, 0xb422,0x3e9d
        .short 0xaa6a,0x1c12, 0xf606,0x31f8, 0xb388,0x3e72
        .short 0xaaf8,0x1b02, 0xf579,0x3236, 0xb2f2,0x3e45
        .short 0xab8e,0x19ef, 0xf4ec,0x3274, 0xb25e,0x3e15
        .short 0xac2b,0x18db, 0xf45f,0x32b2, 0xb1cd,0x3de3
        .short 0xacd0,0x17c4, 0xf3d2,0x32ef, 0xb140,0x3daf
        .short 0xad7b,0x16ab, 0xf345,0x332c, 0xb0b5,0x3d78
        .short 0xae2e,0x1590, 0xf2b8,0x3368, 0xb02d,0x3d3f
        .short 0xaee8,0x1473, 0xf22c,0x33a3, 0xafa9,0x3d03
        .short 0xafa9,0x1354, 0xf19f,0x33df, 0xaf28,0x3cc5
        .short 0xb071,0x1234, 0xf113,0x3419, 0xaea9,0x3c85
        .short 0xb140,0x1112, 0xf087,0x3453, 0xae2e,0x3c42
        .short 0xb215,0x0fee, 0xeffb,0x348d, 0xadb6,0x3bfd
        .short 0xb2f2,0x0eca, 0xef6f,0x34c6, 0xad41,0x3bb6
        .short 0xb3d5,0x0da4, 0xeee3,0x34ff, 0xacd0,0x3b6d
        .short 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21
        .short 0xb5af,0x0b54, 0xedcc,0x356e, 0xabf6,0x3ad3
        .short 0xb6a5,0x0a2b, 0xed41,0x35a5, 0xab8e,0x3a82
        .short 0xb7a2,0x0901, 0xecb6,0x35dc, 0xab29,0x3a30
        .short 0xb8a6,0x07d6, 0xec2b,0x3612, 0xaac8,0x39db
        .short 0xb9af,0x06aa, 0xeba1,0x3648, 0xaa6a,0x3984
        .short 0xbabf,0x057e, 0xeb16,0x367d, 0xaa0f,0x392b
        .short 0xbbd4,0x0451, 0xea8c,0x36b1, 0xa9b7,0x38cf
        .short 0xbcf0,0x0324, 0xea02,0x36e5, 0xa963,0x3871
        .short 0xbe11,0x01f7, 0xe978,0x3718, 0xa912,0x3812
        .short 0xbf38,0x00c9, 0xe8ef,0x374b, 0xa8c5,0x37b0
        .short 0xc065,0xff9b, 0xe865,0x377e, 0xa87b,0x374b
        .short 0xc197,0xfe6e, 0xe7dc,0x37b0, 0xa834,0x36e5
        .short 0xc2cf,0xfd40, 0xe753,0x37e1, 0xa7f1,0x367d
        .short 0xc40c,0xfc13, 0xe6cb,0x3812, 0xa7b1,0x3612
        .short 0xc54e,0xfae6, 0xe642,0x3842, 0xa774,0x35a5
        .short 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537
        .short 0xc7e1,0xf88e, 0xe532,0x38a1, 0xa705,0x34c6
        .short 0xc932,0xf763, 0xe4aa,0x38cf, 0xa6d3,0x3453
        .short 0xca88,0xf639, 0xe423,0x38fd, 0xa6a4,0x33df
        .short 0xcbe2,0xf50f, 0xe39c,0x392b, 0xa678,0x3368
        .short 0xcd41,0xf3e6, 0xe315,0x3958, 0xa650,0x32ef
        .short 0xcea5,0xf2bf, 0xe28e,0x3984, 0xa62c,0x3274
        .short 0xd00c,0xf198, 0xe208,0x39b0, 0xa60b,0x31f8
        .short 0xd178,0xf073, 0xe182,0x39db, 0xa5ed,0x3179
        .short 0xd2e8,0xef4f, 0xe0fc,0x3a06, 0xa5d3,0x30f9
        .short 0xd45c,0xee2d, 0xe077,0x3a30, 0xa5bc,0x3076
        .short 0xd5d3,0xed0c, 0xdff2,0x3a59, 0xa5a9,0x2ff2
        .short 0xd74e,0xebed, 0xdf6d,0x3a82, 0xa599,0x2f6c
        .short 0xd8cd,0xeacf, 0xdee9,0x3aab, 0xa58d,0x2ee4
        .short 0xda4f,0xe9b4, 0xde64,0x3ad3, 0xa585,0x2e5a
        .short 0xdbd5,0xe89a, 0xdde1,0x3afa, 0xa57f,0x2dcf
        .short 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41
        .short 0xdee9,0xe66d, 0xdcda,0x3b47, 0xa57f,0x2cb2
        .short 0xe077,0xe559, 0xdc57,0x3b6d, 0xa585,0x2c21
        .short 0xe208,0xe448, 0xdbd5,0x3b92, 0xa58d,0x2b8f
        .short 0xe39c,0xe33a, 0xdb52,0x3bb6, 0xa599,0x2afb
        .short 0xe532,0xe22d, 0xdad1,0x3bda, 0xa5a9,0x2a65
        .short 0xe6cb,0xe124, 0xda4f,0x3bfd, 0xa5bc,0x29ce
        .short 0xe865,0xe01d, 0xd9ce,0x3c20, 0xa5d3,0x2935
        .short 0xea02,0xdf19, 0xd94d,0x3c42, 0xa5ed,0x289a
        .short 0xeba1,0xde18, 0xd8cd,0x3c64, 0xa60b,0x27fe
        .short 0xed41,0xdd19, 0xd84d,0x3c85, 0xa62c,0x2760
        .short 0xeee3,0xdc1e, 0xd7cd,0x3ca5, 0xa650,0x26c1
        .short 0xf087,0xdb26, 0xd74e,0x3cc5, 0xa678,0x2620
        .short 0xf22c,0xda31, 0xd6cf,0x3ce4, 0xa6a4,0x257e
        .short 0xf3d2,0xd93f, 0xd651,0x3d03, 0xa6d3,0x24da
        .short 0xf579,0xd851, 0xd5d3,0x3d21, 0xa705,0x2435
        .short 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e
        .short 0xf8ca,0xd67f, 0xd4d8,0x3d5b, 0xa774,0x22e7
        .short 0xfa73,0xd59b, 0xd45c,0x3d78, 0xa7b1,0x223d
        .short 0xfc1d,0xd4bb, 0xd3df,0x3d93, 0xa7f1,0x2193
        .short 0xfdc7,0xd3df, 0xd363,0x3daf, 0xa834,0x20e7
        .short 0xff72,0xd306, 0xd2e8,0x3dc9, 0xa87b,0x203a
        .short 0x011c,0xd231, 0xd26d,0x3de3, 0xa8c5,0x1f8c
        .short 0x02c7,0xd161, 0xd1f2,0x3dfc, 0xa912,0x1edc
        .short 0x0471,0xd094, 0xd178,0x3e15, 0xa963,0x1e2b
        .short 0x061b,0xcfcc, 0xd0fe,0x3e2d, 0xa9b7,0x1d79
        .short 0x07c4,0xcf07, 0xd085,0x3e45, 0xaa0f,0x1cc6
        .short 0x096d,0xce47, 0xd00c,0x3e5c, 0xaa6a,0x1c12
        .short 0x0b14,0xcd8c, 0xcf94,0x3e72, 0xaac8,0x1b5d
        .short 0x0cbb,0xccd4, 0xcf1c,0x3e88, 0xab29,0x1aa7
        .short 0x0e61,0xcc21, 0xcea5,0x3e9d, 0xab8e,0x19ef
        .short 0x1005,0xcb73, 0xce2e,0x3eb1, 0xabf6,0x1937
        .short 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e
        .short 0x134a,0xca24, 0xcd41,0x3ed8, 0xacd0,0x17c4
        .short 0x14ea,0xc983, 0xcccc,0x3eeb, 0xad41,0x1709
        .short 0x1688,0xc8e8, 0xcc57,0x3efd, 0xadb6,0x164c
        .short 0x1824,0xc850, 0xcbe2,0x3f0f, 0xae2e,0x1590
        .short 0x19be,0xc7be, 0xcb6e,0x3f20, 0xaea9,0x14d2
        .short 0x1b56,0xc731, 0xcafb,0x3f30, 0xaf28,0x1413
        .short 0x1ceb,0xc6a8, 0xca88,0x3f40, 0xafa9,0x1354
        .short 0x1e7e,0xc625, 0xca15,0x3f4f, 0xb02d,0x1294
        .short 0x200e,0xc5a7, 0xc9a3,0x3f5d, 0xb0b5,0x11d3
        .short 0x219c,0xc52d, 0xc932,0x3f6b, 0xb140,0x1112
        .short 0x2326,0xc4b9, 0xc8c1,0x3f78, 0xb1cd,0x1050
        .short 0x24ae,0xc44a, 0xc851,0x3f85, 0xb25e,0x0f8d
        .short 0x2632,0xc3e0, 0xc7e1,0x3f91, 0xb2f2,0x0eca
        .short 0x27b3,0xc37b, 0xc772,0x3f9c, 0xb388,0x0e06
        .short 0x2931,0xc31c, 0xc703,0x3fa7, 0xb422,0x0d41
        .short 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c
        .short 0x2c21,0xc26d, 0xc627,0x3fbb, 0xb55e,0x0bb7
        .short 0x2d93,0xc21d, 0xc5ba,0x3fc4, 0xb600,0x0af1
        .short 0x2f02,0xc1d3, 0xc54e,0x3fcc, 0xb6a5,0x0a2b
        .short 0x306c,0xc18e, 0xc4e2,0x3fd4, 0xb74d,0x0964
        .short 0x31d2,0xc14f, 0xc476,0x3fdb, 0xb7f8,0x089d
        .short 0x3334,0xc115, 0xc40c,0x3fe1, 0xb8a6,0x07d6
        .short 0x3492,0xc0e0, 0xc3a1,0x3fe7, 0xb956,0x070e
        .short 0x35eb,0xc0b1, 0xc338,0x3fec, 0xba09,0x0646
        .short 0x373f,0xc088, 0xc2cf,0x3ff1, 0xbabf,0x057e
        .short 0x388e,0xc064, 0xc266,0x3ff5, 0xbb77,0x04b5
        .short 0x39d9,0xc045, 0xc1fe,0x3ff8, 0xbc32,0x03ed
        .short 0x3b1e,0xc02c, 0xc197,0x3ffb, 0xbcf0,0x0324
        .short 0x3c5f,0xc019, 0xc130,0x3ffd, 0xbdb0,0x025b
        .short 0x3d9a,0xc00b, 0xc0ca,0x3fff, 0xbe73,0x0192
        .short 0x3ed0,0xc003, 0xc065,0x4000, 0xbf38,0x00c9
        
        
.end       
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
