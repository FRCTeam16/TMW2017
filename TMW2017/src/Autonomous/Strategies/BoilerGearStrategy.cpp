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


BoilerGearStrategy::BoilerGearStrategy(bool isRed, bool shoot) {
	// Step parameters
	Preferences *prefs = Preferences::GetInstance();

	double angle = prefs->GetDouble("BoilerAutoAngle");
	const double speed = prefs->GetDouble("BoilerGearSpeed");
	double gearX = prefs->GetDouble("BoilerGearX");
	const double gearY = prefs->GetDouble("BoilerGearY");
	const double gearT = prefs->GetDouble("BoilerGearT");
	double driveBumpX = prefs->GetDouble("BoilerBumpX");
	const double jerk = prefs->GetDouble("BoilerJerk");
	const double ackermannAngle = prefs->GetDouble("AckermannAngle");

	const double reverseGearY = prefs->GetDouble("ReverseBoilerGearY");
	double reverseGearX = prefs->GetDouble("ReverseBoilerGearX");
	const double reverseGearT = prefs->GetDouble("ReverseBoilerGearT");

	if (!isRed) {
		angle *= -1;
		gearX *= -1;
		reverseGearX *= -1;
		driveBumpX *= -1;
	}

	//
	// Hang Gear
	//
	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new XYPIDControlledDrive(angle, speed, gearX, gearY, gearT, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(angle, 0.6, reverseGearX, reverseGearY, reverseGearT, DriveUnit::Units::kInches, 999.0));	// ignore collisions

	//
	// Move to wall and shoot
	//
//		steps.push_back(new DropGearAssembly(0.25, true));
	steps.push_back(new Rotate(-180.0));
	steps.push_back(new ControlShooterMotor(true));
	steps.push_back(new DriveToBump(-180.0, 0, driveBumpX, 4, 0.75, jerk));
	steps.push_back(new SimpleEncoderDrive(-180.0, -0.5, 0.0, 5.5, DriveUnit::Units::kInches));
	if (isRed) {
		steps.push_back(new AckermannDrive(0.3, ackermannAngle));
	}
	steps.push_back(new Shoot(10));
}

BoilerGearStrategy::~BoilerGearStrategy() {
}

