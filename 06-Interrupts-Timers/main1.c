/*
 * InteruptAndTimer.c
 *
 * Created: 12/4/2024 5:21:59 AM
 * Author : mamod
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint32_t zustand = 1234;

uint32_t xorshift32(uint32_t zustand)
{
  uint32_t x = zustand;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  zustand = x;
  return x;
}

void initButtonInput(){
	PORTC_DIRCLR = PIN4_bm;
}

void initButtonInterrupt(){
	PORTC_PIN4CTRL = PORT_ISC_RISING_gc;
}

void initLEDOutputs(){
	PORTE_DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
}

void turnRandomLEDOn(){
	uint32_t randomNum = xorshift32(zustand);
	uint8_t color = ((randomNum % 7) + 1); //generiert zahl zwischen 1 und 7 
	
	
	PORTE.OUT = color; //color in bin�r w�hre dann 000 bis 111 damit k�nnen wir pin0 bis pin2 direkt einschalten
	
}

ISR(PORTC_PORT_vect){
	if(PORTC.INTFLAGS & PIN4_bm){
		turnRandomLEDOn();
		PORTC.INTFLAGS = PIN4_bm;
	}
}

int main(void)
{
	initButtonInput();
	initButtonInterrupt();
	initLEDOutputs();

	sei();

	while(1){
		
	}
}

//Was versteht man unter einem Pseudozufallszahlengenerator?
// Mit demselben Seed liefert der PRNG immer dieselbe Sequenz von Zahlen. Dies ermöglicht die Wiederholbarkeit und ist effizient also konstant O(1)

