#ifndef BMP16_555_H
#define BMP16_555_H

#include "bmpinfo.h"
#include "bmp32.h"

//����:��555��ʽ�£��졢�̡���������ֱ��ǣ�0x7C00��0x03E0��0x001F������565��ʽ�£�������ֱ�Ϊ��0xF800��0x07E0��0x001F��
#define MaskR_16_555 0x7C00
#define MaskG_16_555 0x03E0
#define MaskB_16_555 0x001F

class bmp16_555 : public bmpinfo
{
public:
    bmp16_555();
    bmp16_555(unsigned int w,unsigned int h);
    bmp16_555(const bmp16_555& pmb);
    bmp16_555& operator=(const bmp16_555& pmb);
    bmp16_555& operator=(const class bmp32& pmb);
    ~bmp16_555();
    unsigned short turner(unsigned short b1,unsigned short g1,unsigned short r1);
    int readfromfile(const char* filename);
    int write2file(const char* filename);
public:
    unsigned char* dataptr;
    WORD end00;
};

#endif // BMP16_555_H

