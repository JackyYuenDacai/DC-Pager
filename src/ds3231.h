#define uchar   unsigned char 
#define uint    unsigned int
sbit SDA=P1^1;     //??I2C?????SDA       
sbit SCL=P1^0;     //??I2C?????SCL
bit  ack;          //?????
#define DS3231_WriteAddress 0xD0    //?????
#define DS3231_ReadAddress  0xD1    //?????

#define DS3231_SECOND       0x00    //?
#define DS3231_MINUTE       0x01    //?
#define DS3231_HOUR         0x02    //?
#define DS3231_WEEK         0x03    //??
#define DS3231_DAY          0x04    //?
#define DS3231_MONTH        0x05    //?
#define DS3231_YEAR         0x06    //?
//??1           
#define DS3231_SALARM1ECOND 0x07    //?
#define DS3231_ALARM1MINUTE 0x08    //?
#define DS3231_ALARM1HOUR   0x09    //?
#define DS3231_ALARM1WEEK   0x0A    //??/?
//??2
#define DS3231_ALARM2MINUTE 0x0b    //?
#define DS3231_ALARM2HOUR   0x0c    //?
#define DS3231_ALARM2WEEK   0x0d    //??/?
#define DS3231_CONTROL      0x0e    //?????
#define DS3231_STATUS       0x0f    //?????
#define BSY                 2       //?
#define OSF                 7       //???????
#define DS3231_XTAL         0x10    //???????
#define DS3231_TEMPERATUREH 0x11    //????????(8?)
#define DS3231_TEMPERATUREL 0x12    //????????(?2?) 



uchar data dis_buf[9]={0};
uchar data dis_index;
uchar data dis_digit;

uchar BCD2HEX(uchar val)    //BCD???Byte
{
    uchar temp;
    temp=val&0x0f;
    val>>=4;
    val&=0x0f;
    val*=10;
    temp+=val;
  
    return temp;
}

uchar HEX2BCD(uchar val)    //B????BCD?
{
    uchar i,j,k;
    i=val/10;
    j=val;
    k=j+(i<<4);
    return k;
}

void Start_I2C()
{
    SDA=1;                  //???????????
    delayus(1);
    SCL=1;
    delayus(5);             //??????????4.7us,??
  
    SDA=0;                  //??????
    delayus(5);             // ??????????4탎
      
    SCL=0;                  //??I2C??,?????????
    delayus(2);
}

void Stop_I2C()
{
    SDA=0;                  //???????????
    delayus(1);             //???????????
    SCL=1;                  //??????????4us
    delayus(5);
  
    SDA=1;                  //??I2C??????
    delayus(4);
}

void SendByte(uchar c)
{
    uchar BitCnt;
  
    for(BitCnt=0;BitCnt<8;BitCnt++)         //?????????8?
    {
        if((c<<BitCnt)&0x80)
            SDA=1;                          //?????
        else
            SDA=0;              
          delayus(1);
          SCL=1;                            //??????,????????????
          delayus(5);                       //???????????4탎  
          SCL=0;
    }
  
    delayus(2);
    SDA=1;                                  //8??????????,???????
    delayus(2); 
    SCL=1;
    delayus(3);
    if(SDA==1)
        ack=0;   
    else
        ack=1;                              //???????????
    SCL=0;
    delayus(2);
}

uchar RcvByte()
{
   uchar retc;
   uchar BitCnt;
 
   retc=0;
   SDA=1;                           //?????????
   for(BitCnt=0;BitCnt<8;BitCnt++)
   {
        delayus(1); 
        SCL=0;                      //??????,???????
      
        delayus(5);                 //?????????4.7탎
     
        SCL=1;                      //???????????????
        delayus(3);
        retc=retc<<1;
        if(SDA==1)
            retc=retc+1;            //????,????????retc?
        delayus(2);
   }
   SCL=0;
   delayus(2);
   return(retc);
}

void Ack_I2C(bit a)
{
 
    if(a==0)
        SDA=0;              //????????????
    else
        SDA=1;
    delayus(3);    
    SCL=1;
  
    delayus(5);             //?????????4탎
  
    SCL=0;                  //????,??I2C????????
    delayus(2);  
}

uchar write_byte(uchar addr, uchar write_data)
{
    Start_I2C();
    SendByte(DS3231_WriteAddress);
    if (ack == 0)
        return 0;
  
    SendByte(addr);  
    if (ack == 0)
        return 0;
  
    SendByte(write_data);
    if (ack == 0)
        return 0;
  
    Stop_I2C();
    delayus(10);     
    return 1;
}

