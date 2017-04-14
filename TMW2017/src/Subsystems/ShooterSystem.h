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
	double shooterRPM = 3000;
	bool shooterMotorsEnabled = false;
	bool fireEnabled = false;
	bool automaticRotateState = false;

	bool  inElevatorRampUp = false;
	double elevatorRampUp = 0;
	double elevatorRampUpStartValue = 5;
	double elevatorSpeed = -1.0;

	double hopperSpeed = 0.0;
	bool reverseHopper = false;
	int reverseHopperCountdownTimer = 0;
	int reverseHopperCountDownTimerStartValue = 15;

	int pulseBallLoadCountdown = 0;
	int shooterRampCountdown = 0;

	void ConfigureShooter();
	bool CheckPulsingBallLoad();
	void TriggerShooterRamp(int countdownScansStart = 25);
	void ControlShooterRamp();

public:
	ShooterSystem();
	void InitDefaultCommand();

	void Run();
	void InitManager(Manager::RunMode runMode);
	void SMDB();

	void SetFireEnabled(bool enabled);
	void ToggleShooter();
	void SetShooterEnabled(bool enabled, bool doLoad = true);

	void SetHopperSpeed(double speed);

	void EnableElevator(double speed);
	void DisableElevator();

	void PulseHopperReverse();
	void PulseBallLoad(int countdownScansStart = 5);

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
