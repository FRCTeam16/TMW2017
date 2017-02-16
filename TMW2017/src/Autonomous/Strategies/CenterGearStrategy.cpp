/*
 * CenterGearStrategy.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Steps/PIDDrive.h>
#include <Autonomous/Steps/EjectGear.h>

CenterGearStrategy::CenterGearStrategy() {
	steps.push_back(new ZeroDriveEncoders());
	steps.push_back(new PIDControlledDrive(0.0, 1750, 50, PIDControlledDrive::Units::kPulses));
	steps.push_back(new EjectGear());
}

CenterGearStrategy::~CenterGearStrategy() {
}

