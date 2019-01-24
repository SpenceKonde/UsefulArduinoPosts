### What does this guide cover?
If any of the following are not true, **STOP READING NOW, THIS GUIDE WILL NOT HELP YOU AND WILL SEND YOU DOWN WRONG PATH**.

* You are using an 8-bit AVR based board - Arduino Uno/Mega/Nano/ProMini, clone thereof, or a third party board with an AVR programmed over serial through a USB-serial adapter (external or on-board - such as Sanguino/Bobuino/Mighty1284p, or ATTiny with optiboot bootloader).
* You are NOT using a board with native USB (Leonardo, Pro Micro, Micro, Digispark, Trinket). 
* You are NOT using a board that you are programming via an ISP programmer. 
* You are NOT using a non-AVR board! Due, Zero, MKR boards, ESP8266/ESP32, and any other third party board not based on an atmega or attiny board is NOT an AVR. 
* You can successfully "Verify" (compile) your sketch, but cannot "Upload" it. 
* The board has a bootloader already installed (if starting from a virgin processor, you must have done "Burn Bootloader" with an ISP programmer successfully)
* You are not using an Arduino Uno Wifi Rev. 2. These are new and we don't yet have a sufficient body of knowledge within the community to create a troubleshooting guide like this. 

### Using this guide
Start at the top, and go to other sections when indicated. Don't try solutions from other sections that this guide doesn't tell you to use. 

If you get to an "Open Thread in Arduino Forum" step, be sure to include the following:
* What board you are using. 
* What operating system you are using.
* The verbose upload error output (click the copy error message button to copy it to clipboard easily)
* Put the verbose error output between [code] [/code] tags, otherwise people will make disparaging comments and tell you to read the thread on how to use the forum. 
* A link to the product page for the board you are using, if it did not come in an official arduino box. Use the link button (chain icon) to make the link clickable. 
* List the troubleshooting steps you have taken.
* If you are using a board that requires a third party hardware package, link to where you got it from. Use the Link button to make the link clickable. 
* If you are using an own-built board, attach a schematic. If you are building an arduino-on-breadboard, attach a clear photograph of your breadboard, as well as a schematic. Do not include a fritzing image, we hate those - a clear photograph of a hand-drawn schematic is better. 

### Do you have the right board selected?
1. Open the Tools -> Board submenu. Select the board you are using. 
2. Open Tools menu - if you see new sub-menus have appeared, make sure you have selectected the correct board. 

### Do you have the right port selected? 
1. Connect board to computer (via USB port for board connected via on-board serial adapter, or with external USB-serial adapter for a board without one).
2. Open IDE, Open the tools menu. Is the Port submenu greyed out? If so, go to Board Not Detected. 
3. Open the Tools -> Port submenu. Note the available ports. Close the tools menu. 
4. Disconnect the Arduino from the USB port. 
5. Open the Tools -> Port menu. One port should now be missing. If not, none of the ports correspond do your arduino, go to Board Not Detected. 
6. Close Tools menu, reconnect arduino. 
7. From Tools -> port, select the port that has now reappeared.
8. Open the blink sketch. File -> Examples -> Basics -> Bare Minimum
9. Attempt to upload. If success, you're done. Stop reading this guide and start using your arduino. 
10. If failure, open File -> Preferences. In the Verbose Output section, uncheck "Compilation" (if it's checked) and check "Uploading"
11. Attempt to upload Blink again. Go to section that matches the error. 

### Access Denied
1. Another program may be using the serial port. Make sure any programs that might attempt to use the serial port are closed.
2. If using Linux, access to serial ports is restricted, and by default users do not have access to them. Add your user to the "dialout" group and try again. 
3. Some unusual programs (often "modem managers" that run in the background, or background programs intended for working with other serial devices) may connect to any serial port connected, assuming that it is a modem, or whatever serial device the program was intended to work with. You must close this program before using your Arduino (and unless you actually use it, you should uninstall it). 
4. If still experiencing this problem, post to Installation/Troubleshooting section of the Arduino Forums. 

### STK500 Sync Error
Unfortunately, this is a very generic error message - it essentially means "Found a serial port, but board gave the wrong response" 
1. If using a Nano, try using the (Old Bootloader) option from Tools -> Processor, and attempt to upload again. If this is not present, open board manager, and update the official AVR board package to version 1.6.21 (later versions have a bug) and restart the IDE - if you had to do this, try to upload with both "Atmega328p (Old Bootloader)" and "Atmega328p". Generally, official boards since 2018 require the "Atmega328p" option, while clones and older official boards require the Old Bootloader option. 
2. Doublecheck that correct board and board version is selected. 
3. If board is a clone based on an atmega328p (nano/uno/pro mini and clones thereof), try uploading using the other atmega328p boards selected. Occasionally, Arduino clones sometimes ship with the wrong bootloader). 
4. If you have anything else connected to TX, RX (0 and 1 on official boards, for third party boards, check the documentation to be sure which is TX and RX) or Reset pin, remove them before uploading. Anything connected to these pins will interfere with uploads. 
5. Make sure that board is not sitting on a conductive surface, and that the bottom of the board is not in contact with any electrically conductive debris. Try to upload again if this was found to be the case. 
6. If board uses an external USB-serial adapter (skip this step if USB is on-board), double-check connections. TX of adapter goes to RX of board, RX of adapter goes to TX of board. DTR or RTS line of serial adapter goes to pin normally marked DTR (sometimes BLK) on Arduino. If using an own-built arduino board, or one without a 1x6 serial programming header or pin marked DTR, the DTR pin of serial adapter should be connected to one side of a 0.1uF ceramic capacitor, and the other side connected to the Reset pin of the microcontroller. If using a serial adapter without a DTR or RTS pin, the serial adapter is not suitable for programming an arduino. 
7. Perform a loopback test: Connect Reset of Arduino to ground, and TX of Arduino to RX of Arduino. Open Serial monitor, type something, and press enter. The text you type should be echoed back. If not, serial adapter is not working - replace it (or entire board if it has on-board USB-serial adapter). 
8. Open a thread on Arduino forum. If using own-built board, or third party board that is not a clone of an official board, post in Microcontrollers section. If using official board or clone thereof, post in Installation/Troubleshooting section.

