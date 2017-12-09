#include <avr\io.h>
#include <avr\interrupt.h>
#include <avr\signal.h>
#include <indicator.h>

#define B0	PINB == 254
#define B1	PINB == 253
#define B2	PINB == 251
#define DREBZ	for(U8 i=0; i>50; i++)


volatile U8 milisec, sec, min, t, btn0, btn1, btn2, m;

ISR(TIMER1_COMPA_vect){
    // tick-tock
    milisec++;
    if(milisec == 100) {
  	   sec++;
  	   milisec = 0;
  	 }
  	 if(sec == 60) {
  	   min++;
  	   sec = 0;
    }
    if(min == 10) {
  	   min = 0;  	
    }
    // 7Segment dot
	 if(milisec==0) {
	   t = 1;
	 }
	 if(milisec==50){
	   t = 0;
	 }
}




void main(void) {
   asm("cli"); // Disable global interrupts

   // I/O port
   DDRC = 255;
   PORTC = 0;
   // Button
   DDRB = 0;
   PORTB = 255;
	
   // Parameters
   milisec = 0;
   sec = 0;
   min = 0;
   t = 0;
   btn0 = 1;
   btn1 = 0;
   btn2 = 0;

   // Timer 1
   TCCR1A = 0;
   TCCR1B = (1<<WGM12)|(1<<CS12); // CTC mode, CLK/256
   OCR1A = 144; // 1 msec --> if CLK/256
   TIMSK|=(1<<OCIE1A); // Enable compare interrupt on timer 1
   TCNT1 = 0; // Init counter

   asm("sei"); // Enable global interrupts

   while(1) {
   	if(B0) {
        DREBZ;
        btn0 = 1;
    	btn1 = 0;
        btn2 = 0;
  		}

  		if(B1) {
    		DREBZ;
    		btn0 = 0;
    		btn1 = 1;
    		btn2 = 0;
  		}

  		if(B2) {
    		DREBZ;
    		btn0 = 0;
    		btn1 = 0;
    		btn2 = 1;
  		}

  		// Button0
  		if(btn0 == 1) {  			
    		asm("cli");
    		milisec = 0;
    		sec = 0;
    		min = 0;
    		t = 0;
    		SEGdigit(0,0);
    		SEGdigit(0,0);
    		SEGdigit(0,0);
			DELAY2;
  		}	
  		// Button1
  		if(btn1 == 1) {
    		asm("sei");
    		SEGdigit(min, t);
  			SEGdigit(sec/10, 0);
  			SEGdigit(sec%10, 0);
  			DELAY2;
  		}
  		// Button2
  		if(btn2 == 1) {
    		asm("cli");
    		SEGdigit(min, t);
  			SEGdigit(sec/10, 0);
  			SEGdigit(sec%10, 0);
  			DELAY2;
  		}
	}
}







