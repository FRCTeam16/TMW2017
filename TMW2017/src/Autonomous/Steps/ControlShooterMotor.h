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
	ControlShooterMotor(bool _enabled) : enabled(_enabled) {};
	virtual ~ControlShooterMotor() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	bool enabled = false;
};

#endif /* SRC_AUTONOMOUS_STEPS_CONTROLSHOOTERMOTOR_H_ */
