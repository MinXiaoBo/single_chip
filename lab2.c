#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

uchar code num_code[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};                     
uchar code bit_code[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

uchar index = 0;
uchar bit_index = 0;

void sleep(uint time){
	uchar t;
	while(time--)
		for(t=120;t>0;t--);
}

void main(){
	P0 = 0x00;
	P2 = 0x00;
	while(1){
		P2 = ~bit_code[bit_index++];
		bit_index = bit_index % 6;
		index = index % 6;
		P0 = ~num_code[index++];
		sleep(5);
	}
}