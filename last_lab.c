#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int


sbit LD1 = P1^0;
sbit LD2 = P1^1;
sbit LD3 = P1^2;
sbit VD1 = P1^3;
sbit VD2 = P1^4;
sbit VD3 = P1^5;
sbit BIT1 = P1^6;
sbit BIT2 = P1^7;

uchar code matrix_code[10][8]=
{
	{0xcf,0x87,0x83,0xc1,0xc1,0x83,0x87,0xcf}
};

uchar code num_code[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};                     
uchar code bit_code[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
uchar time_code[2] = {0x5b,0x6d};

uchar index = 0;

uchar times = 25;
uchar count = 0;

uchar vd_flag = 0xff;

uchar offset = 0;


void sleep(uint time){
	uchar t;
	while(time--)
		for(t=120;t>0;t--);
}

void init(){
	TMOD = 0x01;
	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	EA = 1;
	ET0 =1;
	TR0 = 1;
}


void t0_time() interrupt 1 using 1{
	TH0 = (65536-10000)/256;
	TL0 = (65536-10000)%256;
	count++;
	if(count == 100){
	 	count = 0;
		times--;
		if(times == 3){
			if(vd_flag == 0){
				VD2 = 1;
				VD3 = 0;
			}else{
				LD2 = 1;
				LD3 = 0;
			}
		}

		if(times == 0){
			if(vd_flag == 0){
				VD3 = 1;
				VD1 = 0;
				LD1 = 1;
				LD2 = 0;
	
			}else{
				LD3 = 1;
				LD1 = 0;
				VD1 = 1;
				VD2 = 0;
			}
			vd_flag = ~vd_flag;
		}

		if(times == -1){
			times = 25;
		}
		time_code[0] = ~num_code[times/10];
		time_code[1] = ~num_code[times%10];
	}
}


void dis_time(){
	BIT1 = ~BIT1;
	sleep(1);
	BIT2 = ~BIT2;
	index = index % 2;
	P0 = time_code[index++];
	sleep(1);
}

void dis_matrix(){
	P2 = 0xff;
	P2 = matrix_code[0][offset]; 	
	P3 = _crol_(P3, 1);
	if(++offset == 8){
		offset = 0;
	}
}

void main(){
	init();
	VD1 = 0;
	LD2 = 0;
	BIT1 = 1;
	BIT2 = 0;
	P3 = 0x80;
	while(1){
		dis_time();
		dis_matrix();
	}
}