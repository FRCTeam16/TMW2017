/*
 * Strategy.h
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGY_H_

#include "WPILib.h"
#include <vector>
#include "Step.h"

class World;

class Strategy {
public:
	Strategy();
	virtual ~Strategy();
	virtual void Init(std::shared_ptr<World> world) = 0;
	virtual bool Run(std::shared_ptr<World> world) = 0;
};

class StepStrategy : public Strategy {
public:
	StepStrategy();
	virtual ~StepStrategy();
	virtual void Init(std::shared_ptr<World> world);
	virtual bool Run(std::shared_ptr<World> world);
protected:
	int currentStep = -1;
	std::vector<Step> steps;
};

#endif /* SRC_AUTONOMOUS_STRATEGY_H_ */
