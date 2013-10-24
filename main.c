/*
 * main.c
 * Created on: Oct 21, 2013
 * Author: C15Colin.Busho
 * Description- calls functions to write
 * on an LCD screen
 */

#include <msp430.h> 
#include "Lab4.h"

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    char * myString1 = "ECE382 is my favorite class!";
    char * myString2 = "lol jk lol jk lol jk lol jk ";
    char myString1Length = 28;
    char myString2Length = 28;

    initSPI();

    LCDinit();

    LCDclear();

    while(1){
    	scrollString(myString1, myString2, myString1Length, myString2Length);
    }


}
