// QR_Encode.h : CQR_Encode
//�����Ǹ��ձ���д��,ԭע����������(����),��������ע��һ��
//�����˶����ĺ��ֵ�֧�� ������΢�޸��˴�������VCƽ̨֮����� (BOOL LPCSTR LPBYTE FALSE TRUE �Ķ��壬ZeroMemory�����)
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

//���־���ȼ�
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// ���ֱ����ַ��������֡���ĸ���ֽڡ��ձ������ַ������ĺ��� 
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3
#define QR_MODE_HANZI		4

// 1~40��40���汾�������з�Ϊ����������д���
#define QR_VRESION_S	0 // 1 ~ 9
#define QR_VRESION_M	1 // 10 ~ 26
#define QR_VRESION_L	2 // 27 ~ 40

#define MAX_ALLCODEWORD	 3706 // �汾Ϊ40ʱ����������
#define MAX_DATACODEWORD 2956 // �汾Ϊ40������ȼ�ΪLʱ����������
#define MAX_CODEBLOCK	  153 // 153�Ƿֿ鷽ʽ�������ε�"��������"
#define MAX_MODULESIZE	  177 // �汾Ϊ40ʱ��ÿ�ߵ�ģ����

//��Ե�հ׿�� 
#define QR_MARGIN	4

/////////////////////////////////////////////////////////////////////////////
//�ֿ�ṹ
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock; // ���ֿ�������		
	int ncAllCodeWord;	//��������
	int ncDataCodeWord;	//��������
} RS_BLOCKINFO, *LPRS_BLOCKINFO;

/////////////////////////////////////////////////////////////////////////////
//��汾��ص���Ϣ
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾
	int ncAllCodeWord; //��������

	// 4�־���ȼ�(0 = L, 1 = M, 2 = Q, 3 = H)�µ�����������
	int ncDataCodeWord[4];

    // ��λͼ�ε�λ�ã���Ӧ�������飬�����ǶԽṹ��ֻ�洢�˵�����
	int ncAlignPoint;	// ����/����������λͼ�εĸ��� 
	int nAlignPoint[6];		// ��λͼ�εĺ�����/�����꣨�����ǶԳƽṹ��

	RS_BLOCKINFO RS_BlockInfo1[4]; // ��(1)(���־���ȼ��µķֿ鷽ʽ1)
	RS_BLOCKINFO RS_BlockInfo2[4]; // ��(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////

class CQR_Encode
{
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// ����ȼ�
	int m_nVersion;		// �汾
	BOOL m_bAutoExtent;	// �Ƿ�֧����չ�ַ���
	int m_nMaskingNo;	// ��ģ��ʽ����001~111

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // 177*177������//��Ÿ��ֹ���ͼ��
    // ÿλ����ͬ����Ϣ
	// bit5:��λ��Ϊ����ͼ��λ
	// bit4:bit5Ϊ1ʱ��1�����λ���е� 0�����λ���޵�
	// bit1:bit5Ϊ0��Ϊ���ݣ���ģ֮ǰ����ʵ����
	// bit0:bit5Ϊ0����ģ�������
    // ����
    //����ͼ��λ�ô� �ڣ�0x30 �ף�0x20
    // ������ �ڣ�0x01  �ף�0x00

private:
	int m_ncDataCodeWordBit;  
	BYTE m_byDataCodeWord[MAX_DATACODEWORD];
	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];
	int m_ncAllCodeWord; 
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; 
	BYTE m_byRSWork[MAX_CODEBLOCK]; // �ܴ���������͵ķֿ�,�������ݺ;�����

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
