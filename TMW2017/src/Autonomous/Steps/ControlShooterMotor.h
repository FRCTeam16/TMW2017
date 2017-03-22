/*
 * ControlShooterMotor.h
 *
 *  Created on: Mar 1, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_CONTROLSHOOTERMOTOR_H_
#define SRC_AUTONOMOUS_STEPS_CONTROLSHOOTERMOTOR_H_

#include "WPILib.h"
#include <Autonomous/Step.h>

class ControlShooterMotor : public Step {
public:
	ControlShooterMotor(bool _enabled, double _thresholdPct = -1, double _timeout = -1, bool _doLoad = true) :
		enabled(_enabled), thresholdPercent(_thresholdPct), timeout(_timeout), doLoad(_doLoad) {};
	virtual ~ControlShooterMotor() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	double startTime = -1;
	const double enableDelayTime = 0.1;
	int thresholdCounter = 0;
	int thresholdCounterTarget = 5;
	const bool enabled;
	const double thresholdPercent;
	const double timeout;
	const bool doLoad;
};

#endif /* SRC_AUTONOMOUS_STEPS_CONTROLSHOOTERMOTOR_H_ */
