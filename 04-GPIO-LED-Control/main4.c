/**
 * main4.c
 *
 * Created: 11/22/2024 6:15:47 PM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 
 #define STACK_SIZE 8

 unsigned int stack[STACK_SIZE];
 unsigned int sp = 0;
 
 unsigned int SLEEP_TIME = 50;
 
 volatile uint8_t counter = 0;
 
 void push (unsigned int num){
	 if(sp < STACK_SIZE){
		stack[sp++]	 = num;
	 }
 }
 
 unsigned int pop (){
	return stack[--sp];
  }

 void sleep(unsigned int time){
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
		PORTD_OUTSET = (number << sp); //die nummern die an der stack gespeichert sind k�nnen entweder 0 oder 1 sein und 'sp' ist die stelle die es aktivieren sollte (number << sp)  
	 }
 }
 
 int main(void)
 {
	 while(1){
		initOutputs();
		turnAllLedsOff();
		changeDecimalToBinary(counter++);
		printStackInLEDs();
		sleep(SLEEP_TIME);
	 }
 }

/**
 * Was versteht man unter dem sogenannten arithmetischen Uberlauf, und ist dieser hier von Nutzen?
 * wenn der zahl 8 bit ist und zahl = 255 ist wenn wir jetzt 1 addiren also gesamt 256 dan wird der zahl auf 0 gesetzt
 */

