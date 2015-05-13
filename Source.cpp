#include <iostream>
#include <Windows.h>
#include "MVAPI.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CompressiveTracker.h"
#include "SerialPort.h"
#include "SpeedControl.h"
#include <math.h>
#include <time.h>
#include "FgbgGMG.h"
using namespace cv;

#define WIDTH 768
#define HEIGHT 576
//���ҿ���·��

CSpeedControl sc;
CompressiveTracker ct;
CSerialPort sp;
FgbgGMG fg;
bool drawing_box = false;
bool gotBB = false;	// got tracking box or not
Rect box;
bool isMoving = false;
time_t sClock, eClock;


class CView 
{
public:
	//void init(HANDLE BoardNo,DWORD BoardType);
	HANDLE init();
};

//////////////�ص�����//////////////////////////////////////////////////////////////////////
//�ص�ִ�к�������
BOOL CALLBACK CALLBACKFUNCT(PVOID pData,PMV_IMAGEINFO pImageInfo,PVOID pUserData,ULONG Index)
{
	/*������óɳ��ɼ���Index=0ʱpDataΪż�����ݣ�=1ʱpDataΪ�泡���ݣ����ΪP�Ʋɼ�1����50������
	���ΪN�Ʋɼ�1����60�����ݣ�ʹ�ó��ɼ��������ͼ����Ӱ����
	����֡����MV_AmplifyImage()��ʹ�����ڻص���ʹ�������� ʹCPUռ�÷ǳ�����ֻ�ʺ����ڵ���Ƶ�ʵ͵�ʱ�����豣��һ֡ͼ��ǰ��MV_CaptureSingle�õ���һ����������һ֡����
	�����Ҫ��ÿһ��������֡����Ҫ����д����֡����*/
	//printf("\n\n\nCALLBACKFUNCT~\n");
	return true;
}
HANDLE CView::init()
{
	DWORD nBdNum=MV_GetDeviceNumber();
	printf("�ҵ��ɼ���������%d\n",nBdNum);
//	nBdNum=0;
	//HWND hwnd=GetSafeHwnd();
	if(nBdNum<=0)
	{
		MessageBox(NULL, (LPCWSTR)L"δ�ҵ��豸,����忨������װ�Ƿ���ȷ!", (LPCWSTR)L"����!",MB_OK);
        return NULL;
	}

	HANDLE CurDevice;
	CurDevice=MV_OpenDevice( 0, TRUE );//ÿ�������Ӧһ��Ƶͨ����֮��ͨ���þ������ͨ��

	//����ͨ������
///////////�ɼ�����/////////////////////////////////////////////////////////////////
	MV_SetDeviceParameter( CurDevice,ADJUST_STANDARD,PAL);//����������PALΪPa�ƣ�NTSCΪN��
 	MV_SetDeviceParameter( CurDevice,ADJUST_SOURCE,COMPOSITE_IN);//��������

	MV_SetDeviceParameter( CurDevice, GARB_IN_HEIGHT, HEIGHT);//ͨ������߶�
	MV_SetDeviceParameter( CurDevice, GARB_IN_WIDTH, WIDTH );//ͨ��������
	MV_SetDeviceParameter( CurDevice, GARB_HEIGHT, HEIGHT);//��ͨ���в���ĸ߶�
	MV_SetDeviceParameter( CurDevice, GARB_WIDTH, WIDTH  );//��ͨ���в���Ŀ��
	MV_SetDeviceParameter( CurDevice, GRAB_BITDESCRIBE, DATA_CO_RGB24);//����������ΪRGB24Bit�ɼ�
	MV_SetDeviceParameter( CurDevice, WORK_FIELD, COLLECTION_FRAME);//COLLECTION_FRAME֡�ɼ���COLLECTION_FIELDΪ���ɼ�
/////////////////////////////////////////////////////////////////////////////////////

////////��ʾ����//////////////////////////////////////////////////////////////////////
	MV_SetDeviceParameter(CurDevice,DISP_TOP,0);//�����Ͻ���ʼ��ʼ
	MV_SetDeviceParameter(CurDevice,DISP_LEFT,0);
	MV_SetDeviceParameter( CurDevice, DISP_HEIGHT, HEIGHT );//��ʾ�ĸ߶�
 	MV_SetDeviceParameter( CurDevice, DISP_WIDTH, WIDTH  );//��ʾ�Ŀ��
	// MV_SetDeviceParameter(CurDevice, DISP_WHND,(DWORD)hwnd);//hwnd������ʾ�Ŀؼ����
    MV_SetDeviceParameter(CurDevice,DISP_PRESENCE,SHOW_CLOSE);//����������SHOW_OPEN����ʾ��SHOW_CLOSEΪֻ�ɼ�����ʾ����Ҫ���õ���ͼ���Լ�д��ʾ����,һ���ڻص�����������ʾ
	MV_SetDeviceParameter(CurDevice, BUFFERTYPE, SYSTEM_MEMORY_GDI); //GDI��ʾ
	MV_SetDeviceParameter(CurDevice, WORK_UPDOWN, NON_TURN);//NON_TURN����ת��TURN���ҷ�ת
	
	//�ص����õ���,���ڿ�ʼ�ɼ�ǰ����
	MV_SetCallBack(CurDevice,CALLBACKFUNCT,this,BEFORE_PROCESS);
	//////////////////////////////////////////////////////////////////////////////////////////////
	//�������������ÿ��ͨ����ʼ����
	printf("�ص����õ���,���ڿ�ʼ�ɼ�ǰ����~\%dn",nBdNum);
	MV_OperateDevice(CurDevice,MVRUN);
	
    return CurDevice;
}

