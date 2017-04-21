/*
 * AckermannDrive.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: User
 */

#include <Autonomous/Steps/AckermannDrive.h>
#include <Robot.h>

bool AckermannDrive::Run(std::shared_ptr<World> world) {
	const double currentAngle = RobotMap::gyro->GetYaw();

	if (startTime < 0) {
		startTime = world->GetClock();
		manualDriveControl = true;
		startAngle = currentAngle;
	}
	std::cout << "Ackermann: start = " << currentAngle << " target = " << targetAngle <<
			"  diff = " << fabs(currentAngle - targetAngle) << "\n";

	const float A = 1.0;
	const float radians = M_PI;
	Robot::driveBase->Steer(radians, speed, A);
	return (fabs(currentAngle - targetAngle) <= threshold);
}


bool RedShootOnlyAckermannDrive::Run(std::shared_ptr<World> world) {
	const double currentAngle = RobotMap::gyro->GetYaw();

	if (startTime < 0) {
		startTime = world->GetClock();
		manualDriveControl = true;
		startAngle = currentAngle;
	}
	const double diff = currentAngle - targetAngle;
	std::cout << "Ackermann: start = " << currentAngle << " target = " << targetAngle <<
			"  diff = " << diff << "\n";

	const float A = 1.0;
	const float radians = M_PI;
	Robot::driveBase->Steer(radians, speed, A);
	if ((diff > -100) && (diff < threshold)) {
		return true;
	} else {
		return false;
	}
}

bool BlueShootScootAckermannDrive::Run(std::shared_ptr<World> world) {
	const double currentAngle = RobotMap::gyro->GetYaw();

	if (startTime < 0) {
		startTime = world->GetClock();
		manualDriveControl = true;
		startAngle = currentAngle;
	}
	const double diff = currentAngle - targetAngle;
	std::cout << "Ackermann: start = " << currentAngle << " target = " << targetAngle <<
			"  diff = " << diff << "\n";

	const float A = 1.0;
	const float radians = M_PI;
	Robot::driveBase->Steer(radians, speed, A);
	if (diff <= threshold) {
		return true;
	} else {
		return false;
	}
}


bool AckermannDriveYawDiff::Run(std::shared_ptr<World> world) {
	const double currentAngle = RobotMap::gyro->GetYaw();

	if (startTime < 0) {
		startTime = world->GetClock();
		manualDriveControl = true;
		startAngle = currentAngle;
	}

	const float A = 1.0;
	const float radians = M_PI;
	Robot::driveBase->Steer(radians, speed, A);

	return (fabs(currentAngle - startAngle) > targetYawDiff);
}

