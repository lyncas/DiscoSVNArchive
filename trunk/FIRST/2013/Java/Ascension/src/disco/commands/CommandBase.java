package disco.commands;

import disco.OI;
import disco.subsystems.*;
import edu.wpi.first.wpilibj.command.Command;

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.exampleSubsystem
 * @author Author
 */
public abstract class CommandBase extends Command {

    public static OI oi;
    // Create a single static instance of all of your subsystems
    public static Drivetrain drivetrain;
    public static Shooter shooter;
    public static Collector collector;
    public static CompressorSub compressor;

    public static void init() {
        drivetrain = new Drivetrain();
        System.out.println("command2");
        shooter = new Shooter();
        System.out.println("command3");
        collector = new Collector();
        System.out.println("command4");
        compressor = new CompressorSub();
        System.out.println("command5");
        // This MUST be here. If the OI creates Commands (which it very likely
        // will), constructing it during the construction of CommandBase (from
        // which commands extend), subsystems are not guaranteed to be
        // yet. Thus, their requires() statements may grab null pointers. Bad
        // news. Don't move it.
        oi = new OI();
        System.out.println("command1");

        // Show what command your subsystem is running on the SmartDashboard
    }

    public CommandBase(String name) {
        super(name);
    }

    public CommandBase() {
        super();
    }
}
