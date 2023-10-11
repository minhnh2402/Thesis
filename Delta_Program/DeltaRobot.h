#pragma once
#ifndef DELTAROBOT
#define DELTAROBOT

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <Windows.h>

using namespace Eigen;
using namespace std;

struct PointStruct
{
    double x;
    double y;
    double z;

};

struct ThetaStruct
{
    double q1;
    double q2;
    double q3;

};

struct ThetaStruct_INT32
{
    INT32 q1;
    INT32 q2;
    INT32 q3;
};

class Delta
{
public:
	Delta();
    ~Delta();
    void goHome();
    void goTo(PointStruct& point, ThetaStruct& theta);
    void goToAngle(PointStruct& point, ThetaStruct& theta);
    void delta_calcInverse(PointStruct& point, ThetaStruct& theta);
    void delta_calcForward(PointStruct& point, ThetaStruct& theta);
    void reportPosition();
    void reportAngles();
    void convertPulse(ThetaStruct& theta_rad, ThetaStruct_INT32& theta_pulse);
    void convertRad(ThetaStruct& theta_pulse, ThetaStruct& theta_rad);
    void circleMove(double h, double R, int time, double step);
    void delta_calcOmega(PointStruct& point, ThetaStruct& theta, PointStruct& veclocity);
    //void lineMove(PointStruct& pointA, PointStruct& pointB, );
    int  testInWorkspace(PointStruct& point);


public: //parameter
    PointStruct myPoint;
    ThetaStruct myTheta;
    vector <ThetaStruct> jointValue;
    vector <ThetaStruct_INT32> c_PulseVector;
    vector <ThetaStruct_INT32> c_OmegaVector;
    ThetaStruct_INT32 c_PulseMove;
    PointStruct c_PMove;
    PointStruct c_VMove;
    ThetaStruct c_TMove;
    vector <ThetaStruct> omegaValue;


private:
    double PI;
    double R;
    double r;
    double d;
    double L;
    double l;
    double a; // -118
    double b;
    double c;
    double rMax;
    double zMin;
    double zMax;
};



#endif // !DELTAFUNCTION

