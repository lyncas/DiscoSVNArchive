/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package main;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {
    boolean stopped = true;
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
        HW.drive.setInvertedMotor(DiscoDrive.kLeftMotor, true); //Invert Left
        HW.drive.setInvertedMotor(DiscoDrive.kRightMotor, true); //Invert Right
    }

    /**
     * This function is called once every time the robot is disabled
     */
    public void disabledInit() {
        HW.frontEncoder.reset();
        HW.frontEncoder.stop();
        HW.rearEncoder.reset();
        HW.rearEncoder.stop();
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic() {
    }

    /**
     * This function is called once before Autonomous
     */
    public void autonomousInit() {
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopInit() {
        HW.frontEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.frontEncoder.start();
        HW.frontEncoder.reset();
        HW.rearEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.rearEncoder.start();
        HW.rearEncoder.reset();
    }

    public void teleopPeriodic() {
        HW.drive.basicDrive(0.0,
                            0.0,
                            HW.driveStick1.getY(),
                            HW.driveStick2.getY());
    }
}
