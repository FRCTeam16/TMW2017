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
#include <Threads.h>

#include <Autonomous/Steps/DriveSteps.h>

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
	autoManager.reset(new AutoManager());
	collisionDetector.reset(new CollisionDetector(RobotMap::gyro, 10.0));


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
	if (!prefs->ContainsKey("DriveControlP")) {
		prefs->PutFloat("DriveControlP", 0.001);
	}
	if (!prefs->ContainsKey("DriveControlI")) {
		prefs->PutFloat("DriveControlI", 0.0);
	}
	if (!prefs->ContainsKey("DriveControlD")) {
		prefs->PutFloat("DriveControlD", 0.0);
	}
	if (!prefs->ContainsKey("DriveControlF")) {
		prefs->PutFloat("DriveControlF", 0);
	}
	if (!prefs->ContainsKey("DriveControlIZone")) {
		prefs->PutFloat("DriveControlIZone", 0.0);
	}
	SetDoublePref("DriveControlTwistIZone", 5.0);

	SetDoublePref("TeleopAckermannAngle", 172.0);

	SetDoublePref("Hopper Shoot Speed", 0.5);

	// Autonomous
	SetDoublePref(DriveUnit::PULSES_PER_INCH, 18.2);
	SetDoublePref("BoilerAutoAngle", -52.0);
	SetDoublePref("BoilerGearSpeed", 0.3);
	SetDoublePref("BoilerGearX", -60);
	SetDoublePref("BoilerGearY", 88.0);
	SetDoublePref("BoilerGearT", 1.5);
	SetDoublePref("BoilerJerk", 1.3);
	SetDoublePref("BoilerBumpX", 0.4);
	SetDoublePref("ReverseBoilerGearY", -15);
	SetDoublePref("ReverseBoilerGearX", -15);
	SetDoublePref("ReverseBoilerGearT", -1);
	SetDoublePref("AckermannAngle", 167.0);

	SetDoublePref("ReturnAutoAngle", 60.0);
	SetDoublePref("ReturnGearX", 83);
	SetDoublePref("ReturnGearY", 96.0);
	SetDoublePref("ReturnGearT", 1.5);
	SetDoublePref("ReturnAutoAngle", 60.0);

	SetDoublePref("ReturnGearX2", 15);
	SetDoublePref("ReturnGearY2", 15.0);
	SetDoublePref("ReturnGearT2", 1.5);

	SetDoublePref("ReverseReturnGearX", -15);
	SetDoublePref("ReverseReturnGearY", -15);
	SetDoublePref("ReverseReturnGearT", -1);

	SetDoublePref("CenterGearY", 64.25);
	SetDoublePref("CenterGearYSpeed", 0.2);
	SetDoublePref("CenterGearTInches", 4);

	SetDoublePref("ShootOnlySpeed", 0.4);
	SetDoublePref("ShootOnlyY", 85);
	SetDoublePref("ShootOnlyT", 1.5);
	SetDoublePref("ShootOnlyBumpXSpeed", 0.4);
	SetDoublePref("ShootOnlyIgnoreJerk", 0.04);
	SetDoublePref("ShootOnlyJerk", 1.0);

	SetDoublePref("ShootOnlyAfterBumpSpeed", -0.5);
	SetDoublePref("ShootOnlyAfterBumpSpeedX", 0.1);
	SetDoublePref("ShootOnlyAfterBumpY", 3);
	SetDoublePref("ShootOnlyDelayAfterBump", 0.5);
	SetDoublePref("ShootOnlyAckermannSpeed", 0.3);


	SetDoublePref("ShootScootShootAngleOffset", 4.5);
	SetDoublePref("ShootScootForwardSpeed", 0.4);
	SetDoublePref("ShootScootForwardY", 66);
	SetDoublePref("ShootScootForwardT", 1.5);
	SetDoublePref("ShootScootHangSpeed", 0.2);
	SetDoublePref("ShootScootHangY", 4.0);
	SetDoublePref("ShootScootHangX", -2.3);
	SetDoublePref("ShootScootHangT", 0.5);
	SetDoublePref("ShootScootHangAngle", -60.0);
	if (!prefs->ContainsKey("ShootScootDoHang")) {
		prefs->PutBoolean("ShootScootDoHang", true);
	}


	SetDoublePref("DebugAutoParam1", 0.00);


	if (!prefs->ContainsKey("EnabledLED")) {
		prefs->PutBoolean("EnabledLED", false);
	}


	// Initialize LED Communications background thread
	// If problems here, may need to be located in an InitManager() type call in Auto or Teleop
