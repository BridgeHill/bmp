#ifndef BMP1_H
#define BMP1_H

#include "bmpinfo.h"
#include "color.h"
#include "bmp32.h"

class bmp1 : public bmpinfo,public colorpad_1
{
public:
    bmp1();
    bmp1(unsigned long w,unsigned long h);
    bmp1(const bmp1& pmb);
    bmp1& operator=(const bmp1& pmb);
    bmp1& operator=(const class bmp32& pmb);
    ~bmp1();
    int readfromfile(const char* filename);
    int write2file(const char* filename);
public:
    unsigned char* dataptr;
};


#endif // BMP1_H

