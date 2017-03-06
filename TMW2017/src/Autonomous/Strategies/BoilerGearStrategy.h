/*
 * BoilerGearStrategy.h
 *
 *  Created on: Feb 25, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_BOILERGEARSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_BOILERGEARSTRATEGY_H_

#include "WPILib.h"
#include <Autonomous/Strategy.h>

class BoilerGearStrategy : public StepStrategy {
public:
	BoilerGearStrategy(bool isRed, bool shoot);
	virtual ~BoilerGearStrategy();
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_BOILERGEARSTRATEGY_H_ */
