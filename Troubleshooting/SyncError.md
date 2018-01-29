### WHAT THIS APPLIES TO - READ FIRST

This guide applies ONLY when all of the following is true - if this is not the case STOP READING NOW, because this page does not apply. 
* You are using an 8-bit AVR microcontroller with the Arduino IDE (ie, official Uno/Mega/Nano/ProMini, clone thereof, or third party AVR board, such as an ATTiny)
* You are NOT using a Due/Zero, or any other board that is not an AVR (other common non-AVR boards are teensy, ESP8266/ESP32, STM32, among others)
* The microcontroller you are using does NOT have native USB (ie, it is not a Leonardo/Micro)
* The microcontroller you are using makes use of a bootloader, and you are attempting to program it using that bootloader, over a serial port (ie, NOT via ICSP/ISP/SPI) 
* You are attempting to upload a sketch, not burn bootloader. 


When you get a sync error, it is unfortunately a very generic error (and there is no way for the computer to get more information for you) - all it knows is that it sent a command to try to talk to the bootloader, but the response it got was not valid. 

There are a huge number of possible causes. 

Assuming the board is known to have worked previously: 
* Incorrect board selected from Tools -> Board


If the board has not been used successfully yet, there are a few additional possibilities: 

* If the board uses an Atmega328p (Uno/Nano/ProMini) try all the other options that use the '328p. Careless clone manufacturers have been known to ship boards with the wrong bootloader on them, so they act like a different '328p based board.
* 
