/*
 * PIDDrive.cpp
 */

#include <Autonomous/Steps/DriveSteps.h>
#include "../../Robot.h"

using namespace std;

bool ZeroDriveEncoders::Run(std::shared_ptr<World> world) {
	if (firstRun) {
		firstRun = false;
		Robot::driveBase->ZeroDriveEncoders();
	}

	lastEncoderPosition = Robot::driveBase->GetFrontLeftDrive()->GetEncPosition();
	std::cout << "Waiting for encoder position to be zero: " << lastEncoderPosition << "\n";
	return (lastEncoderPosition == 0);
}


bool SimpleEncoderDrive::Run(std::shared_ptr<World> world) {
	cout << "SimpleEncoderDrive target distance" << targetDistance << '\n';

	// Initialize
	if (firstRun) {
		firstRun = false;
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
	}

	const int currentPosition = abs(Robot::driveBase->GetFrontLeftDrive()->GetEncPosition());
	const double elapsedTime = world->GetClock() - startTime;
	SmartDashboard::PutNumber("Encoder Position", currentPosition);
	cout << "SimpleEncoderDrive Encoder: " << currentPosition << "\n";

	if (currentPosition >= targetDistance) {
		cout << "Position reached in " << elapsedTime << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTime > 20) {
		cout << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else {
		crab->Update(Robot::driveBase->GetTwistControlOutput(), ySpeed, xSpeed, true);
		return false;
	}
}

bool PIDControlledDrive::Run(std::shared_ptr<World> world) {
	cout << "PIDControlledDrive target distance" << targetDistance << '\n';

	// Initialize
	if (startTime < 0) {
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
		Robot::driveBase->SetTargetDriveDistance(targetDistance);
		// Allow robot drive to use % vbus to manage speed
		Robot::driveBase->UseClosedLoopDrive();
		startingEncoderCount = Robot::driveBase->GetDriveControlEncoderPosition();
	}

	const double elapsedTimeMillis = world->GetClock() - startTime;
	const double currentPIDOutput = Robot::driveBase->GetDriveControlOutput();

	SmartDashboard::PutNumber("PIDController Output", currentPIDOutput);
	cout << "PIDController Output: " << currentPIDOutput << "\n";

	const double currentEncoderPosition = Robot::driveBase->GetDriveControlEncoderPosition();

	if (abs((startingEncoderCount + targetDistance) - currentEncoderPosition) <= distanceThreshold) {
		cout << "Position reached in " << elapsedTimeMillis << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTimeMillis > 5000) {
		cout << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else {
		const double crabSpeed = speed + currentPIDOutput;	// FIXME - incorrect speed handling
		const double xspeed = crabSpeed * sin(angle * M_PI / 180.0);
		const double yspeed = crabSpeed * cos(angle * M_PI / 180.0);
		crab->Update(
				Robot::driveBase->GetTwistControlOutput(),
				yspeed,
				xspeed,
				true);
		return false;
	}
}


