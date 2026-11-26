#pragma once
#include "includes.h"

int sign(int a);
int speedlimit(int speed, int max );
void LeftWheel(int speed);
void RightWheel(float speed);
void InitialmyInertial();
void Move(int speed,float a=1);
void Rotate(int speed,brakeType m);
void initialize_pid();
void PIDForward(int MoveTarget, int MaxSpeed,int rt=900,float=1);
void PIDTurn_enc(int MoveTarget, int MaxSpeed,int et=800);
void PIDTurn_myInertial(int RotateTarget, int MaxSpeed,int wt=2000);
void launch(int t);
void pull();
void Circlerun(int leftspeed,int rightspeed);
void arm_p(double s, int t);
