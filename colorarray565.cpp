#include <ios>
#include <iostream>
#include <assert.h>
#include <string>

#include "colorarray565.h"
#include "bmp16_565.h"
using namespace std;

colorarray565::colorarray565()
{
    datatype = "unsigned const char";
    name = "unnamed";
    width = 0;
    height = 0;
	dataptr = NULL;
}

colorarray565::colorarray565(string arrayname)
{
    datatype = "unsigned const char";
    name = arrayname;
    width = 0;
    height = 0;
	dataptr = NULL;
}

colorarray565::colorarray565(unsigned long w,unsigned h,string arrayname)
{
    datatype = "unsigned const char";
    name = arrayname;
    width = w;
    height = h;
	dataptr = NULL;
}

int colorarray565::write2file(const char* filename)
{
    fstream file1;
    file1.open(filename,ios::out);
    long size = width*height*2;
    file1 << datatype << ' ' << name << '[' << size << ']' << ' ' << '=' << ' ' << '{';
	if(dataptr != NULL) 
	{
		for(long i = 0;i < size; i++)
		{	        	
			if(0 == (i%16))  
				file1 << endl;
			if(short(dataptr[i]) < 0x10)
				file1 <<"0x0"<<hex<< short(dataptr[i]) << ',';
			else
				file1 <<"0x"<<hex<< short(dataptr[i]) << ',';
		}		
	}
    file1 << endl << '}' << ';' << endl;
    file1.close();
	return 0;
}

int colorarray565::readfromfile(const char* filename,unsigned w,unsigned h)
{
    width = w;
    height = h;
    
    fstream file1;
    file1.open(filename,ios::in);
    if(!file1.is_open())
	{
		cout << ">>>>fail to open file " << filename << endl;
		return -1;
	}
	int size = 0;
	for(char ch=0x00;!file1.eof();)
	{
		file1.get(ch);
		if('[' == ch)
		{
			file1 >> size;
			if(size != w*h*2)
				return -2;
			else
			{
				if(NULL != dataptr)
			    {
			        delete [] dataptr;
					dataptr = NULL;
			    }
				try
				{
					dataptr = new unsigned char[size]();	
				}
					catch(bad_alloc &memExp)
				{
					//失败以后，要么abort要么重分配
					cerr<<memExp.what()<<endl; 
					cerr << "unable to satisfy request for memory\n" << endl;
					assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
				}
				for(char cchh=0x00;!file1.eof();)
				{
					file1.get(cchh);
					if('{' == cchh)
					{
						if(NULL != dataptr)
					    {
					        delete [] dataptr;
							dataptr = NULL;
					    }
						try
						{
							dataptr = new unsigned char[size]();
						}catch(bad_alloc &memExp)
						{
							//失败以后，要么abort要么重分配
							cerr<<memExp.what()<<endl; 
							cerr << "unable to satisfy request for memory\n" << endl;
							assert(0);//如果没定义宏ndebug,表达式为0,调用abort()
						}
						int i = 0;
						for(char ccchhh=0;(!file1.eof())&&(i<size);)
						{
							int pos = file1.tellg();
							file1.get(ccchhh);
							pos = file1.tellg();
							if((ccchhh=='x')||(ccchhh=='X'))
							{
								char ch1=0,ch2=0;
								int ch1ch2=0;
								file1.get(ch1);
								file1.get(ch2);
								if((ch2>='a')&&(ch2<='f'))
								{
									ch1ch2 += ch2 - 'a' + 0x0a;	
								}
								else if((ch2>='A')&&(ch2<='F'))
								{
									ch1ch2 += ch2 - 'A' + 0x0A;
								}
								else if((ch2>='0')&&(ch2<='9'))
								{
									ch1ch2 += ch2 - '0';
								}
								else
								{
									cout << "wrong" << endl;
									return -4;
								}

								if((ch1>='a')&&(ch1<='f'))
								{
									ch1ch2 += (ch1 - 'a' + 0x0a) << 4;	
								}
								else if((ch1>='A')&&(ch1<='F'))
								{
									ch1ch2 += (ch1 - 'A' + 0x0A) << 4;	
								}
								else if((ch1>='0')&&(ch1<='9'))
								{
									ch1ch2 += (ch1 - '0') << 4;	
								}
								//else
								//	return -5;
								dataptr[i++] = ch1ch2;
							}
						}	
					}
				}		
			}
		}		
	}
	file1.close();
}

colorarray565::~colorarray565()
{
    delete [] dataptr;
}

colorarray565& colorarray565::operator=(const class bmp16_565& pmb)
{
    width = pmb.width;
    height = pmb.height;
    if(NULL != dataptr)
    {
        delete [] dataptr;
		dataptr = NULL;
    }
   	try
	{
		dataptr = new unsigned char[width*height*2]();
	}catch(bad_alloc &memExp)
	{
		cerr<<memExp.what()<<endl; 
		cerr << "unable to satisfy request for memory\n" << endl;
		assert(0);
	}

    unsigned long WIDE = ((pmb.width % 2)?((pmb.width/2+1)*4):(pmb.width*2));
    
    for(unsigned long h=0;h < height;h++)
    {
        for(unsigned long w=0;w < width;w++)
        {
            dataptr[width*(height-h)*2 - ((width-w-1)*2 + 0) -2] = pmb.dataptr[h*WIDE + w*2 + 0];
	    	dataptr[width*(height-h)*2 - ((width-w-1)*2 + 1) -0] = pmb.dataptr[h*WIDE + w*2 + 1];
        }
    }
    return *this;
}
