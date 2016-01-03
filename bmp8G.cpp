#include <ios>
#include <iostream>
#include <assert.h>
#define COLOR_PAD_SUM_8 (1024)

#include "bmp8G.h"
using namespace std;

bmp8G::bmp8G():bmpinfo(),colorpad_8G()
{
    dataptr = NULL;
}

bmp8G::bmp8G(unsigned long w,unsigned long h):bmpinfo(w,h),colorpad_8G()
{
    unsigned long tempsize= h * ((w % 4)?((w/4+1)*4):(w));
    offset = 54 + COLOR_PAD_SUM_8;
    file_size = 14 + 40 + COLOR_PAD_SUM_8 + tempsize;
    bit_count = 8;
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
bmp8G::bmp8G(const bmp8G& pmb):bmpinfo(pmb),colorpad_8G()
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

bmp8G& bmp8G::operator=(const bmp8G& pmb)
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
		
        for(int i=0;i < (256);i++)
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

        for(unsigned int i=0;i < (pmb.image_size);i++)
        {
            dataptr[i] = pmb.dataptr[i];
        }
    }
    return *this;
}

bmp8G::~bmp8G()
{
    delete [] dataptr;
}

int bmp8G::readfromfile(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary | ios::in);
	if(!file1.is_open())
	{
		cerr << "Failed to open file " << filename << endl;
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

    for(int tempi=0;tempi<256;tempi++)
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

int bmp8G::write2file(const char* filename)
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

    for(int tempi=0;tempi<256;tempi++)
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

bmp8G& bmp8G::operator=(const class bmp32& pmb)
{
    unsigned long tempsize = pmb.height * ((pmb.width % 4)?((pmb.width/4+1)*4):(pmb.width));
    type = 0x4D42;
    file_size = 14 + 40 + COLOR_PAD_SUM_8 + tempsize;
    reserved = 0;
    offset = 54 + COLOR_PAD_SUM_8;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 8;
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
	}
	catch(bad_alloc &memExp)
	{
		//失败以后，要么abort要么重分配
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
	}

    //用bmp32给bmp8G赋值
    unsigned long WIDE = ((pmb.width % 4)?((pmb.width/4+1)*4):(pmb.width));
    for(unsigned long h=0;h < pmb.height;h++)
    {
        for(unsigned long w=0;w < pmb.width;w++)
        {
            int tempc = getnum(pmb.dataptr[h*pmb.width*4 + w*4 +0],pmb.dataptr[h*pmb.width*4 + w*4 +1],pmb.dataptr[h*pmb.width*4 + w*4 +2]);
            if(-1 == tempc)
            	cerr << "getnum work worong" <<endl;
		dataptr[h*WIDE+w] = tempc;
//	    cout << " tempc " << tempc << endl;
        }
    }
    return *this;
}
