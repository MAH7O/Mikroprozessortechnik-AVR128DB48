/*
 * dacBonus.c
 *
 * Created: 1/15/2025 1:11:26 AM
 * Author : Mahmoud Mahmoud
 */ 
#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "song.h"

uint16_t tone = a1;

void initPins(){
	//init PORTD as an output for the speaker
	PORTD.DIRSET = PIN6_bm;
}

void initDAC(){
	//enable the digital analog converter and the output of it and set the VREF
	DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
	VREF.DAC0REF = VREF_REFSEL_1V024_gc;
}

void initTCA(){
	// enable the timer interupt of it when overflows and set prescaler on DIV1
	TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1_gc;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.PER = (uint16_t)(F_CPU / (tone * 64)) - 1;
}

ISR(TCA0_OVF_vect){
	static uint8_t counter = 0;
	
	if(counter >= 64)
	counter = 0;
	
	DAC0.DATA = sine_table[counter] << 6;
	counter++;
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
	
}
int main(void)
{
    initPins();
	initDAC();
	initTCA();
	sei();
	
    while (1) 
    {
    }
}

