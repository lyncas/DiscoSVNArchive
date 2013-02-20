/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;
import disco.subsystems.Shooter;

/**
 *
 * @author Developer
 */
public class cycleShooter extends CommandBase {
    private boolean done;
    
    public cycleShooter() {
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        done=false;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        switch(shooter.getMode()){
            case Shooter.MODE_BANG:
                shooter.setMode(Shooter.MODE_OPEN_LOOP);
                break;
            case Shooter.MODE_OPEN_LOOP:
                shooter.setMode(Shooter.MODE_CLOSED_LOOP);
                break;
            case Shooter.MODE_CLOSED_LOOP:
                shooter.setMode(Shooter.MODE_BANG);
                break;
        }
        //Please retart your shooter for the changes to take effect
        if(shooter.isEnabled()){
            shooter.disable();
            shooter.enable();
        }
        done=true;
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return done;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
        end();
    }
}
