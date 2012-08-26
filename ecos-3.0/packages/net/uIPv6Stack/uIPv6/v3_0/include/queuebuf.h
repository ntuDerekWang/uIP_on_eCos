/**
 * \addtogroup rime
 * @{
 */

/**
 * \defgroup rimequeuebuf Rime queue buffer management
 * @{
 *
 * The queuebuf module handles buffers that are queued.
 *
 */

/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: queuebuf.h,v 1.3 2010/10/12 19:51:28 oliverschmidt Exp $
 */

/**
 * \file
 *         Header file for the Rime queue buffer management
 * \author
 *         Adam Dunkels <adam@sics.se>
 */
/***************
Usage:    #include "cyg/net/uIPv6Stack/uIPv6/queuebuf.h"
***************/
#ifndef __QUEUEBUF_H__
#define __QUEUEBUF_H__

#include "cyg/net/uIPv6Stack/uIPv6/packetbuf.h"


#ifdef QUEUEBUF_CONF_NUM
#define QUEUEBUF_NUM QUEUEBUF_CONF_NUM
#else
#define QUEUEBUF_NUM 8
#endif

struct queuebuf;

void queuebuf_init(void);

struct queuebuf *queuebuf_new_from_packetbuf(void);
void queuebuf_free(struct queuebuf *b);
void queuebuf_to_packetbuf(struct queuebuf *b);

void *queuebuf_dataptr(struct queuebuf *b);
int queuebuf_datalen(struct queuebuf *b);

rimeaddr_t *queuebuf_addr(struct queuebuf *b, cyg_uint8 type);
packetbuf_attr_t queuebuf_attr(struct queuebuf *b, cyg_uint8 type);

#endif /* __QUEUEBUF_H__ */

/** @} */
/** @} */
