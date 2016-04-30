#include"def.h"

void bbtn()interrupt 2 {
		LED0=0;while(BBTN==0)LED0=1;
}
int a=32;
unsigned long tb=0;
void main(){
	sysinit();
	NK5_draw_bmp_pixel(0,0,dc_ico,84,48);
  LED1=0;
	delayms(1000);
	LED0=1;LED1=1;
	NK5_draw_bmp_pixel(0,0,dp_sp,84,48);
	delayms(3000);	
	NK5_draw_bmp_pixel(0,0,d_btnup,84,48);
	while(BBTN==0);tb=tcount;interv=0;
	NK5_draw_bmp_pixel(0,0,d_btndn,84,48);
	for(a=0;a<10;a++){
			while(BBTN==0||(tcount-tb)<6000);
			interv+=(tcount-tb)/10,tb=tcount;LED0=1;
			NK5_draw_bmp_pixel(0,0,d_btnup,84,48);
			while(BBTN!=0||(tcount-tb)<6000);	
			interv+=(tcount-tb)/10,tb=tcount;
			NK5_draw_bmp_pixel(0,0,d_btndn,84,48);LED0=0;
	}
	delayms(1000);
	interv/=20;
	NK5_draw_bmp_pixel(0,0,d_procg,84,48);
	
	NK5_write_str(0,0,itoa(interv)); 

	while(1)wl_send_package("JackyYuen",10);
}