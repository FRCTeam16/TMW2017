/*
 * World.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#include <Autonomous/World.h>


World::World() {
	timer.reset(new Timer());
}

World::~World() {
	// TODO Auto-generated destructor stub
}

double World::GetClock() const {
	return timer->Get();
}

