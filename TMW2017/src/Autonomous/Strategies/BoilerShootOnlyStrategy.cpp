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

BoilerShootOnlyStrategy::BoilerShootOnlyStrategy(bool isRed) {
	Preferences *prefs = Preferences::GetInstance();

	const double angle = 180.0;
	const double speed = prefs->GetDouble("ShootOnlySpeed", 0.4);
	const double yDistance = prefs->GetDouble("ShootOnlyY", 85);
	const double threshold = prefs->GetDouble("ShootOnlyT", 1.5);
	double driveBumpX = prefs->GetDouble("ShootOnlyBumpXSpeed", 0.4);
	const double ignoreJerk = prefs->GetDouble("ShootOnlyIgnoreJerk", 0.04);
	const double jerk = prefs->GetDouble("ShootOnlyJerk", 1.0);
	const double ackermannAngle = prefs->GetDouble("AckermannAngle", 165.0);
	const double afterBumpSpeed = prefs->GetDouble("ShootOnlyAfterBumpSpeed", -0.5);
	double afterBumpSpeedX = prefs->GetDouble("ShootOnlyAfterBumpSpeedX", 0.2);
	const double afterBumpY = prefs->GetDouble("ShootOnlyAfterBumpY", 3);
	const double delayBeforeShoot = prefs->GetDouble("ShootOnlyDelayAfterBump", 2.0);
	const double ackermanTurnSpeed = prefs->GetDouble("ShootOnlyAckermannSpeed", 0.3);

	if (!isRed) {
		driveBumpX *= -1;
		afterBumpSpeedX *= -1;
	}

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new ControlShooterMotor(true));
	steps.push_back(new XYPIDControlledDrive(angle, speed, 0.0, yDistance, threshold, DriveUnit::Units::kInches ));
	steps.push_back(new DriveToBump(angle, 0, driveBumpX, 1.5, ignoreJerk, jerk));
	steps.push_back(new TimedDrive(180.0, afterBumpSpeed, afterBumpSpeedX, 2.0));
	steps.push_back(new Delay(delayBeforeShoot));
	if (isRed) {
		steps.push_back(new AckermannDrive(ackermanTurnSpeed, ackermannAngle));
	}
	steps.push_back(new Shoot(13));

}

BoilerShootOnlyStrategy::~BoilerShootOnlyStrategy() {
}

