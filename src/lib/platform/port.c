#include "port.h"

const struct device *spi_dev = DEVICE_DT_GET(SPI1_DEVICE);
struct spi_config spi_cfg = {
    .frequency = 2000000U,
    .operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB,
    .slave = 0,
};

const struct device *gpio0_dev = DEVICE_DT_GET(MY_GPIO0);

void deca_sleep(unsigned int time_ms){
    k_msleep(time_ms);
}

void configure_gpio(){
    // Comunication pins GPIO configuration
    gpio_pin_configure(gpio0_dev, GPIO_0_CS, GPIO_OUTPUT);
    // Initialize the gpio pin DW1000_CS as high
	gpio_pin_set(gpio0_dev, GPIO_0_CS, 1);
}

/*
#define NRF_DRV_SPI_CONFIG(freq)            \
{                                           \
    .frequency = NRFX_MHZ_TO_HZ(freq),                \
    .operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB,  \
    .slave = 0,                                       \
}
*/

int spi_lowrate(){
    spi_cfg.frequency = 2000000U;
    if (!device_is_ready(spi_dev)) {
        /* Not ready, do not use */
        printf("ERROR");
        return -ENODEV;
    }
    return 1;
}

int spi_fastrate(){
    spi_cfg.frequency = 4000000U;
    if (!device_is_ready(spi_dev)) {
        /* Not ready, do not use */
        printf("ERROR");
        return -ENODEV;
    }
    return 1;
}

void reset_DW1000(void){
   gpio_pin_configure(gpio0_dev, DW1000_RST, GPIO_OUTPUT);
   gpio_pin_set(gpio0_dev, DW1000_RST, 0);
   k_msleep(2);
   gpio_pin_configure(gpio0_dev, DW1000_RST, GPIO_INPUT);
   k_msleep(10); 
}