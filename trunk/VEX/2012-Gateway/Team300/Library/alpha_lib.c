#pragma config(Sensor, in1,    TubeSensor,          sensorLineFollower)
#pragma config(Sensor, dgtl3,  PotArm,              sensorQuadEncoder)
#pragma config(Motor,  port1,           ArmLL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           collector1,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collector2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          ArmRL,         tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FULL 127
#define AutonFULL 100
#include "PIDController.c"
//--Declare Global Variables--------------------------------------/
/* 'rotations' will be a counter for every 360 encoder clicks */
/* which is one full rotation of the wheel (ie. 2 'rotations' */
/* will equal 720.0 clicks, 2 full rotations of the wheel).   */
const float rotations = 360.0;

//NOTE 10 IS AN ARBITRARY VALUE, HAS NOT BEEN TESTED
int DeadZone = 25; //dead zone value for joysticks
int leftDrivePower, rightDrivePower; //drivetrain variables
int lightMaxValue = 0;
int tubeCount = 0;
int spinOutPrev = 0;
int fullLightCycles = 0;
int justSpunOut = 0;

/*****GENERIC FUNCTIONS********************************************************/

/*Apparently robotc doesn't like the scaling math so it's commented out as
Motor value under 10 are negligible */
//checks dead zone and scales values excluding deadzone back to 0-127
int checkDeadZone(int x) {
    //int scale=FULL/(FULL-DeadZone);
    if (abs(x) < DeadZone) {
        return 0;
    } else {
        return (x);
    }
}

int getSign(int x) {
    if (x < 0)
        return -1;
    else
        return 1;
    }

//scales input based on function, arcsin by default
int scaleInput(int input, int function) {
    if (input != 0) {
        //Squaring input scaling (technically cubic, used to preserve sign)
        //  leftDrivePower = (left^3)/(127^2);
        switch (function)
        {
            case 1 :
                return (input^3)/(127^2);
                break;
            case 2 :
                return asin(input / 127) / asin(1)*127;
                break;
            case 3 :
                return atan((input^3)/(127^2))*127/atan(127);
                break;
            default :
                return input;
        }

    } else {
        return 0;
    }
}

/*//Tube Detection
bool tube_detection() {
    if (SensorValue[DetectTube] < 3075) {
        return true
    } else {
        return false;
    }
}

/*****SET FUNCTIONS************************************************************/

//Set Arm Speed
void setArmSpeed(int speed) {
    motor[ArmLL] = motor[ArmLU] = motor[ArmRL] = motor[ArmRU] = speed;
}

//Set collector speed
void setCollectorSpeed(int speed) {
    motor[collector1] = motor[collector2] = speed;
}

//Set Drive Speed (Left & Right)
void setDriveSpeed(int speed) {
    motor[DriveRF] = motor[DriveRB] = motor[DriveLF] = motor[DriveLB] = speed;
}

//Set Right drive speed
void setDriveRSpeed(int speed) {
    motor[DriveRF] = motor[DriveRB] = speed;
}

//Set Left drive speed
void setDriveLSpeed(int speed) {
    motor[DriveLF] = motor[DriveLB] = speed;
}

//Stops drivetrain
void stopDrive() {
    setDriveSpeed(0);
}

//Stop collector
void stopCollector() {
    setCollectorSpeed(0);
}

/*****ARM FUNCTIONS************************************************************/

//Arm Lock
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
    int current_pos = SensorValue(PotArm); //reads potentiometer
            int direction; //up or down?
            int arm_diff = abs(current_pos - final_pos); //difference between current and desired points

    if (arm_diff > 100) { //potentiometer is very precise, so
        if (current_pos > final_pos) {//arm too high
            direction = 1; //will move down
        } else if (current_pos < final_pos) { //arm too low
            direction = -1; //will move up
        }
        setArmSpeed(FULL * direction);
        return 0;
    } else { //in hindsight, I don't think this is necessary
        setArmSpeed(0);
        return 1;
    }
}

//ARM TIME FUNCTION
void lock_msec(int speed, int duration) {

    setArmSpeed(speed);
    wait1Msec(duration);
    setArmSpeed(0);
}

void score(PIDController arm,int low, int high){
  setSetpoint(arm, low);
  setCollectorSpeed(127);
  setSetpoint(arm,high);
  setCollectorSpeed(0);
}

/*Collector TIME FUNCTION */

int collector(int speed, int duration) { //positive numbers for out
    setCollectorSpeed(speed);
    wait1Msec(duration);
    setCollectorSpeed(0);
    return 1;
}

