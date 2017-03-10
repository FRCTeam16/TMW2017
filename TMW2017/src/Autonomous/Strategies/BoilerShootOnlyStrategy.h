/*
 * BoilerShootOnlyStrategy.h
 *
 *  Created on: Mar 10, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_BOILERSHOOTONLYSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_BOILERSHOOTONLYSTRATEGY_H_

#include "WPILib.h"
#include <Autonomous/Strategy.h>

class BoilerShootOnlyStrategy : public StepStrategy {
public:
	BoilerShootOnlyStrategy(bool isRed);
	virtual ~BoilerShootOnlyStrategy();
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_BOILERSHOOTONLYSTRATEGY_H_ */
