#include "stm32f0xx_hal.h"
#include "timer3_handler.h"
#include "globalDebug.h"

#define KEYBOARD_ROTARY_BTN GPIOA,GPIO_PIN_9
#define KEYBOARD_ROTATY_CH1 GPIOB,GPIO_PIN_6
#define KEYBOARD_ROTATY_CH2 GPIOC,GPIO_PIN_7

#define ROTARY_POS_MIN (0)
#define ROTARY_POS_MAX (255)

static void ScanKeyboard(void); 

static volatile RotaryEvent rotaryEvent = ROTARY_IDLE;
static volatile int32_t rotaryPosition = (ROTARY_POS_MAX- ROTARY_POS_MIN)/2;

void timer3_interrup_handler(void){
	
	ScanKeyboard();
}



static void ScanKeyboard(void) {
	static uint8_t init_needed = 1;
	static uint8_t rotaryBtnTrigger = 1;
	static GPIO_PinState rotaryBtnState, rotaryBtnPrevState;
	
	static GPIO_PinState rotaryCH1State, rotaryCH1PrevState ;
	
	static GPIO_PinState rotaryCH2State, rotaryCH2PrevState ;
	
	// it's not clear how to get the default state
	if (init_needed == 1) {
		rotaryBtnState = rotaryBtnPrevState = HAL_GPIO_ReadPin(KEYBOARD_ROTARY_BTN);
		rotaryCH1State = rotaryCH1PrevState = HAL_GPIO_ReadPin(KEYBOARD_ROTATY_CH1);
		rotaryCH2State = rotaryCH2PrevState = HAL_GPIO_ReadPin(KEYBOARD_ROTATY_CH2);
		init_needed = 0;
		return;
	}
	
	rotaryBtnPrevState = rotaryBtnState;
	rotaryBtnState = HAL_GPIO_ReadPin(KEYBOARD_ROTARY_BTN);
	
	//rotaryCH1PrevState = rotaryCH1State;
	rotaryCH1State = HAL_GPIO_ReadPin(KEYBOARD_ROTATY_CH1);
	
	//rotaryCH2PrevState = rotaryCH2State;
	rotaryCH2State = HAL_GPIO_ReadPin(KEYBOARD_ROTATY_CH2);
	
#ifdef DEBUG_ROTARY
	debugRotaryChanel_1 = rotaryCH1State;
	debugRotaryChanel_2 = rotaryCH2State;
#endif 	
	
	if (rotaryBtnState == GPIO_PIN_RESET) {
		if (rotaryBtnTrigger == 1) {
				rotaryBtnTrigger = 0;
				rotaryEvent = ROTARY_PUSH;
		}		
	} else {
		rotaryBtnTrigger = 1;
	}
	
	
	if (rotaryCH1State != rotaryCH1PrevState) {
	
		if (rotaryCH1PrevState == GPIO_PIN_SET) {
			rotaryCH1PrevState = GPIO_PIN_RESET;
		} else {
			rotaryCH1PrevState = GPIO_PIN_SET;
		}
		
		if (rotaryCH1PrevState == rotaryCH2State) {			
			rotaryPosition--;
			rotaryEvent = ROTARY_CCW;
		} else {
			rotaryPosition++;
			rotaryEvent = ROTARY_CW;
		}
		//bKeyDetected = 1;
	}
	
	if (rotaryPosition > ROTARY_POS_MAX) {
		rotaryPosition = ROTARY_POS_MAX;
	}
	
	if (rotaryPosition < ROTARY_POS_MIN) {
		rotaryPosition = ROTARY_POS_MIN;
	}
	
#ifdef DEBUG_ROTARY
	debugRotaryPosition = rotaryPosition;
}
#endif

RotaryEvent getRotaryEvent(void) {
	RotaryEvent rotaryEventCopy = rotaryEvent;
	rotaryEvent = ROTARY_IDLE;
	return rotaryEventCopy;
	
}










