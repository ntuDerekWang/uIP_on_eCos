#include <cyg/DW_config.h>
    
#include "cyg/io/__uz_type.h"
#include "cyg/io/__uz_data.h"
#include "cyg/io/__uz_srf.h"
#include "cyg/io/__uz2400.h"

void spi_sw(UINT8 Address, UINT8 Value){
  Address = (Address << 1) | 0x0001; //Shfit the Address
  disable_rf_int();
  
  //Set up the SFRPAGE
  uz2400_select();
  
  SPI_I2S_SendData(RF_SPI,Address);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();        
  
  SPI_I2S_SendData(RF_SPI,Value);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  uz2400_deselect();
   
  enable_rf_int();
}    


UINT8 spi_sr(UINT8 Address){
  UINT8 Value; 
  
  Address = (Address << 1);
  
  disable_rf_int();
  
  uz2400_select();
  SPI_I2S_SendData(RF_SPI,Address);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,0x00);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  wait_uz2400();
  Value = SPI_I2S_ReceiveData(RF_SPI);
  
  wait_uz2400();
  uz2400_deselect();
  
  enable_rf_int();
  
  return Value;

}

void spi_lw(UINT16 Address, UINT8 Value)
{
  Address = (Address << 5) | 0x8010;

  disable_rf_int();

//Set up the SFRPAGE
  uz2400_select(); //Put the CS to Low
  SPI_I2S_SendData(RF_SPI,(Address>>8)&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();

  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,Address&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,Value);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);

  wait_uz2400();

  wait_uz2400();
  uz2400_deselect(); //Put the CS to High

  enable_rf_int();
}

UINT8 spi_lr(UINT16 Address){
  UINT8 Value;
  Address = (Address << 5) | 0x8000;

  disable_rf_int();

  uz2400_select(); //Put the CS to Low

  SPI_I2S_SendData(RF_SPI,(Address>>8)&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,Address&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,0x00);
  uz2400_wait_spi_r_ready();
  uz2400_wait_spi_r_ready();
  wait_uz2400();
  Value = SPI_I2S_ReceiveData(RF_SPI);
  
  wait_uz2400();
  uz2400_deselect(); //Put the CS to High

  enable_rf_int();

  return Value;
}

void spi_fill_fifo(UINT16 Address, UINT8 *DataPtr, UINT8 Length){

  Address = (Address << 5) | 0x8010;
  
  disable_rf_int();
  
  uz2400_select(); //Put the CS to Low
  
  SPI_I2S_SendData(RF_SPI,(Address>>8)&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,Address&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  while (Length--){
    SPI_I2S_SendData(RF_SPI,*DataPtr++);
    uz2400_wait_spi_w_ready();
    uz2400_wait_spi_r_ready();
    SPI_I2S_ReceiveData(RF_SPI);
    wait_uz2400();
  }
  wait_uz2400();
  uz2400_deselect(); //Put the CS to High
  
  enable_rf_int();
}


void spi_dump_fifo(UINT16 Address, UINT8 *DataPtr, UINT8 Length)
{

  Address = (Address << 5) | 0x8000;

  disable_rf_int();

  uz2400_select(); //Put the CS to Low

  SPI_I2S_SendData(RF_SPI,(Address>>8)&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();

  SPI_I2S_SendData(RF_SPI,Address&0x00ff);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  while(Length--){
    SPI_I2S_SendData(RF_SPI,0x00ff);
    uz2400_wait_spi_w_ready();
    uz2400_wait_spi_r_ready();
    wait_uz2400();
    *DataPtr++ = SPI_I2S_ReceiveData(RF_SPI);
  }
  wait_uz2400();
  uz2400_deselect(); //Put the CS to High

  enable_rf_int();
}


void spi_rd_rx_fifo(UINT8 *DataPtr, UINT8 *RxLength){

  UINT8 Length;
  
  disable_rf_int();
  
  uz2400_select(); //Put the CS to Low
  
  SPI_I2S_SendData(RF_SPI,0xE0);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,0x00);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  SPI_I2S_ReceiveData(RF_SPI);
  wait_uz2400();
  
  SPI_I2S_SendData(RF_SPI,0x00);
  uz2400_wait_spi_w_ready();
  uz2400_wait_spi_r_ready();
  wait_uz2400();
  Length = SPI_I2S_ReceiveData(RF_SPI);
  
  Length += 2;
  *RxLength = Length;
  
  while(Length--){
    SPI_I2S_SendData(RF_SPI,0x00);
    uz2400_wait_spi_w_ready();
    uz2400_wait_spi_r_ready();
    wait_uz2400();
    *DataPtr++ = SPI_I2S_ReceiveData(RF_SPI);
  }
  wait_uz2400();
  uz2400_deselect(); //Put the CS to High
  
  enable_rf_int();

}

