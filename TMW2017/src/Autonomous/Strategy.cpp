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
}

Strategy::~Strategy() {
}

/*****************************************************************************/


StepStrategy::StepStrategy() {
}

StepStrategy::~StepStrategy() {
	for (auto it = steps.begin(); it != steps.end(); ++it) {
		delete *it;
	}
	steps.clear();
}

void StepStrategy::Init(std::shared_ptr<World> world) {

}

bool StepStrategy::Run(std::shared_ptr<World> world) {
	std::cout << "StepStrategy::Run ";
	std::cout << "currentStep = " << currentStep << "\n";
	if (currentStep >= steps.size()) {
		RunDrives(STOP.get(), false);
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

void StepStrategy::RunDrives(const CrabInfo *crab, bool showMessage) {
	if (showMessage) {
		std::cout << "RunDrives -> ";
		std::cout << "\ttwist: " << std::setw(5) << crab->twist
				  << "  yspeed: " << std::setw(5) << crab->yspeed
				  << "  xspeed: " << std::setw(5) << crab->xspeed
				  << "\n";
	}
	Robot::driveBase->Crab(crab->twist, crab->yspeed, crab->xspeed, crab->gyro);

}
