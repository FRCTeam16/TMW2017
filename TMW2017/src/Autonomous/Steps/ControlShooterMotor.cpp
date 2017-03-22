/*
 * ControlShooterMotor.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: User
 */

#include <Autonomous/Steps/ControlShooterMotor.h>
#include <Robot.h>

bool ControlShooterMotor::Run(std::shared_ptr<World> world) {
	std::cout << "ControlShooterMotor::Run enabled -> " << enabled << "\n";
	const double currentTime = world->GetClock();
	if (startTime < 0) {
		startTime = currentTime;
	}

	bool retval = true;
	const bool afterStartup = enabled && ((currentTime - startTime) > enableDelayTime);
	std::cout << "ControlShooterMotor afterStartup = " << afterStartup << "\n";

	if (enabled) {
		// continue running until after startup checks can begin firing
		std::cout << " ControlShooterMotor in enabled, setting default retval = " << retval << "\n";
		retval = afterStartup;
	}

	if (afterStartup) {
		if (thresholdPercent > 0) {
			std::shared_ptr<CANTalon> shooter = RobotMap::shooterSystemShooter1;
			const double setpoint = shooter->GetSetpoint();
			const double current = shooter->Get();
			std::cout << "ControlShooterMotor setpoint = " << setpoint << "\n";
			std::cout << "ControlShooterMotor current  = " << current << "\n";
			std::cout << "ControlShooterMotor thresholdPercent = " << thresholdPercent << "\n";
			std::cout << "ControlShooterMotor threshold check  = " << fabs(current / setpoint)  << "\n";
			if (fabs(current / setpoint) < thresholdPercent) {
				// continue waiting for rampup unless timed out
				std::cout << "ControlShooterMotor threshold not met, setting retval to false\n";
				retval = false;
				if (timeout > 0) {
					if ((currentTime - startTime) > timeout) {
						std::cout << "Timed out waiting for threshold\n";
						retval = true;
					}
				}
			} else {
				thresholdCounter++;
				retval = (thresholdCounter >= thresholdCounterTarget);
			}
		}
	}

	Robot::shooterSystem->SetShooterEnabled(enabled, doLoad);
	return retval;
}
