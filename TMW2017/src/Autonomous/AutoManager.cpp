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
#include <Autonomous/Strategies/ReturnGearStrategy.h>
#include <Autonomous/Strategies/BoilerShootOnlyStrategy.h>
#include <Autonomous/Strategies/ShootAndScootStrategy.h>



AutoManager::AutoManager() :
		strategies(new frc::SendableChooser<void*>())
{
	strategies->AddDefault("1 - Shoot Only", (void *) AutoStrategy::kShootOnly);
	strategies->AddObject("2 - Center", (void *) AutoStrategy::kCenter);
	strategies->AddObject("3 - Shoot and Scoot", (void *) AutoStrategy::kShootScoot);
	strategies->AddObject("999 - Debug Auto Strategy", (void *) AutoStrategy::kDebug);
	frc::SmartDashboard::PutData("Autonomous Strategy", strategies.get());

	const AutoStrategy selectedKey = static_cast<AutoStrategy>((int) strategies->GetSelected());
	frc::SmartDashboard::PutNumber("Selected Auto", selectedKey);
}

AutoManager::~AutoManager() {
}

std::unique_ptr<Strategy> AutoManager::CreateStrategy(const AutoStrategy &key) {
	const frc::DriverStation::Alliance alliance = frc::DriverStation::GetInstance().GetAlliance();
	const bool isRed =  alliance == frc::DriverStation::Alliance::kRed;
	//|| alliance == frc::DriverStation::Alliance::kInvalid;

	std::cout << "AutoManager::CreateStrategy -> isRed = " << isRed << "\n";

	Strategy *strategy = 0;
	switch (key) {
	case kDebug:
		strategy = new CenterGearStrategy();
//		strategy = new DebugAutoStrategy();
		break;
	case kCenter:
		strategy = new CenterGearStrategy();
		break;
	case kBoiler:
		strategy = new BoilerGearStrategy(isRed, isRed);
		break;
	case kReturn:
		strategy = new ReturnGearStrategy(isRed);
		break;
	case kShootOnly:
		strategy = new BoilerShootOnlyStrategy(isRed);
		break;
	case kShootScoot:
		strategy = new ShootAndScootStrategy(isRed);
		break;
	default:
		strategy = new CenterGearStrategy();
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
