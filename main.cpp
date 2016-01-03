#include <iostream>
#include "bmp32.h"
#include "color.h"
#include "bmp.h"
#include "paint.h"
#include "colorarray565.h"

using namespace std;

int main(int argc, char** argv) {
	
	paint pt1(1001*4,1001);
	pt1.setBcolor(COLOR_WHITE);
	pt1.setFcolor(COLOR_BLACK);
	pt1.clear();
	pt1.write2file("d:\\pt0.bmp");
	const char *teststr = "¸£ÊÙÂ»!@";
	pt1.addQRcode(50,50,10,0,1,1,-1,teststr,0);
	pt1.addQRcode(1050,50,10,1,1,1,-1,teststr,0);
	pt1.addQRcode(2050,50,10,2,1,1,-1,teststr,0);
	pt1.addQRcode(3050,50,10,3,1,1,-1,teststr,0);
	pt1.write2file("d:\\pt1.bmp");
	
//	bmp24 b24;
//	b24.readfromfile("d:\\b24.bmp");
//	bmp32 b32;
//	b32 = b24;
//	b32.write2file("d:\\b32.bmp");
//	bmp16_565 b565in;
//	b565in = b32;
//	b565in.write2file("d:\\b565in.bmp");
//	colorarray565 c1;
//	c1 = b565in;
//	c1.write2file("d:\\pb3.c");
//	bmp16_565 b565out;
//	b565out = c1;
//	b565out.write2file("d:\\b565out.bmp");
	
//	 bmp24 b24;
//	 b24.readfromfile("d:\\in.bmp");
//	 bmp32 b32;
//	 b32 = b24;
//	 b32.write2file("d:\\b32.bmp");
//	 bmp8G b8G(10,10);
//	 b8G.printinfo();
//	 b8G = b32;
//	 b8G.printinfo();
//	 b8G.write2file("d:\\b8G.bmp");
//	 bmp8G b8_2G;
//	 b8_2G.readfromfile("d:\\b8G.bmp");
//	 b8_2G.write2file("d:\\b8_2G.bmp");
//	 bmp32 b32_2;
//	 b32_2 = b8_2G;
////	 b32_2.write2file("d:\\b32_2.bmp");
	
//	paint pt1(2001,2001);
//	pt1.setBcolor(COLOR_WHITE);
//	pt1.setFcolor(COLOR_BLACK);
//	pt1.setBrush(2);
//	pt1.setErase(1);
//	pt1.clear();
//	pt1.addpoint(2000,2000);
//	pt1.erasepoint(5,5);
//	pt1.addcircle(251,251,25);
//	pt1.addcircle(251,251,30);
//	pt1.addcircle(251,251,35);
//	pt1.addcircle(251,251,40);
///	pt1.addcircle(251,251,45);
//	pt1.addcircle(251,251,50);
///	pt1.addcircle(251,251,55);
//	pt1.addcircle(251,251,60);
//	pt1.setBrush(4);
//	pt1.addpoint(251,251);
//	pt1.addcircle(251,251,200);

//	pt1.addline(5,5,2000,5);
//	pt1.addline(5,5,2000,10);
//	pt1.addline(5,5,2000,15);
//	pt1.addline(5,5,2000,20);
//	pt1.addline(5,5,2000,100);
//	pt1.addline(5,5,2000,500);
//	pt1.addline(5,5,2000,1000);
//	pt1.addline(0,0,1998,1998);
//	pt1.addCardioid(1000,1000,300);
//	pt1.addCardioid(1000,1000,20);

//	pt1.write2file("d:\\pt1.bmp");
//	bmp1 b1(99,99);
//	bmp4 b4(88,88);
//	bmp8 b8(77,77);
//	bmp16 b16(66,66);
//	bmp24 b24(55,55);
//	bmp32 b32(44,44);
//	paint pt1(33,33);
//	cout << BmpType(b1) << endl;
//	cout << BmpType(b4) << endl;
//	cout << BmpType(b8) << endl;
//	cout << BmpType(b16) << endl;
//	cout << BmpType(b24) << endl;
//	cout << BmpType(b32) << endl;
//	cout << BmpType(pt1) << endl;
//	cout << "===========" << endl;
//	cout << CompareBmpSize(b1,b4) << endl;
//	cout << CompareBmpSize(b4,b8) << endl;
//	cout << CompareBmpSize(b8,b16) << endl;
//	cout << CompareBmpSize(b16,b24) << endl;
//	cout << CompareBmpSize(b24,b32) << endl;
//	cout << CompareBmpSize(b32,pt1) << endl;
//	cout << "===========" << endl;

//	paint pt1(2001,2001);
//	pt1.setBcolor(COLOR_WHITE);
//	pt1.setFcolor(COLOR_BLACK);
//	pt1.setBrush(2);
//	pt1.setErase(1);
//	pt1.clear();
//	for(size_t i=0;i<10;i++)
//	{
//		pt1.addpoint(5,5);
//	}
//	pt1.write2file("d:\\pt1.bmp");
	return 0;
}
