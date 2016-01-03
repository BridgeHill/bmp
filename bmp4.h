#ifndef BMP4_H
#define BMP4_H
#include "bmpinfo.h"
#include "color.h"
#include "bmp32.h"

class bmp4 : public bmpinfo,public colorpad_4
{
public:
    bmp4();
    bmp4(unsigned long w,unsigned long h);
    bmp4(const bmp4& pmb);
    bmp4& operator=(const bmp4& pmb);
    bmp4& operator=(const class bmp32& pmb);
    ~bmp4();
    int readfromfile(const char* filename);
    int write2file(const char* filename);
public:
    unsigned char* dataptr;
};


#endif // BMP4_H

