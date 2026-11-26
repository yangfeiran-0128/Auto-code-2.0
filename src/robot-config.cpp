#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller(primary);

/*vex-vision-config:begin*/
signature Vis__BLUEBOX = signature (1, -3855, -3177, -3516, 5695, 8193, 6944, 2.2, 0);
signature Vis__REDBOX = signature (2, 5187, 8707, 6947, -1065, 1, -532, 1.6, 0);
signature Vis__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vis__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vis__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vis__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vis__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vis = vision (PORT17, 50, Vis__BLUEBOX, Vis__REDBOX, Vis__SIG_3, Vis__SIG_4, Vis__SIG_5, Vis__SIG_6, Vis__SIG_7);
/*vex-vision-config:end*/

motor mtr_RF(PORT20,ratio18_1,false);
motor mtr_RM(PORT18,ratio18_1,true);
motor mtr_RB(PORT17,ratio18_1,false);
motor mtr_LF(PORT13,ratio18_1,true);
motor mtr_LM(PORT12,ratio18_1,false);
motor mtr_LB(PORT14,ratio18_1,true);



motor mtr_FWG2(PORT11,ratio18_1,false);//出筐2//////////////////////////////

motor mtr_mid_suck(PORT8,ratio18_1,false);//中桥吐球//////////////////////////

motor mtr_top_suck(PORT7,ratio18_1,true);//运球/////////////////////////////






inertial myInertial(PORT21);
//limit LimitSwitchB = limit(Brain.ThreeWirePort.B);
digital_out dig_Bottom=digital_out(Brain.ThreeWirePort.H);
digital_out dig_Top=digital_out(Brain.ThreeWirePort.G);
digital_out dig_Up=digital_out(Brain.ThreeWirePort.E);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}