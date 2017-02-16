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

    Preferences *prefs = Preferences::GetInstance();
    const double P = prefs->GetDouble("ShootP", 0);
    const double I = prefs->GetDouble("ShootI", 0);
    const double D = prefs->GetDouble("ShootD", 0);
    const double F = prefs->GetDouble("ShootF", 0.035);
    shooterRPM = prefs->GetDouble("ShootRPM");
    const double shootRampRate = prefs->GetDouble("ShootVoltRampRate", 6.0);

    if (!prefs->ContainsKey("ShootP")) {
    	prefs->PutDouble("ShootP", P);
    }
    if (!prefs->ContainsKey("ShootI")) {
		prefs->PutDouble("ShootI", I);
	}
    if (!prefs->ContainsKey("ShootD")) {
		prefs->PutDouble("ShootD", D);
	}
    if (!prefs->ContainsKey("ShootF")) {
		prefs->PutDouble("ShootF", F);
	}
    if (!prefs->ContainsKey("ShootRPM")) {
		prefs->PutDouble("ShootRPM", shooterRPM);
	}
    if (!prefs->ContainsKey("ShootVoltRampRate")) {
    	prefs->PutDouble("ShootVoltRampRate", shootRampRate);
    }


    shooter1->SetControlMode(CANSpeedController::kSpeed);
    shooter1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    shooter1->SetPID(P, I, D, F);
    shooter1->ConfigPeakOutputVoltage(0.0, -12.0);
    shooter1->SetVoltageRampRate(shootRampRate);

    shooter2->SetControlMode(CANSpeedController::kFollower);
    shooter2->Set(shooter1->GetDeviceID());
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
	if (shooterMotorsEnabled) {
		Preferences *prefs = Preferences::GetInstance();
		const double shooterSpeedRpm = prefs->GetDouble("ShootRPM", 3000);
	    const double P = prefs->GetDouble("ShootP", 0);
	    const double I = prefs->GetDouble("ShootI", 0);
	    const double D = prefs->GetDouble("ShootD", 0);
	    const double F = prefs->GetDouble("ShootF", 0.035);
	    shooter1->SetPID(P, I, D, F);
		shooter1->SetSetpoint(shooterSpeedRpm * -1);
	} else {
		shooter1->SetSetpoint(0);
	}
	const bool autoReverseHopper = ShouldAutoReverseHopper();
	if (fireEnabled) {
		if (autoReverseHopper) {
			std::cout << "autoReverseHopper TRUE, reversing direction\n";
			hopper->Set(-1 * firingHopperSpeed);
		} else {
			std::cout << "autoReverseHopper FALSE,, normal direction\n";
			hopper->Set(firingHopperSpeed);
		}
		elevator->Set(-1.0);
	}
	else {
		// Use user inputs
		// If/when these are not on the sticks, set to 0
		hopper->Set(hopperSpeed);
		elevator->Set(0);
	}
}

void ShooterSystem::SMDB() {
	frc::SmartDashboard::PutNumber("ShootRPM", shooter1->Get());
	frc::SmartDashboard::PutNumber("Hopper Amps", hopper->GetOutputCurrent());

	hopperAmperageThreshold = frc::SmartDashboard::GetNumber("Hopper Amp Threshold", 6);
	frc::SmartDashboard::PutNumber("Hopper Amp Threshold", hopperAmperageThreshold);
	hopperCheckScanCountThreshold = frc::SmartDashboard::GetNumber("Hopper Scan Threshold", 15);
	frc::SmartDashboard::PutNumber("Hopper Scan Threshold", hopperAmperageThreshold);
	reverseHopperCountDownTimerStartValue = frc::SmartDashboard::GetNumber("Hopper Reverse Start", 50);
	frc::SmartDashboard::PutNumber("Hopper Reverse Start", reverseHopperCountDownTimerStartValue);
}

bool ShooterSystem::ShouldAutoReverseHopper() {
	const bool tripped = (hopper->GetOutputCurrent() > hopperAmperageThreshold);
	if (tripped) {
		hopperCheckScanCount++;
		std::cout << "Checking for Tripped Hopper " << hopperCheckScanCount << "\n";
		if ((hopperCheckScanCount > hopperCheckScanCountThreshold) &&  !hopperAmperageTripped) {
			std::cout << "Tripped Hopper, Reversing!\n";
			hopperAmperageTripped = true;
			reverseHopperCountdownTimer = reverseHopperCountDownTimerStartValue;
		}
	} else {
		hopperCheckScanCount = 0;
	}

	if (hopperAmperageTripped) {
		std::cout << "Hopper Reverse Countdown Timer: " << reverseHopperCountdownTimer << "\n";
	}

	if (hopperAmperageTripped && (--reverseHopperCountdownTimer == 0)) {
		std::cout << "Resetting Hopper Tripped Status\n";
		hopperAmperageTripped = false;
		hopperCheckScanCount = 0.0;
	}
	return hopperAmperageTripped;
}



void ShooterSystem::InitManager(Manager::RunMode runMode) {
	SetHopperSpeed(0.0);
	SetFireEnabled(false);
	shooterMotorsEnabled = false;
}


void ShooterSystem::SetFireEnabled(bool enabled) {
	fireEnabled = enabled;
}

void ShooterSystem::ToggleShooter() {
	shooterMotorsEnabled = !shooterMotorsEnabled;
}

void ShooterSystem::SetHopperSpeed(double speed) {
	hopperSpeed = speed;
}

