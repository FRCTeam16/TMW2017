/*
 * DebugAutoStrategy.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include <Autonomous/DebugAutoStrategy.h>
#include "PIDDrive.h"
#include "NoOp.h"

DebugAutoStrategy::DebugAutoStrategy() {
	steps.push_back(new ZeroDriveEncoders());
	steps.push_back(new NoOp());
	//steps.push_back(new PIDControlledDrive(0, 1000, 10) );
}

DebugAutoStrategy::~DebugAutoStrategy() {
}

