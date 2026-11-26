#include "Actions.h"

void HchasisDrive(double l, double r) {
  mtr_LF.spin(fwd, l, volt);
  mtr_LM.spin(fwd, l, volt);
  mtr_LB.spin(fwd, l, volt);
  mtr_RF.spin(fwd, r, volt);
  mtr_RM.spin(fwd, r, volt);
  mtr_RB.spin(fwd, r, volt);
}
//吸球

void CollectDrive(double power) {

  if (power == 0) {
  
    mtr_FWG2.stop(coast);
  } else {
    
    mtr_FWG2.spin(fwd, power, volt);
  }
}


void MidSuckDrive(double power) {
  if (power == 0) {
    mtr_mid_suck.stop(coast);
  } else {
    mtr_mid_suck.spin(fwd, power, volt);
  }
}
void TopSuckDrive(double power) {
  if (power == 0) {
    mtr_top_suck.stop(coast);
  } else {
    mtr_top_suck.spin(fwd, power, volt);
  }
}