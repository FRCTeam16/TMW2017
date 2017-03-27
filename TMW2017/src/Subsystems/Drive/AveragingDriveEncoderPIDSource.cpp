/*
 * AveragingDriveEncoderPIDSource.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: User
 */

#include <Subsystems/Drive/AveragingDriveEncoderPIDSource.h>
#include "CANTalon.h"
#include "Robot.h"


AveragingDriveEncoderPIDSource::AveragingDriveEncoderPIDSource(DriveInfo<std::shared_ptr<CANTalon>> _motor)
: motor(_motor){
	frc::PIDSource::SetPIDSourceType(PIDSourceType::kDisplacement);
}

AveragingDriveEncoderPIDSource::~AveragingDriveEncoderPIDSource() {
}

void AveragingDriveEncoderPIDSource::SetInitialEncoderValue() {
	initialEncoderValue.FL = motor.FL->GetEncPosition();
	initialEncoderValue.FR = motor.FR->GetEncPosition();
	initialEncoderValue.RL = motor.RL->GetEncPosition();
	initialEncoderValue.RR = motor.RR->GetEncPosition();
}

double AveragingDriveEncoderPIDSource::PIDGet() {
	DriveInfo<double> error;
	error.FL = fabs(motor.FL->GetEncPosition() - initialEncoderValue.FL);
	error.FR = fabs(motor.FR->GetEncPosition() - initialEncoderValue.FR);
	error.RL = fabs(motor.RL->GetEncPosition() - initialEncoderValue.RL);
	error.RR = fabs(motor.RR->GetEncPosition() - initialEncoderValue.RR);

	double sum = 0.0;
	int count = 0;
	if (motorEnabled.FL) { sum += error.FL; count++; }
	if (motorEnabled.FR) { sum += error.FR; count++; }
	if (motorEnabled.RL) { sum += error.RL; count++; }
	if (motorEnabled.RR) { sum += error.RR; count++; }
	const double average = sum / count;

	// TODO: Take motors out if their error is too far from
	const double threshold = 0.5;
//	if (((error.FL / average) < threshold) || ((error.FL/average) > threhsold + 1)) {
//		motorEnabled.FL = false;
//	}
	return average;
}


