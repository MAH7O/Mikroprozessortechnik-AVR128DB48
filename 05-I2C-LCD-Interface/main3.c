/*
 * main1.c
 *
 * Created: 11/26/2024 10:20:48 AM
 * Author : mamod
 */ 

#include <avr/io.h>
#include "I2C_LCD.h"
#include <avr/delay.h>

#define ASCII0 48
#define ASCII1 49
#define LCD_WIDTH 16

#define DELAY_TIME 3000

void startPingPong(){
	
	//FIRST PART
	
	//start by putting number 1 in the beggining of the first part x = 0; y = 0
	lcd_moveCursor(0,0);
	lcd_putChar(ASCII1);
	_delay_ms(DELAY_TIME);
	//moves number 1 to the right and places number the in the previous index all in the top section y = 0
	for (int i = 0; i < LCD_WIDTH - 1; i++){
		lcd_moveCursor(i, 0);
		lcd_putChar(ASCII0);
		lcd_moveCursor(i+1, 0);
		lcd_putChar(ASCII1);
		_delay_ms(DELAY_TIME);
		if(i == 14){ // place number 0 in the top part in the right side before moving to the second part
			lcd_moveCursor(i+1, 0);
			lcd_putChar(ASCII0);
		}
	}
	
	//SECOND PART

	//start by putting number 1 in the beggining of the second part x = 0; y = 1
	lcd_moveCursor(15, 1);
	lcd_putChar(ASCII1);
	_delay_ms(DELAY_TIME);
	
	//moves number 1 to the right and places number the in the previous index all in the top section y = 1
	for (int i = LCD_WIDTH - 1; i > 0; i--){
		lcd_moveCursor(i, 1);
		lcd_putChar(ASCII0);
		lcd_moveCursor(i-1, 1);
		lcd_putChar(ASCII1);
		_delay_ms(DELAY_TIME);
		
		if(i == 1){
			lcd_moveCursor(i-1, 1);
			lcd_putChar(ASCII0);
		}
	}
}

int main(void)
{
	lcd_init();
	lcd_clear();
	
	//fill the first and the second part with number 0
	for(int i = 0; i < LCD_WIDTH; i++){
		lcd_moveCursor(i, 0);
		lcd_putChar(ASCII0);
	}
	for(int i = 0; i < LCD_WIDTH; i++){
		lcd_moveCursor(i, 1);
		lcd_putChar(ASCII0);
	}
		
		while(1){
			startPingPong();
		}

}

