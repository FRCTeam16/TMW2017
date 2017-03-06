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
#include "../Robot.h"

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

    gearBumperLeft.reset(new DigitalInput(0));
    gearBumperRight.reset(new DigitalInput(1));
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
	gearProcessPickUpSpeed = speed;
	gearPickupSpeedLocked = (fabs(speed) + resetRange > 0.0);
}

void GearSystem::UnlockGearPickupSpeedLocked() {
	gearPickupSpeedLocked = false;
}

void GearSystem::ToggleGearBarReverse() {
	if (gearBarReverse) {
		gearBarReverseCooloffCount = 0;
		endGearBarReverse = true;
	}
	gearBarReverse = !gearBarReverse;
}


void GearSystem::StartAutoPickupByAmps() {
	const double currentAmps = gearPickUp->GetOutputCurrent();
	const bool tripped = (currentAmps > gearPickupAmperageThreshold);
	if (tripped && !gearBarReverse) {
		gearCheckScanCount++;
		std::cout << "Tripped Gear Pickup " << gearCheckScanCount << " Amps = " << currentAmps << "\n";
		if (gearCheckScanCount > gearCheckScanCountThreshold) {
			std::cout << "Exceeded scan count threshold\n";
			if (!AnyProcessesRunning()
				&& rotateEnabled == true
				&& extendEnabled == EXTEND_DISABLED) {
					std::cout << "Autostarting gear pickup process\n";
					gearPickupProcess->Start();
					rumbleEnabled = true;
					rumbleCounter = 0;
			}
		}
	} else {
		gearCheckScanCount = 0;
	}
}


void GearSystem::StartAutoPickupBySwitches() {
	if (!gearBumperLeft->Get() || !gearBumperRight->Get()) {
		std::cout << "Detected Both Gear Bumpers Pressed\n";
		if (!AnyProcessesRunning()
			&& rotateEnabled == true
			&& extendEnabled == EXTEND_DISABLED) {
				std::cout << "Autostarting gear pickup process\n";
				hasGear = true;
				gearPickupProcess->Start();
				rumbleEnabled = true;
				rumbleCounter = 0;
		}
	}
}



// Put methods for controlling this subsystem
// here. Call these from Commands.

void GearSystem::Run() {
	if (endGearBarReverse) {
		if (gearBarReverseCooloffCount++ <= gearBarReverseCooloffThreshold) {
			return;
		}
		else {
			endGearBarReverse = false;
		}
	}

	if (useSwitchAutoPickup) {
		StartAutoPickupBySwitches();
	} else {
		StartAutoPickupByAmps();
	}

	if (rumbleEnabled) {
		if (rumbleCounter++ == rumbleCounterThreshold) {
			rumbleEnabled = false;
			rumbleCounter = 0;
		}
		else {
			Robot::oi->SetGamepadBothRumble(1);
		}
	}

	if (compressorEnabled) {
		gearCompressor->Start();
	} else {
		gearCompressor->Stop();
	}

	double speed = gearPickUpSpeed;
	if (gearPickupSpeedLocked) {
		speed = gearProcessPickUpSpeed;
		if (gearBarReverse == true) {
			speed = speed * -1;
		}
	}
	gearPickUp->Set(speed);

	gearPickupProcess->Run();
	gearEjectProcess->Run();
	gearResetProcess->Run();
}

bool GearSystem::AnyProcessesRunning() {
	return !gearPickupProcess->IsStopped() ||
		   !gearEjectProcess->IsStopped() ||
		   !gearResetProcess->IsStopped();
}

void GearSystem::InitManager(Manager::RunMode runMode) {
	SetLiftEnabled(false);
	SetRotateEnabled(false);

	switch (runMode) {
	case Manager::RunMode::kAuto:
		SetSqueezeEnabled(true);
		SetExtendEnabled(EXTEND_ENABLED);
		break;
	case Manager::RunMode::kTele:
		SetSqueezeEnabled(false);
		SetExtendEnabled(EXTEND_DISABLED);
		break;
	}
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
	UnlockGearPickupSpeedLocked();
	hasGear = true;
	if (!gearPickupProcess->Start()) {
		// TODO: ERROR here, should we display on SMDB?
		std::cerr << "************************ Unable to start gear pick up process\n";
	}
}

void GearSystem::EjectGear() {
	std::cout << "GearSystem::EjectGear\n";
	UnlockGearPickupSpeedLocked();
	hasGear = false;
	if (!gearEjectProcess->Start()) {
		// Error on SMDB?
	}
}

bool GearSystem::IsEjectGearRunning() {
	return !gearEjectProcess->IsStopped();
}

void GearSystem::ResetGear() {
	std::cout << "GearSystem::ResetGear\n";
	UnlockGearPickupSpeedLocked();
	hasGear = false;	// assume no gear when we reset
	if (gearResetProcess->Start()) {
		gearBarReverse = false;
	} else {
		// Error on SMDB?
	}
}

bool GearSystem::HasGear() {
	return hasGear;
}


void GearSystem::DropPickupForShooting(bool doDrop) {
	// false is up, true is down
	// FIXME: cleanup/simplify
	if (doDrop) {
		if (!rotateEnabled && !liftEnabled) {
			SetRotateEnabled(true);
			SetLiftEnabled(true);
		}
	} else {
		if (rotateEnabled && liftEnabled) {
			SetRotateEnabled(false);
			SetLiftEnabled(false);
		}
	}
}

