/*
 * CenterGearStrategy.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: User
 */

#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/Delay.h>

CenterGearStrategy::CenterGearStrategy() {
	Preferences *prefs = Preferences::GetInstance();
	const double gearYInches = prefs->GetDouble("CenterGearY");
	const double speed = prefs->GetDouble("CenterGearYSpeed");
	const double threshold = prefs->GetDouble("CenterGearTInches");

	const double angle = 0.0;

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new XYPIDControlledDrive(angle, speed, 0.0, gearYInches, threshold, DriveUnit::Units::kInches));
	steps.push_back(new EjectGear(0.5));
	steps.push_back(new XYPIDControlledDrive(angle, speed, 0.0, 30, threshold, DriveUnit::Units::kInches, true));

}

CenterGearStrategy::~CenterGearStrategy() {
}

