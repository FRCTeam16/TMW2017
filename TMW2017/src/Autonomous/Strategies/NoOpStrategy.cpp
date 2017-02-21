/*
 * NoOpStrategy.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/NoOpStrategy.h>
#include <Autonomous/Steps/NoOp.h>

NoOpStrategy::NoOpStrategy() {
	steps.push_back(new NoOp());
}

NoOpStrategy::~NoOpStrategy() {
}

