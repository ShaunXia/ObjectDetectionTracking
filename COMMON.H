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

// MVSTOP: 停止工作； MVRUN: 卡开始工作； MVPAUSE: 暂停卡的工作； MVQUERYSTATU: 查询卡的当前状态， MVERROR:为错误的状态。
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

	// 控制显示的
	DISP_PRESENCE			= 6,  
	DISP_WHND				= 7,  
	DISP_TOP				= 8,  
	DISP_LEFT				= 9,  
	DISP_HEIGHT				= 10,  
	DISP_WIDTH				= 11,

	// 控制A/D的调节参数
	ADJUST_STANDARD			= 12, 
	ADJUST_SOURCE			= 13,	 
	ADJUST_CHANNEL			= 14, 
	ADJUST_LUMINANCE		= 15, 
	ADJUST_CHROMINANE		= 16, 
	ADJUST_SATURATION		= 17, 
	ADJUST_HUE				= 18,
	ADJUST_CONTRAST			= 19, 

	//支持RGB卡
	ADJUST_R_LUM			= 20, 
	ADJUST_G_LUM			= 21, 
	ADJUST_B_LUM			= 22, 
	ADJUST_R_COARSE			= 23, 
	ADJUST_G_COARSE			= 24, 
	ADJUST_B_COARSE			= 25,

	// 控制板卡的捕获参数
	GRAB_XOFF				= 60, 
	GRAB_YOFF				= 61, 
	GRAB_HEIGHT				= 62, 
	GRAB_WIDTH				= 63, 
	GRAB_IN_HEIGHT			= 64, 
	GRAB_IN_WIDTH			= 65, 
	GRAB_BITDESCRIBE		= 66, 
	GRAB_WHOLEWIDTH			= 67,
				   
	// 控制板卡的工作参数
	WORK_UPDOWN				= 34,  
	WORK_FLIP				= 35, 
	WORK_SKIP				= 36, 
	WORK_SYNC				= 37, 
	WORK_INTERLACE			= 38, 
	WORK_ISBLACK			= 39, 
	WORK_FIELD				= 40,	
	OSD_MODE				= 41,

	//支持V500系列卡
	TENBIT_MODE				= 42, 
	OUTPUT_VIDEO			= 43, 
	FILERSELECT1			= 44, 
	FILERSELECT2			= 45,
    
	// 控制板卡的捕获参数(保留,兼容老版本)
	GARB_XOFF				= 26, 
	GARB_YOFF				= 27, 
	GARB_HEIGHT				= 28, 
	GARB_WIDTH				= 29, 
	GARB_IN_HEIGHT			= 30, 
	GARB_IN_WIDTH			= 31, 
	GARB_BITDESCRIBE		= 32, 
	GARB_WHOLEWIDTH			= 33,


	//shen add 
	//支持卡类型MVBOARD2.h中所有卡
	ADJUST_BACKCOLORKEY		= 200,
	DISP_FLIP				= 201,	
	IMAGE_PROCESS			= 202,
	VIDEO_SINGLE			= 203,
	GET_BOARD_PASS          = 204,
	//20060315
	GRAB_AUTOFIELD          = 205,
	//2007_04_03
	GARB_UVSWAP				= 206,
	//20050407新增
	RESTARTCAPTURE			= 300,
	RESTOPCAPTURE			= 301,
	//20070420新增
	WATCHDOG_ENABLE			= 302,
	WATCHDOG_DISABLE		= 303,
	WATCHDOG_SENDDATA		= 304,
	//20080813新增
	REC_OSDTEXT_ENABLE		= 320,
	REC_OSDTEXT_DISABLE		= 321,
	REC_OSDTIME_ENABLE		= 322,
	REC_OSDTIME_DISABLE		= 323,
	REC_OSDADDTEXT			= 324,

    VIDEO_STANDARD          = 325,

};


