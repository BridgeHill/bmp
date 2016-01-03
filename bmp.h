#ifndef BMP_H
#define BMP_H

template <class T1,class T2>
int CompareBmpSize(const T1 &v1,const T2 &v2)
{
	if((v1.width)*(v1.height) > (v2.width)*(v2.height))
		return 1;
	if((v1.width)*(v1.height) < (v2.width)*(v2.height))	
		return -1;
	return 0;
}

template <class T>
int BmpType(const T &v1)
{
	return v1.bit_count;
}

#endif
