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

#include "BallPickupSystem.h"
#include "../RobotMap.h"

using namespace frc;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

BallPickupSystem::BallPickupSystem() : Subsystem("BallPickupSystem") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    ballPickup = RobotMap::ballPickupSystemBallPickup;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    ballPickup->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast);
}

void BallPickupSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void BallPickupSystem::Run() {
	frc::SmartDashboard::PutNumber("BallPickup Volts", ballPickup->GetOutputVoltage());
	frc::SmartDashboard::PutNumber("BallPickup Amps", ballPickup->GetOutputCurrent());

	ballPickup->Set(ballPickupDirection*ballPickupEnabled);
}

void BallPickupSystem::SMDB() {
	frc::SmartDashboard::PutNumber("BallPickup Volts", ballPickup->GetOutputVoltage());
	frc::SmartDashboard::PutNumber("BallPickup Amps", ballPickup->GetOutputCurrent());
}

void BallPickupSystem::SetBallPickupEnabled(bool enabled) {
	 ballPickupEnabled = enabled;
}

 void BallPickupSystem::ToggleBallPickup() {
	 ballPickupEnabled = !ballPickupEnabled;
 }


 void BallPickupSystem::ReverseBallPickup() {
	 ballPickupDirection *= -1;
	 std::cout << "BallPickupSystem => Switched ball pickup direction to " << ballPickupDirection << "\n";
 }
