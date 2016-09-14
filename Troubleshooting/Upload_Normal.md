You should be here if you are experiencing a problem uploading (but not compiling/"verifying" - if that doesn't work, go here), and you are using an 8-bit AVR-based Arduino board that is programmed via the serial port (ie, using a bootloader), and does NOT have native USB. For example, an Arduino Uno, Mega, Pro Mini or Nano. This is also generally applicable to third party hardware packages that use a serial bootloader (like Optiboot). This guide is not appropriate for the Leonardo/Micro (that has native USB) or anything that you're programming using an ISP programmer (as that does not use a serial bootloader). 

### Check Tools -> Port menu
1. Unplug your Arduino board, and check the contents of the Tools -> Port menu. Close the tools dropdown menu. 
2. Plug in your Arduino board - If using Windows, listen for the "new hardware" noise, and look for the "USB device has malfunctioned" 
3. 




