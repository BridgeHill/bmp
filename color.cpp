#include <iostream>
#include "color.h"

//////////////////////////////////////////////////////////////////////////////
colorpad_1::colorpad_1()
{
	ColorList[0].ulg = COLOR_BLACK;	
	ColorList[1].ulg = COLOR_WHITE;
}

colorpad_1::~colorpad_1()
{

}

union color_u colorpad_1::getcolor(unsigned char num)
{
	return ColorList[num % 2];
}

union color_u colorpad_1::filter(unsigned char b1,unsigned char g1,unsigned char r1)
{
	unsigned long temp = 0.3*r1 + 0.59*g1 + 0.11*b1;
	if(temp < 0x80)
		return ColorList[0];
	return ColorList[1];
}

union color_u colorpad_1::filter(union color_u u1)
{
	unsigned long temp = 0.3*u1.uc[Ri] + 0.59*u1.uc[Gi] + 0.11*u1.uc[Bi];
	if(temp < 0x80)
		return ColorList[0];
	return ColorList[1];
}

int colorpad_1::getnum(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2= filter(b1,g1,r1);
	if(u2.ulg == ColorList[0].ulg)
		return 0;
	else if(u2.ulg == ColorList[1].ulg)
		return 1;
	return -1;
}

int colorpad_1::getnum(union color_u u1)
{
	union color_u u2 = filter(u1);
	if(u2.ulg == ColorList[0].ulg)
		return 0;
	else if(u2.ulg == ColorList[1].ulg)
		return 1;
	return -1;
}

int colorpad_1::printlist()
{
	cout << ColorList[0].ulg << " " << ColorList[1].ulg << endl;	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
colorpad_4::colorpad_4()
{
	ColorList[0].ulg = COLOR_BLACK;
	ColorList[1].ulg = COLOR_HALF_RED;
	ColorList[2].ulg = COLOR_HALF_GREEN;
	ColorList[3].ulg = COLOR_HALF_YELLOW;
	ColorList[4].ulg = COLOR_HALF_BLUE;
	ColorList[5].ulg = COLOR_HALF_VIOLET;
	ColorList[6].ulg = COLOR_HALF_CYAN;
	ColorList[7].ulg = COLOR_DARK_GREY;
	ColorList[8].ulg = COLOR_LIGHT_GREY;
	ColorList[9].ulg = COLOR_RED;
	ColorList[10].ulg = COLOR_GREEN;
	ColorList[11].ulg = COLOR_YELLOW;
	ColorList[12].ulg = COLOR_BLUE;
	ColorList[13].ulg = COLOR_VIOLET;
	ColorList[14].ulg = COLOR_CYAN;
	ColorList[15].ulg = COLOR_WHITE;
}
colorpad_4::~colorpad_4()
{

}
union color_u colorpad_4::getcolor(unsigned char num)
{
	return ColorList[num % 16];
}

union color_u colorpad_4::filter(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2;
//	cout << b1+0 << " " << g1+0 << " " << r1+0 <<endl;
	u2.uc[Bi] = ((b1 < 0x80)?((b1<0x55)?(0x00):(0x80)):((b1<0xaa)?(0x80):(0xff)));
	u2.uc[Gi] = ((g1 < 0x80)?((g1<0x55)?(0x00):(0x80)):((g1<0xaa)?(0x80):(0xff)));
	u2.uc[Ri] = ((r1 < 0x80)?((r1<0x55)?(0x00):(0x80)):((r1<0xaa)?(0x80):(0xff)));
	u2.uc[Ai] = 0;
//	cout << u2.uc[Bi]+0 <<" " << u2.uc[Gi]+0 <<" "<< u2.uc[Ri]+0 << endl;
	unsigned long temp = u2.uc[Bi] + u2.uc[Gi] + u2.uc[Ri];
	if(temp == 0x80+0x80+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi]==0xff)?(0xff):(0);
		u2.uc[Gi] = (u2.uc[Gi]==0xff)?(0xff):(0);
		u2.uc[Ri] = (u2.uc[Ri]==0xff)?(0xff):(0);	
	}
	if(temp == 0x80+0xff+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi]==0x80)?(0):(u2.uc[Bi]);
		u2.uc[Gi] = (u2.uc[Gi]==0x80)?(0):(u2.uc[Gi]);
		u2.uc[Ri] = (u2.uc[Ri]==0x80)?(0):(u2.uc[Ri]);	
	}
	if(temp == 0x80+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi])?((u2.uc[Bi]==0x80)?(0):(0xff)):(0);
		u2.uc[Gi] = (u2.uc[Gi])?((u2.uc[Bi]==0x80)?(0):(0xff)):(0);
		u2.uc[Ri] = (u2.uc[Ri])?((u2.uc[Ri]==0x80)?(0):(0xff)):(0);	
	}
	return u2;
}

