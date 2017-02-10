/*
 * AutoManager.h
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_AUTOMANAGER_H_
#define SRC_AUTONOMOUS_AUTOMANAGER_H_

#include "WPILib.h"
#include "World.h"
#include "Strategy.h"
#include <map>

// TODO: enums for map/strategies
class AutoManager {
public:
	AutoManager();
	virtual ~AutoManager();
	void Init(std::shared_ptr<World> world);
	void Periodic(std::shared_ptr<World> world);
private:
	std::shared_ptr<frc::SendableChooser<void*>> strategies;
	std::map<int, std::shared_ptr<Strategy>> strategyLookup;
};

#endif /* SRC_AUTONOMOUS_AUTOMANAGER_H_ */
