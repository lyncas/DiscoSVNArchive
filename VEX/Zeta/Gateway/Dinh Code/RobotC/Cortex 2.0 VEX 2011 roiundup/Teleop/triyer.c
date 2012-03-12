#pragma config(Sensor, in1,    pot,                 sensorPotentiometer)
#pragma config(Sensor, dgtl1,  touchl,              sensorNone)
#pragma config(Sensor, dgtl2,  ncoderL,             sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  ncoderR,             sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchh,              sensorNone)
#pragma config(Motor,  port6,           port6,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           port7,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           port8,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           port9,         tmotorNormal, openLoop)
#pragma config(Motor,  port10,          Claw,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Lance_Function_Library_v1.0.c" //Funtion Library

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
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  arm_grounded = SensorValue[pot];
  //////////////////////////////////////////////////////////////////////////////////////////////
  descore_low_point = arm_grounded + 365;    low_lock_point = arm_grounded + 1081; //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point



  /////////////////////////////////////
  descore_high_point = arm_grounded + 1100;//<<<<---------------------------------------------------run debugger in tele op and see what this value is,
  //put that value where the XXXXX's are
  ////////////////////////////////////////



  high_lock_point = arm_grounded + 1500; //high goal potentiometer reading
  /////////////////////////////////////////////////////////////////////

  arm_grounded += 250;
}

task autonomous()
{
  pre_auton();


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
        goal_lock = 2;
    }


    if(goal_lock == -1)
      lock(low_lock_point); //brings to low lock point
    else if(goal_lock == 1)
      lock(high_lock_point);//moves arm to high lock point
    ///////////////////////////////////////////////////////////////NEW STUFF TAKE THIS OUT IF IT DOESNT WORK
    else if (goal_lock == 2)
      lock(descore_low_point);//moves arm to descore lock point
    else if(goal_lock == 3)
      lock(descore_high_point);
    //////////////////////////////////////////////////////////////


    switch(vexRT[Btn6U] - vexRT[Btn6D]) //manual arm control
    {
    case  1:motor[port6] =-127;
      motor[port7] = -127;
      motor[port8] = -127;
      motor[port9] = -6127;

      goal_lock = 0;  //unlocks arm
      break;

    case -1:motor[port6] = 127;
      motor[port7] = 127;
      motor[port8] = 127;
      motor[port9] = 127;
      goal_lock = 0;  //unlocks arm
      break;

    case  0:if(goal_lock == 0 ) {
        motor[port6] = 0;
        motor[port7] = 0;
        motor[port8] = 0;
        motor[port9] = 0;
        break;
      }//switch
    }

    //Claw
    switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
    case  1:motor[port10] = -127; //Close
      break;
    case -1:motor[port10] = 127; //Open
      break;
    case  0:motor[port10] = 0; //Do nothing
      break;
    }
    //Drive Train
    {


      motor[port2] = -vexRT[Ch2];//:port6
      motor[port3] = -vexRT[Ch2];//:port7
      motor[port4] = -vexRT[Ch3];
      motor[port5] = -vexRT[Ch3];

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
