/*
 * main.c
 * Created on: Oct 21, 2013
 * Author: C15Colin.Busho
 * Description- calls functions to write
 * on an LCD screen
 */

#include <msp430.h> 
#include "Lab4.h"
#include "../Lab4buttons/buttons/button.h"

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    char myString1[] = "ECE382 is my favorite class!  ";
    char myString2[] = "What's going on here!  ";
    char myString1Length = 30;
    char myString2Length = 23;

    initSPI();

    LCDinit();

    LCDclear();

    while(1){
    	writeString(myString1, 8);
    	cursorToLineTwo();
    	writeString(myString2, 8);
    	cursorToLineOne();
    	__delay_cycles(1000000);

    	scrollString(myString1, myString1Length);
    	scrollString(myString2, myString2Length);
    	LCDclear();

    }


}
