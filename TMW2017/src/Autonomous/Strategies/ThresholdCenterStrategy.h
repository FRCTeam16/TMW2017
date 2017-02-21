/*
 * ThresholdCenterStrategy.h
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STRATEGIES_THRESHOLDCENTERSTRATEGY_H_
#define SRC_AUTONOMOUS_STRATEGIES_THRESHOLDCENTERSTRATEGY_H_

#include <Autonomous/Strategy.h>

/**
 * Uses simple encoder watching to determine when a drive threshold has passed
 */
class ThresholdCenterStrategy : public StepStrategy {
public:
	ThresholdCenterStrategy();
	virtual ~ThresholdCenterStrategy();
};

#endif /* SRC_AUTONOMOUS_STRATEGIES_THRESHOLDCENTERSTRATEGY_H_ */
