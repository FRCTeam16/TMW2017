/*
 * ShootAndScootStrategy.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: User
 */

#include <Autonomous/Strategies/ShootAndScootStrategy.h>
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/Rotate.h>
#include <Autonomous/Steps/Shoot.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Steps/AckermannDrive.h>

ShootAndScootStrategy::ShootAndScootStrategy(bool isRed) {
	Preferences *prefs = Preferences::GetInstance();
	double angle = 90.0;

	const double fwdSpeed = prefs->GetDouble("ShootScootForwardSpeed");
	const double fwdDist = prefs->GetDouble("ShootScootForwardY");
	const double fwdDistThresh = prefs->GetDouble("ShootScootForwardT");
	const double hangSpeed = prefs->GetDouble("ShootScootHangSpeed");
	const double hangY = prefs->GetDouble("ShootScootHangY");
	double hangX = prefs->GetDouble("ShootScootHangX");
	const double hangT = prefs->GetDouble("ShootScootHangT");
	double turnAngle = prefs->GetDouble("ShootScootHangAngle");
	const bool doHang = prefs->GetBoolean("ShootScootDoHang");

	const double ackermannAngle = prefs->GetDouble("AckermannAngle");
	double ackermanTurnSpeed = prefs->GetDouble("ShootOnlyAckermannSpeed");
	const double shootOffsetAngle = prefs->GetDouble("ShootScootShootAngleOffset");


	if (!isRed) {
		angle = -90.0;
		turnAngle *= -1;
		hangX *= -1;
	} else {
		// FIXME: Should ackermann step determine direction to spin?
		// When red this turns us clockwise
		ackermanTurnSpeed *= -1;
	}

	steps.push_back(new SetGyroOffset(angle));
	if (isRed) {
		angle += shootOffsetAngle;
	} else {
		angle = angle - (180.0 - ackermannAngle);		//  -90 - (180.0 - 167) = -103
	}

	steps.push_back(new ControlShooterMotor(true, 0.95, 0.1, false));
	//steps.push_back(new DropGearAssembly(0, true));
	steps.push_back(new AckermannDrive(ackermanTurnSpeed, angle));
	steps.push_back(new ControlShooterMotor(true, 0.95, 2.5, false));
	steps.push_back(new Shoot(2.0));
	steps.push_back(new ControlShooterMotor(false));

	steps.push_back(new TimedDrive(angle, 0.001, 0.0, 0.25));
	XYPIDControlledDrive *drive = new XYPIDControlledDrive(angle, fwdSpeed, 0.0, fwdDist, fwdDistThresh, DriveUnit::Units::kInches, false, 10.0);
	drive->SetUseCurrentAngle();	// use our shooting offset angle to drive at
	steps.push_back(drive);
	steps.push_back(new Rotate(turnAngle));		// R -60 / B 60

	steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, hangY, hangT, DriveUnit::Units::kInches, false, 6.0, false));
	if (doHang) {
		steps.push_back(new EjectGear(0.5));
		steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, hangY, hangT, DriveUnit::Units::kInches, true, 4.0, false));
	}

}