//	if (prefs->GetBoolean("EnabledLED", false)) {
//		ledThread = std::thread(&LEDCommunications::Run, new LEDCommunications(16));
//		ledThread.detach();	// Thread must be detached since WPILIB doesn't provide a suitable join() point
//	}
}

void Robot::SetDoublePref(llvm::StringRef key, double value) {
	Preferences *prefs = Preferences::GetInstance();
	if (!prefs->ContainsKey(key)) {
		prefs->PutDouble(key, value);
	}
}


/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	driveBase->ZeroDriveEncoders();
	driveBase->driveControlEncoderSource->SetShowDebug(false);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	RunManagerSMDBs();
	frc::SmartDashboard::PutNumber("Gyro Angle", RobotMap::gyro->GetAHRS()->GetAngle());
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
	world.reset(new World());
	world->Init();
	autoManager->Init(world);
	driveBase->InitAuto();
	InitManagers();
	driveBase->driveControlEncoderSource->SetShowDebug(false);
}

void Robot::AutonomousPeriodic() {
	// Update World
	Scheduler::GetInstance()->Run();
	autoManager->Periodic(world);
	RunManagers();

	RobotMap::gyro->DebugPrint();
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
	InitManagers();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	const bool isRed =  frc::DriverStation::GetInstance().GetAlliance() == frc::DriverStation::Alliance::kRed;
	bool useCrab = true;
	bool useDriveBaseAngle = false;
	bool robotCentricCrab = false;
	bool firing = false;

	if (oi->DR1->Pressed()) {
		shooterSystem->SetFireEnabled(true);
		firing = true;
	} else {
		shooterSystem->SetFireEnabled(false);
	}

	if (oi->DR11->RisingEdge()) {
		useTeleopSpeedControl = !useTeleopSpeedControl;
		if (useTeleopSpeedControl) {
			driveBase->UseClosedLoopDrive();
		} else {
			driveBase->InitTeleop();
		}
	}

	if (oi->DR2->RisingEdge()) {
		gearSystem->EjectGear();
	}

	if (oi->DR3->Pressed()) {
		Preferences *prefs = Preferences::GetInstance();
		const double ackermannAngle = prefs->GetDouble("TeleopAckermannAngle");
		const double walloffsetShootAngle = prefs->GetDouble("ShootScootShootAngleOffset");
		const double angle = (isRed) ? 90.0 + walloffsetShootAngle : -ackermannAngle;
		driveBase->SetTargetAngle(angle);
		useDriveBaseAngle = true;
	}

	if (oi->DR4->Pressed()) {
		Preferences *prefs = Preferences::GetInstance();
		const double ackermannAngle = prefs->GetDouble("TeleopAckermannAngle");
		const double walloffsetShootAngle = prefs->GetDouble("ShootScootShootAngleOffset");
		const double angle = (isRed) ? ackermannAngle : (-180.0 + walloffsetShootAngle);
		driveBase->SetTargetAngle(angle);
		useDriveBaseAngle = true;
	}



	if (oi->DL1->Pressed()) {
		useCrab = false;
	}


	if (oi->DL2->Pressed()) {
		// Only run auto-centering when we are in field-centric crabbing
		if (useCrab) {
			driveBase->SetTargetAngle(0.0);
			useDriveBaseAngle = true;
		} else {
			robotCentricCrab = true;
		}
	}

	if (oi->DL4->Pressed()) {
		driveBase->SetTargetAngle(60.0);
		useDriveBaseAngle = true;
	}

	if (oi->DL5->Pressed()) {
		driveBase->SetTargetAngle(-60.0);
		useDriveBaseAngle = true;
	}



	if (oi->GPStart->RisingEdge()) {
		gearSystem->ToggleGearBarReverse();
	}
	if (oi->GPBack->RisingEdge()) {
		ballPickupSystem->ReverseBallPickup();
	}

	if (oi->GPX->RisingEdge()) {
		shooterSystem->ToggleShooter();
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

	if (oi->GPLB->Pressed()) {
		RobotMap::indicatorLight->Set(false);
	} else {
		RobotMap::indicatorLight->Set(true);
	}

	if (oi->GPRB->Pressed()) {
		ballPickupSystem->SetBallPickupEnabled(true);
	} else {
		//ballPickupSystem->SetBallPickupEnabled(false);
	}

	if(oi->GPRB->FallingEdge()) {
		ballPickupSystem->PulseReverseBallPickup();
	}

	climberSystem->SetClimberSpeed(oi->GetGamepadLT());
	gearSystem->SetGearBarSpeed(oi->GetGamepadLeftStick());
	shooterSystem->SetHopperSpeed(oi->GetGamepadRightStick());


	const double threshold = (firing) ? 0.2 : 0.1;
	bool lockWheels = false;
	if (firing) {
		if (fabs(oi->GetJoystickTwist(threshold)) > 0 ||
			fabs(oi->GetJoystickX(threshold)) > 0 ||
			fabs(oi->GetJoystickY(threshold)) > 0) {
			lockWheels = false;
		} else {
			lockWheels = true;
		}
	}

	if (useCrab || robotCentricCrab) {
		const double twistInput = (useDriveBaseAngle) ?
					driveBase->GetTwistControlOutput() :
					oi->GetJoystickTwist(threshold);
		const bool useGyro = !robotCentricCrab;

		if (!lockWheels) {
			driveBase->Crab(
					twistInput,
					-oi->GetJoystickY(threshold),
					oi->GetJoystickX(threshold),
					useGyro);
		} else {
			driveBase->Lock();
		}
	} else {
		// Ackermann Steering
		driveBase->Steer(oi->getLeftJoystickXRadians(),
						 oi->GetJoystickY(),
						 0.5);
	}

	SmartDashboard::PutNumber("GyroAngle",RobotMap::gyro->GetYaw());

	RunManagers();
}

void Robot::TestPeriodic() {
	lw->Run();
}


void Robot::InitManagers() {
	const Manager::RunMode runMode = (IsAutonomous() ? Manager::RunMode::kAuto : Manager::RunMode::kTele);
	std::for_each(managers.begin(), managers.end(),
			[=](std::shared_ptr<Manager> &manager) {
				manager->InitManager(runMode);
			});

	if (!ledThread.joinable()) {
		Preferences *prefs = Preferences::GetInstance();
		if (prefs->GetBoolean("EnabledLED", false)) {
			ledThread = std::thread(&LEDCommunications::Run, new LEDCommunications(16));
			ledThread.detach();	// Thread must be detached since WPILIB doesn't provide a suitable join() point
		}
	}
}

void Robot::RunManagers() {
	std::for_each(managers.begin(), managers.end(),
			[](std::shared_ptr<Manager> &manager) {
				manager->Run();
				manager->SMDB();
			});
	collisionDetector->Detect();
	autoManager->SMDB();
	frc::SmartDashboard::PutNumber("DriveControl Error",driveBase->GetRearRightDrive()->GetClosedLoopError());
	frc::SmartDashboard::PutBoolean("Teleop Speed Control", useTeleopSpeedControl);
}

void Robot::RunManagerSMDBs() {
	std::for_each(managers.begin(), managers.end(),
			[](std::shared_ptr<Manager> &manager) {
				manager->SMDB();
			});
	autoManager->SMDB();
	frc::SmartDashboard::PutNumber("DriveControl Error",driveBase->GetRearRightDrive()->GetClosedLoopError());
	frc::SmartDashboard::PutBoolean("Teleop Speed Control", useTeleopSpeedControl);

}

START_ROBOT_CLASS(Robot);

