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

BoilerShootOnlyStrategy::BoilerShootOnlyStrategy(bool isRed) {
	Preferences *prefs = Preferences::GetInstance();

	double angle = 180.0;
	const double speed = prefs->GetDouble("ShootOnlySpeed");
	const double yDistance = prefs->GetDouble("ShootOnlyY");
	const double threshold = prefs->GetDouble("ShootOnlyT");
	double driveBumpX = prefs->GetDouble("ShootOnlyBumpXSpeed");
	const double ignoreJerk = prefs->GetDouble("ShootOnlyIgnoreJerk");
	const double jerk = prefs->GetDouble("ShootOnlyJerk");
	const double ackermannAngle = prefs->GetDouble("AckermannAngle");
	const double afterBumpSpeed = prefs->GetDouble("ShootOnlyAfterBumpSpeed");
	double afterBumpSpeedX = prefs->GetDouble("ShootOnlyAfterBumpSpeedX");
	const double afterBumpY = prefs->GetDouble("ShootOnlyAfterBumpY");
	const double delayBeforeShoot = prefs->GetDouble("ShootOnlyDelayAfterBump");
	const double ackermanTurnSpeed = prefs->GetDouble("ShootOnlyAckermannSpeed");
	const double shootOffsetAngle = prefs->GetDouble("ShootScootShootAngleOffset");


	if (!isRed) {
		driveBumpX *= -1;
		afterBumpSpeedX *= -1;
	}

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new ControlShooterMotor(true));
	steps.push_back(new XYPIDControlledDrive(angle, speed, 0.0, yDistance, threshold, DriveUnit::Units::kInches ));
	steps.push_back(new DriveToBump(angle, 0, driveBumpX, 1.5, ignoreJerk, jerk));
	steps.push_back(new TimedDrive(180.0, afterBumpSpeed, afterBumpSpeedX, 2.0));
	steps.push_back(new DropGearAssembly(0, true));
	steps.push_back(new Delay(delayBeforeShoot));
	if (isRed) {
		steps.push_back(new AckermannDrive(ackermanTurnSpeed, ackermannAngle));
	} else {
		//steps.push_back(new AckermannDrive(-ackermanTurnSpeed, angle - shootOffsetAngle));	// 180 - 2.5 = -177.5
	}
	steps.push_back(new Shoot(13));
}

