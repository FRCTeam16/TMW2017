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

const bool EXTEND_ENABLED = false;
const bool EXTEND_DISABLED = true;

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
    gearResetProcess.reset(new GearResetProcess(this));
    gearEjectProcess.reset(new GearEjectProcess(this));

}

void GearSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void GearSystem::SetGearBarSpeed(double speed) {
	if (!AnyProcessesRunning()) {
		gearPickUpSpeed = speed;
	}
}

void GearSystem::SetGearBarSpeedByProcess(double speed) {
	std::cout << "GearSystem::SetGearBarSpeedByProcess\n";
	gearPickUpSpeed = speed;
}

bool GearSystem::CheckGearBar() {
	const bool tripped = (gearPickUp->GetOutputCurrent() > gearPickupAmperageThreshold);
	if (tripped) {
		gearCheckScanCount++;
		std::cout << "Tripped Gear Pickup " << gearCheckScanCount << "\n";
		if (gearCheckScanCount > gearCheckScanCountThreshold) {
			gearPickupAmperageTripped = true;
			if (!AnyProcessesRunning()
					&& rotateEnabled == true
					&& extendEnabled == false) {
				std::cout << "Autostarting gear pickup process\n";
				gearPickupProcess->Start();
			}
		}
	}

	return gearPickupAmperageTripped;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void GearSystem::Run() {
	if (!gearPickupAmperageTripped && !CheckGearBar()) {
		gearPickUp->Set(gearPickUpSpeed);
	} else {
		gearPickUp->Set(0.0);
	}
	if (fabs(gearPickUpSpeed) <= resetRange) {
		gearPickupAmperageTripped = false;
		gearCheckScanCount = 0;
	}

	gearPickupProcess->Run();
	gearEjectProcess->Run();
	gearResetProcess->Run();
}

bool GearSystem::AnyProcessesRunning() {
	return !gearPickupProcess->IsStopped() ||
		   !gearEjectProcess->IsStopped() ||
		   !gearResetProcess->IsStopped();
}

void GearSystem::InitManager() {
	SetLiftEnabled(false);
	SetRotateEnabled(false);
	SetExtendEnabled(EXTEND_DISABLED);
	SetSqueezeEnabled(false);
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
		squeeze->Set(DoubleSolenoid::kReverse);
	} else {
		squeeze->Set(DoubleSolenoid::kForward);
	}
}
void GearSystem::SetSqueezeEnabled(bool enabled) {
	squeezeEnabled = !enabled;	// reverse incoming since toggle will reverse it back
	ToggleSqueeze();
}

void GearSystem::PickUpGear() {
	std::cout << "GearSystem::PickUpGear\n";
	if (!gearPickupProcess->Start()) {
		// TODO: ERROR here, should we display on SMDB?
		std::cerr << "************************ Unable to start gear pick up process\n";
	}
}

void GearSystem::EjectGear() {
	std::cout << "GearSystem::EjectGear\n";
	if (!gearEjectProcess->Start()) {
		// Error on SMDB?
	}
}

void GearSystem::ResetGear() {
	std::cout << "GearSystem::ResetGear\n";
	if (!gearResetProcess->Start()) {
		// Error on SMDB?
	}
}

void GearSystem::SMDB() {
	frc::SmartDashboard::PutNumber("GearPickup Volts", gearPickUp->GetOutputVoltage());
	frc::SmartDashboard::PutNumber("GearPickup Amps", gearPickUp->GetOutputCurrent());
	frc::SmartDashboard::PutNumber("Pressure Gauge",
			pressureGauge->GetAverageVoltage() * 40); 	// 0 to 5 0 to 200

	gearPickupAmperageThreshold = frc::SmartDashboard::GetNumber("GearPickupAmpTrigger", 6.0);
	frc::SmartDashboard::PutNumber("GearPickupAmpTrigger", gearPickupAmperageThreshold);
	gearCheckScanCountThreshold = frc::SmartDashboard::GetNumber("GearPickupTripScans", 5);
	frc::SmartDashboard::PutNumber("GearPickupTripScans", gearCheckScanCountThreshold);
}



// ***************************************************************************/
//1-pickup - GearPickupProcess
//2-eject - GearEjectProcess
//3-reset - GearResetProcess

GearPickupProcess::GearPickupProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kInit, StateInfo {0.25, kExtend}));
	stateMapping.insert(std::make_pair(kExtend, StateInfo {0.25 ,kSqueeze}));
	stateMapping.insert(std::make_pair(kSqueeze, StateInfo {0.25, kLift}));
	stateMapping.insert(std::make_pair(kLift, StateInfo {0.5, kComplete}));
	timer->Start();
	std::cout << "GearPickupProcess::GearPickupProcess\n";
}


