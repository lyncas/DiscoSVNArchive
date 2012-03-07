#pragma config(Sensor, dgtl1,  liftPneu1,           sensorDigitalOut)
#pragma config(Sensor, dgtl2,  liftPneu2,           sensorDigitalOut)
#pragma config(Motor,  port1,           liftR,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontR,        tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontR2,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           backR,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           frontL,        tmotorNormal, openLoop)
#pragma config(Motor,  port6,           frontL2,       tmotorNormal, openLoop)
#pragma config(Motor,  port7,           backL,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           collectorR,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collectorL,   tmotorNormal, openLoop)
#pragma config(Motor,  port10,          liftL,         tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
/*To example of use:
setSuckSpeed(127);
type desired speed, between -127 and 127, between ()*/
void setSuckSpeed(int speed) {
  motor[collectorL] = motor[collectorR] = speed;
}


void pre_auton()
{
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


task autonomous()
{
  wait1Msec(1000);

  motor[frontL] = motor[frontL2] = motor[backL] = -127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(900);

}


task usercontrol()
{

  while (true)
  {

    motor[frontL] = motor[frontL2] = motor[backL] = vexRT[Ch3];//L drivetrain speed = y axis of L joystick values
    motor[frontR] = motor[frontR2] = motor[backR] = vexRT[Ch2];//R drivetrain speed = y axis of R joystick values


    if(vexRT[Btn6U] == 1) {
      motor[collectorR] = motor[collectorL] = 127;//if btn 6u is pressed turn both collector motors at full suck in
    }
    else if(vexRT[Btn6D] == 1) {
      motor[collectorR] = motor[collectorL] = -127;//if btn 6d is pressed turn both collector motors at full spitout
    }
    else {
      motor[collectorR] = motor[collectorL] = 0;//if no btn is pressed turn neither motors
    }


    if(vexRT[Btn5U] == 1)         // If button 5U is pressed:
    {
      SensorValue[liftPneu1] = SensorValue[liftPneu2] = 1;  // ...both pneumatics shoot out.
    }
    else if(vexRT[Btn5D] == 1)    // If button 5D is pressed:
    {
      SensorValue[liftPneu1] = SensorValue[liftPneu2] = 0;  // ...both pneumatics shoot in.
    }


  }
}