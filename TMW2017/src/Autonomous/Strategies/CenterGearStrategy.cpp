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
	const double gearYInches = prefs->GetDouble("CenterGearY", -83);

	steps.push_back(new SetGyroOffset(0.0));
	steps.push_back(new PIDControlledDrive(0.0, 0.3, gearYInches, 8, DriveUnit::Units::kInches));	// was 1170 pulses
	steps.push_back(new EjectGear());
	steps.push_back(new Delay(0.5));
	steps.push_back(new PIDControlledDrive(0.0, 0.3, 400, 30, DriveUnit::Units::kPulses, true));
}

CenterGearStrategy::~CenterGearStrategy() {
}

