#pragma once
#include <iostream>
using namespace std;
#include <Windows.h>
#include <tchar.h>

class CSerialPort
{
private:
    HANDLE ComID;
    int TimeOuts;

    int xSpeed;
    int ySpeed;

    void c2w(wchar_t *pwstr,const char *str);

    int ReadFromCom(char *TempBuf,DWORD ReadSize);

    BOOL SendToCom(unsigned char *SendBuf,DWORD SendSize);

    unsigned char* String2Hex( string order, unsigned char* cOrder);

public:
    CSerialPort();
    CSerialPort(char *);
    ~CSerialPort();

    HANDLE OpenCom(const char *ComPort,int BaudRate);

    int CloseCom();

    int SetTimeOuts(int TimeOut);

    int SetParity(int Parity);


    BOOL Up(int speed);
    BOOL Down(int speed);
    BOOL Left(int speed);
    BOOL Right(int speed);
    BOOL Stop();
    BOOL ZoomOut(int scale);
    BOOL ZoomIn(int scale);
};

//int main()
//{
//    string order = "FF01000800FF08";
//    
//    HANDLE ComId = OpenCom( "COM4", 4800);
//    SetTimeOuts(TimeOuts);
//    
//    cout<<ComId<<endl;
//    
//    while(1)
//    {
//        char o;
//        cin>>o;
//        int s;
//        switch (o)
//        {
//        case 's':
//            Stop(ComId);
//			cout<<"stop"<<endl;
//            break;
//        case 'u':
//            cin>>s;
//            Up(ComId, s);
//			cout<<"up"<<endl;
//            break;
//        case 'd':
//            cin>>s;
//            Down(ComId, s);
//			cout<<"down"<<endl;
//            break;
//        case 'l':
//            cin>>s;
//            Left(ComId, s);
//			cout<<"left"<<endl;
//        break;
//        case 'r':
//            cin>>s;
//            Right(ComId, s);
//			cout<<"right"<<endl;
//        break;
//        default:
//            break;
//        }
//
//    }
//    return 0;
//}

