/*
 * main1.c
 *
 * Created: 11/26/2024 10:20:48 AM
 * Author : mamod
 */ 

#include <avr/io.h>
#include "I2C_LCD.h"

int main(void)
{
	lcd_init();
	lcd_clear();
	lcd_putString("Hello Display");

}

