#pragma config(Sensor, in1,    detectBall,          sensorReflection)
#pragma config(Sensor, in2,    gyro,                sensorGyro)
#pragma config(Sensor, dgtl1,  btnLiftUpL,          sensorTouch)
#pragma config(Sensor, dgtl2,  btnLiftUpR,          sensorTouch)
#pragma config(Sensor, dgtl3,  btnLiftDownL,        sensorTouch)
#pragma config(Sensor, dgtl4,  btnLiftDownR,        sensorTouch)
#pragma config(Sensor, dgtl5,  btnBackL,            sensorTouch)
#pragma config(Sensor, dgtl6,  btnBackR,            sensorTouch)
#pragma config(Sensor, dgtl7,  btnFrontL,           sensorTouch)
#pragma config(Sensor, dgtl8,  btnFrontR,           sensorTouch)
#pragma config(Sensor, dgtl9,  encL,                sensorQuadEncoder)
#pragma config(Sensor, dgtl11, encR,                sensorQuadEncoder)
#pragma config(Motor,  port1,           rightFront,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           rightMiddle,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           rightBack,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           suckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           suckL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           liftR,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           liftL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           leftBack,      tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMiddle,    tmotorNormal, openLoop)
#pragma config(Motor,  port10,          leftFront,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

/*INCLUDES*/
#include "Vex_Competition_Includes.c"
#include "zeta_lib.c"

/*DEFINITIONS*/
#define FULL 127


/*PRE AUTONOMOUS*//////////////////////////////////////////////////////////////
void pre_auton() {}

/*AUTONOMOUS*//////////////////////////////////////////////////////////////////
task autonomous() {
  //drive backwards to low goal
  drive_to_tower(FULL, -1);
  //score preload
  suck_msec(-FULL,900);
  //return home
  drive_forward_msec(FULL, 600);

  /////////Insert button control here//////////////
  ///User loads 4 and lines up with middle tower///

  //drive to tower
  drive_to_tower(FULL, -1);
  //raise lift
  lift_up(FULL);
  //spit out/score
  suck_msec(-FULL,900);
  //lower lift
  lift_down(FULL);
  //Drive home
  drive_forward_msec(FULL, 2000);
}//Auton

/*TELE OP*//////////////////////////////////////////////////////////////////////
task usercontrol() {

  //Arcade functions: Enable this when enabling arcade
  /*int joy_x;            // will hold the X value of the analog stick (choices below)
  int joy_y;            // will hold the Y value of the analog stick (choices below)
  int threshold = 10;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)
  */
  //

  while (true) {

    // drive
    //tank
    setDriveLSpeed(vexRT[Ch3]);
    setDriveRSpeed(vexRT[Ch2]);

    //arcade
    /*
    joy_x = vexRT[Ch1];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
    joy_y = vexRT[Ch2];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

    // Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
    if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y > 0))
    {
    motor[leftMotor]  = (joy_y + joy_x)/2;
    motor[rightMotor] = (joy_y - joy_x)/2;
    }
    // Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
    else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y < 0))
    {
    motor[leftMotor]  = (joy_y - joy_x)/2;
    motor[rightMotor] = (joy_y + joy_x)/2;
    }
    // Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
    else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
    {
    motor[leftMotor]  = joy_x;
    motor[rightMotor] = (-1 * joy_x);
    }
    // Standing still: (both abs(X) and abs(Y) are below the threshold)
    else
    {
    motor[leftMotor]  = 0;
    motor[rightMotor] = 0;
    }
    */

    //  suck
    setSuckLSpeed((vexRT[Btn5U] - vexRT[Btn5D])*FULL);
    setSuckRSpeed((vexRT[Btn6U] - vexRT[Btn6D])*FULL);

    //raise lift
    setLiftSpeed((vexRT[Btn7U] - vexRT[Btn7D])*FULL);


    /////Auto Controls


    //auto raise suck
    if ((vexRT[Btn8U]) == 1) {
      if (SensorValue[detectBall] < 200) {
        setSuckSpeed(FULL);
      }
      else {
        killSuck();
      }


      //auto raise lift
      if ((vexRT[Btn7L]) == 1) {
        lift_btn(FULL, 1);
      }
      /*if ((vexRT[Btn7L]) == 1) {
      if (SensorValue[btnLiftUpL] == 0) {
      setLiftSpeed(FULL);
      }
      else {
      killLift();
      }
      }
      */

      //auto lower lift
      if ((vexRT[Btn7R]) == 1) {
        lift_btn(FULL, -1);
      }
      /*if ((vexRT[Btn7R]) == 1) {
      if (SensorValue[btnLiftDownL] == 0) {
      setLiftSpeed(FULL);
      }
      else {
      killLift();
      }
      }*/

    }//WHILE
  }//TELEOP

}/*END*/
