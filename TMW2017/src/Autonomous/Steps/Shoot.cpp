/*
 * Shoot.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: User
 */

#include <Autonomous/Steps/Shoot.h>
#include <Robot.h>


bool Shoot::Run(std::shared_ptr<World> world) {
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;

		if (useTargetAngle) {
			Robot::driveBase->SetTargetAngle(targetAngle);
		} else {
			Robot::shooterSystem->SetFireEnabled(true);
		}
	}

	if (useTargetAngle) {
		const double yawError = Robot::driveBase->GetTwistControlError();
		const bool inThreshold = fabs(yawError) <= threshold;
		std::cout << "Shoot() yawError = " << yawError << "  threshold = " << threshold << " inThreshold = " << inThreshold << "\n";
		Robot::shooterSystem->SetFireEnabled(inThreshold);
		crab->Update(Robot::driveBase->GetTwistControlOutput(), 0.0, 0.0, true);
	} else {
		crab->Stop();
	}

	if ((currentTime - startTime) < runTimeMs) {
		return false;
	} else {
		Robot::shooterSystem->SetFireEnabled(false);
		return true;
	}
}
