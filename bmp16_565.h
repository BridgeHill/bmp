#ifndef BMP16_565_H
#define BMP16_565_H

#include "bmpinfo.h"
#include "bmp32.h"
#include "colorarray565.h"

class bmp16_565 : public bmpinfo
{
public:
    bmp16_565();
    bmp16_565(unsigned int w,unsigned int h);
    bmp16_565(const bmp16_565& pmb);
    bmp16_565& operator=(const bmp16_565& pmb);
    bmp16_565& operator=(const class bmp32& pmb);
    bmp16_565& operator=(const class colorarray565& ca);
    ~bmp16_565();
    unsigned short turner(unsigned short b1,unsigned short g1,unsigned short r1);
    int readfromfile(const char* filename);
    int write2file(const char* filename);
public:
	DWORD mask_R_565;
	DWORD mask_G_565;
	DWORD mask_B_565;
	DWORD mask_A_565;
    unsigned char* dataptr;
    WORD end00;//为什么文件大小是14+40+16+w*h*2+2,最后的两个字节有啥意义,没找到标准 
};

#endif // BMP16_565_H

