// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include <vector>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Subsystems/BallPickupSystem.h"
#include "Subsystems/ClimberSystem.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/GearSystem.h"
#include "Subsystems/ShooterSystem.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"
#include "Autonomous/AutoManager.h"
#include "Autonomous/World.h"


class Robot : public IterativeRobot {
private:
	std::vector<std::shared_ptr<Manager>> managers;
	std::unique_ptr<AutoManager> autoManager;
	std::shared_ptr<World> world;

	double angle = 0;
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<DriveBase> driveBase;
    static std::shared_ptr<GearSystem> gearSystem;
    static std::shared_ptr<ClimberSystem> climberSystem;
    static std::shared_ptr<ShooterSystem> shooterSystem;
    static std::shared_ptr<BallPickupSystem> ballPickupSystem;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

	void InitManagers();
	void RunManagers();
	void RunManagerSMDBs();
};
#endif
