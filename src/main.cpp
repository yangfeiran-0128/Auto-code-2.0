/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "includes.h"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  initialize_pid();
  InitialmyInertial();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

timer t1, t2;
float ave;

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // Rotate(100);//以100%的功率原地左转，负号表示右转，取值0-100；
  // Circlerun(100, -40);//左轮速度，右轮速度，哪个绝对值小往哪偏转.
  // Move(100);//以100%的功率前进，负号表示后退，取值0-100；
  // PIDTurn_myInertial(-90,50),相当于PIDTurn_myInertial(270,50)，但转动方向不同，用时不同！
  // -90表示从当前位置，向左转到-90°的位置，即9点钟方向；90表示向右转到90°的位置，即3点钟方向；j角度范围>360
  //注意：具体用法参照函数说明！！
  t2.reset();

  PIDForward(-480, 70, 1300);
  dig_Top.set(true);
  PIDTurn_myInertial(90,50);
  //dig_Bottom.set(true);
  CollectDrive(-100);
  PIDForward(-205,30,1300);
  wait(2.5,sec);
  //CollectDrive(0);
  PIDForward(420,60,1300);
  //CollectDrive(-100);
  TopSuckDrive(-100);
  MidSuckDrive(-100);
  wait(2,sec);
  CollectDrive(0);
  TopSuckDrive(0);
  MidSuckDrive(0);
  dig_Top.set(false);
  PIDForward(-80,50,1000);
  PIDTurn_myInertial(135,30);
  PIDForward(300,30,1000,2.3);
 // PIDTurn_myInertial(-70,30);
  PIDForward(400,30,1000);

/*
  MidSuckDrive(-3);
  wait(0.5, sec);

  // PIDForward(-40, 20);

  PIDTurn_myInertial(65, 20, 700);
  CollectDrive(-12.8); //下收块
  MidSuckDrive(-3);    //中上传
  PIDForward(-200, 10, 1100);

  PIDForward(-650, 40, 2400, 0.78);
  PIDTurn_enc(20, 20);

  dig_Top.set(true);
  wait(0.5, sec);
  MidSuckDrive(0);
  Move(-25);
  wait(0.4, sec);
  Move(-2);
  wait(0.5, sec);
  Move(15);
  wait(0.5, sec);
  TopSuckDrive(0); // shangmian
  CollectDrive(0);
  PIDTurn_myInertial(2, 30,500);
  PIDForward(360, 60, 1000);
  MidSuckDrive(-12.8); // mid
  TopSuckDrive(-12.8); // shangmian
  CollectDrive(-12.8);
  wait(2.3, sec);
  dig_Top.set(false);
  PIDForward(-150, 30);
  PIDTurn_myInertial(47, 20, 500);
  PIDForward(350, 20, 1000, 1.85);

  PIDForward(300, 30, 1000, 1.1);
  PIDTurn_myInertial(10, 20, 1000);
  Rotate(0, hold);*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool topCylinderState1 = false;
bool topCylinderState2 = false;
bool topCylinderState3 = false;

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {

    Hchasishandles(brake); //底盘行走装置
    StoreHandles();        //吸球装置
    if (Controller.ButtonDown.pressing()) {
      topCylinderState1 = !topCylinderState1;
      dig_Top.set(topCylinderState1);
      wait(300, msec);     
    }
    if (Controller.ButtonB.pressing()) {
      topCylinderState2 = !topCylinderState2;
      dig_Bottom.set(topCylinderState2);
      wait(300, msec);     
    }

    if (Controller.ButtonUp.pressing()) {
      topCylinderState3 = !topCylinderState3;
      dig_Up.set(topCylinderState3);
      wait(300, msec);     
    }
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {

    wait(100, msec);
  }
}
