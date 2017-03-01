/*
 * ControlShooterMotor.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: User
 */

#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Robot.h>

bool ControlShooterMotor::Run(std::shared_ptr<World> world) {
	Robot::shooterSystem->SetShooterEnabled(enabled);
	return true;
}
