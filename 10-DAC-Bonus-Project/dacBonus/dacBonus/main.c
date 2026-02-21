/*
 * dacBonus.c
 *
 * Created: 1/15/2025 1:11:26 AM
 * Author : Mahmoud Mahmoud
 */ 
#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "song.h"

uint16_t tone = mute;
uint16_t toneLength = 0;

void initPins(){
		//init buttons as an input and enable the interupt of it
		PORTA.DIRCLR = PIN2_bm;
		PORTA.PIN2CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTA.DIRCLR = PIN3_bm;
		PORTA.PIN3CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTA.DIRCLR = PIN4_bm;
		PORTA.PIN4CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTA.DIRCLR = PIN5_bm;
		PORTA.PIN5CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTA.DIRCLR = PIN6_bm;
		PORTA.PIN6CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTA.DIRCLR = PIN7_bm;
		PORTA.PIN7CTRL = PORT_ISC_BOTHEDGES_gc;
		
		PORTB.DIRCLR = PIN0_bm;
		PORTB.PIN0CTRL = PORT_ISC_BOTHEDGES_gc;
		
	//init PORTD as an output for the speaker
	PORTD.DIRSET = PIN6_bm;
}

void initDAC(){
	//enable the digital analog converter and the output of it and set the VREF
	DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
	VREF.DAC0REF = VREF_REFSEL_VDD_gc;
}

void initTCA(){
	// enable the timer interupt of it when overflows and set prescaler on DIV1
	TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1_gc;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.PER = (uint16_t)(F_CPU / (tone * 64)) - 1;
}



ISR(PORTA_PORT_vect){
	if(PORTA.INTFLAGS & PIN2_bm){
		tone = tone == c ? mute : c;
	}
	if(PORTA.INTFLAGS & PIN3_bm){
		tone = tone == d ? mute : d;	
	}
	if(PORTA.INTFLAGS & PIN4_bm){
		tone = tone == e ? mute : e;
	}
	if(PORTA.INTFLAGS & PIN5_bm){
		tone = tone == f ? mute : f;
	}
	if(PORTA.INTFLAGS & PIN6_bm){
		tone = tone == g ? mute : g;
	}
	if(PORTA.INTFLAGS & PIN7_bm){
		tone = tone == a ? mute : a;
	}
	TCA0.SINGLE.PER = (uint16_t)(F_CPU / (tone * 64)) - 1;
	PORTA.INTFLAGS = PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
}

ISR(PORTB_PORT_vect){
	if(PORTB.INTFLAGS & PIN0_bm){
		tone = tone == h ? mute : h;
	}
	TCA0.SINGLE.PER = (uint16_t)(F_CPU / (tone * 64)) - 1;
	PORTB.INTFLAGS = PIN0_bm;
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
	
	const song* currentSong = &mario;
	uint16_t songLength = currentSong->length;
    while (1) 
    {
		
			
		for (uint8_t i = 0; i < songLength; i++){
			
			tone = currentSong->tone[i];
			toneLength = currentSong->tone_length[i];
			TCA0.SINGLE.PER = (uint16_t)(F_CPU / (tone * 64)) - 1;
			if(toneLength == 2){
				_delay_ms((60000 / currentSong->bpm) * 2);
			}else{
				_delay_ms((60000 / currentSong->bpm));
			}
			
		}
		
    }
}

