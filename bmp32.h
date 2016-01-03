#ifndef BMP32_H
#define BMP32_H

#include "bmpinfo.h"
#include "bmp1.h"
#include "bmp4.h"
#include "bmp8.h"
#include "bmp8G.h"
#include "bmp16_555.h"
#include "bmp16_565.h"
#include "bmp24.h"

class bmp32 : public bmpinfo
{
public:
    bmp32();
    bmp32(unsigned long w,unsigned long h);
    bmp32(const bmp32& pmb);
    bmp32& operator=(const bmp32& pmb);
    bmp32& operator=(const class bmp1& pmb);
    bmp32& operator=(const class bmp4& pmb);
    bmp32& operator=(const class bmp8& pmb);
    bmp32& operator=(const class bmp8G& pmb);
    bmp32& operator=(const class bmp16_555& pmb);
    bmp32& operator=(const class bmp16_565& pmb);
    bmp32& operator=(const class bmp24& pmb);
    ~bmp32();

    int readfromfile(const char* filename);
    int write2file(const char* filename);
    unsigned char* dataptr;
};

#endif // BMP32_H

