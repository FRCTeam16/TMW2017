/*
 * Strategy.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#include <Robot.h>
#include <Autonomous/Strategy.h>
#include "World.h"
#include <iomanip>

Strategy::Strategy() {
	// TODO Auto-generated constructor stub

}

Strategy::~Strategy() {
	// TODO Auto-generated destructor stub
}

/*****************************************************************************/


StepStrategy::StepStrategy() {
}

StepStrategy::~StepStrategy() {
}

void StepStrategy::Init(std::shared_ptr<World> world) {

}

bool StepStrategy::Run(std::shared_ptr<World> world) {
	std::cout << "StepStrategy::Run\n";
	std::cout << "currentStep = " << currentStep << "\n";
	if (currentStep >= steps.size()) {
		RunDrives(new CrabInfo());	// FIXME: Move to 	const std::unique_ptr<CrabInfo> STOP { new CrabInfo() };
		return true;
	}
	Step* step = steps[currentStep];
	const bool stepComplete = step->Run(world);
	RunDrives(step->GetCrabInfo());
	if (stepComplete) {
		currentStep++;
	}
	return false;
}

void StepStrategy::RunDrives(const CrabInfo *crab) {
	std::cout << "RunDrives -> ";
	std::cout << "\ttwist: " << std::setw(5) << crab->twist
			  << "  yspeed: " << std::setw(5) << crab->yspeed
			  << "  xspeed: " << std::setw(5) << crab->xspeed
			  << "\n";
	Robot::driveBase->Crab(crab->twist, crab->yspeed, crab->xspeed, crab->gyro);

}
