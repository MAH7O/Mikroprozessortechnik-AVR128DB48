/**
 * main6.c
 *
 * Created: 11/21/2024 8:32:47 AM
 * @author : Mahmoud Mahmoud
 */

 #include <avr/io.h>
 
 
 void initOutputs(void){
	 PORTD_DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
 }
 
  void turnAllLedsOff(void){
	  PORTD_OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
  }
  
  void turnAllLedsOn(void){
	   PORTD_OUTSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
  }
 
 void initInput(void){
	  PORTC_DIRCLR = PIN4_bm;
	  PORTC_PIN4CTRL = PORT_PULLUPEN_bm;
 }

 
 
 int main(void)
 {
	    initInput();
		initOutputs();
/*		while(1){
			if(PORTC_IN & PIN4_bm){
				PORTD_OUTSET = PIN0_bm;
			}else{
				PORTD_OUTCLR = PIN0_bm;
			}
		}*/

		while(1){
			if((PORTC_IN & PIN4_bm) | (PORTC_IN & PIN5_bm) | (PORTC_IN & PIN6_bm) | (PORTC_IN & PIN7_bm)){
				turnAllLedsOn();
				}else{
				turnAllLedsOff();
			}
		}
 }


