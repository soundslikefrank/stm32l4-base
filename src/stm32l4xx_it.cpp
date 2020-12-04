#include <stm32l4xx_hal.h>

extern "C" {
void SysTick_Handler(void) { HAL_IncTick(); }
}

