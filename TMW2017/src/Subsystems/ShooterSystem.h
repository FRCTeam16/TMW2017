// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef SHOOTERSYSTEM_H
#define SHOOTERSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Manager.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterSystem: public Subsystem, public Manager {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> elevator;
	std::shared_ptr<CANTalon> hopper;
	std::shared_ptr<CANTalon> shooter1;
	std::shared_ptr<CANTalon> shooter2;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	double hopperSpeed = 0.0;
	double shooterRPM = 3000;
	bool shooterMotorsEnabled = false;
	bool fireEnabled = false;
	bool hopperAmperageTripped = false;
	float hopperAmperageThreshold = 6;
	int hopperCheckScanCount = 0;
	int hopperCheckScanCountThreshold = 5;
	const int firingHopperSpeed = 0.5;
	int reverseCountdownTimer = 0;

	bool ShouldAutoReverseHopper();
public:
	ShooterSystem();
	void InitDefaultCommand();

	void Run();
	void InitManager();
	void SMDB();

	void SetFireEnabled(bool enabled);
	void ToggleShooter();

	void SetHopperSpeed(double speed);

	void EnableElevator(double speed);
	void DisableElevator();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
