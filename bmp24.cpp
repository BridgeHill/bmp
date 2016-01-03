#include <ios>
#include <iostream>
#include <assert.h>

#include "bmp24.h"
using namespace std;

bmp24::bmp24():bmpinfo()
{
    dataptr = NULL;
}

bmp24::bmp24(unsigned long w,unsigned long h):bmpinfo(w,h)
{
    unsigned long  tempsize= h*(((w*3)%4)?(((w*3)/4+1)*4):(w*3));
    file_size = 14 + 40 + tempsize;
    bit_count = 24;
    image_size = tempsize;

	try
	{
		dataptr = new unsigned char[tempsize]();		
	}catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}	
}

//拷贝构造函数
bmp24::bmp24(const bmp24& pmb):bmpinfo(pmb)
{
	try
	{
		dataptr = new unsigned char[pmb.image_size];	
	}catch(bad_alloc &memExp)
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

bmp24& bmp24::operator=(const class bmp24& pmb)
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

        if(NULL != dataptr)
        {
            delete [] dataptr;
			dataptr = NULL;
        }
		try
		{
			dataptr = new unsigned char[pmb.image_size];			
		}catch(bad_alloc &memExp)
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

bmp24::~bmp24()
{
    delete [] dataptr;
}

int bmp24::readfromfile(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary | ios::in);
	if(!file1.is_open())
	{
		cout << "fail to open " << filename << endl;
		file1.close();
		return 1;
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
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}	

	if(NULL == dataptr)
	{
		cout << "fail to get ram " << image_size << endl;
		file1.close();
		return 2;
	}

    file1.read(reinterpret_cast<char *>(dataptr),image_size);
    file1.close();
    return 0;
}

int bmp24::write2file(const char* filename)
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
    if(NULL != dataptr)
    {
        file1.write(reinterpret_cast<char *>(dataptr),image_size);
    }
    file1.close();
    return 0;
}


bmp24& bmp24::operator=(const bmp32& pmb)
{
    unsigned long tempsize = pmb.height *(((pmb.width*3)%4)?(((pmb.width*3)/4+1)*4):(pmb.width*3));
    type = 0x4D42;
    file_size = 14 + 40 + tempsize;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 24;
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
		dataptr = new unsigned char[image_size]();
	}catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}		

    //用bmp32给bmp24赋值
    unsigned long WIDE = (((pmb.width*3)%4)?(((pmb.width*3)/4+1)*4):(pmb.width*3));

    for(unsigned long h=0;h < pmb.height;h++)
    {
        for(unsigned long w=0;w < pmb.width;w++)
        {
            for(unsigned long c=0;c < 3;c++)
			{
				dataptr[h*WIDE + w*3 + c] = pmb.dataptr[h*pmb.width*4 + w*4 + c];
				// unsigned long temp1 = h*WIDE + w*3 + c;
				// unsigned long value1 = dataptr[h*WIDE + w*3 + c];
				// unsigned long temp2 = h*pmb.width*4 + w*4 + c;
				// unsigned long value2 = pmb.dataptr[h*pmb.width*4 + w*4 + c];
				// cout << "h=" << h << "|w=" << w <<"|c=" << c << " " << temp1 << " " <<value1 << " " <<temp2 << " " <<value2 << endl; 
			}		
        }
    }
    return *this;
}
