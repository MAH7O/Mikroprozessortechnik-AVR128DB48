/**
 * main7.c
 *
 * Created: 11/22/2024 5:52:47 PM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 
  #define STACK_SIZE 8

  unsigned int stack[STACK_SIZE];
  unsigned int sp = 0;
  
  unsigned int DELAY_TIME = 10; //es sollte 50ms
  
  unsigned int counter = 0;
  
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
			if(PORTC_IN & PIN4_bm){
				
						delay(DELAY_TIME); // die delay sollte ungefähr bei 50ms liegen für den button bouncing
						
						if(PORTC_IN & PIN4_bm){
							counter++;
							turnAllLedsOff();
							changeDecimalToBinary(counter);
							printStackInLEDs();
							while(PORTC_IN & PIN4_bm){
							
							}
					}
			}
		}
 }

 /**
  * Was versteht man unter dem Begriff ”Button-Bouncing“?
  * wir haben es in der vorlesung erklärt bekommen und zwar wenn man den knopf drückt ist nicht direkt auf 1 gestzt also ist noch nicht auf english stable
  * so wir können dann ungefähr 50ms warten biss es dann stabil ist und dann nochmal checken 
  */

