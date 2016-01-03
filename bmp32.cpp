#include <ios>
#include <iostream>
#include <assert.h>

#include "bmp32.h"

using namespace std;

bmp32::bmp32():bmpinfo()
{
    dataptr = NULL;
}

bmp32::bmp32(unsigned long w,unsigned long h):bmpinfo(w,h)
{
    unsigned long tempsize= h * w * 4;
    file_size = 14 + 40 + tempsize;
    offset = 54;
    bit_count = 32;
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
bmp32::bmp32(const bmp32& pmb):bmpinfo(pmb)
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

bmp32& bmp32::operator=(const bmp32& pmb)
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

bmp32::~bmp32()
{//实际上delete 本身会自动检查对象是否为空 .如果为空 , 就不做操作,所以不用事先判断
    delete [] dataptr;
}

int bmp32::readfromfile(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::binary | ios::in);
    if(!file1.is_open())
	{
		cout << ">>>>fail to open file " << filename << endl;
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

    file1.read(reinterpret_cast<char *>(dataptr),image_size);
    file1.close();
    return 0;
}

int bmp32::write2file(const char* filename)
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


//转换函数
bmp32& bmp32::operator=(const class bmp1& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

	unsigned long WIDE = (pmb.width % 32)?((pmb.width/32 + 1)*4):(pmb.width/8);
    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
		unsigned char tempi = (pmb.dataptr[h*WIDE + w/8] & (0x80 >> (w % 8)))?(1):(0);
		dataptr[h*pmb.width*4 + w*4 + 0] = pmb.ColorList[tempi].uc[Bi];
		dataptr[h*pmb.width*4 + w*4 + 1] = pmb.ColorList[tempi].uc[Gi];
		dataptr[h*pmb.width*4 + w*4 + 2] = pmb.ColorList[tempi].uc[Ri];
		dataptr[h*pmb.width*4 + w*4 + 3] = 0x00;//alpha通道赋固定值
        }
    }
    return *this;
}

bmp32& bmp32::operator=(const class bmp4& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = ((pmb.width % 8)?((pmb.width/8+1)*4):((pmb.width/8)*4));

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
		unsigned char tempc = (w%2)?(pmb.dataptr[h*WIDE + w/2] & 0x0f):(pmb.dataptr[h*WIDE + w/2] >> 4);
                dataptr[h*pmb.width*4 + w*4 + 0] = pmb.ColorList[tempc].uc[Bi];
                dataptr[h*pmb.width*4 + w*4 + 1] = pmb.ColorList[tempc].uc[Gi];
                dataptr[h*pmb.width*4 + w*4 + 2] = pmb.ColorList[tempc].uc[Ri];
		dataptr[h*pmb.width*4 + w*4 + 3] = 0x00;//alpha通道赋固定值
        }
    }
    return *this;
}

bmp32& bmp32::operator=(const class bmp8& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = ((pmb.width % 4)?((pmb.width/4+1)*4):(pmb.width));

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
            unsigned char tempc = pmb.dataptr[h*WIDE + w];
            dataptr[h*pmb.width*4 + w*4 + 0] = pmb.ColorList[tempc].uc[Bi];
            dataptr[h*pmb.width*4 + w*4 + 1] = pmb.ColorList[tempc].uc[Gi];
            dataptr[h*pmb.width*4 + w*4 + 2] = pmb.ColorList[tempc].uc[Ri];
            dataptr[h*pmb.width*4 + w*4 + 3] = pmb.ColorList[tempc].uc[Ai];
        }
    }
    return *this;
}
bmp32& bmp32::operator=(const class bmp8G& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = ((pmb.width % 4)?((pmb.width/4+1)*4):(pmb.width));

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
            unsigned char tempc = pmb.dataptr[h*WIDE + w];
            dataptr[h*pmb.width*4 + w*4 + 0] = pmb.ColorList[tempc].uc[Bi];
            dataptr[h*pmb.width*4 + w*4 + 1] = pmb.ColorList[tempc].uc[Gi];
            dataptr[h*pmb.width*4 + w*4 + 2] = pmb.ColorList[tempc].uc[Ri];
            dataptr[h*pmb.width*4 + w*4 + 3] = pmb.ColorList[tempc].uc[Ai];
        }
    }
    return *this;
}

bmp32& bmp32::operator=(const class bmp16_555& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = ((pmb.width % 2)?((pmb.width/2+1)*4):(pmb.width*2));

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
            unsigned short tempi = (unsigned short)(pmb.dataptr[h*WIDE + w*2 + 1] << 8 ) | (unsigned short)(pmb.dataptr[h*WIDE + w*2 + 0]);
            dataptr[h*pmb.width*4 + w*4 + 0] = (tempi & MaskB_16_555) << 3;
            dataptr[h*pmb.width*4 + w*4 + 1] = ((tempi & MaskG_16_555) >> 5) <<3;
            dataptr[h*pmb.width*4 + w*4 + 2] = ((tempi & MaskR_16_555) >> 10) << 3;
            dataptr[h*pmb.width*4 + w*4 + 3] = 0x00;//alpha通道赋固定值
        }
    }
    return *this;
}

bmp32& bmp32::operator=(const class bmp16_565& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = ((pmb.width % 2)?((pmb.width/2+1)*4):(pmb.width*2));

    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
            unsigned short tempi = (unsigned short)(pmb.dataptr[h*WIDE + w*2 + 1] << 8 ) | (unsigned short)(pmb.dataptr[h*WIDE + w*2 + 0]);
            dataptr[h*pmb.width*4 + w*4 + 0] = (tempi & (unsigned short)(pmb.mask_B_565))<< 3;
            dataptr[h*pmb.width*4 + w*4 + 1] = ((tempi & (unsigned short)(pmb.mask_G_565)) >> 5) <<2;
            dataptr[h*pmb.width*4 + w*4 + 2] = ((tempi & (unsigned short)(pmb.mask_R_565)) >> 11) << 3;
            dataptr[h*pmb.width*4 + w*4 + 3] = 0x00;//alpha通道赋固定值
        }
    }
    return *this;
}


bmp32& bmp32::operator=(const class bmp24& pmb)
{
    type = 0x4D42;
    file_size = 14 + 40 + pmb.height * pmb.width * 4;
    reserved = 0;
    offset = 54;
    header_info_size = 0x28;
    width = pmb.width;
    height = pmb.height;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = pmb.height * pmb.width * 4;
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

    unsigned long WIDE = (((pmb.width*3)%4)?(((pmb.width*3)/4+1)*4):(pmb.width*3));
    for(unsigned long h=0;h < pmb.height;h++)
    {
        for(unsigned long w=0;w < pmb.width;w++)
        {
            for(unsigned long c=0;c < 3;c++)
            {
                dataptr[h*pmb.width*4 + w*4 + c] = pmb.dataptr[h*WIDE + w*3 + c];
            }
            dataptr[h*pmb.width*4 + w*4 +3] = 0x00;//alpha通道赋固定值
        }
    }
    return *this;
}