void GearSystem::SetCompressorEnabled(bool enabled) {
	compressorEnabled = enabled;
}

void GearSystem::SMDB() {
	frc::SmartDashboard::PutNumber("GearPickup Volts", gearPickUp->GetOutputVoltage());
	frc::SmartDashboard::PutNumber("GearPickup Amps", gearPickUp->GetOutputCurrent());
	frc::SmartDashboard::PutNumber("Pressure Gauge",
			pressureGauge->GetAverageVoltage() * 40); 	// 0 to 5 0 to 200

	useSwitchAutoPickup = frc::SmartDashboard::GetBoolean("GearAutoPickup SwitchOrAmp", useSwitchAutoPickup);
	frc::SmartDashboard::PutBoolean("GearAutoPickup SwitchOrAmp", useSwitchAutoPickup);

	gearPickupAmperageThreshold = frc::SmartDashboard::GetNumber("GearPickupAmpTrigger", 6.0);
	frc::SmartDashboard::PutNumber("GearPickupAmpTrigger", gearPickupAmperageThreshold);
	gearCheckScanCountThreshold = frc::SmartDashboard::GetNumber("GearPickupTripScans", 5);
	frc::SmartDashboard::PutNumber("GearPickupTripScans", gearCheckScanCountThreshold);
	gearBarReverseCooloffThreshold = frc::SmartDashboard::GetNumber("GearBarReverseCooloffThreshold", 5);
	frc::SmartDashboard::PutNumber("GearBarReverseCooloffThreshold", gearBarReverseCooloffThreshold);

	// duplicated
	frc::SmartDashboard::PutBoolean("GearBumperLeft", gearBumperLeft->Get());
	frc::SmartDashboard::PutBoolean("GearBumperRight", gearBumperRight->Get());
}



// ***************************************************************************/
//1-pickup - GearPickupProcess
//2-eject - GearEjectProcess
//3-reset - GearResetProcess

GearPickupProcess::GearPickupProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kInit, StateInfo {0.0, kExtend}));
	stateMapping.insert(std::make_pair(kExtend, StateInfo {0.1 ,kSqueeze}));
	stateMapping.insert(std::make_pair(kSqueeze, StateInfo {0.1, kLift}));
	stateMapping.insert(std::make_pair(kLift, StateInfo {0.2, kEjectBalls}));
	stateMapping.insert(std::make_pair(kEjectBalls, StateInfo {1.0, kComplete}));
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
		gearSystem->SetGearBarSpeedByProcess(1.0);
		break;
	case ProcessState::kExtend:
		gearSystem->SetExtendEnabled(EXTEND_ENABLED);
		break;
	case ProcessState::kSqueeze:
		gearSystem->SetSqueezeEnabled(true);
		gearSystem->SetGearBarSpeedByProcess(0.0);
		break;
	case ProcessState::kLift:
		gearSystem->SetLiftEnabled(false);
		gearSystem->SetRotateEnabled(false);
		break;
	case ProcessState::kEjectBalls:
		gearSystem->SetGearBarSpeedByProcess(-1.0);
		break;
	case ProcessState::kComplete:
		gearSystem->SetGearBarSpeedByProcess(0.0);
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
	stateMapping.insert(std::make_pair(kRetract, StateInfo {0.25, kExtend2}));
	stateMapping.insert(std::make_pair(kExtend2, StateInfo {0.1, kRetract2}));
	stateMapping.insert(std::make_pair(kRetract2, StateInfo {0.25, kMotorOff}));
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
	case ProcessState::kExtend2:
		gearSystem->SetExtendEnabled(EXTEND_ENABLED);
		gearSystem->SetGearBarSpeedByProcess(-0.5);
		break;
	case ProcessState::kRetract:
	case ProcessState::kRetract2:
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
//	std::cout << "Eject stopped? " << (ProcessState::kStopped == currentState) << "\n";
	return ProcessState::kStopped == currentState;
}

//*************3

GearResetProcess::GearResetProcess(GearSystem *gearSystem_) : timer(new Timer()) {
	std::cout << "GearResetProcess::GearResetProcess\n";
	gearSystem.reset(gearSystem_);
	stateMapping.insert(std::make_pair(kInit, StateInfo {0.3, kRotate}));
	stateMapping.insert(std::make_pair(kRotate, StateInfo {0.5, kComplete}));
	timer->Start();
}


bool GearResetProcess::Start() {
	std::cout << "GearResetProcess::Start\n";
	if (IsStopped()) {
		timer->Reset();
		currentState = kInit;
		gearSystem->SetExtendEnabled(EXTEND_DISABLED);
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
		gearSystem->SetExtendEnabled(EXTEND_DISABLED);
		break;
	case ProcessState::kRotate:
		gearSystem->SetSqueezeEnabled(false);
		gearSystem->SetLiftEnabled(true);
		gearSystem->SetRotateEnabled(true);
		gearSystem->SetGearBarSpeedByProcess(1.0);
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
//	std::cout << "Reset stopped? " << (ProcessState::kStopped == currentState) << "\n";
	return ProcessState::kStopped == currentState;
}
