/*
 * main1.c
 *
 * Created: 12/12/2024 3:41:45 AM
 * Author : Mahmoud Mahmoud
 */ 

#include <avr/io.h>

#define Farbhelligkeit 50

uint8_t cmpPer = 0;

void initLEDOutput(){
	PORTD.DIRSET = PIN0_bm;
}

void initTimer(){
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
	TCA0.SINGLE.PER = 255;
	TCA0.SINGLE.CMP0 = cmpPer;
}

void setCMP(uint8_t percentige){
	if(percentige > 100) cmpPer = 255;
	if(percentige <= 0) cmpPer = 0;
	cmpPer = (255/100) * percentige;
	
	TCA0.SINGLE.CMP0 = cmpPer;
}

int main(void)
{
    initLEDOutput();
	initTimer();
	setCMP(Farbhelligkeit);	
	
    while (1) 
    {
		
    }
}

