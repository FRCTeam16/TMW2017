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
	const double targetAngle;
	const double threshold;
	const bool useTargetAngle;
public:
	Shoot(double _runTimeMs) : runTimeMs(_runTimeMs), targetAngle(0.0), threshold(0.0), useTargetAngle(false) {}
	Shoot(double _runTimeMs, double _targetAngle, double _threshold) : runTimeMs(_runTimeMs), targetAngle(_targetAngle),
			threshold(_threshold), useTargetAngle(true) {}
	virtual ~Shoot() {}
	bool Run(std::shared_ptr<World> world);
};

#endif /* SRC_AUTONOMOUS_STEPS_SHOOT_H_ */
