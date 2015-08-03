
#include "stm32f0xx_hal.h"

#ifndef GLOBAL_DEBUG
#define GOLBAL_DEBUG

#define DEBUG_ENABLED
//#define DEBUG_ROTARY

extern volatile GPIO_PinState debugRotaryChanel_1, debugRotaryChanel_2;
extern volatile int16_t debugRotaryPosition;
#endif

