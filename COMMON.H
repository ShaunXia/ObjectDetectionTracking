//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Microview Technologies, Inc. 2004. All Rights Reserved.
//
//  Module:    Common.H
//
//  Abstract:  Header file for MVAPI.DLL
//
//	VER:	   5.1.0.0
//
//	Data:      2004.08.11
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _COMMON_H_
#define _COMMON_H_

#include "Windows.h"
#include "MVBOARD1.h"
#include "MVBOARD2.h"

enum RUNOPER
{ 
	MVSTOP		 = 0, 
	MVRUN		 = 1, 
	MVPAUSE		 = 2, 
	MVQUERYSTATU = 3, 
	MVERROR		 = 4 
};

// MVSTOP: ֹͣ������ MVRUN: ����ʼ������ MVPAUSE: ��ͣ���Ĺ����� MVQUERYSTATU: ��ѯ���ĵ�ǰ״̬�� MVERROR:Ϊ�����״̬��
enum VIDEOSOURCE  
{  
	COMPOSITE = 0,  
	SVIDEO	  = 1, 
	R_G_B	  =	2, 
	Y_CR_CB   =	3
};

enum VIDEOSTANDARD
{  
	PAL		= 0, 
	NTSC	= 1, 
	OTHER	= 2/*SCAM*/ 
};

enum RGBVECTOR
{  
	R_LUM	 = 0, 
	G_LUM	 = 1, 
	B_LUM	 = 2, 
	R_COARSE = 3, 
	G_COARSE = 4, 
	B_COARSE = 5  
};

enum MV_PARAMTER
{  
	GET_BOARD_TYPE			= 0,   
	GET_GRAPHICAL_INTERFACE = 1,  
	SET_GARBIMAGEINFO		= 2,  
	SET_DISPIMAGEINFO		= 3, 
	BUFFERTYPE				= 4, 
	DEFAULT_PARAM			= 5,

	// ������ʾ��
	DISP_PRESENCE			= 6,  
	DISP_WHND				= 7,  
	DISP_TOP				= 8,  
	DISP_LEFT				= 9,  
	DISP_HEIGHT				= 10,  
	DISP_WIDTH				= 11,

	// ����A/D�ĵ��ڲ���
	ADJUST_STANDARD			= 12, 
	ADJUST_SOURCE			= 13,	 
	ADJUST_CHANNEL			= 14, 
	ADJUST_LUMINANCE		= 15, 
	ADJUST_CHROMINANE		= 16, 
	ADJUST_SATURATION		= 17, 
	ADJUST_HUE				= 18,
	ADJUST_CONTRAST			= 19, 

	//֧��RGB��
	ADJUST_R_LUM			= 20, 
	ADJUST_G_LUM			= 21, 
	ADJUST_B_LUM			= 22, 
	ADJUST_R_COARSE			= 23, 
	ADJUST_G_COARSE			= 24, 
	ADJUST_B_COARSE			= 25,

	// ���ư忨�Ĳ������
	GRAB_XOFF				= 60, 
	GRAB_YOFF				= 61, 
	GRAB_HEIGHT				= 62, 
	GRAB_WIDTH				= 63, 
	GRAB_IN_HEIGHT			= 64, 
	GRAB_IN_WIDTH			= 65, 
	GRAB_BITDESCRIBE		= 66, 
	GRAB_WHOLEWIDTH			= 67,
				   
	// ���ư忨�Ĺ�������
	WORK_UPDOWN				= 34,  
	WORK_FLIP				= 35, 
	WORK_SKIP				= 36, 
	WORK_SYNC				= 37, 
	WORK_INTERLACE			= 38, 
	WORK_ISBLACK			= 39, 
	WORK_FIELD				= 40,	
	OSD_MODE				= 41,

	//֧��V500ϵ�п�
	TENBIT_MODE				= 42, 
	OUTPUT_VIDEO			= 43, 
	FILERSELECT1			= 44, 
	FILERSELECT2			= 45,
    
	// ���ư忨�Ĳ������(����,�����ϰ汾)
	GARB_XOFF				= 26, 
	GARB_YOFF				= 27, 
	GARB_HEIGHT				= 28, 
	GARB_WIDTH				= 29, 
	GARB_IN_HEIGHT			= 30, 
	GARB_IN_WIDTH			= 31, 
	GARB_BITDESCRIBE		= 32, 
	GARB_WHOLEWIDTH			= 33,


