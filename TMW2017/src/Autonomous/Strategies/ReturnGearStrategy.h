/*
 * ReturnGearStrategy.h
 *
 *  Created on: Mar 4, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_RETURNGEARSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_RETURNGEARSTRATEGY_H_

#include "WPILib.h"
#include <Autonomous/Strategy.h>

class ReturnGearStrategy : public StepStrategy {
public:
	ReturnGearStrategy(bool isRed);
	virtual ~ReturnGearStrategy();
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_RETURNGEARSTRATEGY_H_ */
