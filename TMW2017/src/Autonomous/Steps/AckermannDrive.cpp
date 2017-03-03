/*
 * AckermannDrive.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: User
 */

#include <Autonomous/Steps/AckermannDrive.h>
#include <Robot.h>


bool AckermannDrive::Run(std::shared_ptr<World> world) {
	const int encoderPosition = Robot::driveBase->GetRearRightDrive()->GetEncPosition();

	if (startTime < 0) {
		startTime = world->GetClock();
		encoderStartPosition = encoderPosition;
		manualDriveControl = true;
	}

	const float A = 1.0;
	const float radians = M_PI;
	Robot::driveBase->Steer(radians, speed, A);

	return (abs(encoderPosition - encoderStartPosition) > distance);
}

