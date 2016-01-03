#include "paint.h"
#include <iostream>
#include <assert.h>
#include <math.h>
int paint::setBcolor(union color_u Bcolor1)
{
	Bcolor.ulg = Bcolor1.ulg;
	return 0;
}
int paint::setBcolor(unsigned long ulg)
{
	Bcolor.ulg = ulg;
	return 0;
}
int paint::setFcolor(union color_u Fcolor1)
{
	Fcolor.ulg = Fcolor1.ulg;
	return 0;
}
int paint::setFcolor(unsigned long ulg)
{
	Fcolor.ulg = ulg;
	return 0;
}
void paint::setBrush(short r1)
{
	if(r1 < 0)
		Brush = -r1;
	else
		Brush = r1;
//	return 0;
}
void paint::setErase(short r1)
{
	if(r1 < 0)
		Erase = -r1;
	else
		Erase = r1;
//	return 0;
}

paint::paint(unsigned long w,unsigned long h):bmp32(w,h)
{
	Bcolor.ulg = COLOR_WHITE;
	Fcolor.ulg = COLOR_BLACK;
	Brush = 1;
	Erase = 1;
}

paint::paint(const paint& tniap):bmp32(tniap)
{
	Bcolor.ulg = tniap.Bcolor.ulg;
	Fcolor.ulg = tniap.Fcolor.ulg;
	Brush = tniap.Brush;
	Erase = tniap.Erase;
}

paint& paint::operator=(const paint& tniap)
{
    if(this != &tniap)
    {
        type = tniap.type;
        file_size = tniap.file_size;
        reserved = tniap.reserved;
        offset = tniap.offset;
        header_info_size = tniap.header_info_size;
        width = tniap.width;
        height = tniap.height;
        planes = tniap.planes;
        bit_count = tniap.bit_count;
        compression = tniap.compression;
        image_size = tniap.image_size;
        xpels_per_meter = tniap.xpels_per_meter;
        ypels_per_meter = tniap.ypels_per_meter;
        color_used = tniap.color_used;
        color_important = tniap.color_important;

        if(NULL != dataptr)
        {
            delete [] dataptr;
			dataptr = NULL;
        }
		try
		{
			dataptr = new unsigned char[tniap.image_size];
		}catch(bad_alloc &memExp)
		{
			//失败以后，要么abort要么重分配
			cerr<<memExp.what()<<endl; 
			cerr << "unable to satisfy request for memory\n" << endl;
			assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
		}		

        for(unsigned long i=0;i < (tniap.image_size);i++)
        {
            dataptr[i] = tniap.dataptr[i];
        }
		Bcolor.ulg = tniap.Bcolor.ulg;
		Fcolor.ulg = tniap.Fcolor.ulg;
		Brush = tniap.Brush;
		Erase = tniap.Erase;
    }
    return *this;
}

paint::~paint()
{
	
}

int paint::clear()
{
	for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
		dataptr[h*width*4 + w*4 + 0] = Bcolor.uc[Bi];
		dataptr[h*width*4 + w*4 + 1] = Bcolor.uc[Gi];
		dataptr[h*width*4 + w*4 + 2] = Bcolor.uc[Ri];
		dataptr[h*width*4 + w*4 + 3] = Bcolor.uc[Ai];
        }
    }
    return 0;
}

bool paint::isin(short x1,short y1)
{
	if((x1>=0)&&(y1>=0)&&(x1<width)&&(y1<height))
		return true;
	return false;
}

int paint::addpoint(short x0,short y0)
{
	if(!isin(x0,y0))
		return -1;
	for(short y=(y0-Brush);y<=(y0+Brush);y++)
	{
	for(short x=(x0-Brush);x<=(x0+Brush);x++)
	{
		if(isin(x,y)&&(((x-x0)*(x-x0)+(y-y0)*(y-y0))<(Brush*Brush)))
		{
//			cout << "x = " << x << " y = " << y << endl;
			dataptr[y*width*4 + x*4 + 0] = Fcolor.uc[Bi];
			dataptr[y*width*4 + x*4 + 1] = Fcolor.uc[Gi];
			dataptr[y*width*4 + x*4 + 2] = Fcolor.uc[Ri];
			dataptr[y*width*4 + x*4 + 3] = Fcolor.uc[Ai];
		}
	}
	}
	return 0;
}

int paint::drawpoint(short x0,short y0,short r0,bool PointShapeModeIsSquare)
{
	if(!isin(x0,y0))
		return -1;
	if(!isin(x0-r0,y0-r0))
		return -2;
	if(!isin(x0+r0,y0+r0))
		return -3;
	for(short y=(y0-r0);y<=(y0+r0);y++)
	{
		for(short x=(x0-r0);x<=(x0+r0);x++)
		{
			if(isin(x,y)&&( (((x-x0)*(x-x0)+(y-y0)*(y-y0))<(r0*r0)) || PointShapeModeIsSquare ))
			{
				dataptr[y*width*4 + x*4 + 0] = Fcolor.uc[Bi];
				dataptr[y*width*4 + x*4 + 1] = Fcolor.uc[Gi];
				dataptr[y*width*4 + x*4 + 2] = Fcolor.uc[Ri];
				dataptr[y*width*4 + x*4 + 3] = Fcolor.uc[Ai];
			}
		}
	}
	return 0;
}

