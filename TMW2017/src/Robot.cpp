// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include <vector>
#include <algorithm>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveBase> Robot::driveBase;
std::shared_ptr<GearSystem> Robot::gearSystem;
std::shared_ptr<ClimberSystem> Robot::climberSystem;
std::shared_ptr<ShooterSystem> Robot::shooterSystem;
std::shared_ptr<BallPickupSystem> Robot::ballPickupSystem;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveBase.reset(new DriveBase());
    gearSystem.reset(new GearSystem());
    climberSystem.reset(new ClimberSystem());
    shooterSystem.reset(new ShooterSystem());
    ballPickupSystem.reset(new BallPickupSystem());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	managers.push_back(gearSystem);
	managers.push_back(climberSystem);
	managers.push_back(shooterSystem);
	managers.push_back(ballPickupSystem);

	world.reset(new World());


	// driveBase Twist control
	// TODO: Think about better place than this
	Preferences *prefs = Preferences::GetInstance();
	if (!prefs->ContainsKey("TwistP")) {
		prefs->PutFloat("TwistP", 0.02);
	}
	if (!prefs->ContainsKey("TwistI")) {
		prefs->PutFloat("TwistI", 0.0);
	}
	if (!prefs->ContainsKey("TwistD")) {
		prefs->PutFloat("TwistD", 0.12);
	}
	// driveBase Twist Control

	// driveBase Drive PID Control
	if (!prefs->ContainsKey("DriveP")) {
		prefs->PutFloat("DriveP", 2);
	}
	if (!prefs->ContainsKey("DriveI")) {
		prefs->PutFloat("DriveI", 0.001);
	}
	if (!prefs->ContainsKey("DriveD")) {
		prefs->PutFloat("DriveD", 0.0);
	}
	if (!prefs->ContainsKey("DriveF")) {
		prefs->PutFloat("DriveF", 3.93);
	}
	if (!prefs->ContainsKey("DriveIZone")) {
		prefs->PutFloat("DriveIZone", 20.0);
	}
	// driveBase Drive PID

  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	RunManagerSMDBs();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
	autoManager.reset(new AutoManager());
	autoManager->Init(world);
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	autoManager->Periodic(world);
	RunManagers();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Cancel();
	}
	driveBase->InitTeleop();
	driveBase->UseOpenLoopDrive();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	if (oi->GPStart->RisingEdge()) {
		ballPickupSystem->ToggleBallPickup();
	}
	if (oi->GPBack->RisingEdge()) {
		ballPickupSystem->ReverseBallPickup();
	}

	if (oi->GPY->RisingEdge()) {
		gearSystem->ResetGear();
	}
	if (oi->GPB->RisingEdge()) {
		gearSystem->EjectGear();
	}
	if (oi->GPA->RisingEdge()) {
		gearSystem->PickUpGear();
	}



	if (oi->GPLT->Pressed()) {
		climberSystem->SetClimberEnabled(true);
	} else {
		climberSystem->SetClimberEnabled(false);
	}

	if (oi->DR1->Pressed()) {
		shooterSystem->SetShooterEnabled(true);
	} else {
		shooterSystem->SetShooterEnabled(false);
	}


	gearSystem->SetGearBarSpeed(oi->GetGamepadLeftStick());

	shooterSystem->EnableHopper(oi->GetGamepadRightStick());

	driveBase->Crab(
			oi->GetJoystickTwist(),
			-oi->GetJoystickY(),
			oi->GetJoystickX(),
			true);

	RunManagers();
}

void Robot::TestPeriodic() {
	lw->Run();
}


void Robot::InitManagers() {
	std::for_each(managers.begin(), managers.end(),
			[](std::shared_ptr<Manager> &manager) {
				manager->InitManager();
			});
}

void Robot::RunManagers() {
	std::for_each(managers.begin(), managers.end(),
			[](std::shared_ptr<Manager> &manager) {
				manager->Run();
				manager->SMDB();
			});
}

void Robot::RunManagerSMDBs() {
	std::for_each(managers.begin(), managers.end(),
			[](std::shared_ptr<Manager> &manager) {
				manager->SMDB();
			});
}

START_ROBOT_CLASS(Robot);

