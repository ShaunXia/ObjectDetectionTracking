#include <iostream>
using namespace std;
#include <Windows.h>
#include <tchar.h>
#include "SerialPort.h"

CSerialPort::CSerialPort()
{
    TimeOuts = 500;
    xSpeed = 3;
    ySpeed = 15;
    char* s = new char[100];
    cout<<"请输入串口序号："<<endl;
    int n;
    cin>>n;
    sprintf(s, "COM%d\0", n);
    ComID = OpenCom( s, 4800);
    if(ComID)
        cout<<"Open Port "<<s<<" Success"<<endl;
    else
        cout<<"Open Port Fail"<<endl;
};

CSerialPort::~CSerialPort()
{
    CloseCom();
};

CSerialPort::CSerialPort(char* id)
{
    TimeOuts = 500;
    ComID = OpenCom( id, 4800);
    if(ComID)
        cout<<"Open Port Success"<<endl;
    else
        cout<<"Open Port Fail"<<endl;
};

void CSerialPort::c2w(wchar_t *pwstr,const char *str)
{
    if(str)
    {

        size_t nu = strlen(str);

        size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,NULL,0);

        MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,pwstr,(int)n);

        pwstr[n]=0;
    }

}

//////////////////////////////////////////////////////////////////////////
// 功  能: 关闭 COM Port;//
// 返回值：= 0:  关闭成功//
//         = 其它值: 关闭失败//
//////////////////////////////////////////////////////////////////////////
int CSerialPort::CloseCom()
{
    if(ComID > 0)
        if(CloseHandle(ComID))
            return 0;

    return -1;
}

//////////////////////////////////////////////////////////////////////////
// 功  能: 初始化 COM Port//
// 参  数: ComPort  --  串口号//
//         BaudRate --  波特率//
// 返回值：>0 :  打开成功，返回串口的设备句柄//
//         = 其它值:  打开失败//
//////////////////////////////////////////////////////////////////////////
HANDLE CSerialPort::OpenCom(const char *ComPort,int BaudRate)
{
    _DCB FDCB;

    HANDLE ComID = NULL;
    WCHAR* WComPort = new wchar_t[strlen(ComPort)+1];
    c2w(WComPort, ComPort);
    ComID = CreateFile(WComPort,
        GENERIC_READ | GENERIC_WRITE,  // 可读 可写
        NULL,                              // 独占方式
        NULL,
        OPEN_EXISTING,
        NULL,
        NULL);

    if(ComID == INVALID_HANDLE_VALUE)
        return 0;

    if(!GetCommState(ComID,&FDCB))
        return 0;

    TimeOuts = 500;
    FDCB.BaudRate = BaudRate;
    FDCB.ByteSize = 8;            // 8 Bits 数据
    FDCB.StopBits = ONESTOPBIT;   // 一位停止位
    FDCB.Parity = 0;                //缺省无校验

    if(!SetCommState(ComID,&FDCB))
        return 0;

    if(!SetupComm(ComID,500,500))
        return 0;

    return ComID;
}

//////////////////////////////////////////////////////////////////////////
// 功  能: 设置超时//
// 参  数: TimeOut --  超时时间（单位：毫秒）//
//////////////////////////////////////////////////////////////////////////
int CSerialPort::SetTimeOuts(int TimeOut)
{
    TimeOuts = TimeOut;
    return TimeOut;
}

