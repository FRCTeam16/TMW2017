/*
 * ThresholdCenterStrategy.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/ThresholdCenterStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/EjectGear.h>

ThresholdCenterStrategy::ThresholdCenterStrategy() {
	steps.push_back(new ZeroDriveEncoders());
	steps.push_back(new SimpleEncoderDrive(0.0, 0.3, 0.0, 1500));
	steps.push_back(new EjectGear());
	// FIXME: Test steps.push_back(new SimpleEncoderDrive(0.0, -0.3, 0.0, 200));
}

ThresholdCenterStrategy::~ThresholdCenterStrategy() {
}

