/*
 * main1.c
 *
 * Created: 12/12/2024 3:41:45 AM
 * Author : Mahmoud Mahmoud
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void initServoOutput(){
	PORTF.DIRSET = PIN4_bm;
}

/*void initTimer(){
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTE_gc;
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm;
	TCA0.SINGLE.PER = MAX_HELLIGKEIT;
	TCA0.SINGLE.CMP0 = 255;
}*/

#define LEFT 250
#define RIGHT 500
#define CENTER 375

void initTCA(){
	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	TCA0.SINGLE.INTCTRL = TCA0_SINGLE_CMP0 | TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.PER = 5000;
	TCA0.SINGLE.CMP0 = LEFT;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV16_gc;
}
volatile uint16_t pos = 0;
 
 void talf(){
	 PORTD.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;
 }
 
ISR(TCA0_CMP0_vect) {
	
	PORTF.OUTCLR = PIN4_bm;  // End pulse
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm; // Clear flag
}

ISR(TCA0_OVF_vect){
	talf();
	pos = (pos + 1) % 3;
	if(pos == 0){
		TCA0.SINGLE.CMP0 = LEFT;
		PORTD.OUTSET = PIN0_bm;
	}else if (pos == 1){
		TCA0.SINGLE.CMP0 = RIGHT;
		PORTD.OUTSET = PIN1_bm;
	}else{
		TCA0.SINGLE.CMP0 = CENTER;
		PORTD.OUTSET = PIN2_bm;
	}	
	
	
	
	PORTF.OUTSET = PIN4_bm;
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
	PORTD.DIRSET = PIN0_bm;
	PORTD.DIRSET = PIN1_bm;
	PORTD.DIRSET = PIN2_bm;
    initServoOutput();
	initTCA();	
	sei();
	PORTF.OUTSET = PIN4_bm;
	
    while (1) 
    {
		    

    }
}