bool MoveToCenter(Rect& pos, CSerialPort& sp)
{
    int x = pos.x + pos.width / 2, y = pos.y + pos.height/2;
    x = WIDTH/2 - x;
    y = HEIGHT/2 - y;

    if(abs(x) <= 50 && abs(y) <= 25 && isMoving)
    {
        sp.Stop();
        isMoving = false;
        return true;
    }
    isMoving = true;
    if(abs(x) > abs(y))
    {
        if(x>0)
        {
            if(x>300)
            {
                sp.Left(45);   
            }
            else if(x>250)
            {
                sp.Left(40);
            }
            else if(x>200)
            {
                sp.Left(30);
            }
            else if(x>100)
            {
                sp.Left(15);
            }
            else if(x>50)
            {
                sp.Left(10);
            }
        }
        else
        {
            if(x<-300)
            {
                sp.Right(45);   
            }
            else if(x<-250)
            {
                sp.Right(40);
            }
            else if(x<-200)
            {
                sp.Right(30);
            }
            else if(x<-100)
            {
                sp.Right(15);
            }
            else if(x<-50)
            {
                sp.Right(10);
            }
        }
    }
    else
    {
        if(y>0)
        {
            if(y>200)
                sp.Up(45);
            else if(y>150)
                sp.Up(35);
            else if(y>100)
                sp.Up(20);
            else if(y>50)
                sp.Up(10);
            else
                sp.Up(5);
        }
        else
        {
            if(y<-200)
                sp.Down(45);
            else if(y<-150)
                sp.Down(35);
            else if(y<-100)
                sp.Down(20);
            else if(y<-50)
                sp.Down(10);
            else
                sp.Down(5);
        }
    }
    return false;
}

// tracking box mouse callback
void mouseHandler(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if( box.height < 0 )
		{
			box.y += box.height;
			box.height *= -1;
		}
		gotBB = true;
		break;
	default:
		break;
	}
}

void runFGBG(HANDLE &CurDevice, MV_IMAGEINFO &info)
{
    BYTE *DATA=new BYTE[WIDTH*HEIGHT*3];
    int i = 50;
    Mat frame;
    char t;
    while(i--)
    {
        PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	    memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������
	    IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	    cvSetData(img,DATA,WIDTH*3);
	    frame = Mat(img,0);

        box = fg.readFrame(frame);

        imshow("Tracking",frame);

        t = cvWaitKey(33);
    }
    while(1)
    {
        PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	    memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������
	    IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	    cvSetData(img,DATA,WIDTH*3);
	    frame = Mat(img,0);

        /*for (int i=0; i<10; i++)
            for (int j=0; j<frame.rows; j++)
            {
                frame.col(i) = 0;
                frame.row(j) = 0;
            }*/

        box = fg.readFrame(frame);

        imshow("Tracking",frame);
        t = cvWaitKey(33);
        if(t == 'q') return;
        float x = 1.0 * box.width/WIDTH, y =1.0 * box.height/HEIGHT;
        if ((y<=0.8 || x<=0.7)
            && (y>=0.15 || x>=0.5))
			break;

    }
    delete(DATA);
}

void controlMove(HANDLE &CurDevice, MV_IMAGEINFO &info)
{
    BYTE *DATA=new BYTE[WIDTH*HEIGHT*3];
    int i = 30;
    Mat frame;
    char t;
    while(1)
    {
        PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	    memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������
	    IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	    cvSetData(img,DATA,WIDTH*3);
	    frame = Mat(img,0);
        imshow("Tracking",frame);
        t = cvWaitKey(33);
        if(t == 'b')
            break;
        switch (t)
        {
        case 'w':
            sp.Up(63);
            break;
        case 's':
            sp.Down(63);
            break;
        case 'a':
            sp.Left(15);
            break;
        case 'd':
            sp.Right(15);
            break;
        case 'f':
            sp.ZoomIn(15);
            break;
        case 'g':
            sp.ZoomOut(15);
            break;
        case 'q':
            sp.Stop();
            break;
        default:
            break;
        }
    }
}