// 控制板卡使用的缓存类型, 对应BUFFERTYPE
#define  SYSTEM_MEMORY_DX    0  // 系统内存显示方式, 支持所有的选项,如左右翻转, 该方式下采集不丢帧，显示可能会丢帧;
#define  SYSTEM_MEMORY_GDI   1  // GDI系统内存显示方式, 支持所有的选项, 如左右翻转, 该方式下采集不丢帧, 显示可能会丢帧;
#define  VIDEO_MEMORY        2  // 直接显存显示方式, 只有在显示位数和采集位数相等时采用, 该方式下支持不丢帧显示而采集丢
                                // 帧或不支持采集; 对于M10，RGB10，M20，RGB20型卡不支持所有的选项(如左右翻转)。
#define  RECEDE_NOISES       3  // 对于M10，RGB10，M20，RGB20型卡不支持，而V3型卡为4帧平均方式

// 控制系统的显示工作状态，对应DISP_PRESENCE
#define  SHOW_CLOSE          0  // 显示关闭
#define  SHOW_OPEN           1  // 显示打开

// 控制视频采集标准，对应ADJUST_STANDARD
#define  SIGNAL_PAL          0  // PAL
#define  SIGNAL_NTSC         1  // NTSC
#define  SIGNAL_NONSTANDARD  2  // 对于M20，RGB20
// 控制视频信号的输入源, 对应ADJUST_SOURCE
#define  SVIDEO_IN           1  // SVIDEO输入
#define  COMPOSITE_IN        0  // 复合输入
// 控制视频信号输入源的通道, 对应ADJUST_CHANNEL
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

// 控制视频捕获的格式，对应GARB_BITDESCRIBE
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

// 控制板卡的翻转工作参数，对应WORK_UPDOWN和WORK_FLIP
#define  NON_TURN           0    // 不翻转
#define  TURN               1    // 翻转

// 控制板卡的跳行采集工作参数，对应WORK_SKIP, 即对于隔行信号一帧中偶奇场的存储是按帧方式还是按先偶场后奇场
#define  FLATNESS           0   // 一帧中偶奇场的存储是按偶场后奇场
#define  INTERLUDE          1   // 一帧中偶奇场的存储是按帧方式


// 控制板卡的同步信号的来源, 对应WORK_SYNC
#define  SYN_RED            0   // 红路信号带复合同步;
#define  SYN_GREEN          1   // 绿路信号带复合同步;
#define  SYN_BLUE           2   // 兰路信号带复合同步;
#define  SYN_OUTSIDE        3   // 外同步；
#define  SYN_RESERVE        4   // 保留不使用;
#define  SYN_SEPARATE       5   // 同步信号行场分离;
#define  SYN_INSIDE1        6   // 内同步1
#define  SYN_INSIDE2        7   // 内同步2

// 控制板卡的信号种类, 对应WORK_INTERLACE
#define  LINE_BY_LINE       0   // 逐行
#define  INTERLEAVED        1   // 隔行

// 控制板卡在采集信号时对灰度级的范围, 对应WORK_ISBLACK, 该类型仅对M10，RGB10，M20，RGB20系列卡有效，
#define  BOGUS_COLOR        0   // 伪彩采集
#define  FULL_COLOR         1   // 全灰阶采集。

// 控制板卡在采集信号时场或按帧采集, 对应WORK_FIELD
#define  COLLECTION_FRAME   0   // 按帧采集
#define  COLLECTION_FIELD   1   // 按场采集

// 控制板卡的OSD模式, 对应OSD_MODE。该类型仅对V3系列卡有效，
#define  OSD_NON            0   // 无OSD
#define  OSD_ZERO           1   // 0屏蔽OSD
#define  OSD_ONE            2   // 1屏蔽OSD

typedef struct  _MV_IMAGEINFO_
{
	ULONG  Length;      // 图像的大小，以字节计
	ULONG  nColor;      // 图像的颜色
	ULONG  Heigth;      // 图像的高
	ULONG  Width;       // 图像的宽
	ULONG  SkipPixel;   // 每行跳过的像素
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