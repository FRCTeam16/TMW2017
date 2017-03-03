// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GEARSYSTEM_H
#define GEARSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "Manager.h"
#include <map>


class GearPickupProcess;
class GearEjectProcess;
class GearResetProcess;
class GearSystem: public Subsystem, public Manager {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> gearPickUp;
	std::shared_ptr<Solenoid> lift;
	std::shared_ptr<Solenoid> rotate;
	std::shared_ptr<Solenoid> extend;
	std::shared_ptr<DoubleSolenoid> squeeze;
	std::shared_ptr<Compressor> gearCompressor;
	std::shared_ptr<AnalogInput> pressureGauge;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<DigitalInput> gearBumperLeft;
	std::shared_ptr<DigitalInput> gearBumperRight;

	float gearPickupAmperageThreshold = 10;
	int gearCheckScanCount = 0;
	int gearCheckScanCountThreshold = 5;		// Tracks # of scans before amp tripping
	const double resetRange = 0.00001;			// detect noisy float zeros for resetting trip
	int gearBarReverseCooloffThreshold = 5;
	int gearBarReverseCooloffCount = gearBarReverseCooloffThreshold;

	double gearPickUpSpeed = 0.0;
	double gearProcessPickUpSpeed = 0.0;		// overrides gearPickUpSpeed
	bool gearPickupSpeedLocked = false;
	bool gearBarReverse = false;
	bool endGearBarReverse = false;

	bool rumbleEnabled = false;
	int rumbleCounter = 0;
	const int rumbleCounterThreshold = 25;

	// pneumatic states
	bool liftEnabled = false;
	bool rotateEnabled = false;
	bool extendEnabled = false;
	bool squeezeEnabled = false;

	// Auto gear pickup selection strategy
	bool useSwitchAutoPickup = true;


	std::unique_ptr<GearPickupProcess> gearPickupProcess;
	std::unique_ptr<GearEjectProcess> gearEjectProcess;
	std::unique_ptr<GearResetProcess> gearResetProcess;
	bool hasGear = false;	// guess whether we have a gear

	void StartAutoPickupByAmps();
	void StartAutoPickupBySwitches();
	bool AnyProcessesRunning();
	void UnlockGearPickupSpeedLocked();	// safety utility to enforce returning user control

public:
	GearSystem();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Run();
	void InitManager(Manager::RunMode runMode);
	void SMDB();
	void SetGearBarSpeed(double speed);
	void SetGearBarSpeedByProcess(double speed);
	void ToggleGearBarReverse();

	void ToggleLift();
	void SetLiftEnabled(bool enabled);
	void ToggleRotate();
	void SetRotateEnabled(bool enabled);
	void ToggleExtend();
	void SetExtendEnabled(bool enabled);
	void ToggleSqueeze();
	void SetSqueezeEnabled(bool enabled);

	void PickUpGear();
	void EjectGear();
	bool IsEjectGearRunning();
	void ResetGear();
	bool HasGear();
};

class GearPickupProcess {


private:
	enum ProcessState { kStopped, kInit, kLift, kExtend, kSqueeze, kEjectBalls, kComplete };

	struct StateInfo {
			double waitTime;
			ProcessState nextState;
		};

	std::map<ProcessState, StateInfo> stateMapping;

	std::shared_ptr<GearSystem> gearSystem;
	std::unique_ptr<Timer> timer;
	ProcessState currentState = kStopped;
	bool firstStateRun = false;
public:
	GearPickupProcess(GearSystem *gearSystem);
	~GearPickupProcess() {}
	bool IsStopped();
	bool Start();
	void Run();


};

class GearEjectProcess {


private:
	enum ProcessState { kStopped, kExtend, kExtend2, kRelease, kRetract, kRetract2, kMotorOff, kComplete };

	struct StateInfo {
			double waitTime;
			ProcessState nextState;
		};

	std::map<ProcessState, StateInfo> stateMapping;

	std::shared_ptr<GearSystem> gearSystem;
	std::unique_ptr<Timer> timer;
	ProcessState currentState = kStopped;
	bool firstStateRun = false;
public:
	GearEjectProcess(GearSystem *gearSystem);
	~GearEjectProcess() {}
	bool IsStopped();
	bool Start();
	void Run();


};


class GearResetProcess {


private:
	enum ProcessState { kStopped, kInit, kRotate, kComplete };

	struct StateInfo {
			double waitTime;
			ProcessState nextState;
		};

	std::map<ProcessState, StateInfo> stateMapping;

	std::shared_ptr<GearSystem> gearSystem;
	std::unique_ptr<Timer> timer;
	ProcessState currentState = kStopped;
	bool firstStateRun = false;
public:
	GearResetProcess(GearSystem *gearSystem);
	~GearResetProcess() {}
	bool IsStopped();
	bool Start();
	void Run();


};

#endif
