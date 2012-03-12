#pragma config(Sensor, in1,    pot,                 sensorPotentiometer)
#pragma config(Sensor, in4,    gy,                  sensorGyro)
#pragma config(Sensor, dgtl1,  ncoder1,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  ncoder2,             sensorQuadEncoder)
#pragma config(Sensor, dgtl12, TouchGoal,           sensorTouch)
#pragma config(Motor,  port2,           DriveR,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveL,        tmotorNormal, openLoop)
#pragma config(Motor,  port4,           Lift1,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           Lift2,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           Lift3,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           Lift4,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           Claw,          tmotorNormal, openLoop)
//*!!Co de automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Test 1.c" //Funtion Library

/*
Pot values NOT CODE
arm_grounded = 1400 or 1250
descore_lock_point = 1748 - 1250(1400) = 347
low_lock_point = 2550 - arm grounded = 1150
descore_high_point =
high_lock_point = 2775 - arm_grounded = 1475

*/

int arm_grounded;
int descore_low_point;
int low_lock_point;
int descore_high_point;
int high_lock_point;

void pre_auton()
{
  SensorValue[dgtl1] = 0;
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  arm_grounded = SensorValue[pot];
  //////////////////////////////////////////////////////////////////////////////////////////////
  descore_low_point = arm_grounded + 365;    low_lock_point = arm_grounded + 1160; //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point



  /////////////////////////////////////
  descore_high_point = arm_grounded + 200;//<<<<---------------------------------------------------run debugger in tele op and see what this value is,
  //put that value where the XXXXX's are
  ////////////////////////////////////////



  high_lock_point = arm_grounded + 1500; //high goal potentiometer reading
  /////////////////////////////////////////////////////////////////////

  arm_grounded += 0;
}

task autonomous()
{
  pre_auton();
  motor[DriveR] = 63;
  motor[DriveL] = 63;
  wait1Msec(1000);

  motor[DriveR] = 0;
  motor[DriveL] = 0;

  //lock(low_lock_point); //<-------------------------------------pot code
}

//USER CONTROL/////////////////////////////////////////////////////////////////
task usercontrol()
{
  pre_auton();
  int goal_lock = 0;  //0 for unlocked, -1 for low gal, 1 for high goal
  //calibration for potentiometer setting the arm
  /*int low_lock_point = SensorValue[in1] + 703; //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point
  int high_lock_point = SensorValue[in1] + 1000; //high goal potentiometer reading*/
  //end calibrarion


  while(true)
  {
    //Arm/////////////////////////////////////////////////////////////////////////
    if(vexRT[Btn7L] == 1)//auto button close loop
    {
      goal_lock = -1;   //sets to low lock
    }
    else if(vexRT[Btn7U] == 1) {
      goal_lock = 1;	//sets to high lock
    }
    else if(vexRT[Btn7D] == 1) {// descore/ score on low goal...
        goal_lock = 2;
    }
    else if(vexRT[Btn7R] == 1) {//same as 7D...
        goal_lock = -2;
    }




    if(goal_lock == -1)
      lock(low_lock_point); //brings to low lock point
    else if(goal_lock == 1)
      lock(high_lock_point);//moves arm to high lock point
    ///////////////////////////////////////////////////////////////NEW STUFF TAKE THIS OUT IF IT DOESNT WORK
    else if (goal_lock == 2)
      lock(descore_low_point);//moves arm to descore lock point
    	else if(goal_lock == -2)
    lock(descore_high_point);
    //////////////////////////////////////////////////////////////










    switch(vexRT[Btn6U] - vexRT[Btn6D]) //manual arm control
    {
    case  1:motor[port4] =- 127;
      motor[port5] = -127;
      motor[port6] = 127;
      motor[port7] = 127;

      goal_lock = 0;  //unlocks arm
      break;

    case -1:motor[port4] = 127;
      motor[port5] = 127;
      motor[port6] = -127;
      motor[port7] = -127;
      goal_lock = 0;  //unlocks arm
      break;

    case  0:if(goal_lock == 0 ) {
        motor[port4] = 0;
        motor[port5] = 0;
        motor[port6] = 0;
        motor[port7] = 0;
        break;
      }//switch
    }

    //Claw
    switch(vexRT[Btn5D] - vexRT[Btn5U])
    {
    case  1:motor[Claw] = -127; //Close
      break;
    case -1:motor[Claw] = 127; //Open
      break;
    case  0:motor[Claw] = 0; //Do nothing
      break;


    }




    //Drive Train
    if(vexRT[Ch2] < 15 && vexRT[Ch2]> -15 && vexRT[Ch3] < 15 && vexRT[Ch3]> -15)
    {
      motor[DriveR] = 0;

      motor[DriveL] = 0;
    }



    else
    {
      motor[DriveL]  = vexRT[Ch3];
      motor[DriveR] = vexRT[Ch2];
    }






    // Shuts all motors down
    {

      if(vexRT[Btn8U] == 1)
      {
        motor[port1] = 0;
        motor[port6] = 0;
        motor[port7] = 0;
        motor[port10] = 0;



      }
    }

  }//while


}//taskusercontrol
