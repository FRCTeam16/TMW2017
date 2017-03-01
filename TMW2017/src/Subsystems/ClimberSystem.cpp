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

#include "ClimberSystem.h"
#include "../RobotMap.h"

using namespace frc;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

ClimberSystem::ClimberSystem() : Subsystem("ClimberSystem") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    climber = RobotMap::climberSystemClimber;
    prod = RobotMap::climberSystemProd;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    climber->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);
}

void ClimberSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void ClimberSystem::Run() {
	climber->Set(climberSpeed *-1);
	if (prodEnabled) {
		prod->Set(DoubleSolenoid::kForward);
	} else {
		prod->Set(DoubleSolenoid::kReverse);
	}
}

void ClimberSystem::InitManager(Manager::RunMode runMode) {
}

void ClimberSystem::SetProdEnabled(bool enabled) {
	prodEnabled = enabled;
}

void ClimberSystem::ToggleProd() {
	prodEnabled = !prodEnabled;
}

void ClimberSystem::SetClimberSpeed(double speed) {
	climberSpeed = speed;
}

void ClimberSystem::SMDB() {

}