### Upload stops partway through
Note: If using an Arduino Mega 2560 clone or very old official one, and bare minimum uploads, but your sketch fails part-way, check if your sketch contains any strings with three or more consecutive exclamation marks "!!!" - this triggers a bug in old versions of the bootloader, and this version is still shipping on many clones; remove these. This can be solved permanently be using an ISP programmer to "Burn Bootloader" - see guides on burning bootloader. 
1. Open a thread in AVRDude/STK500/Bootloader problem section of Arduino Forum - you have a very strange problem. 

### Verification Failed
1. Open a thread in AVRDude/STK500/Bootloader problem section of Arduino Forum - you have a very strange problem.

### Other error referring to the port
1. Go to section Driver Not Installed
2. Failing that, open a thread in Installation/Troubleshooting section.

### Board not recognized (Windows)
1. Turn on sound (if it's off). Disconnect arduino (or external USB-serial adapter) from USB port.
2. Reconnect board, listening for the "Ka-bing" noise. 
3. If you heard a noise, open device manager. If there is a device that says Code 43 device descriptor failed, or if no device with the ! marker indicating an error is shown, continue.  If there is an "Unknown Device", or a device with a the ! symbox next to it, go to section Driver Not Installed
4. Use a different USB cable - bad USB cables are surprisingly common. If it uses a micro usb port, this is especially true, as there are many "charging only" cables around. Ideally, use a cable that is known to be good. 
5. If using a USB 3.0 port, try using a USB 2.0 port. If you only have USB 3.0 ports, try with a USB 2.0 hub between the port and your computer. Some USB 3.0 interfaces fall far short of the goal of perfect backward compatibility. 
6. If you were previously using an official Uno or Mega, or a clone that uses the same mega16u2 as serial adapter, AND it previously worked, and then failed when using an external power supply or driving motors, you've probably damaged the USB-serial adapter. This part is not replacible without hot-air rework facilities - discard board or place it in your junk bin and replace board. 
7. Open a thread in Installation/Troubleshooting section if using an official board or clone thereof. Otherwise, post in Microcontrollers section. 

### Board not recognized (other OS) 
Pending - I don't know enough about these operating systems to create an analogous set of steps for them. 

### Driver not installed (Windows)
1. Identify the USB-serial adapter chip. For boards with on-board USB-serial adapter, examine the black chip near the USB connector (this is on the bottom of Nano boards). It will be either mega16u2, CH340G, CP2102, or FT232. 
2. If mega16u2 or FT232, this driver is installed automatically when installing the IDE using the installer; if using the .zip package, they are located in the drivers folder; use Device Manager to install the appropriate driver. 
3. If CH340G or CP2102, google your operating system, the word drivers, and the part number, download and install the driver. 
4. After installing driver, device manager should no longer show an unknown device. Go back to the beginning, and hopefully everything will now work. 
5. If still showing Unknown Device, open a thread in Installation/Troubleshooting section. 

### Driver not installed (other OS) 
Pending - I don't know enough about these operating systems to create analogous list. 
