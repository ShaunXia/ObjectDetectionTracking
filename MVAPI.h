#ifndef  __MVAPI__
#define  __MVAPI__

#include "Common.h"

#ifdef __cplusplus
#define MVAPI extern "C" __declspec (dllexport)
#else
#define MVAPI __declspec (dllexport)
#endif

class CLabView
{
private:
	HANDLE  m_fHandle;
	ULONG   m_DataPoint;

	HANDLE  m_BmpThread;
	BOOL    m_Exit;
	BOOL    m_bBusy;
	static DWORD WINAPI Bmp_Thread( CLabView* lp );

public:
	ULONG   m_Width;
	ULONG   m_Height;
	ULONG   m_nColor;
	ULONG   m_SkipPixel;
	PUCHAR  m_pMiddle;

	ULONG   m_BmpLength;
	ULONG   m_BmpLineByte;
	ULONG   m_RawLineByte;
	ULONG   m_RawSkipByte;

	CLabView( ULONG Width, ULONG Heigth, ULONG nColor, ULONG SkipPixel );
	~CLabView();
	static BOOL  WINAPI LabViewCallBack( PVOID pData, PMV_IMAGEINFO pImageInfo, CLabView* lp, ULONG Index );
};

// 错误提示
MVAPI DWORD WINAPI MV_GetLastError( BOOL bDisplayErrorStyring );

// 保存pImageData中图像到MV_FILETYPE指定类型的文件
MVAPI BOOL WINAPI MV_SaveFile( PUCHAR FileName, MV_FILETYPE FileType, PVOID pImageData, PMV_IMAGEINFO pImage,
							   ULONG ImageTotal, BOOL IsUpDown, BOOL ColororNot, ULONG Quality, BOOL m_bRGB15=TRUE);
MVAPI BOOL WINAPI MV_SaveFilePro( PUCHAR FileName, MV_FILETYPE FileType, PVOID pImageData, PMV_IMAGEINFO pImage,
							   ULONG ImageTotal, BOOL IsUpDown, BOOL ColororNot, ULONG Quality,BOOL m_bRGB15=TRUE);

// 得到主机中插的微视的卡数
MVAPI DWORD   WINAPI MV_GetDeviceNumber();

// 创建设备
MVAPI HANDLE  WINAPI MV_OpenDevice( DWORD Index, BOOL bRelese );

// 删除设备
MVAPI VOID    WINAPI MV_CloseDevice( HANDLE hDevice );

// 操纵设备
MVAPI RUNOPER WINAPI MV_OperateDevice( HANDLE hDevice, RUNOPER Oper );

// 设置设备的参数
MVAPI BOOL    WINAPI MV_SetDeviceParameter( HANDLE hDevice, MV_PARAMTER Oper, DWORD Val );

// 得到设备的参数
MVAPI LONG    WINAPI MV_GetDeviceParameter( HANDLE hDevice, MV_PARAMTER Oper );

MVAPI BOOL    WINAPI MV_SaveDeviceParam( HANDLE hDevice );
MVAPI BOOL    WINAPI MV_ResetDeviceParam( HANDLE hDevice );

// 捕获一帧
MVAPI PVOID WINAPI MV_CaptureSingle( HANDLE hDevice, BOOL IsProcess, PVOID pInBuff, ULONG BuffLen, PMV_IMAGEINFO pInfo );

// 设置设备的回调
MVAPI BOOL    WINAPI MV_SetCallBack( HANDLE hDevice, CALLBACKFUNC pCallBack, PVOID pUserData, CALLBACKTYPE CallType );

// 输出控制
MVAPI BOOL    WINAPI MV_SetOutputState( HANDLE hDevice, ULONG Index, ULONG HorL );

//输入状态读取
MVAPI ULONG WINAPI MV_GetInputState( HANDLE hDevice, ULONG Index );

// 输入触发控制
MVAPI BOOL  WINAPI MV_SetInputCallBack( HANDLE hDevice, ULONG Index, ULONG UniquelyID, PTRIGGEROUTINE pTirggerCall, PVOID pContext );

// 创建自动帧测
MVAPI BOOL    WINAPI MV_TestSignal( HANDLE hDevice, DWORD XSize, DWORD YSize );

