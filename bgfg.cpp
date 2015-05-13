/*
	ͼ��Աȣ�GMG�㷨��
*/

#include <iostream>
#include "FgbgGMG.h"
using namespace std;

bool FgbgGMG::getDiagram(Mat & img, int * & drag)
{
    int length = img.cols * img.rows * img.channels();
    uchar * data = img.ptr<uchar>(0);
    for (int i=0; i< length; i++)
        drag[i]=*data ;
    return 0;
}
Rect FgbgGMG::readFrame(Mat frame)
{
	Rect aRect;
	if (frame.empty()) return aRect;
	(*fgbg)(frame, fgmask);
	//uchar * data = fgmask.ptr<uchar>(0);
	Mat fgmask_gray,fgmask_bin;
	Mat tmp = fgmask;

	morphologyEx(tmp,fgmask,MORPH_OPEN,Mat(3,3,CV_8U),Point(-1,-1),2);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours( tmp, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	if (contours.size()>0)
	{
		float maxArea = 0.0;
		int num = 0;
		for(int i = 0;i < contours.size();i++)
		{
			//��ȡ��ǰ�������
			double area = fabs(contourArea(contours[i]));

			//cout << "Area: " << area << endl;
			if (area>maxArea)
			{
				maxArea = area;
				num = i;
			}
		}

		aRect = boundingRect(contours[num]);

	}

	imshow("�������֮��",tmp);

	waitKey(1);

	return aRect;
}

FgbgGMG::FgbgGMG()
{
	initModule_video();
	setUseOptimized(true);
	setNumThreads(8);

	fgbg = Algorithm::create<BackgroundSubtractorGMG>("BackgroundSubtractor.GMG");

	if (fgbg.empty())
		std::cerr << "Failed to create BackgroundSubtractor.GMG Algorithm." << std::endl;
	fgbg->set("initializationFrames", 30);
	fgbg->set("decisionThreshold", 0.99);

	//fgbg->set("maxFeatures", 255);  //������ֵ��Χ֮һ�� max:256,Խ��Խ�á�
	//fgbg->set("learningRate", 0.5);   //����ѧϰ�ʣ�0.1~0.2�á�0.9������кܶ��ӵ㣬����Ҳ����׼ȷһЩ
}

FgbgGMG::FgbgGMG(int initFrames, float decisionThreshold)
{
    initModule_video();
    setUseOptimized(true); 
    setNumThreads(8);

    fgbg = Algorithm::create<BackgroundSubtractorGMG>("BackgroundSubtractor.GMG");

    if (fgbg.empty())
        std::cerr << "Failed to create BackgroundSubtractor.GMG Algorithm." << std::endl;
    fgbg->set("initializationFrames", initFrames);
    fgbg->set("decisionThreshold", decisionThreshold);
}

//bool FgbgGMG::getDiagram(Mat & img, int * & drag)
//{
//    int length = img.cols * img.rows * img.channels();
//    uchar * data = img.ptr<uchar>(0);
//    for (int i=0; i< length; i++)
//    drag[i]=*data ;
//    return 0;
//}
//bool FgbgGMG::readFrame(Mat frame)
//{
//    if (frame.empty()) return 0;
//    (*fgbg)(frame, fgmask);
//    Mat tmp = fgmask;
//    //morphologyEx(tmp,fgmask,MORPH_OPEN,Mat(5,5,CV_8U),Point(-1,-1),2);
//    //uchar * data = fgmask.ptr<uchar>(0);
//	Mat fgmask_gray,fgmask_bin;
//
//	  
//	vector<vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//    findContours( fgmask, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//
//	//cout << contours.size() << endl;
//	  
//	if (contours.size()>7)
//	{
//		float maxArea[2] = {0.0, 0};
//		for(int i = 0;i < contours.size();i++)
//		{
//			//��ȡ��ǰ�������
//			double area = fabs(contourArea(contours[i]));
//		 
//		    //cout << "Area: " << area << endl;
//			if (area>maxArea[0])
//			{
//				maxArea[0] = area;
//				maxArea[1] = i;
//			}
//		}
//
//		Rect aRect = boundingRect(contours[maxArea[1]]);
//
//		/*cout << "height =" << aRect.height << endl
//			<< "width =" << aRect.width << endl;*/
//	    imshow("nanananna",fgmask);
//        //imshow("nyanyanyanya",frame);
//	}
//	  
//	  
//	waitKey(1);
//
//    return 1;
//}
//
//FgbgGMG::FgbgGMG()
//{
//    initModule_video();
//    setUseOptimized(true);
//    setNumThreads(8);
//
//    fgbg = Algorithm::create<BackgroundSubtractorGMG>("BackgroundSubtractor.GMG");
//
//    if (fgbg.empty())
//    std::cerr << "Failed to create BackgroundSubtractor.GMG Algorithm." << std::endl;
//	fgbg->set("initializationFrames", 20);
//	fgbg->set("decisionThreshold", 0.8);
//
//	//fgbg->set("maxFeatures", 20);  //������ֵ��Χ֮һ�� max:256,Խ��Խ�á�
//	//fgbg->set("learningRate", 0.15);   //����ѧϰ�ʣ�0.1~0.2�á�
//}
//
//FgbgGMG::FgbgGMG(int initFrames, float decisionThreshold)
//{
//    initModule_video();
//    setUseOptimized(true); 
//    setNumThreads(8);
//
//    fgbg = Algorithm::create<BackgroundSubtractorGMG>("BackgroundSubtractor.GMG");
//
//    if (fgbg.empty())
//    std::cerr << "Failed to create BackgroundSubtractor.GMG Algorithm." << std::endl;
//    fgbg->set("initializationFrames", initFrames);
//    fgbg->set("decisionThreshold", decisionThreshold);
//}
//
//void main()
//{
//	FgbgGMG *fgmg = new FgbgGMG();
//
//
//
//	//findContours();
//	int n=30;
//	int i = 0;
//	String img0 = "./imgs/img00001.png" ;
//
//	Mat frame;
//	VideoCapture cap;
//	cap.open(0);
//
//	while(n--)
//	{	
//		i = i%9;
//		img0[13] = '0' + i + 1;
//		i++;
//
//		//frame = imread( img0 );
//		//fgmg->readFrame(frame);
//
//		cap>>frame;
//		fgmg->readFrame(frame);
//		
//	}
//}
