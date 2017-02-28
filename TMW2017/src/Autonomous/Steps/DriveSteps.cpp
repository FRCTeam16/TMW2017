/*
 * PIDDrive.cpp
 */

#include <Autonomous/Steps/DriveSteps.h>
#include <Robot.h>

using namespace std;

bool ZeroDriveEncoders::Run(std::shared_ptr<World> world) {
	if (firstRun) {
		firstRun = false;
		Robot::driveBase->ZeroDriveEncoders();
	}

	lastEncoderPosition = Robot::driveBase->GetFrontLeftDrive()->GetEncPosition();
	std::cout << "Waiting for encoder position to be zero: " << lastEncoderPosition << "\n";
	return (lastEncoderPosition == 0);
}

const std::string DriveUnit::PULSES_PER_INCH = "PulsesPerInch";
double DriveUnit::ToPulses(double value, DriveUnit::Units unit) {
	Preferences *prefs = Preferences::GetInstance();
	const double pulsesPerInch = prefs->GetDouble(PULSES_PER_INCH, 16.5);
	double converted = 0;
	switch (unit) {
	case kInches:
		converted = value * pulsesPerInch;
		break;
	case kPulses:
		converted = value;
		break;
	default:
		std::cerr << "Asked to convert unhandled unit: " << unit << "\n";
		converted = value;
		break;
	}
	std::cout << "Converted " << value << " to " << converted << " with ppi " << pulsesPerInch << "\n";
	return converted;
}

bool SimpleEncoderDrive::Run(std::shared_ptr<World> world) {
	cout << "SimpleEncoderDrive target distance" << targetDistance << '\n';

	// Initialize
	if (firstRun) {
		firstRun = false;
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
	}

	const int currentPosition = abs(Robot::driveBase->GetFrontLeftDrive()->GetEncPosition());
	const double elapsedTime = world->GetClock() - startTime;
	SmartDashboard::PutNumber("Encoder Position", currentPosition);
	cout << "SimpleEncoderDrive Encoder: " << currentPosition << "\n";

	if (currentPosition >= targetDistance) {
		cout << "Position reached in " << elapsedTime << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTime > 20) {
		cout << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else {
		crab->Update(Robot::driveBase->GetTwistControlOutput(), ySpeed, xSpeed, true);
		return false;
	}
}



bool PIDControlledDrive::Run(std::shared_ptr<World> world) {
	if (startTime < 0) {
		targetSetpoint = DriveUnit::ToPulses(targetDistance, units);
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
		Robot::driveBase->SetTargetDriveDistance(targetSetpoint, speed);
		Robot::driveBase->UseClosedLoopDrive();
		startingEncoderCount = Robot::driveBase->GetDriveControlEncoderPosition();
	}

	const double currentEncoderPosition = Robot::driveBase->GetDriveControlEncoderPosition();
	const double currentError = Robot::driveBase->GetDriveControlError();
	const double elapsedTimeMillis = world->GetClock() - startTime;
	const double currentPIDOutput = Robot::driveBase->GetDriveControlOutput();

	SmartDashboard::PutNumber("PIDController Output", currentPIDOutput);
	cout << "PIDControlledDrive target setpoint          = " << targetSetpoint << '\n';
	cout << "PIDControlledDrive Current Encoder Position = " << currentEncoderPosition << "\n";
	cout << "PIDControlledDrive Current Error            = " << currentError << "\n";
	cout << "PIDControlledDrive PID Output:              " << currentPIDOutput << "\n";

	if (abs(currentError) <= DriveUnit::ToPulses(distanceThreshold, units)) {
		cout << "!!!Position reached in " << elapsedTimeMillis << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTimeMillis > 5000) {
		cerr << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else if (collisionDetector->Detect()) {
		cerr << "**** EMERGENCY HALT DUE TO COLLISION ****\n";
		crab->Stop();
		return true;
	} else {
		const double crabSpeed = currentPIDOutput * ((reverse) ? -1.0 : 1.0);
		const double xspeed = crabSpeed * sin(angle * M_PI / 180.0);
		const double yspeed = crabSpeed * cos(angle * M_PI / 180.0);
		crab->Update(
				Robot::driveBase->GetTwistControlOutput(),
				yspeed,
				xspeed,
				true);
		return false;
	}
}



bool XYPIDControlledDrive::Run(std::shared_ptr<World> world) {
	if (startTime < 0) {
		const double hypotenuse = sqrt(XtargetDistance*XtargetDistance + YtargetDistance*YtargetDistance);
		targetSetpoint = DriveUnit::ToPulses(hypotenuse, units);
		startTime = world->GetClock();
		Robot::driveBase->SetTargetAngle(angle);
		Robot::driveBase->SetTargetDriveDistance(targetSetpoint, speed);
		Robot::driveBase->UseClosedLoopDrive();
		startingEncoderCount = Robot::driveBase->GetDriveControlEncoderPosition();
	}

	const double currentEncoderPosition = Robot::driveBase->GetDriveControlEncoderPosition();
	const double currentError = Robot::driveBase->GetDriveControlError();
	const double elapsedTimeMillis = world->GetClock() - startTime;
	const double currentPIDOutput = Robot::driveBase->GetDriveControlOutput();

	SmartDashboard::PutNumber("PIDController Output", currentPIDOutput);
	cout << "PIDControlledDrive target setpoint          = " << targetSetpoint << '\n';
	cout << "PIDControlledDrive Current Encoder Position = " << currentEncoderPosition << "\n";
	cout << "PIDControlledDrive Current Error            = " << currentError << "\n";
	cout << "PIDControlledDrive PID Output:              " << currentPIDOutput << "\n";

	if (abs(currentError) <= DriveUnit::ToPulses(distanceThreshold, units)) {
		cout << "!!!Position reached in " << elapsedTimeMillis << "\n";
		crab->Stop();
		return true;
	} else if (elapsedTimeMillis > 5000) {
		cout << "**** EMERGENCY HALT ***" << "\n";
		crab->Stop();
		return true;
	} else if (collisionDetector->Detect()) {
		cerr << "**** EMERGENCY HALT DUE TO COLLISION ****\n";
		crab->Stop();
		return true;
	} else {
		const double crabSpeed = currentPIDOutput * ((reverse) ? -1.0 : 1.0);
		const double angleRadians = atan2(XtargetDistance, YtargetDistance);

		// FIXME: detect direction, avoid divide by zero, could abs ratio
		const double xspeed = crabSpeed * sin(angleRadians);
		const double yspeed = crabSpeed * cos(angleRadians);

		// Handle translation of axes manually if yaw offset is not available
//		const double xspeed = -crabSpeed * cos(angleRadians);
//		const double yspeed = -crabSpeed * sin(angleRadians);

		crab->Update(
				Robot::driveBase->GetTwistControlOutput(),
				yspeed,
				xspeed,
				true);
		return false;
	}
}