// 得到信号的某一个参数
MVAPI DWORD   WINAPI MV_GetSignalParam( HANDLE hDevice, VIDEOSIGNAL Signal, float *FloatVal, DWORD *IntVal );

// 保存自动帧测的参数到Ini
MVAPI BOOL    WINAPI MV_SaveSignalParamToIni( HANDLE hDevice );

MVAPI BOOL    WINAPI MV_SplitRGB( HANDLE hDevice, PMV_RGB pRGB, ULONG DispType, ULONG DispPolicy, ULONG CallBackPolicy );

// 按OsdMode模式使能OSD(掩码)功能:
MVAPI BOOL   WINAPI MV_SetMaskFunction( HANDLE hDevice, ULONG OsdMode );
// 将OSD图案发送到设备
MVAPI BOOL   WINAPI MV_SetMaskBit( HANDLE hDevice, RECT MaskArea, LPBYTE pBitPattern );
MVAPI LPBYTE WINAPI MV_MakeMaskBit( HANDLE hDevice, HWND hWnd, RECT Area, COLORREF Color );

// 对设备分配大帧存
MVAPI BOOL   WINAPI MV_AllocSequenceFrameMemory( HANDLE hDevice, ULONG Action, DWORD Number, CALLBACKTYPE MemoryType );
// 对设备释放大帧存
MVAPI BOOL   WINAPI MV_FreeSequenceFrameMemory( HANDLE hDevice );
// 对大帧存开始连续捕获
MVAPI BOOL WINAPI MV_StartSequenceCapture( HANDLE hDevice, CONTINUEGARBMECHANISM pContinueCall, PVOID pContext );
// 对大帧存停止连续捕获
MVAPI LONG   WINAPI MV_StopSequenceCapture( HANDLE hDevice );
// 根据FrameNo返回帧号地址和帧属性
MVAPI PVOID WINAPI MV_GetSequenceFrameAddress( HANDLE hDevice, ULONG FrameNo, PMV_IMAGEINFO pProperty );

MVAPI ULONG WINAPI MV_ReadPixel( PMV_IMAGEINFO pProperty, PVOID pImageData, PPOINT Point, PBYTE pVal );
MVAPI VOID  WINAPI MV_WritePixel( PMV_IMAGEINFO pProperty, PVOID pImageData, PPOINT Point, PBYTE pVal );
MVAPI ULONG WINAPI MV_ReadLine( PMV_IMAGEINFO pProperty, PVOID pImageData, ULONG  nLine, PBYTE pVal );
MVAPI VOID  WINAPI MV_WriteLine( PMV_IMAGEINFO pProperty, PVOID pImageData, ULONG  nLine, PBYTE pVal );
MVAPI ULONG WINAPI MV_ReadArea( PMV_IMAGEINFO pProperty, PVOID pImageData, PRECT  pRect, PBYTE pVal );
MVAPI VOID  WINAPI MV_WriteArea( PMV_IMAGEINFO pProperty, PVOID pImageData, PRECT  pRect, PBYTE pVal );

MVAPI BOOL WINAPI I2CWrite( HANDLE hDevice, ULONG SubAdd, UCHAR buff, BOOL bPort );
MVAPI BOOL WINAPI I2CRead( HANDLE hDevice, ULONG SubAdd, PUCHAR pBuff, BOOL bPort );

MVAPI RUNOPER WINAPI MV_LabView_OperateDevice( HANDLE hDevice, RUNOPER Oper );
MVAPI PVOID WINAPI MV_LabView_GetBuffer( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetLength( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetnColor( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetHeigth( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetWidth( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetLineSkipPixel( HANDLE hDevice );

MVAPI HANDLE WINAPI MV_CreateAvi( char* FileName, PMV_IMAGEINFO pInfo, ULONG dwRate );
MVAPI VOID   WINAPI MV_WriteAvi( HANDLE hAvi, PUCHAR pBuffer, PMV_IMAGEINFO pInfo, LONG Index );
MVAPI VOID   WINAPI MV_CloseAvi( HANDLE hAvi );

MVAPI BOOL WINAPI MV_AmplifyImage(BYTE* pInputImage, long lWidth, long lHeight, BYTE* pOutputImage,int Bits);
MVAPI BOOL WINAPI MV_RGB16TORGB24(BYTE* pRGB16Buf, long lWidth, long lHeight, BYTE* pRGB24Buf,BOOL RGB1516);

#endif