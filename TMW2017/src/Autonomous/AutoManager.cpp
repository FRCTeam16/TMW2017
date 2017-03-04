/*
 * AutoManager.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include <Autonomous/AutoManager.h>
#include <Autonomous/Strategies/BoilerGearStrategy.h>
#include "../RobotMap.h"
#include "Strategies/DebugAutoStrategy.h"
#include <Autonomous/Strategies/DebugAutoStrategy.h>
#include <Autonomous/Strategies/CenterGearStrategy.h>



AutoManager::AutoManager() :
		strategies(new frc::SendableChooser<void*>())
{
	strategies->AddDefault("0 - Debug Auto Strategy", (void *) AutoStrategy::kDebug);
	strategies->AddObject("1 - Center", (void *) AutoStrategy::kCenter);
	strategies->AddObject("2 - Boiler", (void *) AutoStrategy::kBoiler);
	strategies->AddObject("3 - Return", (void *) AutoStrategy::kReturn);
	frc::SmartDashboard::PutData("Autonomous Strategy1", strategies.get());

	const AutoStrategy selectedKey = static_cast<AutoStrategy>((int) strategies->GetSelected());
	frc::SmartDashboard::PutNumber("Selected Auto", selectedKey);
}

AutoManager::~AutoManager() {
}

std::unique_ptr<Strategy> AutoManager::CreateStrategy(const AutoStrategy &key) {
	Strategy *strategy = 0;
	switch (key) {
	case kDebug:
		strategy = new DebugAutoStrategy();
		break;
	case kCenter:
		strategy = new CenterGearStrategy();
		break;
	case kBoiler:
		strategy = new BoilerGearStrategy();
		break;
	case kReturn:
		strategy = new DebugAutoStrategy();
		break;
	default:
		std::cerr << "No valid strategy selected";
	}
	return std::unique_ptr<Strategy>(strategy);
}


void AutoManager::Init(std::shared_ptr<World> world) {
	std::cout << "AutoMan Init\n";
	const AutoStrategy selectedKey = static_cast<AutoStrategy>((int) strategies->GetSelected());
	frc::SmartDashboard::PutNumber("Selected Auto", selectedKey);
	std::cout << "Selected Strategy: " << selectedKey << "\n";
	currentStrategy = CreateStrategy(selectedKey);
	if (!currentStrategy) {
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

void AutoManager::SMDB() {
	const AutoStrategy selectedKey = static_cast<AutoStrategy>((int) strategies->GetSelected());
	frc::SmartDashboard::PutNumber("Selected Auto", selectedKey);
}
