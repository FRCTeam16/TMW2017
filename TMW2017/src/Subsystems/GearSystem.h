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
#include "Manager.h"
#include <map>


class GearPickupProcess;
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
	bool gearPickupVoltageTripped = false;
	const float gearPickupVoltageThreshold = 8.0;
	const double resetRange = 0.00001;
	double gearPickUpSpeed = 0.0;

	bool liftEnabled = false;
	bool rotateEnabled = false;
	bool extendEnabled = false;
	bool squeezeEnabled = false;

	std::unique_ptr<GearPickupProcess> gearPickupProcess;

public:
	GearSystem();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Run();
	void InitManager();
	void SMDB();
	void SetGearBarSpeed(double speed);

	void ToggleLift();
	void SetLiftEnabled(bool enabled);
	void ToggleRotate();
	void SetRotateEnabled(bool enabled);
	void ToggleExtend();
	void SetExtendEnabled(bool enabled);
	void ToggleSqueeze();
	void SetSqueezeEnabled(bool enabled);

	void PickUpGear();

};

class GearPickupProcess {


private:
	enum ProcessState { kStopped = -1, kInit, kLift, kRotate, kExtend, kSqueeze, kComplete };

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

#endif
