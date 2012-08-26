/**
 * \addtogroup rimequeuebuf
 * @{
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
 * $Id: queuebuf.c,v 1.4 2010/10/12 19:51:28 oliverschmidt Exp $
 */

/**
 * \file
 *         Implementation of the Rime queue buffers
 * \author
 *         Adam Dunkels <adam@sics.se>
 */
/*
#include "contiki-net.h"//////////待處理
*/
#include "cyg/net/uIPv6Stack/uIPv6/queuebuf.h"
#include "cyg/net/uIPv6Stack/uIPv6/memb_lib.h"
 
#include <string.h> /* for memcpy() */

#ifdef QUEUEBUF_CONF_REF_NUM
#define QUEUEBUF_REF_NUM QUEUEBUF_CONF_REF_NUM
#else
#define QUEUEBUF_REF_NUM 2
#endif

struct queuebuf {
  cyg_uint16 len;
  cyg_uint8 data[PACKETBUF_SIZE];
  struct packetbuf_attr attrs[PACKETBUF_NUM_ATTRS];
  struct packetbuf_addr addrs[PACKETBUF_NUM_ADDRS];
};

struct queuebuf_ref {
  cyg_uint16 len;
  cyg_uint8 *ref;
  cyg_uint8 hdr[PACKETBUF_HDR_SIZE];
  cyg_uint8 hdrlen;
};

MEMB(bufmem, struct queuebuf, QUEUEBUF_NUM);
MEMB(refbufmem, struct queuebuf_ref, QUEUEBUF_REF_NUM);

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#ifdef QUEUEBUF_CONF_STATS
#define QUEUEBUF_STATS QUEUEBUF_CONF_STATS
#else
#define QUEUEBUF_STATS 0
#endif /* QUEUEBUF_CONF_STATS */

#if QUEUEBUF_STATS
cyg_uint8 queuebuf_len, queuebuf_ref_len, queuebuf_max_len;
#endif /* QUEUEBUF_STATS */

/*---------------------------------------------------------------------------*/
void
queuebuf_init(void)
{
  memb_init(&bufmem);
  memb_init(&refbufmem);
#if QUEUEBUF_STATS
  queuebuf_max_len = QUEUEBUF_NUM;
#endif /* QUEUEBUF_STATS */
}
/*---------------------------------------------------------------------------*/
struct queuebuf *
queuebuf_new_from_packetbuf(void)
{
  struct queuebuf *buf;
  struct queuebuf_ref *rbuf;

  if(packetbuf_is_reference()) {
    rbuf = memb_alloc(&refbufmem);
    if(rbuf != NULL) {
#if QUEUEBUF_STATS
      ++queuebuf_ref_len;
#endif /* QUEUEBUF_STATS */
      rbuf->len = packetbuf_datalen();
      rbuf->ref = packetbuf_reference_ptr();
      rbuf->hdrlen = packetbuf_copyto_hdr(rbuf->hdr);
    } else {
      PRINTF("queuebuf_new_from_packetbuf: could not allocate a reference queuebuf\n");
    }
    return (struct queuebuf *)rbuf;
  } else {
    buf = memb_alloc(&bufmem);
    if(buf != NULL) {
#if QUEUEBUF_STATS
      ++queuebuf_len;
      PRINTF("queuebuf len %d\n", queuebuf_len);
      printf("#A q=%d\n", queuebuf_len);
      if(queuebuf_len == queuebuf_max_len + 1) {
	memb_free(&bufmem, buf);
	queuebuf_len--;
	return NULL;
      }
#endif /* QUEUEBUF_STATS */
      buf->len = packetbuf_copyto(buf->data);
      packetbuf_attr_copyto(buf->attrs, buf->addrs);
    } else {
      PRINTF("queuebuf_new_from_packetbuf: could not allocate a queuebuf\n");
    }
    return buf;
  }
}
/*---------------------------------------------------------------------------*/
void
queuebuf_free(struct queuebuf *buf)
{
  if(memb_inmemb(&bufmem, buf)) {
    memb_free(&bufmem, buf);
#if QUEUEBUF_STATS
    --queuebuf_len;
    printf("#A q=%d\n", queuebuf_len);
#endif /* QUEUEBUF_STATS */
  } else if(memb_inmemb(&refbufmem, buf)) {
    memb_free(&refbufmem, buf);
#if QUEUEBUF_STATS
    --queuebuf_ref_len;
#endif /* QUEUEBUF_STATS */
  }
}
/*---------------------------------------------------------------------------*/
void
queuebuf_to_packetbuf(struct queuebuf *b)
{
  struct queuebuf_ref *r;

  if(memb_inmemb(&bufmem, b)) {
    packetbuf_copyfrom(b->data, b->len);
    packetbuf_attr_copyfrom(b->attrs, b->addrs);
  } else if(memb_inmemb(&refbufmem, b)) {
    r = (struct queuebuf_ref *)b;
    packetbuf_clear();
    packetbuf_copyfrom(r->ref, r->len);
    packetbuf_hdralloc(r->hdrlen);
    memcpy(packetbuf_hdrptr(), r->hdr, r->hdrlen);
  }
}
/*---------------------------------------------------------------------------*/
void *
queuebuf_dataptr(struct queuebuf *b)
{
  struct queuebuf_ref *r;
  
  if(memb_inmemb(&bufmem, b)) {
    return b->data;
  } else if(memb_inmemb(&refbufmem, b)) {
    r = (struct queuebuf_ref *)b;
    return r->ref;
  }
  return NULL;
}
/*---------------------------------------------------------------------------*/
int
queuebuf_datalen(struct queuebuf *b)
{
  return b->len;
}
/*---------------------------------------------------------------------------*/
rimeaddr_t *
queuebuf_addr(struct queuebuf *b, cyg_uint8 type)
{
  return &b->addrs[type - PACKETBUF_ADDR_FIRST].addr;
}
/*---------------------------------------------------------------------------*/
packetbuf_attr_t
queuebuf_attr(struct queuebuf *b, cyg_uint8 type)
{
  return b->attrs[type].val;
}
/*---------------------------------------------------------------------------*/
/** @} */
