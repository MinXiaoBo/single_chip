#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit BIT1 = P3^0;
sbit BIT2 = P3^1;
sbit KEY =  P1^0;

uchar code num_code[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
uchar time_code[2] = {0x7d, 0x3f};

uchar index = 0;
uchar times = 60;
uchar count = 0;

void sleep(uint time){
	uchar t;
	while(time--)
		for(t=120;t>0;t--);
}


void t0_time() interrupt 1 using 1{
	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	count++;
	if(count == 100){
	 	count = 0;
		times--;
		if(times == 0){
			times = 60;
		}
		time_code[0] = ~num_code[times/10];
		time_code[1] = ~num_code[times%10];
	}
}

void init(){
	TMOD = 0x01;
	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	EA = 1;
	ET0 =1;
	TR0 = 1;
}

void main(){
	init();
	BIT1 = 1;
	BIT2 = 0;
	while(1){
		if(!KEY){
			sleep(5);
			if(!KEY){
				if(time_code[0] != 0 || time_code[1] != 0){
					time_code[0] = 0x7d;
					time_code[1] = 0x3f;
					times = 60;
				}else{

				}
			}
		}
   		BIT1 = ~BIT1;
		sleep(5);
		BIT2 = ~BIT2;
		index = index % 2;
		P0 = time_code[index++];
		sleep(5);
	}
}
