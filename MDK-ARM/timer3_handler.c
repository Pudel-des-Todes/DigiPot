#include "stm32f0xx_hal.h"
#include "lcd_lib.h"

static void ScanKeyboard(void); 

void timer3_interrup_handler(void){
	
	ScanKeyboard();
}



static void ScanKeyboard(void) {
	GPIO_PinState rotaryBtn;
	GPIO_PinState rotaryCH1;
	GPIO_PinState rotaryCH2;
	
	
}
