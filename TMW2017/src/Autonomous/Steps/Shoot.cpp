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
//		Robot::shooterSystem->ToggleShooter();
		Robot::shooterSystem->SetFireEnabled(true);
	}
	crab->Stop();
	if ((currentTime - startTime) < runTimeMs) {
		return false;
	} else {
		Robot::shooterSystem->SetFireEnabled(false);
//		Robot::shooterSystem->ToggleShooter();
		return true;
	}
}
