/*
 * CenterGearStrategy.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: User
 */

#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Steps/EjectGear.h>

CenterGearStrategy::CenterGearStrategy() {
	steps.push_back(new PIDControlledDrive(0.0, 0.3, 1170, 8, DriveUnit::Units::kPulses));
	steps.push_back(new EjectGear());
	steps.push_back(new PIDControlledDrive(0.0, 0.3, 400, 30, DriveUnit::Units::kPulses, true));
}

CenterGearStrategy::~CenterGearStrategy() {
}

