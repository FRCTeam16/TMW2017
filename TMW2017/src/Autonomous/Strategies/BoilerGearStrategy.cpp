/*
 * BoilerGearStrategy.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: User
 */

#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Steps/Rotate.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Autonomous/Steps/AckermannDrive.h>
#include <Autonomous/Steps/Delay.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Steps/Shoot.h>
#include <Autonomous/Strategies/BoilerGearStrategy.h>


BoilerGearStrategy::BoilerGearStrategy() {
	const frc::DriverStation::Alliance alliance = frc::DriverStation::GetInstance().GetAlliance();
	const bool isRed =  alliance == frc::DriverStation::Alliance::kRed ||
						alliance == frc::DriverStation::Alliance::kInvalid;

	// Step paramaters
	Preferences *prefs = Preferences::GetInstance();

	double angle = prefs->GetDouble("BoilerAutoAngle", -52.0);
	double gearX = prefs->GetDouble("RightGearX", -83);
	const double gearY = prefs->GetDouble("RightGearY", 96);
	const double gearT = prefs->GetDouble("RightGearT", 1.5);

	double reverseGearX = 15;
	const double reverseGearY = -15;
	const double reverseGearT = -1;

	if (!isRed) {
		angle *= -1;
		gearX *= -1;
		// gearY stays positive
		// gearT stays the same
		reverseGearX *= -1;
		// reverseGearY stays the same
		// reverseGearT statys the same
	}

	//
	// Begin Step Definitions
	//
	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new XYPIDControlledDrive(angle, 0.5, gearX, gearY, gearT, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(angle, 0.6, reverseGearX, reverseGearY, reverseGearT, DriveUnit::Units::kInches, 999.0));	// ignore collisions


	if (isRed) {
		steps.push_back(new DropGearAssembly(0.25, true));
		steps.push_back(new ControlShooterMotor(true));
		steps.push_back(new DriveToBump(-180.0, 0, 0.4, 4, 0.75, 1.3));
		steps.push_back(new SimpleEncoderDrive(-180.0, -0.5, 0.0, 5.5, DriveUnit::Units::kInches));
		steps.push_back(new AckermannDrive(0.3, 7));
		steps.push_back(new Shoot(10));
	} else {
		// blue specific steps
	}
}

BoilerGearStrategy::~BoilerGearStrategy() {
}

