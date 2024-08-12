#include "deca_spi.h"
#include <deca_device_api.h>

void print_buffer(uint32 readlength, uint8 *readBuffer){
    int j = 0;
    printf("Payload is: ");
    for(int loop = readlength; loop >= 0; loop--){
        j = (j << 8) | readBuffer[loop];
    } 
    printf("0x%.8X \t\n", j);
}

/*! ----------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */
#pragma GCC optimize ("O3")
int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer)
{
	/*
    uint8 * p1;
    uint32 idatalength=0;

    idatalength= headerLength + bodylength;

    uint8 idatabuf[idatalength];
    uint8 itempbuf[idatalength];

    memset(idatabuf, 0, idatalength);
    memset(itempbuf, 0, idatalength);

    p1=idatabuf;	
    memcpy(p1,headerBuffer, headerLength);
    p1 += headerLength;
    memcpy(p1,bodyBuffer,bodylength);
	*/

    struct spi_buf tx_buf[2] = {
		{.buf = (void *)headerBuffer, .len = headerLength},
		{.buf = (void *)bodyBuffer, .len = bodylength}
	};
	struct spi_buf_set tx = {
		.buffers = tx_buf,
		.count = 2
	};

	/*
	struct spi_buf rx_buf[] = {
		{.buf = itempbuf, .len = sizeof(itempbuf),}
	};
	struct spi_buf_set rx = {
		.buffers = rx_buf,
		.count = 1
	};
	*/

	int err;
    gpio_pin_set(gpio0_dev, GPIO_0_CS, 0);
    // Start transaction
	err = spi_write(spi_dev, &spi_cfg, &tx);
	if(err<0){
		printk("SPI transaction error: %i\n", err);
		return err;
	}
	/*
	err = spi_read(spi_dev, &spi_cfg, &rx);
	if(err<0){
		printk("SPI receive error: %i\n", err);
		return err;
	}
	*/
	gpio_pin_set(gpio0_dev, GPIO_0_CS, 1);

	//printf("DATA WRITE");

    return 0;
}

/*! ---------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */
#pragma GCC optimize ("O3")
int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer)
{

    struct spi_buf tx_buf[] = {
		{.buf = (void *)headerBuffer, .len = headerLength,}
	};
	struct spi_buf_set tx = {
		.buffers = tx_buf,
		.count = 1
	};

	struct spi_buf rx_buf[] = {
        {.buf = (void *)readBuffer, .len = readlength,}
	};
	struct spi_buf_set rx = {
		.buffers = rx_buf,
		.count = 1
	};

	int err;
    gpio_pin_set(gpio0_dev, GPIO_0_CS, 0);
    // Start transaction
	err = spi_write(spi_dev, &spi_cfg, &tx);
	if(err<0){
		printk("SPI transaction error: %i\n", err);
		return err;
	}
	err = spi_read(spi_dev, &spi_cfg, &rx);
	if(err<0){
		printk("SPI receive error: %i\n", err);
		return err;
	}
	gpio_pin_set(gpio0_dev, GPIO_0_CS, 1);

	printf("DATA READ\n");
    
    print_buffer(readlength, readBuffer);

    return 0;
}
