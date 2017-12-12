## Simple timer on ATmega16

Simple real timer on ATmega16 based on 3 seven segment leds (counting 10 minutes) and 3 controlling buttons (PINB Atmega16). Pinouts of Atmega16 you can see in `datasheet_atmega16.pdf` or on [official page](http://www.microchip.com/design-centers/8-bit).
- Segment X and Y shows seconds  
- Segment Z shows minutes
- Button 0 resets timer 
- Button 1 starts timer 
- Button 2 pauses timer
Electrical circuit connection of segments:
![](images/7segments.png)

## Motivation

It's based structure shows how to work with timer in MCU. It can be useful for students class or for DIY stuff who begginer in AVR.   

## Installation

0. You can use another MCUs. All you need is datasheet. Don't forget change pins!  
1. Make project in AVR Studio choosing 8-bit MCU ATmega16.  
2. Download head file `indicator.h` into your project location.
3. Copy code from `sec_r.c` into your `main.c` file.
4. Build project.

## License

Free
