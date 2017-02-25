/*
 * DriveEncoderPIDSource.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: User
 */

#include "DriveEncoderPIDSource.h"
#include "CANTalon.h"
#include "Robot.h"

DriveEncoderPIDSource::DriveEncoderPIDSource(std::shared_ptr<CANTalon> _motor, int *_inverted) {
	motor = _motor;
	inverted = _inverted;
	PIDSource::SetPIDSourceType(PIDSourceType::kDisplacement);
}

DriveEncoderPIDSource::~DriveEncoderPIDSource() {
}

void DriveEncoderPIDSource::SetInitialEncoderValue() {
	initialEncoderValue = motor->GetEncPosition();
}

double DriveEncoderPIDSource::PIDGet() {
	return abs(motor->GetEncPosition() - initialEncoderValue);
}

