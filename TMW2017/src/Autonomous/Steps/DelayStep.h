/*
 * DelayStep.h
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_DELAYSTEP_H_
#define SRC_AUTONOMOUS_STEPS_DELAYSTEP_H_

#include <Autonomous/Step.h>

class DelayStep {
private:
	double startTime = -1;
	double delayTime;
public:
	DelayStep(double _delay = -1) : delayTime(_delay) {}
	~DelayStep() {}
	bool Run(std::shared_ptr<World> world);
};

#endif /* SRC_AUTONOMOUS_STEPS_DELAYSTEP_H_ */
