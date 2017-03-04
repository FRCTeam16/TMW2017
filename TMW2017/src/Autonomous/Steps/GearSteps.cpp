/*
 * EjectGear.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: User
 */

#include <Autonomous/Steps/GearSteps.h>
#include <Robot.h>
#include <Subsystems/GearSystem.h>


bool DropGearAssembly::Run(std::shared_ptr<World> world) {
	std::cout << "DropGearAssembly::doDrop = " << doDrop << "\n";
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;
		Robot::gearSystem->DropPickupForShooting(doDrop);
	}
	const bool exitFn = (currentTime - startTime) > delay;
	return exitFn;
}

bool EjectGear::Run(std::shared_ptr<World> world) {
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;
		Robot::gearSystem->EjectGear();
	}
	std::cout << "Current: " << currentTime << "\n";
	std::cout << "Start  : " << startTime << "\n";
	std::cout << "Delay  : " << delay << "\n";
	const bool exitFn = (currentTime - startTime) > delay;
	std::cout << "EjectGear: " << exitFn << "\n";
	return exitFn;
}

bool ResetGear::Run(std::shared_ptr<World> world) {
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;
		Robot::gearSystem->ResetGear();
	}
	const bool exitFn = (currentTime - startTime) > delay;
	return exitFn;
}

bool PickupGear::Run(std::shared_ptr<World> world) {
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;
		Robot::gearSystem->PickUpGear();
	}
	const bool exitFn = (currentTime - startTime) > delay;
	return exitFn;
}


