#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit KEY =  P1^0;

uchar code num_code[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};


uchar ten,single;
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
			times = 59;
		}
		ten = ~num_code[times/10];
		single = ~num_code[times%10];
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
	while(1){
		if(!KEY){
			sleep(5);
			if(!KEY){
				if(ten != 0 || single != 0){
					ten = ~0x82;
					single = ~0xc0;
					times = 60;
				}else{

				}
			}
		}
	   	P0 = ten;
		sleep(100);
		P2 = single;
		sleep(100);
	}
}