bool GearPickupProcess::Start() {
	std::cout << "GearPickupProcess::Start currentState = " << currentState << "\n";
	if (IsStopped()) {
		timer->Reset();
		currentState = kInit;
		firstStateRun = true;
		return true;
	} else {
		std::cerr << "ERROR: Unable to start gear pickup process, already in progress\n;";
		return false;
	}
}


void GearPickupProcess::Run() {
	if (IsStopped()) {
		return;
	} else if (timer->HasPeriodPassed(stateMapping[currentState].waitTime)) {
		// Handle state transition
		std::cout << "Doing first run of state!\n";
		timer->Reset();
		currentState = stateMapping[currentState].nextState;
		firstStateRun = true;
	}

	switch (currentState) {
	case ProcessState::kInit:
		std::cout << "handling kInit\n";
		gearSystem->SetGearBarSpeedByProcess(0.5);
		break;
	case ProcessState::kExtend:
		std::cout << "handling kExtend\n";
		gearSystem->SetExtendEnabled(EXTEND_ENABLED);
		break;
	case ProcessState::kSqueeze:
		std::cout << "handling kSqueeze\n";
		gearSystem->SetSqueezeEnabled(true);
		gearSystem->SetGearBarSpeedByProcess(0.0);
		break;
	case ProcessState::kLift:
		std::cout << "handling kLift\n";
		gearSystem->SetLiftEnabled(false);
		gearSystem->SetRotateEnabled(false);
		break;
	case ProcessState::kComplete:
		std::cout << "handling kComplete\n";
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

//*************2

GearEjectProcess::GearEjectProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	std::cout << "GearEjectProcess::GearEjectProcess\n";
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kRelease, StateInfo {0.1, kExtend}));
	stateMapping.insert(std::make_pair(kExtend, StateInfo {0.1, kRetract}));
	stateMapping.insert(std::make_pair(kRetract, StateInfo {0.25, kMotorOff}));
	stateMapping.insert(std::make_pair(kMotorOff, StateInfo {0.1, kComplete}));
	timer->Start();
}


bool GearEjectProcess::Start() {
	std::cout << "GearEjectProcess::Start\n";
	if (IsStopped()) {
		timer->Reset();
		currentState = kRelease;
		firstStateRun = true;
		return true;
	} else {
		std::cout << "ERROR: Unable to start gear eject process, already in progress\n;";
		return false;
	}
}

void GearEjectProcess::Run() {
	if (IsStopped()) {
		return;
	} else if (timer->HasPeriodPassed(stateMapping[currentState].waitTime)) {
		// Handle state transition
		timer->Reset();
		currentState = stateMapping[currentState].nextState;
		firstStateRun = true;
	}

	switch (currentState) {
	case ProcessState::kRelease:
		gearSystem->SetSqueezeEnabled(false);
		break;
	case ProcessState::kExtend:
		gearSystem->SetExtendEnabled(EXTEND_ENABLED);
		gearSystem->SetGearBarSpeedByProcess(-0.5);
		break;
	case ProcessState::kRetract:
		gearSystem->SetExtendEnabled(EXTEND_DISABLED);
		break;
	case ProcessState::kComplete:
		currentState = kStopped;
		break;
	case ProcessState::kMotorOff:
		gearSystem->SetGearBarSpeedByProcess(0.0);
		break;
	case ProcessState::kStopped:
		std::cout << "ERROR: should not handle kStopped in state machine\n";
		break;
	}
	firstStateRun = false;
}

bool GearEjectProcess::IsStopped() {
	return ProcessState::kStopped == currentState;
}

//*************3

GearResetProcess::GearResetProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	std::cout << "GearResetProcess::GearResetProcess\n";
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kInit, StateInfo {0.5, kComplete}));
	timer->Start();
}


bool GearResetProcess::Start() {
	std::cout << "GearResetProcess::Start\n";
	if (IsStopped()) {
		timer->Reset();
		currentState = kInit;
		firstStateRun = true;
		return true;
	} else {
		std::cout << "ERROR: Unable to start gear reset process, already in progress\n;";
		return false;
	}
}

void GearResetProcess::Run() {
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
		gearSystem->SetSqueezeEnabled(false);
		gearSystem->SetExtendEnabled(EXTEND_DISABLED);
		gearSystem->SetLiftEnabled(true);
		gearSystem->SetRotateEnabled(true);
		gearSystem->SetGearBarSpeedByProcess(0.5);
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

bool GearResetProcess::IsStopped() {
	return ProcessState::kStopped == currentState;
}
