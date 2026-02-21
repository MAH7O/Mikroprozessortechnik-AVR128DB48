#define F_CPU 4000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY 40

typedef enum {
	GREEN_PHASE,
	YELLOW_TO_RED_PHASE,
	RED_PHASE,
	YELLOW_TO_GREEN_PHASE
} TrafficLightPhase;

volatile TrafficLightPhase currentPhase = RED_PHASE;
volatile uint8_t isTransitioning = 0;

void turnOffLED() {
	PORTE.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;
}

void switchToGreen() {
	turnOffLED();
	PORTE.OUTSET = PIN1_bm; 
}

void switchToYellow() {
	turnOffLED();
	PORTE.OUTSET = PIN0_bm | PIN1_bm;
}

void switchToRed() {
	turnOffLED();
	PORTE.OUTSET = PIN0_bm; 
}

void startTimer(uint16_t duration) {
	TCA0.SINGLE.PER = duration;
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect) {
	switch (currentPhase) {
		case YELLOW_TO_RED_PHASE:
		switchToRed();
		currentPhase = RED_PHASE;
		break;
		case YELLOW_TO_GREEN_PHASE:
		switchToGreen();
		currentPhase = GREEN_PHASE;
		break;
		default:
		break;
	}
	isTransitioning = 0; 
	TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

ISR(PORTC_PORT_vect) {
	_delay_ms(DEBOUNCE_DELAY); 

	if (isTransitioning) {
		PORTC.INTFLAGS = PIN4_bm | PIN5_bm;
		return;
	}

	if (PORTC.INTFLAGS & PIN4_bm) {
		if (currentPhase == RED_PHASE) {
			switchToYellow();
			currentPhase = YELLOW_TO_GREEN_PHASE;
			isTransitioning = 1;
			startTimer(62500);
		}
		} else if (PORTC.INTFLAGS & PIN5_bm) { 
		if (currentPhase == GREEN_PHASE) {
			switchToYellow();
			currentPhase = YELLOW_TO_RED_PHASE;
			isTransitioning = 1;
			startTimer(62500);
		}
	}

	PORTC.INTFLAGS = PIN4_bm | PIN5_bm;
}

int main(void) {
	// Initialize buttons
	PORTC.PIN4CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN5CTRL = PORT_ISC_RISING_gc;
	PORTC_PIN4CTRL = PORT_ISC_RISING_gc;

	// Initialize timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
	switchToRed(); 

	sei();

	while (1) {
		
	}
}
