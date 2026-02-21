/*
 * i2c.c
 *
 * Created: 1/19/2025 7:42:04 PM
 * Author : mamod
 */ 
#define F_CPU 4000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "I2C_LCD.h"

uint8_t sensor_read_buffer[8];

#define SENSOR_ADDRESS 0x29

void sensor_init(){
	i2c_write_byte(SENSOR_ADDRESS, 0x00);
	i2c_write_byte(SENSOR_ADDRESS, 0x0C);
	_delay_ms(50);
}

int main(void)
{
    lcd_init();
	lcd_clear();
	sensor_init();
	
	char lcd_buffer[16];
	
    while (1) 
    {
		lcd_clear();
		i2c_read(SENSOR_ADDRESS, sensor_read_buffer, 8);
		
		uint16_t clear = sensor_read_buffer[1] << 8 | sensor_read_buffer[0];
		uint16_t red = sensor_read_buffer[3] << 8 | sensor_read_buffer[2];
		uint16_t green = sensor_read_buffer[5] << 8 | sensor_read_buffer[4];
		uint16_t blue = sensor_read_buffer[7] << 8 | sensor_read_buffer[6];
		
		lcd_moveCursor(0,0);
		sprintf(lcd_buffer, "C: %d | R: %d", clear, red);
		lcd_putString(lcd_buffer);
		lcd_moveCursor(0,1);
		sprintf(lcd_buffer, "G: %d | B: %d", green, blue);
		lcd_putString(lcd_buffer);
		
		_delay_ms(5000);
    }
}

