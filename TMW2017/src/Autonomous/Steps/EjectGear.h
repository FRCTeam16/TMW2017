/*
 * EjectGear.h
 *
 *  Created on: Feb 14, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_
#define SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_

#include "../Step.h"

class EjectGear : public Step {
private:
	double startTime = -1;
public:
	EjectGear() : startTime(-1) {}
	~EjectGear() {}
	bool Run(std::shared_ptr<World> world) override;
};

#endif /* SRC_AUTONOMOUS_STEPS_EJECTGEAR_H_ */
