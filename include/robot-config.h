using namespace vex;

extern brain Brain;
using signature = vision::signature;

// VEXcode devices
extern signature Vis__BLUEBOX;
extern signature Vis__REDBOX;
extern signature Vis__SIG_3;
extern signature Vis__SIG_4;
extern signature Vis__SIG_5;
extern signature Vis__SIG_6;
extern signature Vis__SIG_7;
extern vision Vis;

extern controller Controller;
extern motor mtr_LF;
extern motor mtr_LM;
extern motor mtr_LB;
extern motor mtr_RF;
extern motor mtr_RM;
extern motor mtr_RB;


extern motor mtr_FWG2;

extern motor mtr_mid_suck;


extern motor mtr_top_suck;



extern inertial myInertial;
extern digital_out dig_Top;
extern digital_out dig_Bottom;
extern digital_out dig_Up;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
