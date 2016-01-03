#include <ios>
#include <iostream>
#include <assert.h>
#include "bmp16_565.h"
using namespace std;

bmp16_565::bmp16_565():bmpinfo()
{
	file_size = 14 + 40 + 16;
	offset = 0x46;
	header_info_size = 0x38;
    compression = 3;
    bit_count = 16;
    mask_R_565 = 0x0000F800;
	mask_G_565 = 0x000007E0;
	mask_B_565 = 0x0000001F;
	mask_A_565 = 0x00000000;
    dataptr = NULL;
    end00 = 0x0000; 
}

bmp16_565::bmp16_565(unsigned int w,unsigned int h):bmpinfo(w,h)
{
    unsigned long tempsize= h * ((w % 2)?((w/2+1)*4):(w*2));
    file_size = 14 + 40 + 16 + tempsize;
    offset = 0x46;
    header_info_size = 0x38;
    compression = 3;
    bit_count = 16;
    image_size = tempsize;
    mask_R_565 = 0x0000F800;
	mask_G_565 = 0x000007E0;
	mask_B_565 = 0x0000001F;
	mask_A_565 = 0x00000000;
    dataptr = new unsigned char[tempsize]();
    end00 = 0x0000;
}

//拷贝构造函数
bmp16_565::bmp16_565(const bmp16_565& pmb):bmpinfo(pmb)
{
	mask_R_565 = pmb.mask_R_565;
	mask_G_565 = pmb.mask_G_565;
	mask_B_565 = pmb.mask_B_565;
	mask_A_565 = pmb.mask_A_565;
    dataptr = new unsigned char[pmb.image_size]();
    for(unsigned long i=0;i < (pmb.image_size);i++)
    {
        dataptr[i] = pmb.dataptr[i];
    }
    end00 = 0x0000;
}

bmp16_565& bmp16_565::operator=(const bmp16_565& pmb)
{
    if(this != &pmb)
    {
        type = pmb.type;
        file_size = pmb.file_size;
        reserved = pmb.reserved;
        offset = pmb.offset;
        header_info_size = pmb.header_info_size;
        width = pmb.width;
        height = pmb.height;
        planes = pmb.planes;
        bit_count = pmb.bit_count;
        compression = pmb.compression;
        image_size = pmb.image_size;
        xpels_per_meter = pmb.xpels_per_meter;
        ypels_per_meter = pmb.ypels_per_meter;
        color_used = pmb.color_used;
        color_important = pmb.color_important;
        mask_R_565 = pmb.mask_R_565;
		mask_G_565 = pmb.mask_G_565;
		mask_B_565 = pmb.mask_B_565;
		mask_A_565 = pmb.mask_A_565;
        if(NULL != dataptr)
        {
            delete [] dataptr;
        }
        dataptr = new unsigned char[pmb.image_size];

        for(unsigned int i=0;i < (pmb.image_size);i++)
        {
            dataptr[i] = pmb.dataptr[i];
        }
        end00 = 0x0000;
    }
    return *this;
}

bmp16_565::~bmp16_565()
{
    delete [] dataptr;
}

int bmp16_565::readfromfile(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary | ios::in);
    if(!file1.is_open())
        return 1;
    file1.read(reinterpret_cast<char *>(&type),2);
    file1.read(reinterpret_cast<char *>(&file_size),4);
    file1.read(reinterpret_cast<char *>(&reserved),4);
    file1.read(reinterpret_cast<char *>(&offset),4);
    file1.read(reinterpret_cast<char *>(&header_info_size),4);
    file1.read(reinterpret_cast<char *>(&width),4);
    file1.read(reinterpret_cast<char *>(&height),4);
    file1.read(reinterpret_cast<char *>(&planes),2);
    file1.read(reinterpret_cast<char *>(&bit_count),2);
    file1.read(reinterpret_cast<char *>(&compression),4);
    file1.read(reinterpret_cast<char *>(&image_size),4);
    file1.read(reinterpret_cast<char *>(&xpels_per_meter),4);
    file1.read(reinterpret_cast<char *>(&ypels_per_meter),4);
    file1.read(reinterpret_cast<char *>(&color_used),4);
    file1.read(reinterpret_cast<char *>(&color_important),4);
	file1.read(reinterpret_cast<char *>(&mask_R_565),4);
	file1.read(reinterpret_cast<char *>(&mask_G_565),4);
	file1.read(reinterpret_cast<char *>(&mask_B_565),4);
	file1.read(reinterpret_cast<char *>(&mask_A_565),4);
    if(NULL != dataptr)
    {
        delete [] dataptr;
    }
    dataptr = new unsigned char[image_size];
    file1.read(reinterpret_cast<char *>(dataptr),image_size);
	file1.read(reinterpret_cast<char *>(&end00),2);
    file1.close();
    return 0;
}

