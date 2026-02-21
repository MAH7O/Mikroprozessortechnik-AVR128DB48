/*
 * main2.c
 *
 * Created: 12/7/2024 5:21:59 AM
 * Author : Mahmoud Mahmoud
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 4000000
#include <util/delay.h>
#include "I2C_LCD.h"

#define DELAY_TIME 40
#define LCD_WIDTH 16

typedef enum{
	PAUSED,
	STARTED
	} timerState;

timerState currentState = PAUSED;
uint32_t timer = 0;
char lcdText[16];	
void initRGBLEDOutputs(){
		PORTE.DIRSET = PIN0_bm;
}
	
void initButtonInterput(){
	PORTC.PIN4CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN5CTRL = PORT_ISC_RISING_gc;
}

void initTimerInterupt(){
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc;
	TCA0.SINGLE.PER = 15625; // 1 seconds overFlow
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
}

void turnAllRGBLightsOff(){
	PORTE.OUTCLR = PIN0_bm;	
}

void turnRGBLEDOn (){
	PORTE.OUTSET = PIN0_bm;
}

ISR(PORTC_PORT_vect){
		_delay_ms(DELAY_TIME);
		if(PORTC.INTFLAGS & PIN4_bm){
			if(currentState == PAUSED){
							timer += 5;
							lcd_clear();
							lcd_moveCursor(4,0);
							sprintf(lcdText, "ADD TIME");
							lcd_putString(lcdText);
							
							uint8_t numLength = sprintf(lcdText, "%lu", timer);
							uint8_t col = (LCD_WIDTH - numLength) / 2;
							lcd_moveCursor(col, 1);
							lcd_putString(lcdText); 
													
			}
		}
		if(PORTC.INTFLAGS & PIN5_bm){
			if(currentState == STARTED){
				currentState = PAUSED;
				lcd_clear();
				lcd_moveCursor(5, 0);
				lcd_putString("TIMER");
				lcd_moveCursor(5, 1);
				lcd_putString("PAUSED");
				TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
			}else{
				currentState = STARTED;
				TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
			}
		}
		PORTC.INTFLAGS = PIN4_bm | PIN5_bm;
}

ISR(TCA0_OVF_vect){
	if(currentState == STARTED){
		if(timer > 0){
			timer--;
			lcd_clear();
			lcd_moveCursor(2,0);
			sprintf(lcdText, "CURRENT TIME");
			lcd_putString(lcdText);
			uint8_t numLength = sprintf(lcdText, "%lu", timer);
			uint8_t col = (LCD_WIDTH - numLength) / 2;
			lcd_moveCursor(col, 1);
			lcd_putString(lcdText);
		}else{
			turnRGBLEDOn();
			TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
			currentState = PAUSED;
		}	
	}
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
	lcd_init();
	lcd_clear();
	initRGBLEDOutputs();
	initButtonInterput();
	initTimerInterupt();
	sei();
	
	lcd_moveCursor(1,0);
	lcd_putString("PC4: ADD 5 SEC");
	lcd_moveCursor(0,1);
	lcd_putString("PC5: START/PAUSE");
	
	while(1){

	}
}

