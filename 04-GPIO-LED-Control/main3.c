/**
 * main3.c
 *
 * Created: 11/21/2024 8:32:47 AM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 
 #define BLINK_TIME 50

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

 int main(void)
 {
		initOutputs();
			
		while(1){
			//leuchte von PD0 bis PD7
			for(int i = 0; i < 8; i++){
				sleep(BLINK_TIME);
				turnAllLedsOff();
				PORTD_OUTSET = (1 << i); // aktiviert PD in der stelle i es kann von PD0 bis PD7 sein (1 << 0) = PD0 bis (1 << 7) = PD7
			}

			//leuchte von PD7 bis PD0 rückwärts
			for(int i = 7; i >= 0; i--){
				sleep(BLINK_TIME);
				turnAllLedsOff();
				PORTD_OUTSET = (1 << i); // aktiviert PD in der stelle i es kann von PD0 bis PD7 sein (1 << 0) = PD0 bis (1 << 7) = PD7
			}
		}
		
 }

 /**
  * Gibt es einen eleganten Weg, mittels einer Zahl die LEDs wie gewollt einzeln aufleuchten zu lassen?
  * mann kann es durch PORTx.OUT = zahl; falls der zahl 10 ist wird sich dann automatisch auf binär gewechselt und macht es ihm einfach an´
  * ich habe es in diesem fall nicht benutzt aufgrund plagiate zu vermeiden damit mein code dann einfach besonders ist usw.
  */

