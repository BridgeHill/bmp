#ifndef BMP24_H
#define BMP24_H
#include "bmpinfo.h"
#include "bmp32.h"

class bmp24 : public bmpinfo
{
public:
    bmp24();
    bmp24(unsigned long w,unsigned long h);
    bmp24(const bmp24& pmb);
    bmp24& operator=(const bmp24& pmb);
    bmp24& operator=(const class bmp32& pmb);
    ~bmp24();
    int readfromfile(const char* filename);
    int write2file(const char* filename);
    unsigned char* dataptr;

};

#endif // BMP24_H

