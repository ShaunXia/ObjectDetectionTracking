#include <iostream>
using namespace std;

#pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "videoInput.h"
#include "CompressiveTracker.h"
#include "SerialPort.h"
#include <stdio.h>
using namespace std;
using namespace cv;

CompressiveTracker ct;
Rect box(50,50,100,100);

int main()
{
    CompressiveTracker ct;

	Mat frame;
	Mat last_gray;
	Mat first;

		cvtColor(frame, last_gray, CV_RGB2GRAY);
		rectangle(frame, box, Scalar(0,0,255));
		imshow("CT", frame);
		if (cvWaitKey(33) == 'q') {	return 0; }
	
	// Remove callback
	setMouseCallback("CT", NULL, NULL);
	printf("Initial Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);
	// CT initialization
	ct.init(last_gray, box);

	// Run-time
	Mat current_gray;

	while(capture.read(frame))
	{
		// get frame
		cvtColor(frame, current_gray, CV_RGB2GRAY);
		// Process Frame
		ct.processFrame(current_gray, box);
		// Draw Points
		rectangle(frame, box, Scalar(0,0,255));
		// Display
		imshow("CT", frame);
		//printf("Current Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);

		if (cvWaitKey(33) == 'q') {	break; }
	}
	return 0;
}
}