int paint::erasepoint(short x0,short y0)
{
	if(!isin(x0,y0))
		return -1;
	for(short y=(y0-Erase);y<=(y0+Erase);y++)
    {
        for(short x=(x0-Erase);x<=(x0+Erase);x++)
        {
		if(isin(x,y)&&((x-x0)*(x-x0)+(y-y0)*(y-y0)<(Erase*Erase)))
		{
			dataptr[y*width*4 + x*4 + 0] = Bcolor.uc[Bi];
			dataptr[y*width*4 + x*4 + 1] = Bcolor.uc[Gi];
			dataptr[y*width*4 + x*4 + 2] = Bcolor.uc[Ri];
			dataptr[y*width*4 + x*4 + 3] = Bcolor.uc[Ai];
		}
        }
    }
	return 0;
}

int paint::clearpoint(short x0,short y0,short r0,bool PointShapeModeIsSquare)
{
	if(!isin(x0,y0))
		return -1;
	if(!isin(x0-r0,y0-r0))
		return -2;
	if(!isin(x0+r0,y0+r0))
		return -3;
	for(short y=(y0-r0);y<=(y0+r0);y++)
	{
		for(short x=(x0-r0);x<=(x0+r0);x++)
		{
			if(isin(x,y)&&( (((x-x0)*(x-x0)+(y-y0)*(y-y0))<(r0*r0)) || PointShapeModeIsSquare ))
			{
				dataptr[y*width*4 + x*4 + 0] = Bcolor.uc[Bi];
				dataptr[y*width*4 + x*4 + 1] = Bcolor.uc[Gi];
				dataptr[y*width*4 + x*4 + 2] = Bcolor.uc[Ri];
				dataptr[y*width*4 + x*4 + 3] = Bcolor.uc[Ai];
			}
		}
	}
	return 0;
}

int paint::addcircle(short x0,short y0,short r0)
{
	if(!isin(x0,y0)||(r0 < 0))
		return -1;
	for(short y=(y0-r0);y<=(y0+r0);y++)
    {
        for(short x=(x0-r0);x<=(x0+r0);x++)
        {
		if(isin(x,y)&&((x-x0)*(x-x0)+(y-y0)*(y-y0)<(r0*r0))&&((x-x0)*(x-x0)+(y-y0)*(y-y0)>=((r0-1)*(r0-1))))
		{
			addpoint(x,y);
		}
        }
    }
	return 0;
}
//short min(short x1,short x2)
//{
//	return (x1>x2)?(x2):(x1);
//}

int paint::addline(short x1,short y1,short x2,short y2)
{
	if(x1==x2&&y1==y2)
	{
		addpoint(x1,y1);	
		return -2;
	}
	if((x2-x1)*(x2-x1)>=(y2-y1)*(y2-y1))
	{
		for(short x=((x1>x2)?(x2):(x1));x<=((x1>x2)?(x1):(x2));x++)
	    {
		double k = (double)(y2-y1)/(double)(x2-x1);
		short y = k*(x-x1)+y1;
		if(isin(x,y))
		{
			addpoint(x,y);
		}
	    }		
	}
	else
	{
		for(short y=((y1>y2)?(y2):(y1));y<=((y1>y2)?(y1):(y2));y++)
	    {
    		double k = (double)(x2-x1)/(double)(y2-y1);
		short x = k*(y-y1)+x1;
		if(isin(x,y))
		{
			addpoint(x,y);
		}
	    }		
	}
	return 0;
}
//x=a*(2*cos(t)-cos(2*t))
//y=a*(2*sin(t)-sin(2*t))
int paint::addCardioid(short x1,short y1,short a)
{
	if((x1<0)||(y1<0)||(a<0))
		return -1;
	for(double t=0;t<6.28+0.01;t+=0.001)
	{
//		short x = a*(2*cos(t)-cos(2*t))+x1;
//		short y = a*(2*sin(t)-sin(2*t))+y1;
//		addpoint(y,x);
		short x = a*16*sin(t)*sin(t)*sin(t)+x1;
		short y = a*(13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t))+y1;
		addpoint(x,y);
	}
	return 0;
}


int paint::addQRcode(	
				short x0,
				short y0,
				short r0,
				int nLevel, 
				int nVersion, 
				BOOL bAutoExtent, 
				int nMaskingNo, 
				LPCSTR lpsSource, 
				int ncSource)
{

	CQR_Encode QR1;
	QR1.EncodeData(nLevel,nVersion,bAutoExtent,nMaskingNo,lpsSource,ncSource);
	if(!isin(x0,y0))
		return -1;
	if(!isin(x0-r0,y0-r0))
		return -2;
	if(!isin(x0+QR1.m_nSymbleSize*(2*r0+1),y0+QR1.m_nSymbleSize*(2*r0+1)))
		return -3;
	for(int i=0;i < QR1.m_nSymbleSize;i++)
		for(int j=0;j< QR1.m_nSymbleSize;j++)
		{
			if(QR1.m_byModuleData[i][j] & 0x20)
			{
				if(QR1.m_byModuleData[i][j] & 0x30)
					drawpoint(x0+i*(2*r0+1),y0+(QR1.m_nSymbleSize-j)*(2*r0+1),r0,true);
				else
					clearpoint(x0+i*(2*r0+1),y0+(QR1.m_nSymbleSize-j)*(2*r0+1),r0,true);
			}		
			else if(QR1.m_byModuleData[i][j] & 0x01)
			{
					drawpoint(x0+i*(2*r0+1),y0+(QR1.m_nSymbleSize-j)*(2*r0+1),r0,true);		
			}
			else
			{
					clearpoint(x0+i*(2*r0+1),y0+(QR1.m_nSymbleSize-j)*(2*r0+1),r0,true);
			}
		}	
}
