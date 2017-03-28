// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "CANTalon.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "AHRS.h"
#include <Util/BSGyro.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::driveBaseFrontLeftSteer;
std::shared_ptr<AnalogInput> RobotMap::driveBaseFrontLeftPos;
std::shared_ptr<PIDController> RobotMap::driveBaseFrontLeft;
std::shared_ptr<CANTalon> RobotMap::driveBaseFrontRightSteer;
std::shared_ptr<AnalogInput> RobotMap::driveBaseFrontRightPos;
std::shared_ptr<PIDController> RobotMap::driveBaseFrontRight;
std::shared_ptr<CANTalon> RobotMap::driveBaseRearLeftSteer;
std::shared_ptr<AnalogInput> RobotMap::driveBaseRearLeftPos;
std::shared_ptr<PIDController> RobotMap::driveBaseRearLeft;
std::shared_ptr<CANTalon> RobotMap::driveBaseRearRightSteer;
std::shared_ptr<AnalogInput> RobotMap::driveBaseRearRightPos;
std::shared_ptr<PIDController> RobotMap::driveBaseRearRight;
std::shared_ptr<CANTalon> RobotMap::driveBaseFrontLeftDrive;
std::shared_ptr<CANTalon> RobotMap::driveBaseFrontRightDrive;
std::shared_ptr<CANTalon> RobotMap::driveBaseRearLeftDrive;
std::shared_ptr<CANTalon> RobotMap::driveBaseRearRightDrive;
std::shared_ptr<PowerDistributionPanel> RobotMap::driveBasePDP;
std::shared_ptr<CANTalon> RobotMap::gearSystemGearPickUp;
std::shared_ptr<Solenoid> RobotMap::gearSystemLift;
std::shared_ptr<Solenoid> RobotMap::gearSystemRotate;
std::shared_ptr<Solenoid> RobotMap::gearSystemExtend;
std::shared_ptr<DoubleSolenoid> RobotMap::gearSystemSqueeze;
std::shared_ptr<Compressor> RobotMap::gearSystemGearCompressor;
std::shared_ptr<AnalogInput> RobotMap::gearSystemPressureGauge;
std::shared_ptr<CANTalon> RobotMap::climberSystemClimber;
std::shared_ptr<DoubleSolenoid> RobotMap::climberSystemProd;
std::shared_ptr<CANTalon> RobotMap::shooterSystemElevator;
std::shared_ptr<CANTalon> RobotMap::shooterSystemHopper;
std::shared_ptr<CANTalon> RobotMap::shooterSystemShooter1;
std::shared_ptr<CANTalon> RobotMap::shooterSystemShooter2;
std::shared_ptr<CANTalon> RobotMap::ballPickupSystemBallPickup;
std::shared_ptr<DigitalOutput> RobotMap::gearUpStatusIndicator;
std::shared_ptr<DigitalOutput> RobotMap::indicatorLight;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<BSGyro> RobotMap::gyro;


