/**
 * main7.c
 *
 * Created: 11/22/2024 5:52:47 PM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 #include <stdbool.h>
 #include "I2C_LCD.h"
 
  #define STACK_SIZE 33
  
  #define ASCII0 48
  #define ASCIINEG 45
  
  #define PLUS1 PIN4_bm
  #define MINUS1 PIN5_bm
  #define MUL2 PIN6_bm
  #define DIV2 PIN7_bm

  int32_t stack[STACK_SIZE];
  unsigned int sp = 0;
  
  unsigned int DELAY_TIME = 10; //es sollte 50ms
  
  int32_t counter = 0;
  
  bool IS_BUTTON_PRESSED = false;
  
  bool negativeNumber = false;
  
  bool zeroHit = false;
  
  
  
  void push (unsigned int num){
	  if(sp < STACK_SIZE){
		  stack[sp++] = num;
	  }
  }
  
  int32_t pop (){
	  return stack[--sp];
  }

  void delay(unsigned int time){
	  for(unsigned int i = 0; i < time; i++){
		  for(volatile unsigned int j = 0; j < 1000; j++){
			  
		  }
	  }
  }

 void sortTheNumbersInStack(int32_t num){
	 if (num == INT32_MIN) { // adds manually the min negative number positive -2147483648 because was always converting the number to a positive one
		 negativeNumber = true;
		 push(8);
		 push(4);
		 push(6);
		 push(3);
		 push(8);
		 push(4);
		 push(7);
		 push(4);
		 push(1);
		 push(2);
		 return;
	 }
	 
	 if(num < 0){ // check if the number is negative
		 negativeNumber = true; //turn the negative number boolean to true its for the '-' char to show it in the LCD screen when a negative number is there
		 num = ~num + 1; // make it positive 
	 }else{
		 negativeNumber = false;
	 }
	 
	 do{
				 push(num % 10);
				 num /= 10; 
	 }while(num > 0);
	 

 }
 
 void printStackInLCD(){
	 if(negativeNumber){
		 lcd_putChar(ASCIINEG);
	 }
	 while(sp != 0){
		 int32_t number = pop();
		 lcd_putChar(number + ASCII0);
	 }
 }
 
 
 int main(void)
 {
		lcd_init();
		lcd_clear();
		lcd_putChar(ASCII0);	
		while(1){
			if(!IS_BUTTON_PRESSED){
				if(PORTC_IN & PLUS1){			
					delay(DELAY_TIME); // die delay sollte ungef?hr bei 50ms liegen f?r den button bouncing	
					if(PORTC_IN & PLUS1){
						counter++;
						lcd_clear();	
						sortTheNumbersInStack(counter);
						printStackInLCD();
						IS_BUTTON_PRESSED = true;
						
					}
				}else if(PORTC_IN & MINUS1){
					delay(DELAY_TIME); // die delay sollte ungef?hr bei 50ms liegen f?r den button bouncing
					if(PORTC_IN & MINUS1){
						counter--;
						lcd_clear();	
						sortTheNumbersInStack(counter);
						printStackInLCD();
						IS_BUTTON_PRESSED = true;
					
					}
				}else if(PORTC_IN & MUL2){
					delay(DELAY_TIME); // die delay sollte ungef?hr bei 50ms liegen f?r den button bouncing
					if(PORTC_IN & MUL2){
						counter <<= 1; //multiplikation mit 2 durch bitoperation
						lcd_clear();	
						sortTheNumbersInStack(counter);
						printStackInLCD();
						IS_BUTTON_PRESSED = true;
					
					}
				}else if(PORTC_IN & DIV2){
					delay(DELAY_TIME); // die delay sollte ungef?hr bei 50ms liegen f?r den button bouncing
					if(PORTC_IN & DIV2){
						counter >>= 1; //division mit 2 durch bitoperation
						lcd_clear();	
						sortTheNumbersInStack(counter);
						printStackInLCD();
						IS_BUTTON_PRESSED = true;
					
					}
				}
			}else{
				if(!(PORTC_IN & (PLUS1 | MINUS1 | MUL2 | DIV2))){ // checkt ob alle kn?pfe nicht gedr?ckt sind
					IS_BUTTON_PRESSED = false;
				}
			}
		}
 }