//////////////////////////////////////////////////////////////////////////
// 功  能: 设置校验方式//
// 参  数: Parity --  校验方式//
//         =0  无校验(no)//
//         =1  奇校验(odd)//
//         =2  偶校验(even)//
//         =3  标记校验(mark)//
//         =4  空格校验(space)//
// 返回值：=0     :  成功//
//         =其它值:  失败//
//////////////////////////////////////////////////////////////////////////
int CSerialPort::SetParity(int Parity)
{
    DCB FDCB;
    if(!GetCommState(ComID,&FDCB))
        return -1;

    FDCB.Parity = Parity;   //校验方式

    if(!SetCommState(ComID,&FDCB))
        return -1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////
// 功  能: 从串口读所有字节流//
// 参  数: 无//
// 返回值：> 0:  读取数据大小//
//         = -1: 失败//
//////////////////////////////////////////////////////////////////////////
int CSerialPort::ReadFromCom(char *TempBuf,DWORD ReadSize)
{
    DWORD TempSize;
    DWORD EndTime,ErrorFlag;
    COMSTAT cs;
    BOOL bResult;

    EndTime = GetTickCount() + TimeOuts;
    while(GetTickCount() <= EndTime)
    {
        bResult = ClearCommError(ComID,&ErrorFlag,&cs);
        if(!bResult)
            return 0;

        if(cs.cbInQue < ReadSize)//如果串口数据小于ReadSize
        {
            bResult = ReadFile(ComID,TempBuf,cs.cbInQue,&TempSize,NULL) ;
            if(!bResult)
                return 0;
        }
        else
        {
            bResult = ReadFile(ComID,TempBuf,ReadSize,&TempSize,NULL);
            if(!bResult)
                return 0;
        }

        if(TempSize > 0)
            return TempSize;
    }

    return -1;
}

//////////////////////////////////////////////////////////////////////////
// 功  能: 向串口发送字节流.//
// 参  数: 无//
// 返回值：= 0:  成功//
//         = -1: 失败//
//////////////////////////////////////////////////////////////////////////
BOOL CSerialPort::SendToCom(unsigned char *SendBuf,DWORD SendSize)
{
    DWORD Status;
    BOOL bResult;

    bResult = PurgeComm(ComID,PURGE_TXCLEAR | PURGE_RXCLEAR); // 清除接收队列和发送队列
    if(!bResult)
        return 0;
    bResult = WriteFile(ComID,SendBuf,SendSize,&Status,0);
    if(!bResult)
        return 0;

    return -1;
}

unsigned char* CSerialPort::String2Hex( string order, unsigned char* cOrder)
{
    for (int i = 0,j=0; i < 8; i+=2,j++)
    {
        cOrder[j] = 0;
        if(order[i] >= 'A')
        {
            int temp = 16 * (order[i] - 'A' + 10);
            cOrder[j] += temp;
        }
        else
            cOrder[j] += 16 * (order[i] - '0');

        if(order[i+1] >= 'A')
            cOrder[j] += (order[i+1] - 'A' + 10);
        else
            cOrder[j] += (order[i+1] - '0');
    }
    
    return cOrder;
}

BOOL CSerialPort::Up( int speed)
{
    //string order = "FF010004FF0004";
    string order = "FF010008";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[4] = 0;
    cOrder[5] = speed;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
		return 1;
	}
    return 0;
}

BOOL CSerialPort::Down( int speed)
{
    //string order = "FF010004FF0004";
    string order = "FF010010";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[4] = 0;
    cOrder[5] = speed;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
        return 1;
	}
    return 0;
}

BOOL CSerialPort::Left( int speed)
{
    //string order = "FF010004FF0004";
    string order = "FF010004";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[5] = 0;
    cOrder[4] = speed;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
        return 1;
	}
    return 0;
}

BOOL CSerialPort::Right( int speed)
{
    //string order = "FF010004FF0004";
    string order = "FF010002";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[5] = 0;
    cOrder[4] = speed;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
        return 1;
	}
    return 0;
}

BOOL CSerialPort::Stop()
{
    //string order = "FF010004FF0004";
    string order = "FF010000";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[4] = 0;
    cOrder[5] = 0;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 8;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
        return 1;
	}
    return 0;
}

BOOL CSerialPort::ZoomIn( int scale)
{
    //string order = "FF010004FF0004";
    string order = "FF010040";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[4] = 0;
    cOrder[5] = scale;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
		return 1;
	}
    return 0;
}

BOOL CSerialPort::ZoomOut( int scale)
{
    //string order = "FF010004FF0004";
    string order = "FF010020";

    unsigned char* cOrder = new unsigned char[7];
    String2Hex(order,cOrder);
    cOrder[4] = 0;
    cOrder[5] = scale;

    int sum = 0;
    for (int i = 1; i < 6; ++i)
    {
        sum += cOrder[i];
    }

    cOrder[6] = sum % 256;

    if(SendToCom(cOrder, 7))
	{
		//cout<<"Send Ok"<<endl;
		return 1;
	}
    return 0;
}