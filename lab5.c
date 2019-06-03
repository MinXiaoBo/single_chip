/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <string.h>
#define uchar unsigned char
#define uint unsigned int

void Initialize_LCD();
void ShowString(uchar,uchar,uchar *);


sbit K1 = P3^0;
sbit K2 = P3^1;
sbit K3 = P3^2;

uchar statu_flag = 0;

uchar code Prompt[]="PRESS K1--K4 TO START DEMO PROG";

uchar code Msg[500]=
{
 	"My Name Is MinBo and this is very interesting."
	"A slow sparrow should make an early start."
	"One is never too old to learn."
};

uchar Disp_Buffer[32];

void Delayxms(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void v_display(){
	uchar *code_index = Msg;
	uchar *buf_index = Disp_Buffer;
	uchar i,j = 0;
	F0 = 0;
	ShowString(0,0,"                ");
	ShowString(0,1,"                ");
	while(code_index[i] != '\0'){
		 buf_index[j++] = code_index[i++];
		 if(j == 16){
		 	  buf_index[j+1] = '\0';
			  ShowString(0,0,buf_index);
			  ShowString(0,1,buf_index);
			  j = 0;
			  ShowString(0,0,"                ");
		 	  ShowString(0,1,"                ");
		 }
		 
	}
	 buf_index[j+1] = '\0';
	 ShowString(0,0,buf_index);
	 ShowString(0,1,buf_index);
	 F0 = 1;	
}

void h_display(){
	uchar *code_index = Msg;
	uchar *buf_index = Disp_Buffer;
	uchar i,j,k = 0;
	F0 = 0;
	ShowString(0,0,"                ");
	ShowString(0,1,"                ");
	while(code_index[i] != '\0' && F0 == 0){
		 buf_index[j++] = code_index[i++];
		 if(j == 16){
		 	  buf_index[j+1] = '\0';
			  ShowString(0,k,buf_index);
			  ShowString(0,k,"                ");
			  j = 0;
			  if(k == 0){
			  	k = 1;
			  }else{
			  	k = 0;
			  }
			  
		 }
	}
	if(F0 == 0){
		buf_index[j+1] = '\0';
    	ShowString(0,0,buf_index);
    	ShowString(0,1,buf_index);
		F0 = 1;
	}
}


void EX_INT0() interrupt 0
{
 	F0 = !F0;
}

void main()
{
 	uint Count = 0;
	IE = 0x81;
	IT0 = 1;
	F0  = 0;
	Initialize_LCD();
	ShowString(0,0,Prompt);
	ShowString(0,1,Prompt+16);
	while(1)
	{
	 	if(K1 == 0)
		{
			v_display();
			Delayxms(200);
		}
		else if(K2 == 0)
		{
			h_display();
			Delayxms(200);	
		}
	}
}