#ifndef __COLORARRAY565__
#define __COLORARRAY565__

//typedef char BYTE;
//typedef unsigned short WORD;
//typedef unsigned long DWORD;

#include <ios>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std; 
#include "bmp16_565.h"

class colorarray565
{
   public:
      colorarray565();
      colorarray565(string arrayname);
      colorarray565(unsigned long w,unsigned h,string arrayname);
      colorarray565& operator=(const class bmp16_565& pmb);
      int write2file(const char* filename);
      int readfromfile(const char* filename,unsigned w,unsigned h);
	  ~colorarray565();
    public:
      string datatype;
      string name;
      DWORD width;
      DWORD height;
      unsigned char* dataptr;
};

#endif

