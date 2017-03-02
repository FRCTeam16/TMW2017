/*
 * RightGearStrategy.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/RightGearStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Steps/EjectGear.h>
#include <Autonomous/Steps/Rotate.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/ControlShooterMotor.h>


RightGearStrategy::RightGearStrategy() {
	Preferences *prefs = Preferences::GetInstance();
	const double rightGearX = prefs->GetDouble("RightGearX", -83);
	const double rightGearY = prefs->GetDouble("RightGearY", 96);
	const double rightGearT = prefs->GetDouble("RightGearT", 1.5);

	steps.push_back(new SetGyroOffset(-45.0));
	steps.push_back(new XYPIDControlledDrive(-45.0, 0.3, rightGearX, rightGearY, rightGearT, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(-45.0, 0.35, 21, -21, -1, DriveUnit::Units::kInches, 999.0));	// ignore collisions
	steps.push_back(new ResetGear(0.25));
	steps.push_back(new ControlShooterMotor(false));			// FIXME: Temporarily disabled 3/2/2017 until hopper is fixed
	steps.push_back(new DriveToBump(-180.0, 0, 0.4, 4000));
	steps.push_back(new ControlShooterMotor(false));
	steps.push_back(new PickupGear(0.1));


	/*
	 * 	steps.push_back(new SimpleEncoderDrive(-45.0, -0.3, 0.3, 400, DriveUnit::Units::kPulses));
	 *
	 */

	/*
	steps.push_back(new XYPIDControlledDrive(-45.0, 0.3, rightGearX, rightGearY, rightGearT, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear());
	steps.push_back(new PIDControlledDrive(-45.0, 0.3, 400, 30, DriveUnit::Units::kPulses, true));
	steps.push_back(new DriveToBump(-180.0, 0, 0.5, 4000));
	*/
}

RightGearStrategy::~RightGearStrategy() {
}

