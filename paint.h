#ifndef PAINT_H
#define PAINT_H
#include "color.h"
#include "bmp32.h"
#include "QR_Encode.h"

class paint:public bmp32
{
public:
	int setBcolor(union color_u Bcolor1);
	int setBcolor(unsigned long ulg);
	int setFcolor(union color_u Fcolor1);
	int setFcolor(unsigned long ulg);
	void setBrush(short r1);
	void setErase(short r1);
	paint(unsigned long w,unsigned long h);
	paint(const paint& tniap);
	paint& operator=(const paint& tniap);
	~paint();	
	int clear();
	bool isin(short x1,short y1);
	int addpoint(short x0,short y0);
	int drawpoint(short x0,short y0,short r0,bool PointShapeModeIsSquare);
	int erasepoint(short x0,short y0);
	int clearpoint(short x0,short y0,short r0,bool PointShapeModeIsSquare);
	int addcircle(short x0,short y0,short r0);
	int addline(short x1,short y1,short x2,short y2);
	int addCardioid(short x1,short y1,short a);
	int addQRcode(	
					short x0,
					short y0,
					short r0,
					int nLevel, 
					int nVersion, 
					BOOL bAutoExtent, 
					int nMaskingNo, 
					LPCSTR lpsSource, 
					int ncSource = 0
				);

private:
	union color_u Fcolor;
	union color_u Bcolor;
	short Brush;
	short Erase;
};

#endif
