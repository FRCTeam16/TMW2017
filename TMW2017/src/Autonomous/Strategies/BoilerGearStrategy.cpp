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
	Preferences *prefs = Preferences::GetInstance();
	const double rightGearX = prefs->GetDouble("RightGearX", -83);
	const double rightGearY = prefs->GetDouble("RightGearY", 96);
	const double rightGearT = prefs->GetDouble("RightGearT", 1.5);

	const double angle = -52.0;

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new XYPIDControlledDrive(angle, 0.5, rightGearX, rightGearY, rightGearT, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(angle, 0.6, 15, -15, -1, DriveUnit::Units::kInches, 999.0));	// ignore collisions
	steps.push_back(new ResetGear(0.25));
	steps.push_back(new ControlShooterMotor(true));
	steps.push_back(new DriveToBump(-180.0, 0, 0.4, 4, 0.75, 1.3));

	steps.push_back(new SimpleEncoderDrive(-180.0, -0.5, 0.0, 5.5, DriveUnit::Units::kInches));
	steps.push_back(new AckermannDrive(0.3, 7));
	steps.push_back(new Shoot(10));
}

BoilerGearStrategy::~BoilerGearStrategy() {
}

