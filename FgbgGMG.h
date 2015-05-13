/*
	Í¼Ïñ¶Ô±È£¬GMGËã·¨£»
*/


#include <opencv2/opencv.hpp>

using namespace cv;

class FgbgGMG
{
  private:
    Mat frame, fgmask, segm, grayImg;
    Ptr<BackgroundSubtractorGMG> fgbg;
    bool getDiagram(Mat & img, int * & drag);
    int width,height;


  public:
    Rect readFrame(Mat frame);

    FgbgGMG();

	FgbgGMG(int initFrames, float decisionThreshold);

};