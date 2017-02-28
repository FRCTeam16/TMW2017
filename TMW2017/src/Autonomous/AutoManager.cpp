/*
 * AutoManager.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include <Autonomous/AutoManager.h>
#include "../RobotMap.h"
#include "Strategies/DebugAutoStrategy.h"
#include <Autonomous/Strategies/DebugAutoStrategy.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>
#include <Autonomous/Strategies/RightGearStrategy.h>

enum AutoStrategy {
	kDebug = 0, kCenter, kBoiler, kReturn
};

AutoManager::AutoManager() :
		strategies(new frc::SendableChooser<void*>())
{
	strategyLookup.insert(std::make_pair(AutoStrategy::kDebug, std::shared_ptr<Strategy>{ new DebugAutoStrategy() }));
	strategyLookup.insert(std::make_pair(AutoStrategy::kCenter, std::shared_ptr<Strategy>{ new CenterGearStrategy() }));
	strategyLookup.insert(std::make_pair(AutoStrategy::kBoiler, std::shared_ptr<Strategy>{ new RightGearStrategy() }));
	strategyLookup.insert(std::make_pair(AutoStrategy::kReturn, std::shared_ptr<Strategy>{ new DebugAutoStrategy() }));

	strategies->AddDefault("Debug Auto Strategy", (void *) AutoStrategy::kDebug);
	strategies->AddObject("Center", (void *) AutoStrategy::kCenter);
	strategies->AddObject("Boiler", (void *) AutoStrategy::kBoiler);
	strategies->AddObject("Return", (void *) AutoStrategy::kReturn);
	frc::SmartDashboard::PutData("Autonomous Strategy", strategies.get());
}

AutoManager::~AutoManager() {
}

void AutoManager::Init(std::shared_ptr<World> world) {
	std::cout << "AutoMan Init\n";
	const AutoStrategy selectedKey =
				static_cast<AutoStrategy>((int) strategies->GetSelected());
	std::cout << "Selected Strategy: " << selectedKey << "\n";
	auto iterator = strategyLookup.find(selectedKey);
	if (iterator != strategyLookup.end()) {
		currentStrategy = iterator->second;
	} else {
		std::cerr << "NO AUTONOMOUS STRATEGY FOUND\n";
	}
	RobotMap::gyro->GetAHRS()->ZeroYaw();
	std::cout << "AutoManager::Init COMPLETE\n";
}

void AutoManager::Periodic(std::shared_ptr<World> world) {
	std::cout << "AutoMan Periodic\n";
	if (currentStrategy) {
		currentStrategy->Run(world);
	}
}
