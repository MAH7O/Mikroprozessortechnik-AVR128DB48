/**
 * main1.c
 *
 * Created: 11/19/2024 11:26:41 AM
 * @author : Mahmoud Mahmoud
 */ 

#include <avr/io.h>

int main()
{
	PORTD_DIRSET = PIN7_bm;
	PORTD_OUTSET = PIN7_bm;
	return 0;
}

