/*
 * main1.c
 *
 * Created: 12/12/2024 3:41:45 AM
 * Author : Mahmoud Mahmoud
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 50

#define MAX_HELLIGKEIT 255
#define MAX_HELLIGKEIT_IN_PROZENT 100

void initLEDOutput(){
	PORTE.DIRSET = PIN0_bm;
	PORTE.DIRSET = PIN1_bm;
	PORTE.DIRSET = PIN2_bm;
}

void initTimer(){
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTE_gc;
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm;
	TCA0.SINGLE.PER = MAX_HELLIGKEIT;
	TCA0.SINGLE.CMP0 = 255;
}

void setCMP(uint8_t percentigeRed, uint8_t percentigeGreen, uint8_t percentigeBlue){	
	TCA0.SINGLE.CMP0 = (255/100) * percentigeRed;
	TCA0.SINGLE.CMP1 = (255/100) * percentigeGreen;
	TCA0.SINGLE.CMP2 = (255/100) * percentigeBlue;
}

void redToGreen(){
	for(int i = 0; i < MAX_HELLIGKEIT_IN_PROZENT; i++){
		setCMP(MAX_HELLIGKEIT_IN_PROZENT - i, i, 0);
		_delay_ms(DELAY_TIME);
	}
}

void greenToBlue(){
	for(int i = 0; i < MAX_HELLIGKEIT_IN_PROZENT; i++){
		setCMP(0, MAX_HELLIGKEIT_IN_PROZENT - i, i);
		_delay_ms(DELAY_TIME/2);
	}
}

void blueToRed(){
	for(int i = 0; i < MAX_HELLIGKEIT_IN_PROZENT; i++){
		setCMP(i, 0, MAX_HELLIGKEIT_IN_PROZENT - i);
		_delay_ms(DELAY_TIME);
	}
}

int main(void)
{
    initLEDOutput();
	initTimer();
	
    while (1) 
    {
		redToGreen();
		greenToBlue();
		blueToRed();
    }
}