union color_u colorpad_4::filter(union color_u u1)
{
	union color_u u2;
	u2.uc[Bi] = ((u1.uc[Bi] < 0x80)?((u1.uc[Bi]<0x55)?(0x00):(0x80)):((u1.uc[Bi]<0xaa)?(0x80):(0xff)));
	u2.uc[Gi] = ((u1.uc[Gi] < 0x80)?((u1.uc[Gi]<0x55)?(0x00):(0x80)):((u1.uc[Gi]<0xaa)?(0x80):(0xff)));
	u2.uc[Ri] = ((u1.uc[Ri] < 0x80)?((u1.uc[Ri]<0x55)?(0x00):(0x80)):((u1.uc[Ri]<0xaa)?(0x80):(0xff)));
	u2.uc[Ai] = 0;
	unsigned long temp = u2.uc[Bi] + u2.uc[Gi] + u2.uc[Ri];
	if(temp == 0x80+0x80+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi]==0xff)?(0xff):(0);
		u2.uc[Gi] = (u2.uc[Gi]==0xff)?(0xff):(0);
		u2.uc[Ri] = (u2.uc[Ri]==0xff)?(0xff):(0);	
	}
	if(temp == 0x80+0xff+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi]==0x80)?(0):(u2.uc[Bi]);
		u2.uc[Gi] = (u2.uc[Gi]==0x80)?(0):(u2.uc[Gi]);
		u2.uc[Ri] = (u2.uc[Ri]==0x80)?(0):(u2.uc[Ri]);	
	}
	if(temp == 0x80+0xff)
	{
		u2.uc[Bi] = (u2.uc[Bi])?((u2.uc[Bi]==0x80)?(0):(0xff)):(0);
		u2.uc[Gi] = (u2.uc[Gi])?((u2.uc[Bi]==0x80)?(0):(0xff)):(0);
		u2.uc[Ri] = (u2.uc[Ri])?((u2.uc[Ri]==0x80)?(0):(0xff)):(0);	
	}
	return u2;
}

int colorpad_4::getnum(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2 = filter(b1,g1,r1);
	for(unsigned char tempi=0;tempi<16;tempi++)
	{
		if(u2.ulg == ColorList[tempi].ulg)
			return tempi;
	}
	return 0;
//	return -1;
}

