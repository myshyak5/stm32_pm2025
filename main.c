#include <stdint.h>
#include "stm32f10x.h"
#include "spi1.h"


void display_cmd(uint8_t cmd) {
    GPIOA->ODR &= ~GPIO_ODR_ODR4;
    GPIOA->ODR &= ~GPIO_ODR_ODR1;

    SPI1_Write(cmd);

    while (!(SPI1->SR & SPI_SR_TXE));
    while (SPI1->SR & SPI_SR_BSY);

    GPIOA->ODR |= GPIO_ODR_ODR4;
}

void display_data(uint8_t data) {
    GPIOA->ODR &= ~GPIO_ODR_ODR4;
    GPIOA->ODR |= GPIO_ODR_ODR1;

    SPI1_Write(data);

    while (!(SPI1->SR & SPI_SR_TXE));
    while (SPI1->SR & SPI_SR_BSY);

    GPIOA->ODR |= GPIO_ODR_ODR4;
}

void display_init(void) {
    GPIOA->ODR &= ~GPIO_ODR_ODR2;

    for (volatile uint32_t i = 0; i < 100000; i++) {
        __NOP();
    }

    GPIOA->ODR |= GPIO_ODR_ODR2;

    for (volatile uint32_t i = 0; i < 100000; i++) {
        __NOP();
    }

    display_cmd(0xAE);

    display_cmd(0xD5);
    display_cmd(0x80);

    display_cmd(0xA8);
    display_cmd(0x3F);

    display_cmd(0xD3);
    display_cmd(0x00);

    display_cmd(0x40);

    display_cmd(0x8D);
    display_cmd(0x14);

    display_cmd(0x20);
    display_cmd(0x00);

    display_cmd(0xA1);
    display_cmd(0xC8);

    display_cmd(0xDA);
    display_cmd(0x12);

    display_cmd(0x81);
    display_cmd(0x7F);

    display_cmd(0xD9);
    display_cmd(0xF1);

    display_cmd(0xDB);
    display_cmd(0x40);

    display_cmd(0xA4);
    display_cmd(0xA6);

    display_cmd(0xAF);
}

void display_chessboard(void) {
    display_cmd(0x21);
    display_cmd(0x00);
    display_cmd(0x7F);

    display_cmd(0x22);
    display_cmd(0x00);
    display_cmd(0x07);

    for (uint8_t page = 0; page < 8; page++) {
        for (uint8_t col = 0; col < 128; col++) {
            if ((page + col / 8) % 2 == 0) {
                display_data(0xFF);
            }
            else {
                display_data(0x00);
            }
        }
    }
}

int main(void) {
    SPI1_Init();

    display_init();

    display_chessboard();

    while (1);
}