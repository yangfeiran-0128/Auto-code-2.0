#include "handles.h"

//左摇杆控制机器底盘
void Hchasishandles(brakeType m) {
  double y = fabs(Controller.Axis3.position() * 12.8 / 100.0) > 0.64
                 ?-Controller.Axis3.position() * 12.8 / 100.0
                 : 0;
  double x = fabs(Controller.Axis1.position() * 12.8 / 100.0) > 0.64
                 ?Controller.Axis1.position() * 12.8 / 100.0
                 : 0;
  if (y == 0 && x == 0) {
    mtr_LF.stop(m);
    mtr_LM.stop(m);
    mtr_LB.stop(m);
    mtr_RF.stop(m);
    mtr_RM.stop(m);
    mtr_RB.stop(m);
  } else {
    HchasisDrive(y + 0.6 * x, y - 0.6 * x);
  }
}
void Releasehandles() {
  if (Controller.ButtonL1.pressing()) {
    // ClawDrive(12.8);
    MidSuckDrive(-12.8); // mid
    // UpSuckDrive(-12.8);
    TopSuckDrive(-12.8); // shangmian
    CollectDrive(-12.8); // c
  } else if (Controller.ButtonL2.pressing()) {
    MidSuckDrive(-12.8);
    // UpSuckDrive(-12.8);
    TopSuckDrive(12.8);
    CollectDrive(-12.8);

  } else {

    // ClawDrive(0);
    MidSuckDrive(0);
    // UpSuckDrive(0);
    CollectDrive(0);
    TopSuckDrive(0);
  }
}

void StoreHandles() {

  if (Controller.ButtonR1.pressing()) {
    // ClawDrive(0);
    MidSuckDrive(0);
    // UpSuckDrive(-12.8);
    CollectDrive(-12.8);
    TopSuckDrive(0);
    // TopSuckDrive(12.8);
    //‘b’是吐蓝球，‘r’吐红球
    // chekcolor('r');
    if (Controller.ButtonR2.pressing()) {
    CollectDrive(-12.8);
    // ClawDrive(-12.8);
    MidSuckDrive(-12.8);
    TopSuckDrive(0);}

  } else if (Controller.ButtonR2.pressing()) {
    CollectDrive(12.8);
    // ClawDrive(-12.8);
    MidSuckDrive(12.8);
    TopSuckDrive(0);
    // UpSuckDrive(0);
  } else {
    Releasehandles();
  }
}

void chekcolor(char flag) {
  if (flag == 'r') {
    Vis.takeSnapshot(Vis__REDBOX);
  } else if (flag == 'b') {
    Vis.takeSnapshot(Vis__BLUEBOX);
  }
  if (Vis.largestObject.exists && Vis.largestObject.width > 160 &&
      Vis.largestObject.height > 100) {
    TopSuckDrive(-12.8);
    wait(0.35, sec);
  } else {
    TopSuckDrive(12.8);
  }
}
