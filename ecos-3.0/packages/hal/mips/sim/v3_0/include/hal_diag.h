#ifndef CYGONCE_HAL_HAL_DIAG_H
#define CYGONCE_HAL_HAL_DIAG_H

/*=============================================================================
//
//      hal_diag.h
//
//      HAL Support for Kernel Diagnostic Routines
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg
// Contributors:        nickg
// Date:        1998-03-02
// Purpose:     HAL Support for Kernel Diagnostic Routines
// Description: Diagnostic routines for use during kernel development.
// Usage:       #include <cyg/hal/hal_diag.h>
//
//####DESCRIPTIONEND####
//
//===========================================================================*/

#include <pkgconf/hal.h>

#include <cyg/infra/cyg_type.h>

/*---------------------------------------------------------------------------*/

#define CYG_DIAG_USE_PAL

/*---------------------------------------------------------------------------*/

#ifdef CYG_DIAG_USE_PAL

/*---------------------------------------------------------------------------*/
/* Register addresses                                                        */
  
#define PAL_RESET        0x00
#define PAL_CPU_NR       0x04
#define PAL_INT          0x08
#define PAL_NR_CPU       0x0a

#define PAL_READ_FIFO    0x10
#define PAL_READ_STATUS  0x14
#define PAL_WRITE_FIFO   0x18
#define PAL_WRITE_STATUS 0x1a

#define OEA_DEV          0xFFFF0000

/*---------------------------------------------------------------------------*/

#define HAL_DIAG_INIT()

#define HAL_DIAG_WRITE_CHAR(_c_)                        \
{                                                       \
    volatile unsigned char *tty_buffer =                \
        (unsigned char*)(OEA_DEV + PAL_WRITE_FIFO);     \
    volatile unsigned char *tty_status =                \
        (unsigned char*)(OEA_DEV + PAL_WRITE_STATUS);   \
    if( _c_ != '\r' )                                   \
    {                                                   \
        while( *tty_status == 0 ) continue;             \
        *tty_buffer = _c_;                              \
    }                                                   \
}

#define HAL_DIAG_READ_CHAR(_c_)                         \
{                                                       \
    volatile unsigned char *tty_buffer =                \
        (unsigned char*)(OEA_DEV + PAL_READ_FIFO);      \
    volatile unsigned char *tty_status =                \
        (unsigned char*)(OEA_DEV + PAL_READ_STATUS);    \
    while( *tty_status == 0 ) continue;                 \
    _c_ = *tty_buffer;                                  \
}

#else
/*---------------------------------------------------------------------------*/
/* There is no diagnostic output on MIPS simulator                           */

#define HAL_DIAG_INIT()

#define HAL_DIAG_WRITE_CHAR(_c_)

#define HAL_DIAG_READ_CHAR(_c_) (_c_) = 0

#endif

/*---------------------------------------------------------------------------*/
/* end of hal_diag.h                                                         */
#endif /* CYGONCE_HAL_HAL_DIAG_H */
