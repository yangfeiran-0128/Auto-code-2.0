#include "program.h"

timer mytime, T1, T2, TAcc;

// define your global instances of motors and other devices here
// void pull() {
//   while (!LimitSwitchB.pressing()) {
//     FlyWheelGunDrive(-12.8);
//   }
//   FlyWheelGunDrive(0);
// }
// void launch(int t) {

//   FlyWheelGunDrive(-12.8);
//   wait(t, msec);
//   FlyWheelGunDrive(0);
// }

int sign(int a) {
  if (a > 0)
    return 1;
  else if (a < 0)
    return -1;
  else
    return 0;
}

int speedlimit(int speed, int max = 100) {
  return abs(speed) > max ? sign(speed) * max : speed;
}

void LeftWheel(int speed) {
  mtr_LF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  mtr_LM.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  mtr_LB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}
void RightWheel(float speed) {
  mtr_RF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  mtr_RM.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  mtr_RB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}
void Move(int speed,float a) {
  LeftWheel(speed);
  RightWheel(a*speed);
  if (speed == 0) {
    mtr_LF.stop(brake);
    mtr_LM.stop(brake);
    mtr_LB.stop(brake);
    mtr_RF.stop(brake);
    mtr_RM.stop(brake);
    mtr_RB.stop(brake);
  }
}
void InitialmyInertial() {
  myInertial.calibrate();
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("myInertial is Calibrating......");
  while (myInertial.isCalibrating()) {
  };
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(red);
  Brain.Screen.setCursor(2, 5);
  Brain.Screen.setFont(monoXXL);
  Brain.Screen.print("JLHS-8176A");
}
void Circlerun(int leftspeed, int rightspeed) {
  LeftWheel(leftspeed);
  RightWheel(rightspeed);
}

void Rotate(int speed, brakeType mode = brake) {
  LeftWheel(-1 * speed);
  RightWheel(speed);
  if (speed == 0) {
    mtr_LF.stop(mode);
    mtr_LM.stop(mode);
    mtr_LB.stop(mode);
    mtr_RF.stop(mode);
    mtr_RM.stop(mode);
    mtr_RB.stop(mode);
  }
}

float tolerance = 3.0;
int OutPut_limit;
typedef struct {
  float Kp;
  float Ki;
  float Kd;
  int Error;
  int Integral;
  int Derivative;
  int LastError;
  int Output;
  bool insidetarget;
} TPID;

TPID PIDEncoder;
TPID PIDmyInertial;

void initialize_pid() {
  PIDEncoder.Kp = 0.4;  // 0.190;//0.5*0.6+0.05;
  PIDEncoder.Ki = 0.001; // 0.002;//110;
  PIDEncoder.Kd = 0.00;  // 0.173;//0.5*0.6*0.12*110;

  PIDmyInertial.Kp = 0.48;
  PIDmyInertial.Ki = 0.002;
  PIDmyInertial.Kd = 0;
}

