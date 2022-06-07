#include "zf_common_headfile.h"
#include "deca_device_api.h"
#include "Config.h"
#include "port.h"
//void Init()
//{
//    gpio_init(A4, GPO, 1, SPEED_50MHZ | GPO_PUSH_PULL); // ¹Ø±Õ spi
//    spi_init(SPI_1, SPI_MODE0, 1*1000*1000, SPI1_SCK_A5, SPI1_MOSI_A7, SPI1_MISO_A6, SPI_CS_NULL);
//    uart_init(UART_3, 9600, UART3_TX_B10, UART3_RX_B11);
//}
//
//
//uint32_t dw1000_read_device_id(void)
//{
//    uint8_t header = 0x00;
//    uint32_t device_id;
//    gpio_init(D8, GPO, 0, GPO_PUSH_PULL);
//    system_delay_ms(2);
//    gpio_init(D8, GPI, 1, GPI_FLOATING_IN);
//
//    // read
//    gpio_set_level(A4, 0);
//    spi_write_8bit(SPI_1, header);
//    gpio_set_level(A4, 1);
//    gpio_set_level(A4, 0);
//    spi_read_8bit_array(SPI_1, (uint8_t*)device_id, 4);
//    gpio_set_level(A4, 1);
//    return device_id;
//}

static dwt_config_t config = {
    2,               /* Channel number. */
    DWT_PRF_64M,     /* Pulse repetition frequency. */
    DWT_PLEN_1024,   /* Preamble length. Used in TX only. */
    DWT_PAC32,       /* Preamble acquisition chunk size. Used in RX only. */
    9,               /* TX preamble code. Used in TX only. */
    9,               /* RX preamble code. Used in RX only. */
    1,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
    DWT_BR_110K,     /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};

int main(void)
{
    interrupt_global_disable();
    clock_init(SYSTEM_CLOCK_144M);
    debug_init();
    GPIO_RCC_Configuration();
    SPI_DW_Configuration(SPIx, SPI_BaudRatePrescaler_32);

    port_set_deca_isr(dwt_isr);

    interrupt_global_enable();

    reset_DW1000();

    //spi_set_rate_low();
    while(dwt_initialise(DWT_LOADNONE) == DWT_ERROR)
    {
        printf("Error");
    }
    spi_set_rate_high();
    dwt_configure(&config);

    while(1)
    {

        system_delay_ms(1000);
    }
}
