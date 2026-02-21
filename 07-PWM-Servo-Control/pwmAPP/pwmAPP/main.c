/*
 * main1.c
 *
 * Created: 12/12/2024 3:41:45 AM
 * Author : Mahmoud Mahmoud
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 2000

#define PWM_DELAY_TIME 10

#define MINIMALPOSITION 1000
#define NULLPOSITION 1500
#define MAXIMALPOSITION 2000

#define PWM_PERIOD 20000

#define ROTATION_SPEED 5 // je weniger je schneller

void initServoOutput(){
	PORTF.DIRSET = PIN4_bm;
}

void softPWM(uint16_t time){
	
	PORTF.OUTSET = PIN4_bm;
	for (uint16_t i = 0; i < time / 10; i++) {
		_delay_us(PWM_DELAY_TIME);
	}
	
	PORTF.OUTCLR = PIN4_bm;
	for (uint16_t i = 0; i < (PWM_PERIOD - time) / 10; i++) {
		_delay_us(PWM_DELAY_TIME);
	}
}

void leftRotation(){
	softPWM(MINIMALPOSITION);
}

void resetToNormal(){
	softPWM(NULLPOSITION);
}

void rightRotation(){
	softPWM(MAXIMALPOSITION);
}

void continuousRotation(){
	for(uint16_t pos = MINIMALPOSITION; pos <= MAXIMALPOSITION; pos += 10){
		softPWM(pos);
		_delay_ms(ROTATION_SPEED);
	}
	
	for(uint16_t pos = MAXIMALPOSITION ; pos >= MINIMALPOSITION; pos -= 10){
		softPWM(pos);
		_delay_ms(ROTATION_SPEED);
	}
}

int main(void)
{
    initServoOutput();
	
	resetToNormal();
	_delay_ms(DELAY_TIME);
				
	leftRotation();
	_delay_ms(DELAY_TIME);
				
	rightRotation();
	_delay_ms(DELAY_TIME);
	
    while (1) 
    {

		continuousRotation();
		    

    }
}

