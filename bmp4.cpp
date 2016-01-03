#include <ios>
#include <iostream>
#include <assert.h>
#define COLOR_PAD_SUM_4 (64)

#include "bmp4.h"
using namespace std;

bmp4::bmp4():bmpinfo()
{
    dataptr = NULL;
}

bmp4::bmp4(unsigned long w,unsigned long h):bmpinfo(w,h),colorpad_4()
{
    unsigned long tempsize= h * ((w % 8)?((w/8+1)*4):(w/8)*4);
    offset = 54 + COLOR_PAD_SUM_4;
    file_size = 14 + 40 + COLOR_PAD_SUM_4 + tempsize;
    bit_count = 4;
    image_size = tempsize;
	try
	{
		dataptr = new unsigned char[tempsize]();		
	}
	catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}
}

//拷贝构造函数
bmp4::bmp4(const bmp4& pmb):bmpinfo(pmb),colorpad_4()
{
	try
	{
		dataptr = new unsigned char[pmb.image_size]();			
	}
	catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}	

    for(unsigned long i=0;i < (pmb.image_size);i++)
    {
        dataptr[i] = pmb.dataptr[i];
    }
}

bmp4& bmp4::operator=(const bmp4& pmb)
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

	for(int i=0;i < (16);i++)
        {
            ColorList[i].ulg = pmb.ColorList[i].ulg;
	}

        if(NULL != dataptr)
        {
            delete [] dataptr;
	    dataptr = NULL;
        }
		try
		{
			dataptr = new unsigned char[pmb.image_size]();					
		}
		catch(bad_alloc &memExp)
		{
			//失败以后，要么abort要么重分配
			cerr<<memExp.what()<<endl; 
			cerr << "unable to satisfy request for memory\n" << endl;
			assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
		}

        for(unsigned long i=0;i < (pmb.image_size);i++)
        {
            dataptr[i] = pmb.dataptr[i];
        }
    }
    return *this;
}

bmp4::~bmp4()
{
    delete [] dataptr;
}

int bmp4::readfromfile(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary | ios::in);
	if(!file1.is_open())
	{
		cerr << "Fail to open " << filename << endl;
		return -1;
	}
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

    for(int tempi=0;tempi<16;tempi++)
    {
	file1.read(reinterpret_cast<char *>(&ColorList[tempi].uc[Bi]),1);
	file1.read(reinterpret_cast<char *>(&ColorList[tempi].uc[Gi]),1);
	file1.read(reinterpret_cast<char *>(&ColorList[tempi].uc[Ri]),1);
	file1.read(reinterpret_cast<char *>(&ColorList[tempi].uc[Ai]),1);
    }
    if(NULL != dataptr)
    {
        delete [] dataptr;
		dataptr = NULL;
    }
	try
	{
		dataptr = new unsigned char[image_size]();
	}
	catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}
    file1.read(reinterpret_cast<char *>(dataptr),image_size);
    file1.close();
    return 0;
}

int bmp4::write2file(const char* filename)
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

    for(int tempi=0;tempi<16;tempi++)
    {
    	file1.write(reinterpret_cast<char *>(&ColorList[tempi].uc[Bi]),1);
		file1.write(reinterpret_cast<char *>(&ColorList[tempi].uc[Gi]),1);
		file1.write(reinterpret_cast<char *>(&ColorList[tempi].uc[Ri]),1);
		file1.write(reinterpret_cast<char *>(&ColorList[tempi].uc[Ai]),1);
    }
    if(NULL != dataptr)
    {
        file1.write(reinterpret_cast<char *>(dataptr),image_size);
    }
    file1.close();
    return 0;
}

bmp4& bmp4::operator=(const bmp32& pmb)
{
    unsigned long tempsize = pmb.height * ((pmb.width % 8)?((pmb.width/8+1)*4):(pmb.width/8)*4);
    type = 0x4D42;
    file_size = 14 + 40 + COLOR_PAD_SUM_4 + tempsize;
    reserved = 0;
    offset = 54 + COLOR_PAD_SUM_4;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 4;
    compression = 0;
    image_size = tempsize;
    xpels_per_meter = 0;
    ypels_per_meter = 0;
    color_used = 0;
    color_important = 0;

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
    
    //用bmp32给bmp4赋值
    unsigned long WIDE = ((pmb.width % 8)?((pmb.width/8+1)*4):((pmb.width/8)*4));

    for(unsigned long h=0;h < pmb.height;h++)
    {
        for(unsigned long w=0;w < pmb.width;w++)
        {
            unsigned char tempc = getnum(pmb.dataptr[h*pmb.width*4 + w*4 + 0],pmb.dataptr[h*pmb.width*4 + w*4 + 1],pmb.dataptr[h*pmb.width*4 + w*4 + 2]);
//	    unsigned long test = tempc;
//	    cout << test << endl;
            if(w%2)
            {
		dataptr[h*WIDE+w/2] &= 0xf0;
		tempc = (tempc & 0x0f);
		dataptr[h*WIDE+w/2] |= tempc;
            }else
            {
                dataptr[h*WIDE+w/2] &= 0x0f;
                tempc = (tempc & 0x0f) << 4;
                dataptr[h*WIDE+w/2] |= tempc;
            }
        }
    }
    return *this;
}
