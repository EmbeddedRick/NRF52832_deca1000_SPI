#ifndef PORT_h
#define PORT_h

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

// SPI communication pins
#define DW1000_CLK             3 //NRF_GPIO_PIN_MAP(0, 3) // output
#define DW1000_MISO            4 //NRF_GPIO_PIN_MAP(0, 4) // input
#define DW1000_MOSI            28 //NRF_GPIO_PIN_MAP(0, 28) // output
#define DW1000_CS              29 //NRF_GPIO_PIN_MAP(0, 29) // ouput
// Additional pins for functionality
#define DW1000_RST             18 //NRF_GPIO_PIN_MAP(0, 18)
#define DW1000_IRQ             19 //NRF_GPIO_PIN_MAP(0, 19)
// define instances of the SPI ports
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   		1000
#define ZEPHYR_MHZ_TO_HZ(freq)  ((freq) * 1000 * 1000)
#define SPI1_DEVICE            DT_NODELABEL(spi1)
extern const struct device *spi_dev;
extern struct spi_config spi_cfg;
extern const struct device *gpio0_dev;

// Chip select functionality
#define MY_GPIO0                DT_NODELABEL(gpio0)
#define GPIO_0_CS               29

void deca_sleep(unsigned int time_ms);
void configure_gpio(void);
int spi_lowrate(void);
int spi_fastrate(void);
void setup_DW1000IRQ(void);
void reset_DW1000(void);

#endif