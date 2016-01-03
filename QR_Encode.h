// QR_Encode.h : CQR_Encode
//好像是个日本人写的,原注释疑是日语(乱码),试着中文注释一下
//增加了对中文汉字的支持 ，另稍微修改了代码以在VC平台之外可用 (BOOL LPCSTR LPBYTE FALSE TRUE 的定义，ZeroMemory的替代)
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
#define AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
#include "common.h"
typedef int BOOL;
typedef const char* LPCSTR;
typedef unsigned char* LPBYTE;
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define FALSE false
#define TRUE true

//四种纠错等级
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// 多种编码字符集：数字、字母、字节、日本汉字字符、中文汉字 
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3
#define QR_MODE_HANZI		4

// 1~40共40个版本，程序中分为三类情况进行处理。
#define QR_VRESION_S	0 // 1 ~ 9
#define QR_VRESION_M	1 // 10 ~ 26
#define QR_VRESION_L	2 // 27 ~ 40

#define MAX_ALLCODEWORD	 3706 // 版本为40时的码字总数
#define MAX_DATACODEWORD 2956 // 版本为40，纠错等级为L时，数据码数
#define MAX_CODEBLOCK	  153 // 153是分块方式中最大块形的"码字总数"
#define MAX_MODULESIZE	  177 // 版本为40时的每边的模块数

//边缘空白宽度 
#define QR_MARGIN	4

/////////////////////////////////////////////////////////////////////////////
//分块结构
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock; // 此种块区数量		
	int ncAllCodeWord;	//码字总数
	int ncDataCodeWord;	//数据码数
} RS_BLOCKINFO, *LPRS_BLOCKINFO;

/////////////////////////////////////////////////////////////////////////////
//与版本相关的信息
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本
	int ncAllCodeWord; //码字总数

	// 4种纠错等级(0 = L, 1 = M, 2 = Q, 3 = H)下的数据码容量
	int ncDataCodeWord[4];

    // 定位图形的位置，本应是坐标组，由于是对结构，只存储了单坐标
	int ncAlignPoint;	// 横向/纵向看来，定位图形的个数 
	int nAlignPoint[6];		// 定位图形的横坐标/纵坐标（由于是对称结构）

	RS_BLOCKINFO RS_BlockInfo1[4]; // 块(1)(四种纠错等级下的分块方式1)
	RS_BLOCKINFO RS_BlockInfo2[4]; // 块(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////

class CQR_Encode
{
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// 纠错等级
	int m_nVersion;		// 版本
	BOOL m_bAutoExtent;	// 是否支持扩展字符集
	int m_nMaskingNo;	// 掩模方式代号001~111

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // 177*177的数组//存放各种功能图形
    // 每位代表不同的信息
	// bit5:此位置为功能图形位
	// bit4:bit5为1时，1代表此位置有点 0代表此位置无点
	// bit1:bit5为0（为数据）掩模之前的真实数据
	// bit0:bit5为0，掩模后的数据
    // 所以
    //功能图形位置处 黑：0x30 白：0x20
    // 数据区 黑：0x01  白：0x00

private:
	int m_ncDataCodeWordBit;  
	BYTE m_byDataCodeWord[MAX_DATACODEWORD];
	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];
	int m_ncAllCodeWord; 
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; 
	BYTE m_byRSWork[MAX_CODEBLOCK]; // 能存下最大类型的分块,包括数据和纠错码

public:
	BOOL EncodeData(int nLevel, int nVersion, BOOL bAutoExtent, int nMaskingNo, LPCSTR lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, LPCSTR lpsSource, int ncLength);
	BOOL EncodeSourceData(LPCSTR lpsSource, int ncLength, int nVerGroup);
	int GetBitLength(BYTE nMode, int ncData, int nVerGroup);
	int SetBitStream(int nIndex, WORD wData, int ncData);
	BOOL IsNumeralData(unsigned char c);
	BOOL IsAlphabetData(unsigned char c);
	BOOL IsKanjiData(unsigned char c1, unsigned char c2);
	BOOL IsHanziData(unsigned char c1, unsigned char c2);
	BYTE AlphabetToBinaly(unsigned char c);
	WORD KanjiToBinaly(WORD wc);
	WORD HanziToBinaly(WORD wc);
	void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

private:
	void FormatModule();
	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
