#include "globalDebug.h"
#include "stm32f0xx_hal.h"

#ifdef DEBUG_ROTARY
volatile GPIO_PinState debugRotaryChanel_1 = GPIO_PIN_RESET, debugRotaryChanel_2 = GPIO_PIN_RESET;
volatile int32_t debugRotaryPosition = 0;
#endif
