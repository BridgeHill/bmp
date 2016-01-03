#ifndef BMP8_H
#define BMP8_H

#include "bmpinfo.h"
#include "color.h"
#include "bmp32.h"

class bmp8 : public bmpinfo,public colorpad_8
{
public:
    bmp8();
    bmp8(unsigned long w,unsigned long h);
    bmp8(const bmp8& pmb);
    bmp8& operator=(const bmp8& pmb);
    bmp8& operator=(const class bmp32& pmb);
    ~bmp8();
    int readfromfile(const char* filename);
    int write2file(const char* filename);
public:
    unsigned char* dataptr;
};


#endif // BMP8_H

