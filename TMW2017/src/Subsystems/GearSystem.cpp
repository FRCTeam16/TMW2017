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


#include "GearSystem.h"
#include "../RobotMap.h"

using namespace frc;
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

GearSystem::GearSystem() : Subsystem("GearSystem") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    gearPickUp = RobotMap::gearSystemGearPickUp;
    lift = RobotMap::gearSystemLift;
    rotate = RobotMap::gearSystemRotate;
    extend = RobotMap::gearSystemExtend;
    squeeze = RobotMap::gearSystemSqueeze;
    gearCompressor = RobotMap::gearSystemGearCompressor;
    pressureGauge = RobotMap::gearSystemPressureGauge;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    gearPickUp->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);
    gearPickupProcess.reset(new GearPickupProcess(this));
}

void GearSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void GearSystem::SetGearBarSpeed(double speed) {
	if (!gearPickupVoltageTripped && (gearPickUp->GetOutputVoltage() < gearPickupVoltageThreshold)) {
		gearPickUpSpeed = speed;
	} else {
		gearPickUpSpeed = 0.0;
		gearPickupVoltageTripped = true;
	}

	if (fabs(speed) <= resetRange) {
		gearPickupVoltageTripped = false;
	}

	gearPickupProcess->Run();
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void GearSystem::Run() {
	gearPickUp->Set(gearPickUpSpeed);
}

void GearSystem::InitManager() {
	SetLiftEnabled(false);
	SetRotateEnabled(false);
	extendEnabled = false;
	squeezeEnabled = false;
}

void GearSystem::ToggleLift() {
	liftEnabled = !liftEnabled;
	lift->Set(liftEnabled);
}
void GearSystem::SetLiftEnabled(bool enabled) {
	liftEnabled = enabled;
	lift->Set(liftEnabled);
}

void GearSystem::ToggleRotate() {
	rotateEnabled = !rotateEnabled;
	rotate->Set(rotateEnabled);
}
void GearSystem::SetRotateEnabled(bool enabled) {
	rotateEnabled = enabled;
	rotate->Set(rotateEnabled);
}

void GearSystem::ToggleExtend() {
	extendEnabled = !extendEnabled;
	extend->Set(extendEnabled);
}
void GearSystem::SetExtendEnabled(bool enabled) {
	extendEnabled = enabled;
	extend->Set(extendEnabled);
}
void GearSystem::ToggleSqueeze() {
	squeezeEnabled = !squeezeEnabled;
	if (squeezeEnabled) {
		squeeze->Set(DoubleSolenoid::kForward);
	} else {
		squeeze->Set(DoubleSolenoid::kReverse);
	}
}
void GearSystem::SetSqueezeEnabled(bool enabled) {
	squeezeEnabled = !enabled;	// reverse incoming since toggle will reverse it back
	ToggleSqueeze();
}

void GearSystem::PickUpGear() {
	if (!gearPickupProcess->Start()) {
		// TODO: ERROR here, should we display on SMDB?
	}
}

void GearSystem::SMDB() {
	frc::SmartDashboard::PutNumber("GearPickup Volts", gearPickUp->GetOutputVoltage());
	frc::SmartDashboard::PutNumber("GearPickup Amps", gearPickUp->GetOutputCurrent());
	frc::SmartDashboard::PutNumber("Pressure Gauge",
			pressureGauge->GetAverageVoltage() * 40); 	// 0 to 5 0 to 200
}



// ***************************************************************************/


GearPickupProcess::GearPickupProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kInit, StateInfo {100, kLift}));
	stateMapping.insert(std::make_pair(kLift, StateInfo {1000, kRotate}));
	stateMapping.insert(std::make_pair(kRotate, StateInfo {1000, kExtend}));
	stateMapping.insert(std::make_pair(kExtend, StateInfo {1000, kSqueeze}));
	stateMapping.insert(std::make_pair(kSqueeze, StateInfo {1000, kComplete}));
	stateMapping.insert(std::make_pair(kComplete, StateInfo {10, kStopped}));
}


bool GearPickupProcess::Start() {
	if (IsStopped()) {
		timer->Reset();
		currentState = kInit;
		firstStateRun = true;
		return true;
	} else {
		std::cout << "ERROR: Unable to start gear pickup process, already in progress\n;";
		return false;
	}
}

void GearPickupProcess::Run() {
	if (IsStopped()) {
		return;
	} else if (timer->HasPeriodPassed(stateMapping[currentState].waitTime)) {
		// Handle state transition
		timer->Reset();
		currentState = stateMapping[currentState].nextState;
		firstStateRun = true;
	}

	switch (currentState) {
	case ProcessState::kInit:
		gearSystem->SetGearBarSpeed(0.5);
		break;
	case ProcessState::kLift:
		gearSystem->SetGearBarSpeed(0.0);
		gearSystem->SetLiftEnabled(true);
		break;
	case ProcessState::kRotate:
		gearSystem->SetRotateEnabled(true);
		break;
	case ProcessState::kExtend:
		gearSystem->SetExtendEnabled(true);
		break;
	case ProcessState::kSqueeze:
		gearSystem->SetSqueezeEnabled(true);
		break;
	case ProcessState::kComplete:
		currentState = kStopped;
		break;
	case ProcessState::kStopped:
		std::cout << "ERROR: should not handle kStopped in state machine\n";
		break;
	}
	firstStateRun = false;
}

bool GearPickupProcess::IsStopped() {
	return ProcessState::kStopped == currentState;
}

