/*
 * LCDApp.c
 *
 * Created: 11/26/2024 10:20:48 AM
 * Author : mamod
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "I2C_LCD.h"

#define ASCII0 48
#define ARRAY_LENGTH 4

char numsInString[ARRAY_LENGTH];

void convertIntToString(uint32_t number, char numsInString[]){
	for (int i = 0; i < ARRAY_LENGTH; i++) {
		numsInString[i] = ' ';
	}
	
    int index = ARRAY_LENGTH - 1;
	
    while (number > 0 && index >= 0) {
	    uint32_t tempNum = number % 10;
	    numsInString[index] = tempNum + ASCII0;
	    number /= 10;
	    index--;
    }
}

void printDigitsInLCD(){
	for (int i = 0; i < ARRAY_LENGTH; i++) {
		lcd_moveCursor(i, 0);
		lcd_putChar(numsInString[i]);
	}
}

int main(void)
{
	lcd_init();
	lcd_clear();
	uint32_t numbers = 0;
	while(1){
		if(numbers > 1000){
			numbers = 0;
		}
		convertIntToString(numbers, numsInString);
		printDigitsInLCD();
		numbers++;
		if(numbers > 990){
		_delay_ms(5000);	
		}
		_delay_ms(200);
	}

}

