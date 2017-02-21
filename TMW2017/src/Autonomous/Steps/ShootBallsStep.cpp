/*
 * ShootBallsStep.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#include <Robot.h>
#include <Autonomous/Steps/ShootBallsStep.h>

bool ShootBallsStep::Run(std::shared_ptr<World> world) {
	if (startTime < 0) {
		startTime = world->GetClock();
		Robot::shooterSystem->SetShooterMotorsEnabled(true);
	}

	if (waitingForShooterMotors) {
		waitingForShooterMotors = !Robot::shooterSystem->AreShooterMotorReady();
		if (!waitingForShooterMotors) {
			// first time able to fire
			beginShootingTime = world->GetClock();
			Robot::shooterSystem->SetFireEnabled(true);
		}
	}

	const double currentTime = world->GetClock();
	const bool exitFiringTime = (currentTime - beginShootingTime) > timeToShoot;
	if (!waitingForShooterMotors && exitFiringTime) {
		// exiting firing sequence
		Robot::shooterSystem->SetFireEnabled(false);
		Robot::shooterSystem->SetShooterMotorsEnabled(false);
		return true;
	}
	return false;
}
