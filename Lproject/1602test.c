#include<ioCC2530.h>
typedef unsigned char uchar;
typedef unsigned int  uint;
#define RS P0_0
#define RW P0_1
#define EN P0_2
uchar table[]={
  0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
  0x00,0x00,0x00,0x0e,0x00,0xff,0x00,0x00,
  0x00,0x00,0xff,0x00,0x0e,0x00,0xff,0x00,
  0x00,0x00,0xff,0xf5,0xfb,0xf1,0xff,0x00,
  0x00,0xfe,0x08,0xfe,0x0a,0x0a,0xff,0x00,
  0x00,0x04,0x00,0xff,0x00,0x0a,0x11,0x00,
  0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00,
  0x00,0x04,0x0e,0x0e,0x0e,0x1f,0x04,0x00,
};
uchar table1[]="This is";
uchar table2[]="CGRAM";

void delay(uint n)
{
    uint x,y;
    for(x=n;x>0;x--)
        for(y=110;y>0;y--);
}
void initIO1()
{
  P0SEL &= 0xf0; 
  P0DIR |= 0xff; 
  P1SEL &= 0x00; 
  P1DIR |= 0xff; 
}
void lcd_wcom(uchar com)
{
    RS=0;
    RW=0;
    P1=com;
    delay(500);
    EN=1;
    EN=0;
}
void lcd_wdat(uchar dat)
{
    RS=1;
    RW=0;
    P1=dat;
    delay(500);
    EN=1;
    EN=0;
}
void lcd_init() 
{
  lcd_wcom(0x01);
  lcd_wcom(0x38); 
  lcd_wcom(0x0c); 
  lcd_wcom(0x06); 
  // lcd_wcom(0x01); 
}
void main()
{
  char m=0;
  initIO1();
  lcd_init();
  lcd_wcom(0x40);
  lcd_wcom(0x80);
  for(m=0;m<7;m++)
  {
    lcd_wdat(table1[m]);
    delay(500);
  }
  lcd_wcom(0xc0);
  for(m=0;m<5;m++)
  {
    lcd_wdat(table2[m]);
    delay(500);
  }
  lcd_wcom(0x40);
  for(m=0;m<64;m++)
  {
    lcd_wdat(table[m]);
    //delay(5);
  }
  lcd_wcom(0x80+12);
  for(m=0;m<4;m++)
  {
    lcd_wdat(m);
    delay(500);
  }
  lcd_wcom(0xc0+12);
  for(m=4;m<8;m++)
  {
    lcd_wdat(m);
    delay(500);
  }
  while(1);
}
