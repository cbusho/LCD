/*
 * main.c
 * Created on: Oct 21, 2013
 * Author: C15Colin.Busho
 * Description- calls functions to write
 * on an LCD screen
 */

#include <msp430.h> 
#include "Lab4_LCD.h"
#include "buttons/button.h"

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    char myString1[] = "ECE382 is my favorite class!  ";
    char myString2[] = "What's going on here!  ";
    char myString3[] = "Sup dudeski!  ";
    char myString4[] = "Hello bro-han!  ";
    char * Top = "Message?";
    char * Bot = "Press123";
    char myString1Length = 30;
    char myString2Length = 23;
    char myString3Length = 14;
    char myString4Length = 16;

    initSPI();

    LCDinit();

    LCDclear();

    writeString(Top, 8);
    cursorToLineTwo();
    writeString(Bot, 8);
    cursorToLineOne();

    configureP1PinAsButton(BIT1|BIT2|BIT3);         // configure pins 1, 2, and 3 as buttons

    P1DIR |= BIT0|BIT6;                             // set launchpad LEDs to output


        char buttons[] = {BIT1, BIT2, BIT3};
        char pressedButton = pollP1Buttons(buttons, 3);
        char myButton = 0;

        switch (pressedButton) {
            case BIT1:
            	cursorToLineTwo();
            	writeString(myString2, 8);
            	myButton = 1;
                break;
            case BIT2:
            	cursorToLineTwo();
            	writeString(myString3, 8);
            	myButton = 2;
                break;
            case BIT3:
            	cursorToLineTwo();
            	writeString(myString4, 8);
            	myButton = 3;
                P1OUT ^= BIT0|BIT6;
                waitForP1ButtonRelease(BIT3);
                break;
        }


    while(1){
    	writeString(myString1, 8);
    	cursorToLineTwo();
    	if (myButton == 1){
    		writeString(myString2, 8);
    	}
    	else if (myButton == 2){
    		writeString(myString3, 8);
    	}
    	else if (myButton == 3){
    	    writeString(myString4, 8);
    	}
    	cursorToLineOne();
    	__delay_cycles(100000);

    	scrollString(myString1, myString1Length);
    	if (myButton == 1){
    		scrollString(myString2, myString2Length);
    	}
    	else if (myButton == 2){
    		scrollString(myString3, myString3Length);
    	}
    	else if (myButton == 3){
    		scrollString(myString4, myString4Length);
    	}

    	LCDclear();

    }


}
