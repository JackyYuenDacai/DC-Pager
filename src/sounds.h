#ifndef __STC15F2K60S2_H_
	#include<STC15F2K60S2.H>
#endif
void SPK_Blink() interrupt 4{
		SPK_IO=~SPK_IO;
}