int tubeCounter() {
    int motorValue;
  	short sensor_val = SensorValue(TubeSensor);
    int spinOut = vexRT[Btn6D];
  	if ((spinOut != spinOutPrev) && spinOut){ //if we just pressed the button increment tube count
	    tubeCount++;
	  }

	  spinOutPrev = spinOut; //keep track of previous button state

	  if (tubeCount > 0) {
	    motorValue = -127;
	    if (sensor_val < (lightMaxValue - 400) && justSpunOut == 0) { //if we detect we spit a tube decrement tubeCount and set the justSpunOut variable
	      tubeCount--;
        justSpunOut = 1000;
	      lightMaxValue = 0;
	    } else {
	      if (justSpunOut > 0) { //Wait before checking if we have dropped the next tube
	        justSpunOut--;
	      }
        if (lightMaxValue < sensor_val) { //keep track of largest light value while we are spining out the tubes
          lightMaxValue = sensor_val;
        }
      }
    } else if (tubeCount == 0 && justSpunOut > 0) { // if we just spit out spin the collectors in to hold the tubes
      justSpunOut--;
      motorValue = 127;
    } else { //if tube count is zero than turn off the spinners and reset max light value to zero
      lightMaxValue = 0;
      motorValue = 0;
    }

    //Override the tube counter if the driver is holding spit out
    if (spinOut) {
      motorValue = -127;
    }

    //if we are empty drop the tubeCount to zero
    if (fullLightCycles > 100) {
      tubeCount = 0;
      fullLightCycles = 0;
    } else if (sensor_val > 3000) {
      fullLightCycles++;
    }


    return motorValue;
 }

 int spinners(){
   int motorValue;
  if (vexRT[Btn6U]){
    motorValue = 127;
    tubeCount = 0;
  } else if (vexRT(Btn8U)) {
    motorValue = -127;
    tubeCount = 0;
  } else {
     if (SensorValue[TubeSensor] > 260) { //if tubeSensor plugged in
       motorValue = tubeCounter();
     } else if (vexRT[Btn6D]){ // else run spinners directly off the button
       motorValue = -127;
     } else {  //stop if the button isn't pressed
       motorValue = 0;
     }
  }
    return motorValue;
 }

/* DRIVE FUNCTIONS
 *
 * drive_forward_1msec
 * drive_straight
 * drive_straight_to_touch
 */

 /* rateFilter
 * @purpose: protect motors from sudden acceleration (teleop)
 * @param JoystickValue: raw joystick input, -127 to 127; negative values reverse
 * @param MotorValue: current motor value, -127 to 127; negative values reverse
 * @param accelRateLimit: maximum limit for acceleration
 */
int rateFilter(int JoystickValue, int MotorValue, int accelRateLimit) {
    if (JoystickValue > 0) { //Want to go fwd
        if (MotorValue >= 0) { //current motor value already going fwd
            if (JoystickValue > MotorValue) {
                MotorValue += accelRateLimit; //accelerating from fwd to faster fwd
            } else {
                MotorValue = JoystickValue; //Declarating to a value greater than zero
            }
        } else { //want to go foward but going rev
            if (MotorValue < -64) {
                MotorValue = MotorValue / 2; //slow down a little
            } else {
                MotorValue = 0; //slow down to zero for a cyle if motor is already going less than half speed
            }
        }
    } else if (JoystickValue < 0) { //Want to go rev
        if (MotorValue <= 0) { //already going rev
            if (JoystickValue > MotorValue) {
                MotorValue -= accelRateLimit; //accelerating from rev to faster rev
            } else {
                MotorValue = JoystickValue; //Declarating to a value less than zero
            }
        } else { //want to go rev but going fwd
            if (MotorValue > 64) {
                MotorValue = MotorValue / 2; //slow down a little
            } else {
                MotorValue = 0; //slow down to zero for a cyle if motor is going slowly
            }
        }
    } else { //should only be when joystick equals 0
        MotorValue = 0;
    }
    return MotorValue;
}

/* driveTank
* @purpose: Teleop tank drive
* @param leftInput: raw left joystick input, -127 to 127; negative values reverse
* @param rightInput: raw right joystick input, -127 to 127; negative values reverse
* @param scale: boolean value to enable joystick input scaling
* @param filter: boolean value to enable rate filtering
*/

void driveTank(int leftInput, int rightInput, bool scale, bool filter, int function) {
    //checks for dead zone
    leftInput = checkDeadZone(leftInput);
    rightInput = checkDeadZone(rightInput);
            //scales initial input by specified function (arcsin)
    if (scale) {
        scaleInput(leftInput,function);
        scaleInput(rightInput,function);
    }
    //sets power of drive train based on rate filter
    if (filter) {
        leftDrivePower = rateFilter(leftInput,leftDrivePower, 40);
        rightDrivePower = rateFilter(rightInput, rightDrivePower, 40);
    } else {
        leftDrivePower = leftInput;
        rightDrivePower = rightInput;
    }
    //sets motors to power values
    setDriveLSpeed(leftDrivePower);
    setDriveRSpeed(rightDrivePower);
}

/* drive_forward_msec
 * @purpose: autonomously drive robot forward for provided duration
 * @param speed: speed of motors, -127 to 127; negative values go reverse
 * @param duration: duration in milliseconds
 */
void drive_msec(int speed, int duration) {
    setDriveSpeed(speed);
    wait1Msec(duration);
    stopDrive();
}
/*

 turn (SAFE)
 * timed, no Sensor
 * in this funtion you set the speed of the left and right sides of the drive train individually
 *@param speedL: speed of left motors
 *@param speedR: speed of right motors

void turn_timed(int speedr, int speedl, duration) {
    //right drive

    setDriveRSpeed(speedl);
            //left drive
            setDriveLSpeed(speedr);
            wait1Msec(duration);
            killdrive;
}
*/