void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    driveBaseFrontLeftSteer.reset(new CANTalon(2));
    lw->AddActuator("DriveBase", "FrontLeftSteer", driveBaseFrontLeftSteer);
    
    driveBaseFrontLeftPos.reset(new AnalogInput(0));
    lw->AddSensor("DriveBase", "FrontLeftPos", driveBaseFrontLeftPos);
    
    driveBaseFrontLeft.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ driveBaseFrontLeftPos.get(), driveBaseFrontLeftSteer.get(), 0.02));
    lw->AddActuator("DriveBase", "FrontLeft", driveBaseFrontLeft);
    driveBaseFrontLeft->SetContinuous(false); driveBaseFrontLeft->SetAbsoluteTolerance(0.2); 
        driveBaseFrontLeft->SetOutputRange(-1.0, 1.0);
    driveBaseFrontRightSteer.reset(new CANTalon(4));
    lw->AddActuator("DriveBase", "FrontRightSteer", driveBaseFrontRightSteer);
    
    driveBaseFrontRightPos.reset(new AnalogInput(1));
    lw->AddSensor("DriveBase", "FrontRightPos", driveBaseFrontRightPos);
    
    driveBaseFrontRight.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ driveBaseFrontRightPos.get(), driveBaseFrontRightSteer.get(), 0.02));
    lw->AddActuator("DriveBase", "FrontRight", driveBaseFrontRight);
    driveBaseFrontRight->SetContinuous(false); driveBaseFrontRight->SetAbsoluteTolerance(0.2); 
        driveBaseFrontRight->SetOutputRange(-1.0, 1.0);
    driveBaseRearLeftSteer.reset(new CANTalon(6));
    lw->AddActuator("DriveBase", "RearLeftSteer", driveBaseRearLeftSteer);
    
    driveBaseRearLeftPos.reset(new AnalogInput(2));
    lw->AddSensor("DriveBase", "RearLeftPos", driveBaseRearLeftPos);
    
    driveBaseRearLeft.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ driveBaseRearLeftPos.get(), driveBaseRearLeftSteer.get(), 0.02));
    lw->AddActuator("DriveBase", "RearLeft", driveBaseRearLeft);
    driveBaseRearLeft->SetContinuous(false); driveBaseRearLeft->SetAbsoluteTolerance(0.2); 
        driveBaseRearLeft->SetOutputRange(-1.0, 1.0);
    driveBaseRearRightSteer.reset(new CANTalon(8));
    lw->AddActuator("DriveBase", "RearRightSteer", driveBaseRearRightSteer);
    
    driveBaseRearRightPos.reset(new AnalogInput(3));
    lw->AddSensor("DriveBase", "RearRightPos", driveBaseRearRightPos);
    
    driveBaseRearRight.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ driveBaseRearRightPos.get(), driveBaseRearRightSteer.get(), 0.02));
    lw->AddActuator("DriveBase", "RearRight", driveBaseRearRight);
    driveBaseRearRight->SetContinuous(false); driveBaseRearRight->SetAbsoluteTolerance(0.2); 
        driveBaseRearRight->SetOutputRange(-1.0, 1.0);
    driveBaseFrontLeftDrive.reset(new CANTalon(1));
    lw->AddActuator("DriveBase", "FrontLeftDrive", driveBaseFrontLeftDrive);
    
    driveBaseFrontRightDrive.reset(new CANTalon(3));
    lw->AddActuator("DriveBase", "FrontRightDrive", driveBaseFrontRightDrive);
    
    driveBaseRearLeftDrive.reset(new CANTalon(5));
    lw->AddActuator("DriveBase", "RearLeftDrive", driveBaseRearLeftDrive);
    
    driveBaseRearRightDrive.reset(new CANTalon(7));
    lw->AddActuator("DriveBase", "RearRightDrive", driveBaseRearRightDrive);
    
    driveBasePDP.reset(new PowerDistributionPanel(0));
    lw->AddSensor("DriveBase", "PDP", driveBasePDP);
    
    gearSystemGearPickUp.reset(new CANTalon(9));
    lw->AddActuator("GearSystem", "GearPickUp", gearSystemGearPickUp);
    
    gearSystemLift.reset(new Solenoid(0, 0));
    lw->AddActuator("GearSystem", "Lift", gearSystemLift);
    
    gearSystemRotate.reset(new Solenoid(0, 1));
    lw->AddActuator("GearSystem", "Rotate", gearSystemRotate);
    
    gearSystemExtend.reset(new Solenoid(0, 2));
    lw->AddActuator("GearSystem", "Extend", gearSystemExtend);
    
    gearSystemSqueeze.reset(new DoubleSolenoid(0, 3, 4));
    lw->AddActuator("GearSystem", "Squeeze", gearSystemSqueeze);
    
    gearSystemGearCompressor.reset(new Compressor(0));
    
    
    gearSystemPressureGauge.reset(new AnalogInput(4));
    lw->AddSensor("GearSystem", "PressureGauge", gearSystemPressureGauge);
    
    climberSystemClimber.reset(new CANTalon(10));
    lw->AddActuator("ClimberSystem", "Climber", climberSystemClimber);
    
    climberSystemProd.reset(new DoubleSolenoid(0, 5, 6));
    lw->AddActuator("ClimberSystem", "Prod", climberSystemProd);
    
    shooterSystemElevator.reset(new CANTalon(13));
    lw->AddActuator("ShooterSystem", "Elevator", shooterSystemElevator);
    
    shooterSystemHopper.reset(new CANTalon(15));
    lw->AddActuator("ShooterSystem", "Hopper", shooterSystemHopper);
    
    shooterSystemShooter1.reset(new CANTalon(11,1));
    lw->AddActuator("ShooterSystem", "Shooter1", shooterSystemShooter1);
    
    shooterSystemShooter2.reset(new CANTalon(12));
    lw->AddActuator("ShooterSystem", "Shooter2", shooterSystemShooter2);
    
    ballPickupSystemBallPickup.reset(new CANTalon(14));
    lw->AddActuator("BallPickupSystem", "BallPickup", ballPickupSystemBallPickup);
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    //ahrs.reset(new AHRS(I2C::Port::kMXP));
    gyro.reset(new BSGyro(I2C::Port::kMXP));

    gearUpStatusIndicator.reset(new frc::DigitalOutput(2));
    indicatorLight.reset(new frc::DigitalOutput(3));
}
