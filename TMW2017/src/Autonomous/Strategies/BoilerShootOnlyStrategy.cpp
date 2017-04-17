/*
 * BoilerShootOnlyStrategy.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/BoilerShootOnlyStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/Shoot.h>
#include <Autonomous/Steps/AckermannDrive.h>
#include <Autonomous/Steps/Delay.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Steps/Rotate.h>

BoilerShootOnlyStrategy::BoilerShootOnlyStrategy(bool isRed) {
	const bool isBlue = !isRed;
	Preferences *prefs = Preferences::GetInstance();

	const bool blueSpinOnly = isBlue && prefs->GetBoolean("ShootOnlyBlueSpin");
	double angle = 180.0 ;
	if (blueSpinOnly) {
		angle = 0.0;
	}
	const double speed = prefs->GetDouble("ShootOnlySpeed");
	const double yDistance = prefs->GetDouble("ShootOnlyY");
	const double threshold = prefs->GetDouble("ShootOnlyT");
	double driveBumpX = prefs->GetDouble("ShootOnlyBumpXSpeed");
	const double ignoreJerk = prefs->GetDouble("ShootOnlyIgnoreJerk");
	const double jerk = prefs->GetDouble("ShootOnlyJerk");
	const double ackermannAngle = prefs->GetDouble("AckermannAngle");
	const double afterBumpSpeed = prefs->GetDouble("ShootOnlyAfterBumpSpeed");
	double afterBumpSpeedX = prefs->GetDouble("ShootOnlyAfterBumpSpeedX");
	const double driveIntoWallTime = prefs->GetDouble("ShootOnlyDriveIntoWallTime");
	const double blueSpinSpeed = prefs->GetDouble("ShootOnlyBlueSpinSpeed");
	const double blueSpinX = prefs->GetDouble("ShootOnlyBlueSpinX");
	const double blueSpinPushT = prefs->GetDouble("ShootOnlyBlueSpinPushT");
	const double blueSpinReturnTime = prefs->GetDouble("ShootOnlyBlueSpinReturnTime");
	const double blueSpinAngle = prefs->GetDouble("ShootOnlyBlueSpinAngle");
	const double blueSpinShootAngleThreshold = prefs->GetDouble("ShootOnlyBlueSpinShootAngleT");
	const double afterBumpY = prefs->GetDouble("ShootOnlyAfterBumpY");
	const double delayBeforeShoot = prefs->GetDouble("ShootOnlyDelayAfterBump");
	const double ackermanTurnSpeed = prefs->GetDouble("ShootOnlyAckermannSpeed");
	const double shootOffsetAngle = prefs->GetDouble("ShootScootShootAngleOffset");


	if (isBlue) {
		driveBumpX *= -1;
		afterBumpSpeedX *= -1;
	}

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new ControlShooterMotor(true));
	steps.push_back(new XYPIDControlledDrive(angle, speed, 0.0, yDistance, threshold, DriveUnit::Units::kInches ));
	steps.push_back(new DriveToBump(angle, 0, driveBumpX, 1.5, ignoreJerk, jerk));
	steps.push_back(new TimedDrive(angle, afterBumpSpeed, afterBumpSpeedX, driveIntoWallTime));
	if (blueSpinOnly) {
		steps.push_back(new XYPIDControlledDrive(angle, blueSpinSpeed, blueSpinX, 0.0, blueSpinPushT, DriveUnit::Units::kInches ));
		steps.push_back(new Rotate(blueSpinAngle));
//		steps.push_back(new TimedDrive(blueSpinAngle, 0.0, -blueSpinSpeed, blueSpinReturnTime));
	}
	steps.push_back(new DropGearAssembly(0, true));
	steps.push_back(new Delay(delayBeforeShoot));
	if (isRed) {
		steps.push_back(new AckermannDrive(ackermanTurnSpeed, ackermannAngle));
	} else {
		//steps.push_back(new AckermannDrive(-ackermanTurnSpeed, angle - shootOffsetAngle));	// 180 - 2.5 = -177.5
	}
	if (blueSpinOnly) {
		steps.push_back(new Shoot(13, blueSpinAngle, blueSpinShootAngleThreshold));
	} else {
		steps.push_back(new Shoot(13));
	}
}

