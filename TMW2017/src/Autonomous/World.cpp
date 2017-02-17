/*
 * World.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: User
 */

#include <Autonomous/World.h>


World::World() {
	timer.reset(new frc::Timer());
}

World::~World() {
}

double World::GetClock() const {
	return timer->Get();
}

