/*
 * AutoManager.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include <Autonomous/AutoManager.h>
#include "DebugAutoStrategy.h"

AutoManager::AutoManager() {
	std::shared_ptr<Strategy> debugStrategy { new DebugAutoStrategy() };

	strategyLookup.insert(std::make_pair(1, debugStrategy));

	strategies.reset(new frc::SendableChooser<void*>());
	strategies->AddDefault("Testing", (void *) 1);
	SmartDashboard::PutData("Autonomous Strategy", strategies.get());
}

AutoManager::~AutoManager() {
	// TODO Auto-generated destructor stub
}

void AutoManager::Init(std::shared_ptr<World> world) {
	std::cout << "AutoMan Init\n";
}

void AutoManager::Periodic(std::shared_ptr<World> world) {
	std::cout << "AutoMan Periodic\n";
	int selectedKey = (int) strategies->GetSelected();
	std::cout << "Selected Strategy: " << selectedKey << "\n";
	auto iterator = strategyLookup.find(selectedKey);
	if (iterator != strategyLookup.end()) {
		 iterator->second->Run(world);
	} else {
		std::cout << "NO STRATEGY FOUND\n";
	}

}

