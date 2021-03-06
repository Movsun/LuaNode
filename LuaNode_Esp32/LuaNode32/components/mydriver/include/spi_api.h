#ifndef SPI_APP_H
#define SPI_APP_H

#include "soc/spi_register.h"
#include "rom/ets_sys.h"
//#include "osapi.h"
#include "rom/uart.h"
//#include "os_type.h"
#include "c_types.h"
#include "soc/soc.h"
#include "soc/io_mux_reg.h"
//#include "esp32-hal-spi.h"

#define FSPI  1 //SPI bus attached to the flash (can use the same data lines but different SS)
#define HSPI  2 //SPI bus normally mapped to pins 12 - 15, but can be matrixed to any pins
#define VSPI  3 //SPI bus normally attached to pins 5, 18, 19 and 23, but can be matrixed to any pins

/*SPI number define*/
#define SPI 			0
//#define HSPI			1



//lcd drive function
void spi_lcd_mode_init(uint8 spi_no);
void spi_lcd_9bit_write(uint8 spi_no,uint8 high_bit,uint8 low_8bit);

//spi master init funtion
void spi_master_init(uint8 spi_no, unsigned cpol, unsigned cpha, uint32_t clock_div);
// fill MOSI buffer
void spi_set_mosi(uint8 spi_no, uint8 offset, uint8 bitlen, uint32 data);
// retrieve data from MISO buffer
uint32 spi_get_miso(uint8 spi_no, uint8 offset, uint8 bitlen);
// initiate SPI transaction
void spi_mast_transaction(uint8 spi_no, uint8 cmd_bitlen, uint16 cmd_data, uint8 addr_bitlen, uint32 addr_data,
                          uint16 mosi_bitlen, uint8 dummy_bitlen, sint16 miso_bitlen);

//transmit data to esp8266 slave buffer,which needs 16bit transmission ,
//first byte is master command 0x04, second byte is master data
void spi_byte_write_espslave(uint8 spi_no,uint8 data);
//read data from esp8266 slave buffer,which needs 16bit transmission ,
//first byte is master command 0x06, second byte is to read slave data
void spi_byte_read_espslave(uint8 spi_no,uint8 *data);

 //esp8266 slave mode initial
void spi_slave_init(uint8 spi_no);
  //esp8266 slave isr handle funtion,tiggered when any transmission is finished.
  //the function is registered in spi_slave_init.
void spi_slave_isr_handler(void *para); 


//hspi test function, used to test esp8266 spi slave
void hspi_master_readwrite_repeat(void);


void spi_test_init(void);

uint32 spi_mast_get_miso(uint8 spi_no, uint8 offset, uint8 bitlen);
void spi_mast_set_mosi(uint8 spi_no, uint8 offset, uint8 bitlen, uint32 data);

#endif

