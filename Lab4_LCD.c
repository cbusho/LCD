/*
 * Lab4_LCD.c
 * Created on: Oct 24, 2013
 * Author: C15Colin.Busho
 * Version 2- Adapted from Capt Branchflower
 * Description- Functions to implement various
 * functions to clear and write on an LCD
 */

#include "Lab4_LCD.h"
#include "msp430.h"
#define RS_MASK 0x40

char LCDCON;


void setSSLow(){
	 	 	 	 	 P1DIR |= BIT0;
	 	 	 	 	 P1OUT &= ~BIT0;
}

void setSSHigh(){
					 P1DIR |= BIT0;
					 P1OUT |= BIT0;
}

void SPISEND(char byteToSend){
					volatile char readByte;

					setSSLow();

					UCB0TXBUF = byteToSend;

					while(!(UCB0RXIFG & IFG2)){}

					readByte = UCB0RXBUF;

					setSSHigh();
}

void LCDWRT4(char ByteToWrite){
																							// load data to send
					  ByteToWrite &= 0x0f;                                               // ensure upper half of byte is clear

					  ByteToWrite |= LCDCON;                                             // set LCD control nibble

					  ByteToWrite &= 0x7f;                                               // set E low

	                  SPISEND(ByteToWrite);

	                  __delay_cycles(1000);

	                  ByteToWrite |= 0x80;                                               // set E high

	                  SPISEND(ByteToWrite);

	                  __delay_cycles(1000);

	                  ByteToWrite &= 0x7f;                                                 // set E low

	                  SPISEND(ByteToWrite);

	                  __delay_cycles(1000);

}

void LCDWRT8(char byteToSend){
	 	 	 	 	  char sendByte = byteToSend;

	 	 	 	 	  sendByte &= 0xf0;                                         // load full byte

					  sendByte = sendByte >> 4;												// shift in four zeros on the left
	                  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  // store send data
	                  LCDWRT4(sendByte);                                                // write upper nibble

	                  sendByte = byteToSend;                                            // load full byte

	                  sendByte &= 0x0f;                                               // clear upper nibble

	                  LCDWRT4(sendByte);                                                // write lower nibble

}

void writeDataByte(char dataByte){
					LCDCON |= RS_MASK;

					LCDWRT8(dataByte);

					__delay_cycles(1000);
}

void writeCommandNibble(char commandNibble){
					LCDCON &= ~RS_MASK;

					LCDWRT4(commandNibble);

					__delay_cycles(1000);
}

void writeCommandByte(char commandByte){
	 	 	 	 	LCDCON &= ~RS_MASK;

					LCDWRT8(commandByte);

					__delay_cycles(1000);

}

void initSPI(){
 		UCB0CTL1 |= UCSWRST;

        UCB0CTL0 |= UCCKPH|UCMSB|UCMST|UCSYNC;

        UCB0CTL1 |= UCSSEL1;

        UCB0STAT |= UCLISTEN;                              // enables internal loopback

		P1SEL |= BIT5;
		P1SEL2 |= BIT5;        								// make clock abailable on P1.5


		P1SEL |= BIT6;                             // make UCB0SSOMI available on P1.6
		P1SEL2 |= BIT6;


		P1SEL |= BIT7;                             // make UCB0SSIMO available on P1.7
        P1SEL2 |= BIT7;

        UCB0CTL1 &= ~UCSWRST;                               // enable subsystem

}

void LCDinit(){
    			writeCommandNibble(0x03);

                writeCommandNibble(0x03);

                writeCommandNibble(0x03);

                writeCommandNibble(0x02);                                       // set 4-bit interface

                writeCommandByte(0x28);                                         // 2 lines, 5x7

                writeCommandByte(0x0C);                                         // display on, cursor, blink off

                writeCommandByte(0x01);                                         // clear, cursor home

                writeCommandByte(0x06);                                         // cursor increment, shift off

                writeCommandByte(0x01);                                         // clear, cursor home

                writeCommandByte(0x02);                                         // cursor home

                SPISEND(0);                                                  // clear register

                __delay_cycles(1000);

}

void LCDclear(){
				writeCommandByte(0x01);

				LCDCON |= RS_MASK;

				__delay_cycles(1000);
}

void cursorToLineTwo(){
				writeCommandByte(0xC0);

				LCDCON |= RS_MASK;

				__delay_cycles(1000);
}

void cursorToLineOne(){
				writeCommandByte(0x02);

				LCDCON |= RS_MASK;

				__delay_cycles(1000);
}

void writeChar(char asciiChar){
				writeDataByte(asciiChar);
}

void writeString(char string[], char stringLength){
				char i = 0;
				for(i = 0; i < stringLength; i++){
					writeChar(string[i]);
				}
}

void scrollString(char string[], char stringLength){
				char i = 0;
				int temp = 0;
				temp = string[0];

				for(i = 0; i < stringLength; i++){
					string[i] = string[i+1];
				}
				string[stringLength - 1] = temp;

}


