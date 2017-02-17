/*
 * DebugAutoStrategy.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include "DebugAutoStrategy.h"
#include <Autonomous/Steps/DriveSteps.h>
#include "../Steps/NoOp.h"

DebugAutoStrategy::DebugAutoStrategy() {
	steps.push_back(new ZeroDriveEncoders());
//	steps.push_back(new NoOp());
	//steps.push_back(new PIDControlledDrive(0, 1000, 10) );

	steps.push_back(new PIDControlledDrive(0.0, 0.2, 400, 1, PIDControlledDrive::Units::kPulses));
}

DebugAutoStrategy::~DebugAutoStrategy() {
}

