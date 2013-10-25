LCD
===

Library for initializing a SPI system, LCD screen, and writing to it

FUNCTIONS
=========

void setSSLow() Configures 
  slave select to Pin 0 
  Pin settings P1DIR = 1 (output) 
  P1OUT = 0 (sets it low)

void setSSHigh() 
  Configures slave select to Pin 0 
  Pin settings P1DIR = 1 (output) 
  P1OUT = 1 (sets it high)

void SPISEND(char byteToSend) 
  Sends a byte to the SPI system to be read

void LCDWRT4(char ByteToWrite) 
  Sends a nibble twice 
  once with read enabled and once with write enabled

void LCDWRT8(char byteToSend) 
  sends the upper nibble of a byte to LCDWRT4 and then the lower nibble 
  usage: 
    LCDWRT8(F0) does LCDWRT4(1111) (binary) 
    does LCDWRT4(0000) (binary)

void writeDataByte(char dataByte) 
  sets RS bit to high in order to write 
  then sends parameter to LCDWRT8()

void writeCommandNibble(char commandNibble) 
  sets RS bit low in order to give LCD command 
  then sends parameter to LCDWRT4()

void writeCommandByte(char commandByte) 
  sets RS bit low in order to give LCD command 
  then sends parameter to LCDWRT8()

void initSPI() 
  Configures clock to Pin 5 
  Configures SOMI to Pin 6 
  Configures SIMO to Pin 7

void LCDinit() 
  enables the LCD to two lines by eight spaces

void LCDclear() 
  clears the LCD screen
  sets RS bit high to write

void cursorToLineTwo() 
  moves the cursor to second line of LCD
  sets RS bit high to write

void writeChar(char asciiChar)
  sets RS bit high to write
  writes a Char to the LCD

void writeString(char string[], char stringLength) 
  writes a string to whatever line the LCD is on

void scrollString(char string[], char stringLength) 
  places first character in a temporary variable 
  shifts all other characters left one spot 
  places first character at the end 
  usage: 
    string1 = hello; 
    scrollString(string1, 5); 
    string1 = elloh
