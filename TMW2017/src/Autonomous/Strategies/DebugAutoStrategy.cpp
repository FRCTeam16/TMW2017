/*
 * DebugAutoStrategy.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include "DebugAutoStrategy.h"
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/NoOp.h>
//#include <Autonomous/Steps/TurnWheels.h>

DebugAutoStrategy::DebugAutoStrategy() {
//	steps.push_back(new ZeroDriveEncoders());
//	steps.push_back(new NoOp());
	//steps.push_back(new PIDControlledDrive(0, 1000, 10) );
//	steps.push_back(new PIDControlledDrive(0.0, 0.2, 24, 1, DriveUnit::Units::kInches));
//	steps.push_back(new TurnWheels(-32, 79, 100));

	steps.push_back(new XYPIDControlledDrive(0.0, 0.3, 32, 79, 1.5, DriveUnit::Units::kInches));
}

DebugAutoStrategy::~DebugAutoStrategy() {
}

