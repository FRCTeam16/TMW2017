/*
 * PIDDrive.cpp
 */

#include <Autonomous/PIDDrive.h>
#include "../Robot.h"

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


bool PIDDrive::Run(std::shared_ptr<World> world) {
	cout << "PIDDrive target distance" << targetDistance << '\n';

	// Initialize
	if (firstRun) {
		firstRun = false;
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
		//Robot::driveBase->DriveControlTwist->SetSetpoint(angle);
		Robot::driveBase->UseClosedLoopDrive();
	}

	const int currentPosition = abs(Robot::driveBase->GetFrontLeftDrive()->GetEncPosition());
	const double elapsedTime = world->GetClock() - startTime;
	SmartDashboard::PutNumber("Encoder Position", currentPosition);
	cout << "PIDDrive Encoder: " << currentPosition << "\n";

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
	if (firstRun) {
		firstRun = false;
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
		Robot::driveBase->SetTargetDriveDistance(targetDistance);
		// Allow robot drive to use % vbus to manage speed
		//Robot::driveBase->UseClosedLoopDrive();
	}

	const double elapsedTimeMillis = world->GetClock() - startTime;
	const double currentPIDOutput = Robot::driveBase->GetDriveControlOutput();

	SmartDashboard::PutNumber("PIDController Output", currentPIDOutput);
	cout << "PIDController Output: " << currentPIDOutput << "\n";

	const double currentEncoderPosition = Robot::driveBase->GetDriveControlEncoderPosition();

	if (abs(targetDistance - currentEncoderPosition) <= threshold) {
		cout << "Position reached in " << elapsedTimeMillis << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTimeMillis > 20) {
		cout << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else {
		const double speed = currentPIDOutput;
		const double xspeed = speed * sin(angle * M_PI / 180.0);
		const double yspeed = speed * cos(angle * M_PI / 180.0);
		crab->Update(
				Robot::driveBase->GetTwistControlOutput(),
				yspeed,
				xspeed,
				true);
		return false;
	}
}