void UpdatePIDController(TPID *PIDController, int Error, int tolerance) {

  PIDController->Error = Error;

  if (abs(Error) <= tolerance)
    PIDController->insidetarget = true;
  else {
    PIDController->insidetarget = false;
    T2.clear();
  }

  if (abs(Error) < 30 && Error != 0)
    PIDController->Integral += PIDController->Error;
  else
    PIDController->Integral = 0;

  PIDController->Derivative = PIDController->Error - PIDController->LastError;
  PIDController->LastError = PIDController->Error;

  PIDController->Output =
      (int)((float)PIDController->Error * PIDController->Kp) +
      ((float)PIDController->Integral * PIDController->Ki) +
      ((float)PIDController->Derivative * PIDController->Kd);
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////PID Controller////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void PIDForward(int MoveTarget, int MaxSpeed = 100, int rt ,float a) {
  int wait = 500;
  float ave = 0.0;
  tolerance = 8.0;
  TPID *PID = NULL;
  PID = &PIDEncoder;
  PID->insidetarget = false;
  T1.clear();
  T2.clear();
  TAcc.clear();
  mtr_RB.resetPosition();
  mtr_RF.resetPosition();
  // Controller.Screen.clearScreen();
  // Controller.Screen.setCursor(1, 1);
  while (PID->insidetarget == false || T2.time() < 100) {
    ave = (mtr_RF.position(deg) + mtr_RB.position(deg)) / 2;
    UpdatePIDController(PID, MoveTarget - ave, tolerance);
    OutPut_limit = speedlimit(PID->Output, MaxSpeed);

    if (TAcc.time() < wait && MoveTarget > 0) // limit the acceleration
    {
      OutPut_limit = OutPut_limit * TAcc.time() / wait;
      // OutPut_limit=sign(OutPut_limit)*OutPut_limit*OutPut_limit/100;
    }
    Move(OutPut_limit,a);
    vex::task::sleep(6);
    if (T1.time() > rt)
      break;
  }
  // Controller.Screen.print("goal=%d", MoveTarget);
  // Controller.Screen.newLine();
  // Controller.Screen.print("A=%2f", mtr_RF.position(deg));
  // Controller.Screen.newLine();
  // Controller.Screen.print("B=%2f", mtr_RB.position(deg));
  Move(0);
}

void PIDTurn_enc(int MoveTarget, int MaxSpeed = 100, int et) {
  
  int wait = 500;
  tolerance = 8.0;
  TPID *PID = NULL;
  PID = &PIDEncoder;
  PID->insidetarget = false;
  T1.clear();
  T2.clear();
  TAcc.clear();
  mtr_RB.resetPosition();
  mtr_RF.resetPosition();
  // Controller.Screen.clearScreen();
  // Controller.Screen.setCursor(1, 1);
  while (PID->insidetarget == false /*|| T2.time() < 100*/) {
    UpdatePIDController(PID, MoveTarget - mtr_RF.position(deg), tolerance);
    OutPut_limit = speedlimit(PID->Output, MaxSpeed);

    if (TAcc.time() < wait && MoveTarget > 0) // limit the acceleration
    {
      OutPut_limit = OutPut_limit * TAcc.time() / wait;
      // OutPut_limit=sign(OutPut_limit)*OutPut_limit*OutPut_limit/100;
    }

    LeftWheel(-OutPut_limit);

    RightWheel(OutPut_limit);

    // Move(OutPut_limit);
    vex::task::sleep(6);
    if (T1.time() > et)
      break;
  }
  // Controller.Screen.print("goal=%d", MoveTarget);
  // Controller.Screen.newLine();
  // Controller.Screen.print("A=%2f", mtr_RF.position(deg));
  // Controller.Screen.newLine();
  // Controller.Screen.print("B=%2f", mtr_RB.position(deg));
  Move(0);
}

void PIDTurn_myInertial(int RotateTarget, int MaxSpeed = 100, int wt) {
  TPID *PID = NULL;
  PID = &PIDmyInertial;
  PID->insidetarget = false;
  T1.clear();
  T2.clear();
  tolerance = 1.2;
  // InitialmyInertial();
  // Controller.Screen.clearScreen();
  // Controller.Screen.setCursor(1, 1);
  // Controller.Screen.print("PIDturnTo start......");
  while (PID->insidetarget == false || T2.time() < 100) {
    UpdatePIDController(PID, RotateTarget - myInertial.rotation(deg),
                        tolerance);
    OutPut_limit = speedlimit(PID->Output, MaxSpeed);
    Rotate(-OutPut_limit);
    vex::task::sleep(10); // 10
    if (T1.time() > wt)
      break;
  }
  // Controller.Screen.newLine();
  // Controller.Screen.print("goal=%d", RotateTarget);
  // Controller.Screen.newLine();
  // Controller.Screen.print("angle=%.2f", myInertial.rotation(deg));
  Move(0);
}
