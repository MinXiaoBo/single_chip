#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

uchar code num_code[1][8]=
{
	{0xcf,0x87,0x83,0xc1,0xc1,0x83,0x87,0xcf}
};

uchar times = 0;
uchar index,offset = 0;


void init(){
	TMOD = 0x00;
	TH0 = (8192-2000)/32;
	TL0 = (8192-2000)%32;
	EA = 1;
	ET0 = 1;
	//IE =  0x82;
	TR0 = 1;
}


void t0_time() interrupt 1{
	TH0 = (8192-2000)/32;
	TL0 = (8192-2000)%32;
	P0 = 0xff;
	P0 = num_code[0][offset]; 	
	P3 = _crol_(P3, 1);
	if(++offset == 8){
		offset = 0;
	}
	if(++times == 250){
		times = 0;
		if(++index == 10)
			index = 0;
	}
}


void main(void){
	P3 = 0x80;
	init();
	while(1);
}