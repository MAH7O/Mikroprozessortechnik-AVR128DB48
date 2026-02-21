/**
 * main2.c
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

 int main(void)
 {
		PORTD_DIRSET = PIN7_bm | PIN0_bm;
		PORTD_OUTSET = PIN0_bm;
			
		while(1){
			sleep(BLINK_TIME);
			PORTD_OUTTGL = PIN0_bm;
			PORTD_OUTTGL = PIN7_bm;
		}
		
 }

 /**
  * Wie konnen Sie ihre Programmausführung verzögern? - Stichwort: ¨ Busy Waiting ¨
  * mann erstellt ein methode die einfach zeit verschwendet ist in diesem sleep();
  * es soll irgen eine schleife besitzen for, while, do-while
  */

 /**
  * Was verbirgt sich hinter dem Keyword ”volatile“ ?
  * volatile sagt zu den compiler das diesen varible kann den wert von ihr in irgen ein zeit ändern
  * in diesen fall ich habe sie auch in meiner sleep methode in der zweite forschleife da sich der wert nicht geändert hat
  */

 /**
  * Welches der PORTx-Register eignet sich am besten fur das wiederholte Ein- und Ausschalten?
  * PORTx.OUT ist die allgemeine register für an ausschlaten ansonsten PORTx.OUTSET macht es nur an und PORTx.OUTCLR macht es nur aus
  * aber die richtige antwort ich würde mit PORTx.OUTTGL gehen sie guckt an den bestimmten pin falls er AN es schaltet ihm aus und wenn
  * er AUS ist schaltet ihm an
  */