	//shen add 
	//֧�ֿ�����MVBOARD2.h�����п�
	ADJUST_BACKCOLORKEY		= 200,
	DISP_FLIP				= 201,	
	IMAGE_PROCESS			= 202,
	VIDEO_SINGLE			= 203,
	GET_BOARD_PASS          = 204,
	//20060315
	GRAB_AUTOFIELD          = 205,
	//2007_04_03
	GARB_UVSWAP				= 206,
	//20050407����
	RESTARTCAPTURE			= 300,
	RESTOPCAPTURE			= 301,
	//20070420����
	WATCHDOG_ENABLE			= 302,
	WATCHDOG_DISABLE		= 303,
	WATCHDOG_SENDDATA		= 304,
	//20080813����
	REC_OSDTEXT_ENABLE		= 320,
	REC_OSDTEXT_DISABLE		= 321,
	REC_OSDTIME_ENABLE		= 322,
	REC_OSDTIME_DISABLE		= 323,
	REC_OSDADDTEXT			= 324,

    VIDEO_STANDARD          = 325,

};


// ���ư忨ʹ�õĻ�������, ��ӦBUFFERTYPE
#define  SYSTEM_MEMORY_DX    0  // ϵͳ�ڴ���ʾ��ʽ, ֧�����е�ѡ��,�����ҷ�ת, �÷�ʽ�²ɼ�����֡����ʾ���ܻᶪ֡;
#define  SYSTEM_MEMORY_GDI   1  // GDIϵͳ�ڴ���ʾ��ʽ, ֧�����е�ѡ��, �����ҷ�ת, �÷�ʽ�²ɼ�����֡, ��ʾ���ܻᶪ֡;
#define  VIDEO_MEMORY        2  // ֱ���Դ���ʾ��ʽ, ֻ������ʾλ���Ͳɼ�λ�����ʱ����, �÷�ʽ��֧�ֲ���֡��ʾ���ɼ���
                                // ֡��֧�ֲɼ�; ����M10��RGB10��M20��RGB20�Ϳ���֧�����е�ѡ��(�����ҷ�ת)��
#define  RECEDE_NOISES       3  // ����M10��RGB10��M20��RGB20�Ϳ���֧�֣���V3�Ϳ�Ϊ4֡ƽ����ʽ

// ����ϵͳ����ʾ����״̬����ӦDISP_PRESENCE
#define  SHOW_CLOSE          0  // ��ʾ�ر�
#define  SHOW_OPEN           1  // ��ʾ��

// ������Ƶ�ɼ���׼����ӦADJUST_STANDARD
#define  SIGNAL_PAL          0  // PAL
#define  SIGNAL_NTSC         1  // NTSC
#define  SIGNAL_NONSTANDARD  2  // ����M20��RGB20
// ������Ƶ�źŵ�����Դ, ��ӦADJUST_SOURCE
#define  SVIDEO_IN           1  // SVIDEO����
#define  COMPOSITE_IN        0  // ��������
// ������Ƶ�ź�����Դ��ͨ��, ��ӦADJUST_CHANNEL
#define  CHANNEL_0           0
#define  CHANNEL_1           1
#define  CHANNEL_2           2
#define  CHANNEL_3           3
#define  CHANNEL_4           4
#define  CHANNEL_5           5
#define  CHANNEL_6           6
#define  CHANNEL_7           7
#define  CHANNEL_8           8
#define  CHANNEL_9           9

// ������Ƶ����ĸ�ʽ����ӦGARB_BITDESCRIBE
#define  DATA_MONOCHOY8      0
#define  DATA_RGB1555        1
#define  DATA_CO_RGB24       2
#define  DATA_aRGB8888       3
#define  DATA_RGB8332        4
#define  DATA_CO_RGB565      5
#define  DATA_RGB5515        6
#define  DATA_CO_YUV444      7
#define  DATA_CO_YUV422      8
#define  DATA_YUV411         9

// ���ư忨�ķ�ת������������ӦWORK_UPDOWN��WORK_FLIP
#define  NON_TURN           0    // ����ת
#define  TURN               1    // ��ת

// ���ư忨�����вɼ�������������ӦWORK_SKIP, �����ڸ����ź�һ֡��ż�泡�Ĵ洢�ǰ�֡��ʽ���ǰ���ż�����泡
#define  FLATNESS           0   // һ֡��ż�泡�Ĵ洢�ǰ�ż�����泡
#define  INTERLUDE          1   // һ֡��ż�泡�Ĵ洢�ǰ�֡��ʽ


// ���ư忨��ͬ���źŵ���Դ, ��ӦWORK_SYNC
#define  SYN_RED            0   // ��·�źŴ�����ͬ��;
#define  SYN_GREEN          1   // ��·�źŴ�����ͬ��;
#define  SYN_BLUE           2   // ��·�źŴ�����ͬ��;
#define  SYN_OUTSIDE        3   // ��ͬ����
#define  SYN_RESERVE        4   // ������ʹ��;
#define  SYN_SEPARATE       5   // ͬ���ź��г�����;
#define  SYN_INSIDE1        6   // ��ͬ��1
#define  SYN_INSIDE2        7   // ��ͬ��2

