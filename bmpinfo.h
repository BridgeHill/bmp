#ifndef BMPINFO_H
#define BMPINFO_H
#include <string>
#include <fstream>

#include "common.h"

//enum bmptype{BMP1,BMP4,BMP8,BMP16_555,BMP16_565,BMP24,BMP32};

class bmpinfo
{
public:
    bmpinfo();
    bmpinfo(unsigned int w,unsigned int h);
    bmpinfo(const bmpinfo& pmb);
    virtual ~bmpinfo();

    virtual int write2file(const char* filename) = 0; //纯虚函数
    virtual int readfromfile(const char* filename) = 0; //纯虚函数
    int printinfo();
	//0-1
    WORD type;//0x4D42，
    //2-5
    DWORD file_size;//位图文件的大小，字节为单位
                    //1位图、4位图、8位图：14+40+4*2^n+(w*h*n)/8
                    //16位图555格式：14+40+(w*h*16)/8+2
                    //16位图565格式：14+40+16+(w*h*16)/8+2
                    //24位图：14+40+(w*h*24)/8
                    //32位图：14+40+(w*h*32)/8
    //6-9
    DWORD reserved;//保留字，必须设置为0
    //10-13
    DWORD offset;//从文件头开始到位图数据开始的偏移量
    //信息头
    //14-17
    DWORD header_info_size;//文件信息头的大小
    //18-21
    DWORD width;//位图宽度
    //22-25
    DWORD height;//位图高度
    //26-27
    WORD planes;//位图的位面数，必须为1
    //28-29
    WORD bit_count;//每个像素的位数，1（双色），4（16色），8（256色），16(16位)，24（24位），32（32位）
    //30-33
	DWORD compression;//压缩类型：
                      //0：不压缩
                      //1：使用RLE压缩方式
                      //2：使用4位RLE压缩方式
                      //3：位域存放方式
    //34-37
	DWORD image_size; //位图的大小，字节为单位
	//38-41
    DWORD xpels_per_meter;//水平分辨率
    //42-45
    DWORD ypels_per_meter;//垂直分辨率
    //46-49
    DWORD color_used;//图形实际用到的颜色数，如果为0，则用到的颜色数为2
    //50-53
    DWORD color_important;//本图形中重要的颜色数，如果为0，则用到的颜色都是重要色
    //54
};

#endif // BMP_H
