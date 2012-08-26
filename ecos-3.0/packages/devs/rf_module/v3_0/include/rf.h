/************

Usage:    #include"cyg/io/rf.h"
*************/

#ifndef __RF_TOTAL_H_
#define __RF_TOTAL_H_
  #include "rf_package.h"
  #include "__uz_srf.h"

#define F2p5MHZ  0
#define F5MHZ    1
#define F10MHZ   2
#define F20MHZ   3
  void set_uz_output_freq(unsigned char freq);

  void uz_reset(void);
  void rf_init(unsigned short panid,unsigned short nwkaddr,unsigned char channel);
  void uz_set_panId(UINT16 PanId);
  void uz_set_nwk_addr(UINT16 NwkAddr);
  void uz_set_tx_power(UINT8 dB);
  void uz_set_channel(UINT8 NewChannel);
  
  #define PA500M    0
  #define PA1000M   1
  void uz_enable_pa(unsigned char mode);
  void uz_disable_pa(void);
  
  UINT8 uz_rx(UINT8 *RecvBuff);
  UINT8 uz_tx(UINT8 *DataPtr, UINT8 Length);

  UINT8 UzTransmit(UINT8 Length) ;////////////////modified for contiki mac layer
  UINT8 UzPrepare(UINT8 *DataPtr, UINT8 Length);//modified for contiki mac layer
 
  UINT8 uz_read_rssi(void);

  void uz_rx_normal_mode(void);
  void uz_rx_promiscouos_mode(void);
  
  void uz_enable_ext_wakeup(void);
  void uz_sleep(void);
  void uz_wakeup(void);

extern volatile INTERRUPT_STS IntStatus;
#define is_rf_incoming()    IntStatus.Rx

#endif   /* __RF_TOTAL_H_  */
