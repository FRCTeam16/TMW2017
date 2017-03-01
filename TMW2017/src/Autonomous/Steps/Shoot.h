/*
 * Shoot.h
 *
 *  Created on: Feb 28, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_SHOOT_H_
#define SRC_AUTONOMOUS_STEPS_SHOOT_H_

#include "WPILib.h"
#include <Autonomous/Step.h>

class Shoot : public Step {
private:
	double startTime = -1;
	double runTimeMs = 0;
public:
	Shoot(double _runTimeMs) : runTimeMs(_runTimeMs) {}
	virtual ~Shoot() {}
	bool Run(std::shared_ptr<World> world);
};

#endif /* SRC_AUTONOMOUS_STEPS_SHOOT_H_ */
