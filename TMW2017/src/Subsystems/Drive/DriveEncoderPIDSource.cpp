/*
 * DriveEncoderPIDSource.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: User
 */

#include "DriveEncoderPIDSource.h"
#include "CANTalon.h"

DriveEncoderPIDSource::DriveEncoderPIDSource(std::shared_ptr<CANTalon> _motor) {
	motor = _motor;
	PIDSource::SetPIDSourceType(PIDSourceType::kDisplacement);
}

DriveEncoderPIDSource::~DriveEncoderPIDSource() {
}

double DriveEncoderPIDSource::PIDGet() {
	return abs(motor->GetEncPosition());
}

