/**
 * main2.c
 *
 * Created: 11/21/2024 8:32:47 AM
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
 
 void changeDecimalToGreyCode(int num){
	 unsigned int greyCode = num ^ (num >> 1);
	 while(greyCode != 0){
		push(greyCode % 2);
		greyCode /= 2; 
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
		changeDecimalToGreyCode(counter++);
		printStackInLEDs();
		sleep(SLEEP_TIME);
	 }
 }