int colorpad_4::getnum(union color_u u1)
{
	union color_u u2 = filter(u1);
	for(unsigned char tempi=0;tempi<16;tempi++)
	{
		if(u2.ulg == ColorList[tempi].ulg)
			return tempi;
	}
	return -1;
}
int colorpad_4::printlist()
{
	for(unsigned char tempi=0;tempi<16;tempi++)
	    cout << ColorList[tempi].ulg <<endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////
colorpad_8::colorpad_8()
{
	unsigned char tempi = 0;
	for(unsigned long b1=0;b1<256;b1+=51)
	{
		for(unsigned long g1=0;g1<253;g1+=42)
		{
			for(unsigned long r1=0;r1<256;r1+=51)
			{
				ColorList[tempi].ulg = (b1 << 24)|(g1 << 16)|(r1 << 8);
				tempi++;
			}
		}
	}
	ColorList[252].ulg = COLOR_WHITE;
	ColorList[253].ulg = COLOR_WHITE;
	ColorList[254].ulg = COLOR_WHITE;
	ColorList[255].ulg = COLOR_WHITE;
}
colorpad_8::~colorpad_8()
{
	
}

union color_u colorpad_8::getcolor(unsigned char num)
{
	return ColorList[num];
}

union color_u colorpad_8::filter(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2;
	u2.uc[Bi] = (b1 / 51) * 51 + (((b1%51)<26)?(0):(51));
	u2.uc[Gi] = (g1 / 42) * 42 + (((g1%42)<21)?(0):(42));
	u2.uc[Ri] = (r1 / 51) * 51 + (((r1%51)<26)?(0):(51));
	u2.uc[Ai] = 0;
	return u2;	
}

union color_u colorpad_8::filter(union color_u u1)
{
	union color_u u2;
	u2.uc[Bi] = (u1.uc[Bi] / 51) * 51 + (((u1.uc[Bi]%51)<26)?(0):(51));
	u2.uc[Gi] = (u1.uc[Gi] / 42) * 42 + (((u1.uc[Gi]%42)<21)?(0):(42));
	u2.uc[Ri] = (u1.uc[Ri] / 51) * 51 + (((u1.uc[Ri]%51)<26)?(0):(51));
	u2.uc[Ai] = 0;
	return u2;	
}

int colorpad_8::getnum(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2 = filter(b1,g1,r1);
//	cout << u2.ulg << "|" << b1 << g1 <<r1 << endl;
	for(int tempi=0;tempi<256;tempi++)
	{
		if(u2.ulg == ColorList[tempi].ulg)
		{
//			cout << " tempi = " << tempi <<endl;
			return tempi;			
		}
	}
	return -1;
}

int colorpad_8::getnum(union color_u u1)
{
	union color_u u2 = filter(u1);
	for(unsigned char tempi=0;tempi<16;tempi++)
	{
		if(u2.ulg == ColorList[tempi].ulg)
			return tempi;
	}
	return -1;
}

int colorpad_8::printlist()
{
	for(unsigned short tempi=0;tempi<256;tempi++)
	    cout << tempi <<" = " << ColorList[tempi].ulg << endl;
	return 0;
}

bool colorpad_8::testBLend()
{
	union color_u t1;
	t1.ulg = 0x68697000;
//	cout << t1.uc[0] <<"|"<<t1.uc[1] <<"|"<<t1.uc[2] <<"|"<<t1.uc[3] <<"|"<<endl;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
colorpad_8G::colorpad_8G()
{
	for(unsigned short temp=0;temp<256;temp++)
	{
		ColorList[temp].ulg = (temp<< 24)|(temp << 16)|(temp << 8);
	}
}
colorpad_8G::~colorpad_8G()
{

}
union color_u colorpad_8G::filter(unsigned char b1,unsigned char g1,unsigned char r1)
{
	union color_u u2;
	unsigned char tempc = (r1*30+g1*59+b1*11)/100;
	u2.uc[Bi] = tempc;
	u2.uc[Gi] = tempc;
	u2.uc[Ri] = tempc;
	u2.uc[Ai] = 0;
	return u2;	
}

union color_u colorpad_8G::filter(union color_u u1)
{
	union color_u u2;
	unsigned char tempc = (u1.uc[Ri]*30+u1.uc[Gi]*59+u1.uc[Bi]*11)/100;
	u2.uc[Bi] = tempc;
	u2.uc[Gi] = tempc;
	u2.uc[Ri] = tempc;
	u2.uc[Ai] = 0;
	return u2;	
}

//////////////////////////////////////////////////////////////////////////////
