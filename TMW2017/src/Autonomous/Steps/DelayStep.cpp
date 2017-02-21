/*
 * DelayStep.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#include <Autonomous/Steps/DelayStep.h>
#include <Autonomous/AutoManager.h>

bool DelayStep::Run(std::shared_ptr<World> world) {
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		// first run
		startTime = currentTime;
		if (delayTime < 0) {
			delayTime = frc::SmartDashboard::GetNumber(AUTO_DELAY, 0.0);
			std::cout << "\tDelayStep initialized from Dashboard: " << delayTime << "\n";
		}
	}
	return ((currentTime - startTime) >= delayTime);

}
