#pragma config(Sensor, in1,    ArmPOT,              sensorPotentiometer)
#pragma config(Sensor, in2,    Gyro,                sensorGyro)
#pragma config(Sensor, dgtl1,  touchh,              sensorTouch)
#pragma config(Sensor, dgtl5,  bumper,              sensorTouch)
#pragma config(Sensor, dgtl8,  touchl,              sensorTouch)
#pragma config(Sensor, dgtl9,  EncoderLeft,         sensorQuadEncoder)
#pragma config(Sensor, dgtl11, EncoderRight,        sensorQuadEncoder)
#pragma config(Motor,  port1,           rightBack,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           rightBig,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           rightFront,    tmotorNormal, openLoop)
#pragma config(Motor,  port4,           leftBig,       tmotorNormal, openLoop)
#pragma config(Motor,  port5,           leftFront,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           rightLift,     tmotorNormal, openLoop)
#pragma config(Motor,  port7,           leftLift,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           Collectors1,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           Collectors2,   tmotorNormal, openLoop)
#pragma config(Motor,  port10,          leftBack,      tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Variables.c"
#include "Motor_and_sensor.c"
#include "REAL_LCD.c"



#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  Autonchooser();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{

  Autonfilter();
  if (Isolation_BLUE_Program == 1)
  {
    IsoZone();
  }// if BLue Isolation Zone

  else if(Isolation_RED_Program == 1)
  {
    IsoZone();
  }
  else if(Interaction_BLUE_Program == 1)
  {
    Interaction_auton();
  }//if blue interation zone...

  else if(Interaction_RED_Program == 1)
  {
    Interaction_auton();
  }
}// end of auton




/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
#include" Teleop.c"
}//teleop
