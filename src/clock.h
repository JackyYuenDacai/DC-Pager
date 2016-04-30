unsigned long  tcount=1;
bit blinkt=0;
void timer0() interrupt 1 using 1{
	tcount=tcount+1; if(tcount%8893==0)blinkt=~blinkt;LED0=blinkt;
}
void timer0_init(void)	//50??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xD7;		//??????
	TH0 = 0xFD;		//??????
	TF0 = 0;		//??TF0??
}
void timer0_start(){
	tcount=666;
	TF0 = 0;	
	TR0=1; ET0 = 1; 
}
void timer0_pause(){		
		ET0=0;
		TR0=0;TF0 = 0;	
		if(tcount>=4611686018427387903)tcount=666;

}