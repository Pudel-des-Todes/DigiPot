

#ifndef TIMER3_HANDLER
#define TIMER3_HANDLER

typedef enum {
	ROTARY_IDLE = 0,
	ROTARY_PUSH,
	ROTARY_RELEASE,
	ROTARY_CW,
	ROTARY_CCW,
} RotaryEvent;




void timer3_interrup_handler(void);

RotaryEvent RotaryGetEvent(void);
int16_t RotaryGetPosition(void);















#endif
