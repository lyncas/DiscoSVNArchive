#pragma config(Sensor, in1,    LeftLine,            sensorLineFollower)
#pragma config(Sensor, in2,    CentreLeftLine,      sensorLineFollower)
#pragma config(Sensor, in3,    CentreRightLine,     sensorLineFollower)
#pragma config(Sensor, in4,    RightLine,           sensorLineFollower)
#pragma config(Sensor, in5,    Right2Line,          sensorLineFollower)
#pragma config(Sensor, in6,    GreyCentre,          sensorLineFollower)
#pragma config(Sensor, in7,    Grey,                sensorLineFollower)
#pragma config(Sensor, in8,    Tubecounter,         sensorReflection)
#pragma config(Sensor, dgtl2,  Encoderarm,          sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  touchh,              sensorTouch)
#pragma config(Sensor, dgtl5,  EncoderLeft,         sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  EncoderRight,        sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  touchl,              sensorTouch)
#pragma config(Motor,  port2,           DriveLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLeft2,    tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRight2,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           lift1,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           lift2,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           lift3,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           lift4,         tmotorNormal, openLoop)
#pragma config(Motor,  port10,          Claw,          tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  Project Title: Junk
  Team Members: Lance Dinh
  Date: 6/27/2011
  Section:N/A


  Task Description: Have the LCD pick the program../.


  Pseudocode:

*/

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Variables.c"
#include "LCD.c"//include the library for the lcd...
#include "Motor_and_sensor.c"
#include "LineTracker.c"



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
  clearencoder();
  Autonchooser();
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

   if(Isolation_RED_Program == 1)
  {
    clearLCD();
    displayLCDCenteredString(1, "Line");
    FowardLine(front, 100, 3);//foward until line
    checkstall();//see if the robot is moving
    turnLine(right, 100, 3);
    linefollow(450, 4.5);// follow line first input ticks and then input time...
    // Red program and interaction zone here ...
    //lift();//see if the arm is jamed
    checkarmstall();
    Turnenc(127, 100,2.5);
  }

  else if(Isolation_RED_Program == 2)
  {
    displayLCDCenteredString(1, "checkstall");
    DriveEncoders(-127, 300);
    checkstall();
    //etc...
  }

  else if(Isolation_RED_Program == 3)
  {
    bLCDBacklight = true;
    clearwhichline(1);
    displayLCDCenteredString(1, "Test" );
    wait1Msec(500);
    lift(lowgoal, 2);
    lift (highgoal, 3);
    lift(mediumgoal, 2);
    //etc...
  }
  //-----------------------------------------------------------------------------------------
   if (Interaction_RED_Program == 1)
  {

    clearLCD();
    displayLCDCenteredString(1, "123456");
    wait1Msec(1000);
    //Isolation RED PRogram
  }

  else if (Interaction_RED_Program == 2)
  {clearLCD();
    displayLCDCenteredString(1, "yofdfdfd");
    wait1Msec(1000);
    //etc...
  }

  else if (Interaction_RED_Program == 3)
  {


    //etc...
  }
  //-------------------------------------------------------------------------------------------------
   if (Interaction_BLUE_Program == 1)
  {
    //Interaction Zone Blue PRogram
  }

  else if (Interaction_BLUE_Program == 2)
  {
    //etc...
  }

  else if (Interaction_BLUE_Program == 3)
  {
    //etc...
  }
  //-------------------------------------------------------------------------------------------------------
 else if (Isolation_BLUE_Program == 1)
  {
    displayLCDCenteredString(1, "checkstallb");//Isolation Blue PRogram
  }

  else if (Isolation_BLUE_Program == 2)
  {
    displayLCDCenteredString(1, "checkbcstall");//etc...
  }

  else if (Isolation_BLUE_Program == 3)
  {

   //turn right
    //etc...
  }

  /////////////////////////////////////////////////////////////////////////////////////////


}



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
  allMotorsOff();
  #include "driveCode.c"// Drive code...
}
