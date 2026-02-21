/*
 * adc.c
 *
 * Created: 1/1/2025 9:01:31 AM
 * Author : Mahmoud Mahmoud
 */ 

#define F_CPU 4000000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C_LCD.h"
#include <avr/interrupt.h>

#define BAUD_RATE 9600
#define S (16)

void initInputs(){
	PORTC.PIN4CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN5CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN6CTRL = PORT_ISC_RISING_gc;
	PORTC.PIN7CTRL = PORT_ISC_RISING_gc;
	sei();
} 

void initUsart(){
	USART3.BAUD = 1666;
	//USART3.BAUD = (64 * F_CPU) / (S * BAUD_RATE);
	USART3.CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_ASYNCHRONOUS_gc;
	USART3.CTRLB = USART_TXEN_bm;
}

ISR(PORTC_PORT_vect){
	while(!(USART3.STATUS & USART_DREIF_bm)){}
	if(PORTC.INTFLAGS & PIN4_bm){
		USART3.TXDATAL = 0x6A;
	}
	if(PORTC.INTFLAGS & PIN5_bm){
		USART3.TXDATAL = 0x6B;
	}
	if(PORTC.INTFLAGS & PIN6_bm){
		USART3.TXDATAL = 0x6C;
	}
	if(PORTC.INTFLAGS & PIN7_bm){
		USART3.TXDATAL = 0x6D;		
	}
	
	PORTC.INTFLAGS = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
}

int main(void)
{
	initInputs();
	initUsart();

	PORTB.DIRSET = PIN0_bm;
	PORTB.DIRCLR = PIN1_bm;
	
    while (1) 
    {

    }
}