// ���ư忨���ź�����, ��ӦWORK_INTERLACE
#define  LINE_BY_LINE       0   // ����
#define  INTERLEAVED        1   // ����

// ���ư忨�ڲɼ��ź�ʱ�ԻҶȼ��ķ�Χ, ��ӦWORK_ISBLACK, �����ͽ���M10��RGB10��M20��RGB20ϵ�п���Ч��
#define  BOGUS_COLOR        0   // α�ʲɼ�
#define  FULL_COLOR         1   // ȫ�ҽײɼ���

// ���ư忨�ڲɼ��ź�ʱ����֡�ɼ�, ��ӦWORK_FIELD
#define  COLLECTION_FRAME   0   // ��֡�ɼ�
#define  COLLECTION_FIELD   1   // �����ɼ�

// ���ư忨��OSDģʽ, ��ӦOSD_MODE�������ͽ���V3ϵ�п���Ч��
#define  OSD_NON            0   // ��OSD
#define  OSD_ZERO           1   // 0����OSD
#define  OSD_ONE            2   // 1����OSD

typedef struct  _MV_IMAGEINFO_
{
	ULONG  Length;      // ͼ��Ĵ�С�����ֽڼ�
	ULONG  nColor;      // ͼ�����ɫ
	ULONG  Heigth;      // ͼ��ĸ�
	ULONG  Width;       // ͼ��Ŀ�
	ULONG  SkipPixel;   // ÿ������������
}MV_IMAGEINFO, *PMV_IMAGEINFO;

enum CALLBACKTYPE{  BEFORE_PROCESS = 0, AFTER_PROCESS = 1, NO_USED = 2 };
typedef BOOL (WINAPI *CALLBACKFUNC)( PVOID pData, PMV_IMAGEINFO pImageInfo, PVOID pUserData, ULONG Index );
typedef VOID (WINAPI *PTRIGGEROUTINE)( ULONG UniquelyID, ULONG Reson, PVOID pContext );
typedef VOID (WINAPI *CONTINUEGARBMECHANISM)( PVOID pData, PMV_IMAGEINFO pImage, ULONG ImageNumber,
											  ULONG wholeLength, PVOID pUserData );

typedef struct  _MV_NOTIFY_
{   
	union
	{
		CONTINUEGARBMECHANISM  pContinueCall;
		PTRIGGEROUTINE         pTirggerCall;
	}u;
	PVOID                  pContext;
}MV_NOTIFY, *PMV_NOTIFY;

#define  B_CHANNEL    0x00000001
#define  G_CHANNEL    0x00000002
#define  R_CHANNEL    0x00000004

typedef struct _MV_RGB_
{   
	HWND  R_hWnd;
    RECT  R_Rect;
	HWND  G_hWnd;
    RECT  G_Rect;
	HWND  B_hWnd;
    RECT  B_Rect;
}MV_RGB, *PMV_RGB;

enum MV_FILETYPE{  RAW = 0, BMP = 1, JPEG = 2 };


enum VIDEOSIGNAL
{ 
	GLLEVEL = 0, 
	DIVIDER	= 1, 
	ISINTERLACE	= 2, 
	XSHIFT	= 3, 
	YSHIFT	= 4, 
	XSIZE	= 5, 
	YSIZE	= 6, 
	VCOR	= 7, 
	VCOG	= 8, 
	LPP		= 9,
	
	LINEFREQENCY = 10, 
	LINETOTAL	 = 11, 
	LINEACTIVETIME	= 12, 
	LINESYNTIME	 = 13, 
	LINESHOULDER = 14,
	
	FRAMENUM	 = 15, 
	FIELDSYNTIME = 16, 
	FIELDTOTAL	 = 17, 
	FIELDSHOULDER = 18, 
	SOURFREQ	 = 19, 
	FREQSUB		 = 20  
};

struct  GDIOPERATION;
typedef GDIOPERATION  *PGDIOPERATION;
typedef VOID (WINAPI *GDIOPERATIONFUNC)( PGDIOPERATION pOper, PVOID pVal1, PVOID pVal2, PVOID pVal3 );
typedef struct GDIOPERATION
{
	PVOID pIs;
	GDIOPERATIONFUNC  SetGDIText;
	GDIOPERATIONFUNC  SetGDITextColor;
	GDIOPERATIONFUNC  SetGDITextFormat;
	GDIOPERATIONFUNC  SetGDITextPosition;
	GDIOPERATIONFUNC  SetGDIGraph;
	GDIOPERATIONFUNC  SetGDIGraphPen;
	GDIOPERATIONFUNC  SetGDICanCalAll;
	GDIOPERATIONFUNC  SetGDICanCalOne;
}GDIOPERATION, *PGDIOPERATION;

#endif