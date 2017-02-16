/*
 * EjectGear.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: User
 */

#include <Robot.h>
#include <Autonomous/Steps/EjectGear.h>
#include <Subsystems/GearSystem.h>


bool EjectGear::Run(std::shared_ptr<World> world) {
	if (startTime < 0) {
		startTime = world->GetClock();
		Robot::gearSystem->EjectGear();
	}
	return true;
}


