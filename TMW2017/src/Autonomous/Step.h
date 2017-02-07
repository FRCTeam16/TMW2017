/*
 * Step.h
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEP_H_
#define SRC_AUTONOMOUS_STEP_H_

#include "WPILib.h"

class World;

class Step {
public:
	Step();
	virtual ~Step();
	virtual bool Run(std::shared_ptr<World> world) = 0;
};

#endif /* SRC_AUTONOMOUS_STEP_H_ */
