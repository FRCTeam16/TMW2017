/*
 * EjectGear.h
 *
 *  Created on: Feb 14, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_
#define SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_

#include "WPILib.h"
#include "../Step.h"

class EjectGear : public Step {
private:
	double startTime = -1;
	const double delay;
public:
	EjectGear(double _delay = 0.0) : delay(_delay) {}
	~EjectGear() {}
	bool Run(std::shared_ptr<World> world) override;
};


class ResetGear : public Step {
private:
	double startTime = -1;
	const double delay;
public:
	ResetGear(double _delay = 0.0) : delay(_delay) {}
	~ResetGear() {}
	bool Run(std::shared_ptr<World> world) override;
};

class PickupGear : public Step {
private:
	double startTime = -1;
	const double delay;
public:
	PickupGear(double _delay = 0.0) : delay(_delay) {}
	~PickupGear() {}
	bool Run(std::shared_ptr<World> world) override;
};

#endif /* SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_ */
