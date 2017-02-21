/*
 * NoOpStrategy.h
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_NOOPSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_NOOPSTRATEGY_H_

#include <Autonomous/Strategy.h>

class NoOpStrategy : public StepStrategy {
public:
	NoOpStrategy();
	virtual ~NoOpStrategy();
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_NOOPSTRATEGY_H_ */
