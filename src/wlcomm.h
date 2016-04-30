#define TINTERV 4
#define TTAG 170  //10101010 TICK
#define UTAG 204  //11001100 TURN
unsigned long tbuf;
unsigned char rbuf[128]={0};
int rlen=0;
void wl_sendbyte(unsigned char d);
unsigned char wl_recvbyte();
void wl_send_package(unsigned char *d,int len);
void wl_rsig_en();
void wl_recv_proc();
unsigned char wl_recvbyte();
void wl_recv_event();

void wl_sendbyte(unsigned char d){
		int i=7;
		for(i=7;i>=0;i--){
			while(tcount<tbuf+TINTERV)WMT_TRR=(d&(1<<i))/(1<<i);	
			tbuf=tcount;
		}
}
void wl_send_package(unsigned char *d,int len){
	int e=0;
	WMR_SWT=0;
	WMT_SWT=1;
	tbuf=tcount;
	for(e=0;e<6;e++)wl_sendbyte(TTAG);
	wl_sendbyte(UTAG);
	for(e=0;e<4;e++)wl_sendbyte(((unsigned char*)&len)[e]);
	for(e=0;e<len;e++){
			wl_sendbyte(d[e]);
	}
	wl_sendbyte(UTAG);	
	for(e=0;e<6;e++)wl_sendbyte(TTAG);
	WMT_SWT=0;	
	WMR_SWT=1;
}
void wl_rsig_en(){
	 INT_CLKO |= 0x20;               //(EX3 = 1)??INT3??
   EA = 1;
}
void wl_recv_signal() interrupt 11{
	INT_CLKO |= ~0x20;   
	wl_recv_proc();
	INT_CLKO |= 0x20;
}
unsigned char wl_recvbyte(){
	int tc=0,fc=0,i=7;		unsigned char ret=0;
	for(i=7;i>=0;i--){
		tbuf=tcount;while(tcount<tbuf+TINTERV/4);
		tbuf=tcount;while(tcount<tbuf+TINTERV/4)WMR_RCC==0?fc++:tc++;
		if(fc<tc)ret&=(1<<i);
		tbuf=tcount;while(tcount<tbuf+TINTERV/2);
	}
	return ret;
}
void wl_recv_proc(){
	int e=0;int len=0;
	tbuf=tcount;while(tcount<tbuf+TINTERV/4);
	tbuf=tcount;while(tcount<tbuf+TINTERV*7);
	for(e=0;e<5;e++)if(wl_recvbyte()!=TTAG)return;
	if(wl_recvbyte()!=UTAG)return;
	for(e=0;e<4;e++)((unsigned char*)&len)[e]=wl_recvbyte();
	for(e=0;e<len;e++){
			rbuf[e]=wl_recvbyte();
	}
	if(wl_recvbyte()!=UTAG)return;
	for(e=0;e<5;e++)if(wl_recvbyte()!=TTAG)return;
	wl_recv_event();
	return;
}
void wl_recv_event(){
}