/*
 * ReturnGearStrategy.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/ReturnGearStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Steps/SetGyroOffset.h>


ReturnGearStrategy::ReturnGearStrategy(bool isRed) {
	Preferences *prefs = Preferences::GetInstance();
	double angle = prefs->GetDouble("ReturnAutoAngle", 60.0);
	double gearX = prefs->GetDouble("ReturnGearX", 83);
	const double gearY = prefs->GetDouble("ReturnGearY", 96);
	const double gearT = prefs->GetDouble("ReturnGearT", 1.5);

	double gearX2 = prefs->GetDouble("ReturnGearX2", 83);
	const double gearY2 = prefs->GetDouble("ReturnGearY2", 96);
	const double gearT2 = prefs->GetDouble("ReturnGearT2", 1.5);

	const double reverseGearY = prefs->GetDouble("ReverseReturnGearY", -15);
	double reverseGearX = prefs->GetDouble("ReverseReturnGearX", -15);
	const double reverseGearT = prefs->GetDouble("ReverseReturnGearT", -1);

	if (!isRed) {
		angle *= -1;
		gearX *= -1;
		gearX2 *= -1;
		reverseGearX *= -1;
	}


	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new XYPIDControlledDrive(angle, 0.3, gearX, gearY, gearT, DriveUnit::Units::kInches));
	steps.push_back(new XYPIDControlledDrive(angle, 0.3, gearX2, gearY2, gearT2, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(angle, 0.3, reverseGearX, reverseGearY, reverseGearT, DriveUnit::Units::kInches, 999.0));	// ignore collisions
}

ReturnGearStrategy::~ReturnGearStrategy() {
}

