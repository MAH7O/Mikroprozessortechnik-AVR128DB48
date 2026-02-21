/**
 * main2.c
 *
 * Created: 11/21/2024 8:32:47 AM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 #include <stdlib.h>
 
 unsigned int DELAY_TIME = 10; //es sollte 50ms
 
 uint8_t awaitedButton = 0;
 
   void delay(unsigned int time){
	   for(unsigned int i = 0; i < time; i++){
		   for(volatile unsigned int j = 0; j < 1000; j++){
			   
		   }
	   }
   }
 
 void initOutputs(void){
	 PORTD_DIRSET = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
 }
 
 void turnAllLedsOff(void){
	 PORTD_OUTCLR = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
 }
 
 
 void turnSignleLedOn(uint8_t led){
	 PORTD_OUTSET = led;
 }
 
 uint8_t checkAllLedsOff(){
	 return !(PORTD.OUT & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm));
 }
 
 void turnRandomLEDOnBasedOnNumber(int num){
	 switch (num){
		case 0:
			turnSignleLedOn(PIN4_bm);
			awaitedButton = PIN4_bm;
			break;
		case 1:
			turnSignleLedOn(PIN5_bm);
			awaitedButton = PIN5_bm;
			break;
		case 2:
			turnSignleLedOn(PIN6_bm);
			awaitedButton = PIN6_bm;
			break;
		case 3:
			turnSignleLedOn(PIN7_bm);
			awaitedButton = PIN7_bm;
			break;
	 }
 }
 
  void generateRandomLED(){
	   int randomLED = rand() % (4);
	   turnRandomLEDOnBasedOnNumber(randomLED);
   }
 

 
 int main(void)
 {
	 initOutputs();
	 while(1){
		if(checkAllLedsOff()){
			generateRandomLED();	
		}
		if(PORTC_IN & awaitedButton){
			delay(DELAY_TIME);
			if(PORTC_IN & awaitedButton){
				turnAllLedsOff();
				
				while(PORTC_IN & awaitedButton){
				}
			}
		}
	 }
 }

