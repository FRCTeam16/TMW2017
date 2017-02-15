/*
 * EjectGear.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: User
 */

#include <Autonomous/Steps/EjectGear.h>
#include <Subsystems/GearSystem.h>


bool EjectGear::Run(std::shared_ptr<World> world) {
	if (startTime < 0) {
		startTime = world->GetClock();
	}
	// FIXME: call gear system
	return false;
}


