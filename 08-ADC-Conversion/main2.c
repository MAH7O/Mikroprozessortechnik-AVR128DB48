/*
 * adc.c
 *
 * Created: 1/1/2025 9:01:31 AM
 * Author : Mahmoud Mahmoud
 */ 

#define F_CPU 4000000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C_LCD.h"

void initInputAndADC(){
	PORTF.DIRCLR = PIN2_bm;
	PORTF.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
	VREF.ADC0REF = VREF_REFSEL_VDD_gc;
	ADC0.CTRLA = ADC_ENABLE_bm;

	ADC0.MUXPOS = ADC_MUXPOS_AIN18_gc;
} 

uint16_t readADC(){
	ADC0.COMMAND = ADC_STCONV_bm;
	
	while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	
	return ADC0.RES;
}

int main(void)
{
	initInputAndADC();
    lcd_init();
	lcd_clear();
	
	
	
	char buffer[16];
	
    while (1) 
    {
		uint16_t adcValue = readADC();
		uint16_t voltage = (adcValue * (3.3 / 4095));
		float percent = (adcValue * 100.0) / 4095.0;
		uint16_t percentInt = (uint16_t)(percent);
		
		
					lcd_clear();
					lcd_moveCursor(0, 0);
					sprintf(buffer, "Voltage: %d", voltage);
					lcd_putString(buffer);
					
					lcd_moveCursor(0, 1);
					sprintf(buffer, "Percent: %d", percentInt > 99 ? percentInt : percentInt - 1);
					lcd_putString(buffer);
					
			_delay_ms(250);
    }
}

