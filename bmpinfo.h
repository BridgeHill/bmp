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

    virtual int write2file(const char* filename) = 0; //���麯��
    virtual int readfromfile(const char* filename) = 0; //���麯��
    int printinfo();
	//0-1
    WORD type;//0x4D42��
    //2-5
    DWORD file_size;//λͼ�ļ��Ĵ�С���ֽ�Ϊ��λ
                    //1λͼ��4λͼ��8λͼ��14+40+4*2^n+(w*h*n)/8
                    //16λͼ555��ʽ��14+40+(w*h*16)/8+2
                    //16λͼ565��ʽ��14+40+16+(w*h*16)/8+2
                    //24λͼ��14+40+(w*h*24)/8
                    //32λͼ��14+40+(w*h*32)/8
    //6-9
    DWORD reserved;//�����֣���������Ϊ0
    //10-13
    DWORD offset;//���ļ�ͷ��ʼ��λͼ���ݿ�ʼ��ƫ����
    //��Ϣͷ
    //14-17
    DWORD header_info_size;//�ļ���Ϣͷ�Ĵ�С
    //18-21
    DWORD width;//λͼ���
    //22-25
    DWORD height;//λͼ�߶�
    //26-27
    WORD planes;//λͼ��λ����������Ϊ1
    //28-29
    WORD bit_count;//ÿ�����ص�λ����1��˫ɫ����4��16ɫ����8��256ɫ����16(16λ)��24��24λ����32��32λ��
    //30-33
	DWORD compression;//ѹ�����ͣ�
                      //0����ѹ��
                      //1��ʹ��RLEѹ����ʽ
                      //2��ʹ��4λRLEѹ����ʽ
                      //3��λ���ŷ�ʽ
    //34-37
	DWORD image_size; //λͼ�Ĵ�С���ֽ�Ϊ��λ
	//38-41
    DWORD xpels_per_meter;//ˮƽ�ֱ���
    //42-45
    DWORD ypels_per_meter;//��ֱ�ֱ���
    //46-49
    DWORD color_used;//ͼ��ʵ���õ�����ɫ�������Ϊ0�����õ�����ɫ��Ϊ2
    //50-53
    DWORD color_important;//��ͼ������Ҫ����ɫ�������Ϊ0�����õ�����ɫ������Ҫɫ
    //54
};

#endif // BMP_H
