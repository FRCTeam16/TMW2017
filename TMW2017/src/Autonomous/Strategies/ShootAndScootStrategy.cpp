/*
 * ShootAndScootStrategy.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/ShootAndScootStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/Rotate.h>
#include <Autonomous/Steps/Shoot.h>

ShootAndScootStrategy::ShootAndScootStrategy(bool isRed) {
	Preferences *prefs = Preferences::GetInstance();
	const double angle = 90.0;
	const double fwdSpeed = prefs->GetDouble("ShootScootForwardSpeed", 0.4);
	const double fwdDist = prefs->GetDouble("ShootScootForwardY", 66);
	const double fwdDistThresh = prefs->GetDouble("ShootScootForwardT", 1.5);


	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new ControlShooterMotor(true, 0.95, 2.5, false));
	steps.push_back(new Shoot(2.0));
	steps.push_back(new ControlShooterMotor(false));

	steps.push_back(new TimedDrive(angle, 0.001, 0.0, 0.25));
	steps.push_back(new XYPIDControlledDrive(angle, fwdSpeed, 0.0, fwdDist, fwdDistThresh, DriveUnit::Units::kInches));
	steps.push_back(new Rotate(-60.0));

}

