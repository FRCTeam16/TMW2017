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


RightGearStrategy::RightGearStrategy() {
	const double inchToPulse = 16.5;
	steps.push_back(new XYPIDControlledDrive(0.0, 0.3, 32 * inchToPulse, 79 * inchToPulse, 8, XYPIDControlledDrive::Units::kPulses));
	steps.push_back(new Rotate(-120.0));
//	steps.push_back(new EjectGear());
//	steps.push_back(new PIDControlledDrive(0.0, 0.3, 400, 8, PIDControlledDrive::Units::kPulses, true));
}

RightGearStrategy::~RightGearStrategy() {
}