uchar read_current()
{
    uchar read_data;
    Start_I2C();
    SendByte(DS3231_ReadAddress);
    if(ack==0)
        return(0);
  
    read_data = RcvByte();
    Ack_I2C(1);
    Stop_I2C();
    return read_data;
}

uchar read_random(uchar random_addr)
{
    Start_I2C();
    SendByte(DS3231_WriteAddress);
    if(ack==0)
        return(0);
  
    SendByte(random_addr);
    if(ack==0)
        return(0);
  
    return(read_current());
}

void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec)
{
    uchar temp=0;
  
    temp=HEX2BCD(yea);
    write_byte(DS3231_YEAR,temp);   //???
  
    temp=HEX2BCD(mon);
    write_byte(DS3231_MONTH,temp);  //???
  
    temp=HEX2BCD(da);
    write_byte(DS3231_DAY,temp);    //???
  
    temp=HEX2BCD(hou);
    write_byte(DS3231_HOUR,temp);   //???
  
    temp=HEX2BCD(min);
    write_byte(DS3231_MINUTE,temp); //???
  
    temp=HEX2BCD(sec);
    write_byte(DS3231_SECOND,temp); //???
}

void TimeDisplay(uchar Dhour,uchar Dmin,uchar Dsec)
{
    dis_buf[0]=Dhour / 10+'0';        // ???
    dis_buf[1]=Dhour % 10+'0';        // ???
    dis_buf[3]= Dmin / 10+'0';         // ???
    dis_buf[4]= Dmin % 10+'0';         // ???
    dis_buf[6]= Dsec / 10+'0';         // ???
    dis_buf[7]= Dsec % 10+'0';         // ???
    dis_buf[2]='-';                        // ??"-"
    dis_buf[5]='-';		dis_buf[8]=0;
}

void DateDisplay(uchar Dyear,uchar Dmonth,uchar Dday)
{
    dis_buf[0]= Dyear / 10+'0';        // ???
    dis_buf[1]= Dyear % 10+'0';        // ???
    dis_buf[3]= Dmonth / 10+'0';       // ???
    dis_buf[4]= Dmonth % 10+'0';       // ???
    dis_buf[6]= Dday / 10+'0';         // ???
    dis_buf[7]= Dday % 10+'0';         // ???
    dis_buf[2]='-';                        // ??"-"
    dis_buf[5]='-';		dis_buf[8]=0;
}
void TempDisplay(uchar Temph,uchar Templ){
		dis_buf[0]= Temph / 10+'0';        // ???
    dis_buf[1]= Temph % 10+'0';        // ???
    dis_buf[3]= Templ / 10+'0';       // ???
    dis_buf[4]= Templ % 10+'0';       // ???
		dis_buf[2]='.';
		dis_buf[5]='`';
		dis_buf[6]='C';
		dis_buf[7]=0;
}
void get_show_time(void)
{
    uchar Htemp1,Htemp2,Mtemp1,Mtemp2,Stemp1,Stemp2;
 
    Htemp1=read_random(DS3231_HOUR);    //? 24???
    Htemp1&=0x3f;                  
    Htemp2=BCD2HEX(Htemp1);
  
    Mtemp1=read_random(DS3231_MINUTE);  //?
    Mtemp2=BCD2HEX(Mtemp1);
  
    Stemp1=read_random(DS3231_SECOND);  //?
    Stemp2=BCD2HEX(Stemp1);
  
    TimeDisplay(Htemp2,Mtemp2,Stemp2);
}
void get_show_date(void)
{
    uchar Ytemp1,Ytemp2,Mtemp1,Mtemp2,Dtemp1,Dtemp2;
  
    Ytemp1=read_random(DS3231_YEAR);        //?
    Ytemp2=BCD2HEX(Ytemp1);
  
    Mtemp1=read_random(DS3231_MONTH);       //?
    Mtemp2=BCD2HEX(Mtemp1);
  
    Dtemp1=read_random(DS3231_DAY);         //?
    Dtemp2=BCD2HEX(Dtemp1);
  
    DateDisplay(Ytemp2,Mtemp2,Dtemp2);
}
void get_show_Temperature(void)
{
    uchar Ttemp1,Ttemp2,Ttemp3,Ttemp4;
  
    Ttemp1=read_random(DS3231_TEMPERATUREH);    //?? ???
    Ttemp2=BCD2HEX(Ttemp1);
  
    Ttemp3=read_random(DS3231_TEMPERATUREL);    //?????
    Ttemp4=BCD2HEX(Ttemp3);
    
    TempDisplay(Ttemp2,Ttemp4);
}
