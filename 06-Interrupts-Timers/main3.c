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


#define DELAY_TIME 40

typedef enum{
	NONE,
	RED_TO_GREEEN,
	GREEN_TO_RED
	} state;
	
typedef enum{
	RED,
	YELLOW,
	GREEN
	} lights;

state currentState = NONE;
lights currentLight = RED;
	
void initRGBLEDOutputs(){
		PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
		PORTE.OUTSET = PIN0_bm;
}
	
void initButtonInterput(){
	PORTC.PIN4CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN5CTRL = PORT_ISC_RISING_gc;
}

void initTimerInterupt(){
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc;
	TCA0.SINGLE.PER = 46875; // 3 seconds overFlow
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
}

void turnAllRGBLightsOff(){
	PORTE.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;	
}

void turnRGBLEDOn (lights light){
	turnAllRGBLightsOff();
	switch (light){
		case RED:
			PORTE.OUTSET = PIN0_bm;
			break;
		case YELLOW:
			PORTE.OUTSET = PIN0_bm | PIN1_bm;
			break;	
		case GREEN:
			PORTE.OUTSET = PIN1_bm;
			break;
	}
}



void changeLightPhase(lights light){
	switch(light){
		case RED:
			turnRGBLEDOn(YELLOW);
			currentLight = YELLOW;
			currentState = GREEN_TO_RED;
			TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
			break;
		case GREEN:
			currentLight = YELLOW;
			turnRGBLEDOn(YELLOW);
			currentState = RED_TO_GREEEN;
			TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
			break;
		case YELLOW:
			break;
	}
}

ISR(PORTC_PORT_vect){
		_delay_ms(DELAY_TIME);
		if(PORTC.INTFLAGS & PIN4_bm){
			if(currentLight == RED){
				changeLightPhase(GREEN);
			}
		}
		if(PORTC.INTFLAGS & PIN5_bm){
			if(currentLight == GREEN){
				changeLightPhase(RED);
			}
		}
		PORTC.INTFLAGS = PIN4_bm | PIN5_bm;
}

ISR(TCA0_OVF_vect){

			if(currentState == GREEN_TO_RED){
				turnRGBLEDOn(RED);
				currentLight = RED;
			}
			if(currentState == RED_TO_GREEEN){
				turnRGBLEDOn(GREEN);
				currentLight = GREEN;
			}
	currentState = NONE;	
	TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{

	initRGBLEDOutputs();
	initButtonInterput();
	initTimerInterupt();
	sei();
	
	while(1){

	}
}

// Macht es Sinn, während einer wechselnden Ampelphase auf einen Knopfdruck zu reagieren?
// ja sinnvoll da die ampelsteuerung konsistent und voraussagbar sein muss um sicher zu sein das nieman währen ein wächselung angreift

//Führt das gleichzeitige Auslösen von Knopf- und Timer-ISR zu undefiniertem Verhalten?
// Nein das gleichzeitige Auslösen von Knopf- und Timer-Interrupts führt nicht zu undefiniertem Verhalten, solange die Interrupt-Service-Routinen korrekt implementiert sind
