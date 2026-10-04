#include <stdint.h>
#include "stm32f10x.h"

void delay_us(uint32_t us) {
    __asm volatile (
        "push {r0}\r\n"
        "mov R0, %0\r\n"
        "_loop:\r\n"
        "cmp R0, #0\r\n"
        "beq _exit\r\n"
        "sub R0, R0, #1\r\n"
        "nop\r\n"
        "b _loop\r\n"
        "_exit:\r\n"
        "pop {r0}\r\n"
        :: "r"(9 * us)
    );
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN;

    GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13) | GPIO_CRH_MODE13_0;
    GPIOC->ODR |= GPIO_ODR_ODR13;

    GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0) | GPIO_CRL_CNF0_1;
    GPIOA->ODR |= GPIO_ODR_ODR0;

    GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1) | GPIO_CRL_CNF1_1;
    GPIOA->ODR |= GPIO_ODR_ODR1;

    uint32_t half = 500000;

    const uint32_t HALF_MIN = 7812;
    const uint32_t HALF_MAX = 32000000;

    while (1) {
        if (!(GPIOA->IDR & GPIO_IDR_IDR0)) {

            if (half > HALF_MIN) {
                half /= 2;

                if (half < HALF_MIN)
                    half = HALF_MIN;
            }

            delay_us(20000);
            while (!(GPIOA->IDR & GPIO_IDR_IDR0));
            delay_us(20000);
        }

        if (!(GPIOA->IDR & GPIO_IDR_IDR1)) {
            
            if (half < HALF_MAX) {
                half *= 2;

                if (half > HALF_MAX)
                    half = HALF_MAX;
            }

            delay_us(20000);
            while (!(GPIOA->IDR & GPIO_IDR_IDR1));
            delay_us(20000);
        }

        GPIOC->ODR &= ~GPIO_ODR_ODR13;
        delay_us(half);

        GPIOC->ODR |= GPIO_ODR_ODR13;
        delay_us(half);
    }
}