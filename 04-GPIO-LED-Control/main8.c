/**
 * main7.c
 *
 * Created: 11/22/2024 5:52:47 PM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 #include <stdbool.h>
 
  #define STACK_SIZE 8
  
  #define PLUS1 PIN4_bm
  #define MINUS1 PIN5_bm
  #define MUL2 PIN6_bm
  #define DIV2 PIN7_bm

  unsigned int stack[STACK_SIZE];
  unsigned int sp = 0;
  
  unsigned int DELAY_TIME = 10; //es sollte 50ms
  
  volatile uint8_t counter = 0;
  
  bool IS_BUTTON_PRESSED = false;
  
  
  
  void push (unsigned int num){
	  if(sp < STACK_SIZE){
		  stack[sp++]	 = num;
	  }
  }
  
  unsigned int pop (){
	  return stack[--sp];
  }

  void delay(unsigned int time){
	  for(unsigned int i = 0; i < time; i++){
		  for(volatile unsigned int j = 0; j < 1000; j++){
			  
		  }
	  }
  }
 
 
 void initOutputs(void){
	 PORTD_DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
 }
 
  void turnAllLedsOff(void){
	  PORTD_OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
  }

 void changeDecimalToBinary(int num){
	 while(num != 0){
		 push(num % 2);
		 num /= 2;
	 }
 }
 
 void printStackInLEDs(){
	 while(sp != 0){
		 unsigned int number = pop();
		 PORTD_OUTSET = (number << sp); //die nummern die an der stack gespeichert sind k?nnen entweder 0 oder 1 sein und 'sp' ist die stelle die es aktivieren sollte (number << sp)
	 }
 }
 
 
 int main(void)
 {
		initOutputs();
		turnAllLedsOff();
		while(1){
			if(!IS_BUTTON_PRESSED){
				if(PORTC_IN & PLUS1){			
					delay(DELAY_TIME); // die delay sollte ungefähr bei 50ms liegen für den button bouncing	
					if(PORTC_IN & PLUS1){
						counter++;
						turnAllLedsOff();
						changeDecimalToBinary(counter);
						printStackInLEDs();
						IS_BUTTON_PRESSED = true;
						
					}
				}else if(PORTC_IN & MINUS1){
					delay(DELAY_TIME); // die delay sollte ungefähr bei 50ms liegen für den button bouncing
					if(PORTC_IN & MINUS1){
						counter--;
						turnAllLedsOff();
						changeDecimalToBinary(counter);
						printStackInLEDs();
						IS_BUTTON_PRESSED = true;
					
					}
				}else if(PORTC_IN & MUL2){
					delay(DELAY_TIME); // die delay sollte ungefähr bei 50ms liegen für den button bouncing
					if(PORTC_IN & MUL2){
						counter <<= 1; //multiplikation mit 2 durch bitoperation
						turnAllLedsOff();
						changeDecimalToBinary(counter);
						printStackInLEDs();
						IS_BUTTON_PRESSED = true;
					
					}
				}else if(PORTC_IN & DIV2){
					delay(DELAY_TIME); // die delay sollte ungefähr bei 50ms liegen für den button bouncing
					if(PORTC_IN & DIV2){
						counter >>= 1; //division mit 2 durch bitoperation
						turnAllLedsOff();
						changeDecimalToBinary(counter);
						printStackInLEDs();
						IS_BUTTON_PRESSED = true;
					
					}
				}
			}else{
				if(!(PORTC_IN & (PLUS1 | MINUS1 | MUL2 | DIV2))){ // checkt ob alle knöpfe nicht gedrückt sind
					IS_BUTTON_PRESSED = false;
				}
			}
		}
 }

