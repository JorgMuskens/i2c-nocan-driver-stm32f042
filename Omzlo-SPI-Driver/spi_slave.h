#ifndef _SPI_SLAVE_H_
#define _SPI_SLAVE_H_
#include <stdint.h>

typedef void (*spi_transfer_cb)(uint8_t);
typedef void (*spi_finalize_cb)(void);

typedef struct {
    spi_transfer_cb transfer_cb;
    spi_finalize_cb finalize_cb;
} spi_callbacks_typedef;

int spi_slave_init(void);

void spi_slave_set_callbacks(uint8_t cb_count, const spi_callbacks_typedef *callbacks);


#include <stm32f0xx.h>

inline void spi_send_dma(uint8_t len, void *data) __attribute__((always_inline));
inline void spi_send_dma(uint8_t len, void *data) 
{
    DMA1_Channel3->CMAR = (uint32_t)(data); 
    DMA1_Channel3->CNDTR = (uint32_t)(len);
    DMA1_Channel3->CCR |= DMA_CCR_EN;
}

inline void spi_send_byte(uint8_t byte) __attribute__((always_inline));
inline void spi_send_byte(uint8_t byte) 
{
    *(uint8_t *)&(SPI1->DR) = (uint8_t)(byte);
}

inline void spi_recv_dma(uint8_t len, void *data) __attribute__((always_inline));
inline void spi_recv_dma(uint8_t len, void *data) 
{
    DMA1_Channel2->CMAR = (uint32_t)(data);
    DMA1_Channel2->CNDTR = (uint32_t)(len);
    DMA1_Channel2->CCR |= DMA_CCR_EN;
}


inline uint8_t spi_recv_byte(void) __attribute__((always_inline));
inline uint8_t spi_recv_byte(void)
{
    while ((SPI1->SR & SPI_SR_RXNE) == 0); 
    return (uint8_t)(SPI1->DR);
}

#endif
