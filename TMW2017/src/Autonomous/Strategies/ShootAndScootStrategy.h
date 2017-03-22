/*
 * ShootAndScootStrategy.h
 *
 *  Created on: Mar 21, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_SHOOTANDSCOOTSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_SHOOTANDSCOOTSTRATEGY_H_

#include <Autonomous/Strategy.h>

class ShootAndScootStrategy : public StepStrategy {
public:
	ShootAndScootStrategy(bool isRed);
	virtual ~ShootAndScootStrategy() {}
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_SHOOTANDSCOOTSTRATEGY_H_ */
