#ifndef __STC15F2K60S2_H_
	#include<STC15F2K60S2.H>
#endif



sbit LED0 = P2^7;
sbit LED1 = P4^5;
sbit    NK5_RST = P3^6;  //??,0??
sbit    NK5_CE  = P3^5;  //??
sbit    NK5_DC  = P3^4;  //1???,0???
sbit    NK5_DIN = P4^0;  //??
sbit    NK5_CLK = P5^5;  //??

sbit BTN0 = P5^4;
sbit BTN1 = P1^7;
sbit BTN2 = P1^6;
sbit BTN3 = P1^5;
sbit BBTN = P3^3;

sbit DS_CL	= P1^1;
sbit DS_DA	= P1^0;

sbit WMT_SWT = P0^2;
sbit WMR_SWT = P0^3;

sbit WMT_TRR = P4^7;
sbit WMR_RCC = P4^6;

sbit SPK_IO = P0^4;