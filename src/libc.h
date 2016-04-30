
unsigned char ibuf[16];
unsigned char* itoa(unsigned int n){
		int e=14;
		while(n>=1)ibuf[e]=n%10+'0',n/=10,e--;
		return ibuf+e+1;
}