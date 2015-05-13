#include "SpeedControl.h"
#include <iostream>
using namespace std;

CSpeedControl::CSpeedControl(void)
{
}


CSpeedControl::~CSpeedControl(void)
{
}

void CSpeedControl::init(Rect box)
{
    preTime = clock();
    preBox = box;
    centerX = 384;
    centerY = 288;
    xWay = 0;
    yWay = 0;
    xOry = 0;
}

int CSpeedControl::calculate(Rect box)
{
    nowTime = clock();
    nowBox = box;
    int x = box.width/2 + box.x, y = box.height/2 + box.y;
    int xGap = x - centerX, yGap = y - centerY;
    int XGAP = abs(xGap), YGAP = abs(yGap);

    if(XGAP <= 50 && YGAP <= 20)
    {    
        xSpeed = 0;
        ySpeed = 0;
        preBox = nowBox;
        if(xOry == 1 || xOry == -1)
        {
            preTime = nowTime;
            xWay = 0;
        }
        else if(xOry == 2 || xOry == -2)
        {
            preTime = nowTime;
            yWay = 0;
        }
        else
        {
            xWay = 0;
            yWay = 0;
            preTime = nowTime;
        }
            
        xOry = 0;
        return 0;
    }
    //cout<<"x"<<xGap<<"y"<<yGap<<endl;
    time_t gapTime = nowTime - preTime;
    preTime = nowTime;
    if(XGAP > YGAP + 100)
    {
        if(xGap * xWay >= 0)
        {
            if((nowBox.x - preBox.x) * xWay >=0)
            {
                double xs = abs(1.0*(nowBox.x - preBox.x)/gapTime) * 50;
                cout<<"XXX"<<nowBox.x - preBox.x<<"  "<<xs<<endl;
                if(nowBox.x + nowBox.width >  550 || nowBox.x < 200)
                    xSpeed = 7;
                else xSpeed = xs > 63 ? 63 : xs+1;
                preBox = nowBox;
            
                cout<<xSpeed<<endl;
            }
            if(nowBox.x + nowBox.width >  550 || nowBox.x < 200)
                    xSpeed = 8;
            if(xGap > 0)
                xOry = xWay = 1;
            else xOry = xWay = -1;
            return xOry;

        }
        else
        {
            double xs = abs(1.0*(nowBox.x - centerX)/gapTime) *2 + 20;
            xSpeed = xs > 63 ? 63 : xs+1;
            preBox = nowBox;
            if(xGap > 0)
                xOry = xWay = 1;
            else xOry = xWay = -1;
            //cout<<xSpeed<<endl;
            return xOry;
        }
    }
    else
    {
        if(yGap * yWay >= 0)
        {
            if((nowBox.y - preBox.y) * xWay >=0)
            {
            double ys = abs(1.0*(nowBox.y - preBox.y)/gapTime) * 100;
            

            ySpeed = ys > 63 ? 63 : ys+1;
            //cout<<"YYY"<<ySpeed<<endl;
            preBox = nowBox;
            
            //cout<<ySpeed<<endl;
            }
            if(nowBox.y + nowBox.height >  450 || nowBox.y<125)
                ySpeed = 20;
            if(yGap > 0)
                xOry = yWay = -2;
            else xOry = yWay = 2;
            return xOry;

        }
        else
        {
            double ys = abs(1.0*(nowBox.y - centerY)/gapTime) * 3;
            ySpeed = ys > 63 ? 63 : ys+1;
            preBox = nowBox;
            if(nowBox.y + nowBox.height >  450 || nowBox.y<125)
                ySpeed = 45;
            if(yGap > 0)
                xOry = yWay = -2;
            else xOry = yWay = 2;
            //cout<<ySpeed<<endl;
            return xOry;
        }
    }
}