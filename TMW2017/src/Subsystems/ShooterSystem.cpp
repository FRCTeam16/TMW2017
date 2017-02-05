// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"
#include "Manager.h"

#include "ShooterSystem.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

ShooterSystem::ShooterSystem() : Subsystem("ShooterSystem") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevator = RobotMap::shooterSystemElevator;
    hopper = RobotMap::shooterSystemHopper;
    shooter1 = RobotMap::shooterSystemShooter1;
    shooter2 = RobotMap::shooterSystemShooter2;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevator->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast);
    hopper->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast);
    shooter1->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast);
    shooter2->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast);

}

void ShooterSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterSystem::Run() {
}

void ShooterSystem::Shoot() {
	std::cout << "ShooterSystem::Shoot() => Shoot now!\n";
}

void ShooterSystem::SetHopperSpeed(double speed) {
//	std::cout << "ShooterSystem::SetHopperSpeed => hopper speed is" << speed;
	hopper->Set(speed);
}
