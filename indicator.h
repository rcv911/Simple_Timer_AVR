typedef unsigned char     U8;
typedef signed char       S8;
typedef unsigned int      U16;
typedef signed int        S16;
typedef unsigned long int U32;
typedef signed long int   S32;


#define SETBIT(X,N)	(X)|=(1<<(N))
#define CLEARBIT(X,N)	(X)&=~(1<<(N))
#define DELAY for(U32 i=0; i<35737; i++);
#define DELAY2 for(U32 i=0; i<20000; i++);
//---------------------------------------

void tick(void) {
	U8 i;
	SETBIT(PORTC,1);
	for(i=0;i<5;i++);
	CLEARBIT(PORTC,1);
	for(i=0;i<5;i++);
}

//---------------------------------------
void SEGerase(void) {
	int seg; //clear segment
	CLEARBIT(PORTC,0);
	for(seg=0;seg<25;seg++) {
		tick();
	}
}

void SEGempty(void) {
	int seg; //clear segment
	CLEARBIT(PORTC,0);
	for(seg=0;seg<8;seg++) {
		tick();
	}
}

void SEGdigit(S8 digit, U8 dot) {
	S8 i,data,d;
	//digit = 0..9 if --> data
	if(digit == 0) d = 252;
	if(digit == 1) d = 96;	
	if(digit == 2) d = 218;
	if(digit == 3) d = 242;
	if(digit == 4) d = 102;
	if(digit == 5) d = 182;
	if(digit == 6) d = 190;
	if(digit == 7) d = 224;
	if(digit == 8) d = 254;
	if(digit == 9) d = 246;
	if((digit<0)||(digit>9)) d = 0;
	
	//show dot
	if(dot==1) {
		data = d + 1; // h = 1
	}
	else {
		data = d;// h = 0
	}
	//get data on segment
	for(i=0;i<8;i++) {
		if((data&(1<<i))!=0) {
			SETBIT(PORTC,0);
			tick();
		}
		else {
			CLEARBIT(PORTC,0);
			tick();
		}
		
	}

}

void tripleSEG(S16 number, U8 dot) {
	S16 seg1, seg2, seg3;
	if (number == 0) {
		SEGdigit(0,dot);
		SEGdigit(0,dot);
		SEGdigit(0,dot);
	}
	else {
		seg3 = number%10;
		seg2 = (number/10)%10;
		seg1 =  number/100;
		SEGdigit(seg1,dot);
		SEGdigit(seg2,dot);
		SEGdigit(seg3,dot);
	}	
}



