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
	steps.push_back(new ZeroDriveEncoders());
	steps.push_back(new PIDControlledDrive(0.0, 0.3, 1170, 50, PIDControlledDrive::Units::kPulses));
//	steps.push_back(new SimpleEncoderDrive(0.0, 0.3, 0.0, 1500));
	steps.push_back(new EjectGear());
	// FIXME need reverse	steps.push_back(new PIDControlledDrive(0.0, -0.3, 1170, 50, PIDControlledDrive::Units::kPulses));
}

CenterGearStrategy::~CenterGearStrategy() {
}

