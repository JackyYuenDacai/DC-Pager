void nop(){
	;
}
volatile void delayus(unsigned int n){
		unsigned int j=0,i; 
    for (j=0;j<n*4;j--){
			nop();

			i = 2;
			while (--i);
		}
  
}
volatile void delayms(unsigned int c)//1ms????
{
		unsigned long td=tcount;
		while(tcount<td+20*c);
	
}