int bmp16_565::write2file(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary|ios::out);
    file1.write(reinterpret_cast<char *>(&type),2);
    file1.write(reinterpret_cast<char *>(&file_size),4);
    file1.write(reinterpret_cast<char *>(&reserved),4);
    file1.write(reinterpret_cast<char *>(&offset),4);
    file1.write(reinterpret_cast<char *>(&header_info_size),4);
    file1.write(reinterpret_cast<char *>(&width),4);
    file1.write(reinterpret_cast<char *>(&height),4);
    file1.write(reinterpret_cast<char *>(&planes),2);
    file1.write(reinterpret_cast<char *>(&bit_count),2);
    file1.write(reinterpret_cast<char *>(&compression),4);
    file1.write(reinterpret_cast<char *>(&image_size),4);
    file1.write(reinterpret_cast<char *>(&xpels_per_meter),4);
    file1.write(reinterpret_cast<char *>(&ypels_per_meter),4);
    file1.write(reinterpret_cast<char *>(&color_used),4);
    file1.write(reinterpret_cast<char *>(&color_important),4);
	file1.write(reinterpret_cast<char *>(&mask_R_565),4);
	file1.write(reinterpret_cast<char *>(&mask_G_565),4);
	file1.write(reinterpret_cast<char *>(&mask_B_565),4);
	file1.write(reinterpret_cast<char *>(&mask_A_565),4);
    if(NULL != dataptr)
    {
        file1.write(reinterpret_cast<char *>(dataptr),image_size);
    }
	file1.write(reinterpret_cast<char *>(&end00),2);   
	file1.close();
    return 0;
}

unsigned short bmp16_565::turner(unsigned short b1,unsigned short g1,unsigned short r1)
{
    return (((r1 >> 3) << 11) | ((g1 >> 2) << 5) | ((b1 >> 3)));
}

bmp16_565& bmp16_565::operator=(const class bmp32& pmb)
{
    unsigned long tempsize = pmb.height * ((pmb.width % 2)?((pmb.width/2+1)*4):(pmb.width*2));
    type = 0x4D42;
    file_size = 14 + 40 + 16 +tempsize;
    reserved = 0;
    offset = 0x46;
    header_info_size = 0x38;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 16;
    compression = 3;
    image_size = tempsize;
    xpels_per_meter = 0;
    ypels_per_meter = 0;
    color_used = 0;
    color_important = 0;
    mask_R_565 = 0x0000F800;
	mask_G_565 = 0x000007E0;
	mask_B_565 = 0x0000001F;
	mask_A_565 = 0x00000000;
    if(NULL != dataptr)
    {
        delete [] dataptr;
		dataptr = NULL;
    }
	try
	{
		dataptr = new unsigned char[image_size];
	}
	catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}	

    //用bmp32给bmp16赋值
    unsigned long WIDE = ((pmb.width % 2)?((pmb.width/2+1)*4):(pmb.width*2));

    for(unsigned long h=0;h < pmb.height;h++)
    {
        for(unsigned long w=0;w < pmb.width;w++)
        {
            unsigned short tempi = turner(pmb.dataptr[h*pmb.width*4 + w*4+0],pmb.dataptr[h*pmb.width*4 + w*4+1],pmb.dataptr[h*pmb.width*4 + w*4+2]);
            dataptr[h*WIDE+w*2+0] = (tempi & 0x00ff);
            dataptr[h*WIDE+w*2+1] = (tempi >> 8);
        }
    }
    end00 = 0x0000;
    return *this;
}

bmp16_565& bmp16_565::operator=(const class colorarray565& ca)
{
	width = ca.width;
    height = ca.height;
	unsigned long WIDE = ((width % 2)?((width/2+1)*4):(width*2));
	unsigned long tempsize = ca.height * WIDE;
    type = 0x4D42;
    file_size = 14 + 40 + 16 +tempsize;
    reserved = 0;
    offset = 0x46;
    header_info_size = 0x38;
    planes = 1;
    bit_count = 16;
    compression = 3;
    image_size = tempsize;
    xpels_per_meter = 0;
    ypels_per_meter = 0;
    color_used = 0;
    color_important = 0;
    mask_R_565 = 0x0000F800;
	mask_G_565 = 0x000007E0;
	mask_B_565 = 0x0000001F;
    mask_A_565 = 0x00000000;
    if(NULL != dataptr)
    {
        delete [] dataptr;
		dataptr = NULL;
    }
   	try
	{
		dataptr = new unsigned char[image_size];
	}catch(bad_alloc &memExp)
	{
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);
	}

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
//          dataptr[h*WIDE+w*2 + 0] = ca.dataptr[width*height*2 - (h*width*2+w*2 + 0) -2];
//	    	dataptr[h*WIDE+w*2 + 1] = ca.dataptr[width*height*2 - (h*width*2+w*2 + 1) -0];
	    	
	    	dataptr[h*WIDE+w*2 + 0] = ca.dataptr[width*(height-h)*2 - ((width-w-1)*2 + 0) -2];
	    	dataptr[h*WIDE+w*2 + 1] = ca.dataptr[width*(height-h)*2 - ((width-w-1)*2 + 1) -0];
        }
    }
    return *this;
}
