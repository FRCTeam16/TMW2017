/*
 * DebugAutoStrategy.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: User
 */

#include "DebugAutoStrategy.h"
#include <Autonomous/Steps/DriveSteps.h>
#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Autonomous/Steps/SetGyroOffset.h>
#include <Autonomous/Steps/Rotate.h>
#include <Autonomous/Steps/Shoot.h>
#include <Autonomous/Steps/GearSteps.h>
#include <Autonomous/Steps/AckermannDrive.h>

DebugAutoStrategy::DebugAutoStrategy() {
	Preferences *prefs = Preferences::GetInstance();
	double angle = prefs->GetDouble("DebugAutoParam1");


	const double hangSpeed = prefs->GetDouble("ShootScootHangSpeed");
	const double hangY = prefs->GetDouble("ShootScootHangY");
	double hangX = prefs->GetDouble("ShootScootHangX");
	const double hangT = prefs->GetDouble("ShootScootHangT");
	double turnAngle = prefs->GetDouble("ShootScootHangAngle");

	steps.push_back(new SetGyroOffset(angle));
	steps.push_back(new Rotate(turnAngle));
	steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, hangY, hangT, DriveUnit::Units::kInches, false, 6.0, false));
//	steps.push_back(new EjectGear(0.5));
//	steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, -hangY, hangT, DriveUnit::Units::kInches, true, 4.0));
}

void DebugAutoStrategy::DebugShootScoot() {
	Preferences *prefs = Preferences::GetInstance();
	double angle = 90.0;
	double turnAngle = -60.0;
	const double fwdSpeed = prefs->GetDouble("ShootScootForwardSpeed");
	const double fwdDist = prefs->GetDouble("ShootScootForwardY");
	const double fwdDistThresh = prefs->GetDouble("ShootScootForwardT");
	const double hangSpeed = prefs->GetDouble("ShootScootHangSpeed");
	const double hangY = prefs->GetDouble("ShootScootHangY");
	double hangX = prefs->GetDouble("ShootScootHangX");
	const double hangT = prefs->GetDouble("ShootScootHangT");

	const double ackermannAngle = prefs->GetDouble("AckermannAngle");
	double ackermanTurnSpeed = prefs->GetDouble("ShootOnlyAckermannSpeed");



	ackermanTurnSpeed *= -1;


	steps.push_back(new SetGyroOffset(angle));
	angle += 4.5;
//	steps.push_back(new ControlShooterMotor(true, 0.95, 0.1, false));
	steps.push_back(new AckermannDrive(ackermanTurnSpeed, angle));
//	steps.push_back(new ControlShooterMotor(true, 0.95, 2.5, false));
//	steps.push_back(new Shoot(2.0));
//	steps.push_back(new ControlShooterMotor(false));

	steps.push_back(new TimedDrive(angle, 0.001, 0.0, 0.25));
	steps.push_back(new XYPIDControlledDrive(angle, fwdSpeed, 0.0, fwdDist, fwdDistThresh, DriveUnit::Units::kInches, false, 10.0));
	steps.push_back(new Rotate(turnAngle));
	steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, hangY, hangT, DriveUnit::Units::kInches, false, 6.0));
//	steps.push_back(new EjectGear(0.5));
//	steps.push_back(new XYPIDControlledDrive(turnAngle, hangSpeed, hangX, -hangY, hangT, DriveUnit::Units::kInches, true, 4.0));
}

