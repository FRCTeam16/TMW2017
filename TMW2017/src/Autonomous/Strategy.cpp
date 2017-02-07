/*
 * Strategy.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#include <Autonomous/Strategy.h>
#include "World.h"

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
	if (currentStep >= steps.size()) {
		// TODO: Run Crab->Stop
		return true;
	}
	const bool stepComplete = steps[currentStep].Run(world);
	if (stepComplete) {
		currentStep++;
	}
	return false;
}
