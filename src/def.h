#include<STC15F2K60S2.H>
#include<INTRINS.H>
#include"ports.h"
#include"clock.h"
#include"delays.h"
#include"nokia5110.h"
#include"sounds.h"
#include"ds3231.h"

#include"wlcomm.h"
#include"res.h"
#include"config.h"
#include"libc.h"
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L          //????
#define BAUD 115200             //?????

#define NONE_PARITY     0       //???
#define ODD_PARITY      1       //???
#define EVEN_PARITY     2       //???
#define MARK_PARITY     3       //????
#define SPACE_PARITY    4       //????

#define PARITYBIT EVEN_PARITY   //?????

sbit INT1 = 0xB3;
sbit INT0 = 0xB2;

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

#define S2_S0 0x01              //P_SW2.0

bit busy;
void bbtn_en(){
	  INT1 = 1;
    IT1 = 1;              
    EX1 = 1;                
 
}
void bbtn_dis(){
		IT1 = 0;              
    EX1 = 0;   
}
void sysinit(){
		timer0_init();
		timer0_start();    
		EA = 1;
		NK5_init();	
		NK5_clear();
		BTN0=1,BTN1=1,BTN2=1,BTN3=1;
		wl_rsig_en();
		delayms(10);
		
}