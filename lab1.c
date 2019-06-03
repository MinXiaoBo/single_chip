#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

uchar code bit_code[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
uchar index = 0;

void sleep(uint time){
	uchar t;
	while(time--)
		for(t=120;t>0;t--);
}

void main(void){
	P0 = 0x00;
	while(1){
		P0 = ~bit_code[index++];
		index = index % 8;
		sleep(500);
	}
}