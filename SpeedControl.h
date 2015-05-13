#pragma once
#include <time.h>
#include "opencv2/core/core.hpp"
using namespace cv;
class CSpeedControl
{
private:
    int centerX;
    int centerY;
    Rect preBox;
    Rect nowBox;
    time_t preTime;
    time_t nowTime;
    
    int xSpeed;
    int ySpeed;
    int xWay;
    int yWay;
    int xOry;
public:
    CSpeedControl(void);
    ~CSpeedControl(void);
    
    int getXSpeed(){return xSpeed;}
    int getYSpeed(){return ySpeed;}
    void init(Rect box);

    int calculate(Rect box);
};

