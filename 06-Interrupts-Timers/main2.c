/*
 * main2.c
 *
 * Created: 12/7/2024 5:21:59 AM
 * Author : Mahmoud Mahmoud
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C_LCD.h"

volatile uint32_t secondsCounter = 0;

void initTCA(){
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.PER = 15625;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	sei();
}



ISR(TCA0_OVF_vect){

			secondsCounter++;
			char lcdText[16];
			sprintf(lcdText, "%lu Seconds", secondsCounter);
			lcd_moveCursor(0,0);
			lcd_putString(lcdText);
			
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
	lcd_init();
	lcd_clear();
	
	initTCA();
	
	
	
	while(1){

	}
}

//Welche Interrupt-Flags werden durch die Interrupts gesetzt, und mussen Sie diese manuell loschen?
// TCA_SINGLE_OVF_bm wird gestzt wenn es im overflow ist und muss man nachdem interupt fertig ist wiederlöschen also ja muss man es manuell löschen

