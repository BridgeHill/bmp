#include <ios>
#include <iostream>

#include "bmpinfo.h"
using namespace std;

bmpinfo::bmpinfo()
{
    type = 0x4D42;
    file_size = 54;
    reserved = 0;
    offset = 0x36;
    header_info_size = 0x28;
    width = 0;
    height = 0;
    planes = 1;
    bit_count = 32;
    compression = 0;
    image_size = 0;
    xpels_per_meter = 0;
    ypels_per_meter = 0;
    color_used = 0;
    color_important =0;
}

bmpinfo::bmpinfo(unsigned int w,unsigned int h)
{
    type = 0x4d42;
//    file_size = ;
    reserved = 0;
//    offset = ;
    header_info_size =0x28;
    width = w;
    height = h;
    planes = 0x01;
//    bit_count = ;
    compression = 0;
//    image_size = 0;
    xpels_per_meter = 0;
    ypels_per_meter = 0;
    color_used = 0;
    color_important = 0;
}

//¿½±´¹¹Ôìº¯Êý
bmpinfo::bmpinfo(const bmpinfo& info)
{
    type = info.type;
    file_size = info.file_size;
    reserved = info.reserved;
    offset = info.offset;
    header_info_size = info.header_info_size;
    width = info.width;
    height = info.height;
    planes = info.planes;
    bit_count = info.bit_count;
    compression = info.compression;
    image_size = info.image_size;
    xpels_per_meter = info.xpels_per_meter;
    ypels_per_meter = info.ypels_per_meter;
    color_used = info.color_used;
    color_important = info.color_important;
}

bmpinfo::~bmpinfo()
{
    cout << "~bmpinfo()" << endl;
}

int bmpinfo::printinfo()
{
    cout << "type" << ":" << type << endl;
    cout << "file_size" << ":" << file_size <<endl;
    cout << "reserved" << ":" << reserved <<endl;
    cout << "offset" << ":" << offset <<endl;
    cout << "header_info_size" << ":" << header_info_size <<endl;
    cout << "width" << ":" << width <<endl;
    cout << "height" << ":" << height <<endl;
    cout << "planes" << ":" << planes <<endl;
    cout << "bit_count" << ":" << bit_count <<endl;
    cout << "compression" << ":" << compression <<endl;
    cout << "image_size" << ":" << image_size <<endl;
    cout << "xpels_per_meter" << ":" << xpels_per_meter <<endl;
    cout << "ypels_per_meter" << ":" << ypels_per_meter <<endl;
    cout << "color_used" << ":" << color_used <<endl;
    cout << "color_important" << ":" << color_important <<endl;
    cout << "========================================" << endl;
    return 0;
}