void runMouseCatch(HANDLE &CurDevice, MV_IMAGEINFO &info)
{
    //�ֶ����BOX
    ////////////////////////////////////////////////////////////////////////////////////////////

    BYTE *DATA=new BYTE[WIDTH*HEIGHT*3];
    Mat frame;
    
    setMouseCallback("Tracking", mouseHandler, NULL);
    while(!gotBB)
	{
    PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	    memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������
	    IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	    cvSetData(img,DATA,WIDTH*3);
	    frame = Mat(img,0);

		rectangle(frame, box, Scalar(0,0,255));
		imshow("Tracking", frame);
		if (cvWaitKey(33) == 'q') {	return ; }
	}
    setMouseCallback("Tracking", NULL, NULL);
    delete(DATA);
}

void MainLoop(HANDLE CurDevice)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
	////////�ɼ�һ֡���ڴ�///////////////////////////////////////////////////////////////////////////
    MV_IMAGEINFO info;
	BYTE *DATA=new BYTE[WIDTH*HEIGHT*3];
	MV_SetDeviceParameter( CurDevice, SET_GARBIMAGEINFO, (DWORD)&info );//��ȡͼ���ʽ
    char t;
    Mat grayFrame;
    Mat frame;
    while(1)
    {
        {
            PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	        memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������
	    

	        IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	        cvSetData(img,DATA,WIDTH*3);
	        frame = Mat(img,0);
            imshow("yihihihi",frame);
            imshow("Tracking",frame);
        }

        controlMove(CurDevice, info);
        runFGBG(CurDevice, info);
        //runMouseCatch(CurDevice, info);
        printf("Initial Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);

        cvtColor( frame, grayFrame,  CV_RGB2GRAY);
        ct.init(grayFrame, box);
        rectangle(frame, box, Scalar(0,0,255));
	    imshow("Tracking",frame);
        //while(1)
        //{
	       // PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	       // memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������

	       // IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	       // cvSetData(img,DATA,WIDTH*3);
	       // frame = Mat(img,0);
        //    //box = fg.readFrame(frame);
        //    cvtColor(frame, grayFrame, CV_RGB2GRAY);

        //    ct.processFrame(grayFrame, box);
	       // // Draw Points
	       // rectangle(frame, box, Scalar(0,0,255));

	       // imshow("Tracking",frame);
        //    if(MoveToCenter(box,sp))
        //        break;
	       // if('q' == (t = waitKey(33)))
        //        break;
        //    if('\\' == t)
        //        return;
        //}
        sp.Up(5);
        sc.init(box);
        isMoving = true;
        while(1)
        {
	        PVOID ptr = MV_CaptureSingle( CurDevice, FALSE, NULL, 0, &info );//���ͼ������ָ��ptr
	        memcpy(DATA,ptr,WIDTH*HEIGHT*3);//DATA���鼴Ϊ��Ҫ������

	        IplImage *img= cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	        cvSetData(img,DATA,WIDTH*3);
	        frame = Mat(img,0);
            //box = fg.readFrame(frame);
            cvtColor(frame, grayFrame, CV_RGB2GRAY);
            ct.processFrame(grayFrame, box);

            int way = sc.calculate(box);
            if(way == 0)
            {
                if(isMoving)
                {
                    sp.Stop();
                    cout<<"stop"<<endl;
                    isMoving = false;
                }
            }
            else
            {
                isMoving = true;
                switch (way)
                {
                    case 1:
                        sp.Right(sc.getXSpeed());
                        cout<<"r"<<endl;
                        break;
                    case 2:
                        sp.Up(sc.getYSpeed());
                        cout<<"u"<<endl;
                        break;
                    case -1:
                        sp.Left(sc.getXSpeed());
                        cout<<"l"<<endl;
                        break;
                    case -2:
                        cout<<"d"<<endl;
                        sp.Down(sc.getYSpeed());
                        break;
                    default:
                        break;
                }
            }
            char* sss = new char [200];
            sprintf(sss,"X: %d, Y: %d\n",sc.getXSpeed(),sc.getYSpeed());
	        // Draw Points
	        //rectangle(frame, box, Scalar(0,0,255));
            //putText(frame,sss,Point(100,300),0,1,Scalar(255,0,0));
	        imshow("Tracking",frame);
            rectangle(frame, box, Scalar(0,0,255));
            imshow("yihihihi",frame);
	        if('q' == (t = waitKey(33)))
                break;
            if('\\' == t)
                return;
        }
    }
}

void CloseDevice(HANDLE CurDevice)
{
    MV_OperateDevice(CurDevice,MVSTOP);		//ֹͣ��ǰ�忨�Ĳɼ�����ʾ����
	MV_CloseDevice(CurDevice);	//�ͷŰ忨��Դ
}
#include <Windows.h>
#include <time.h>
#include <iostream>
using namespace std;
int main()

{
	CView pw;
	HANDLE device = pw.init();
    if(device == NULL)
    {
        system("pause");
        return 0;
    }
    MainLoop(device);
    CloseDevice(device); 
}
