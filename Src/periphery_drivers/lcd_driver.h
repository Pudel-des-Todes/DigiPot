


#ifndef LCD_LIB
#define LCD_LIB

#define LCD_4bit 1
#define LCD_RS_enable 1
#define LCD_RW_enable 0
//***********************************************


#define LCD_H GPIO_PIN_SET
#define LCD_L  GPIO_PIN_RESET

// http://www.oomipood.ee/failid/LCD16X2ZN.pdf
// http://www.datsi.fi.upm.es/docencia/Micro_C/lcd/ks0d066u.pdf



#define LCD_RS_GPIOx	GPIOA		//define MCU pin connected to LCD RS
#define LCD_RS_PINxx	GPIO_PIN_0	
#define LCD_E_GPIOx		GPIOA		//define MCU pin connected to LCD E
#define LCD_E_PINxx		GPIO_PIN_1

#if LCD_RW_enable == 1
#define LCD_RW_GPIOx	GPIOA		//define MCU pin connected to LCD R/W
#define LCD_RW_PINxx  	GPIO_PIN_0
#endif

#if LCD_4bit == 0
#define LCD_D0		//define MCU pin connected to LCD D0
#define LCD_D1		//define MCU pin connected to LCD D1
#define LCD_D2		//define MCU pin connected to LCD D1
#define LCD_D3		//define MCU pin connected to LCD D2
#endif
#define LCD_D4_GPIOx	GPIOA		//define MCU pin connected to LCD D3
#define LCD_D4_PINxx	GPIO_PIN_4	
#define LCD_D5_GPIOx	GPIOB		//define MCU pin connected to LCD D4
#define LCD_D5_PINxx	GPIO_PIN_0	
#define LCD_D6_GPIOx	GPIOC		//define MCU pin connected to LCD D5
#define LCD_D6_PINxx	GPIO_PIN_1	
#define LCD_D7_GPIOx	GPIOC		//define MCU pin connected to LCD D6
#define LCD_D7_PINxx	GPIO_PIN_0

#define LCD_WRITE_DELAY_MS 1

#define LCD_CLR             0x01	//DB0: clear display
#define LCD_HOME            0x02	//DB1: return to home position
// Entry mode 
#define LCD_ENTRY_CMD		0x04	//DB2: set entry mode
#define LCD_ENTRY_INC       0x02	//DB1: increment
#define LCD_ENTRY_SHIFT     0x01	//DB2: shift
// Dusplay and Cursor on/off control
#define LCD_ON_CTRL         0x08	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      0x04	//DB2: turn display on (0-> display off)
#define LCD_ON_CURSOR       0x02	//DB1: turn cursor on  (0-> cursor off)
#define LCD_ON_BLINK        0x01	//DB0: blinking cursor  (0-> blink off)
// Cursor or Display shift
#define LCD_MOVE            0x10	//DB4: move cursor/display
#define LCD_MOVE_DISP       0x08	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      0x04	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           0x40	//DB6: set CG RAM address
#define LCD_DDRAM           0x80	//DB7: set DD RAM address
// reading:
#define LCD_BUSY            7	//DB7: LCD is busy
#define LCD_LINES			2	//visible lines
#define LCD_LINE_LENGTH		16	//line length (in characters)
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void LCDsendChar(int8_t);		//forms data ready to send to 74HC164
void LCDsendCommand(uint8_t);	//forms data ready to send to 74HC164
void LCDinit(void);			//Initializes LCD

void LCDstring(char*);	//Outputs string to LCD
void LCDstringDefinedPos(char*, uint8_t, uint8_t);  // Cursor to X, Y and write string
void LCDbytes(char*, unsigned char);	//Outputs byte array to LCD
void LCDGotoXY(unsigned char, unsigned char);	//Cursor to X Y position



void LCDclr(void);				//Clears LCD
void LCDhome(void);			//LCD cursor home
void LCD_entry_mode_set(uint8_t argument);
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM 
void LCDshiftRight(uint8_t);	//shift by n characters Right
void LCDshiftLeft(uint8_t);	//shift by n characters Left
void LCDcursorOn(void);		//Underline cursor ON
void LCDcursorOnBlink(void);	//Underline blinking cursor ON
void LCDcursorOFF(void);		//Cursor OFF
void LCDblank(void);			//LCD blank but not cleared
void LCDvisible(void);			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n
// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);


#endif /* LCD_LIB */
