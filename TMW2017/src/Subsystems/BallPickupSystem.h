// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef BALLPICKUPSYSTEM_H
#define BALLPICKUPSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Manager.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class BallPickupSystem: public Subsystem, public Manager {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> ballPickup;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	bool ballPickupEnabled = false;
	int ballPickupDirection = 1;
	int reverseBallPickupCountdownTimer = 0;
	int reverseBallPickupCountdownTimerStartValue = 25;
	bool reverseBallPickupPulse = false;

public:
	BallPickupSystem();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Run();
	void InitManager(Manager::RunMode runMode);
	void SMDB();
	void SetBallPickupEnabled(bool enabled);
	void ToggleBallPickup();
	void ReverseBallPickup();
	void PulseReverseBallPickup();
};

#endif
