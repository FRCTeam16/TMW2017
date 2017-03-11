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
	const double gearYInches = prefs->GetDouble("CenterGearY", 68);
	const double speed = prefs->GetDouble("CenterGearYSpeed", 0.2);
	const double threshold = prefs->GetDouble("CenterGearTInches", 4);

	steps.push_back(new SetGyroOffset(0.0));
	steps.push_back(new PIDControlledDrive(0.0, speed, gearYInches, threshold, DriveUnit::Units::kInches));	// was 1170 pulses
	steps.push_back(new EjectGear());
	steps.push_back(new Delay(0.5));
	steps.push_back(new PIDControlledDrive(0.0, speed, 400, 30, DriveUnit::Units::kPulses, true));
}

CenterGearStrategy::~CenterGearStrategy() {
}

