// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"
#include "BSButton.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/SetWheelOffsets.h"
#include "Commands/ZeroGyro.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    gamepad.reset(new Joystick(2));
    
    driverRight.reset(new Joystick(1));
    
    driverLeft.reset(new Joystick(0));
    



    // SmartDashboard Buttons
    SmartDashboard::PutData("SetWheelOffsets", new SetWheelOffsets());
    SmartDashboard::PutData("ZeroGyro", new ZeroGyro());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    GPX.reset(new BSButton(gamepad, 3));
    GPY.reset(new BSButton(gamepad, 4));
    GPB.reset(new BSButton(gamepad, 2));
    GPA.reset(new BSButton(gamepad, 1));
    GPLT.reset(new BSButton(gamepad, 7));
    GPRT.reset(new BSButton(gamepad, 8));
    GPBack.reset(new BSButton(gamepad, 9));
    GPStart.reset(new BSButton(gamepad, 10));
    DL1.reset(new BSButton(driverLeft, 1));
    DL2.reset(new BSButton(driverLeft, 2));
    DL3.reset(new BSButton(driverLeft, 3));
    DL4.reset(new BSButton(driverLeft, 4));
    DL5.reset(new BSButton(driverLeft, 5));
    DL6.reset(new BSButton(driverLeft, 6));
    DL7.reset(new BSButton(driverLeft, 7));
    DL8.reset(new BSButton(driverLeft, 8));
    DL9.reset(new BSButton(driverLeft, 9));
    DL10.reset(new BSButton(driverLeft, 10));
    DL11.reset(new BSButton(driverLeft, 11));
    DL12.reset(new BSButton(driverLeft, 12));
    DR1.reset(new BSButton(driverRight, 1));
    DR2.reset(new BSButton(driverRight, 2));
    DR3.reset(new BSButton(driverRight, 3));
    DR4.reset(new BSButton(driverRight, 4));
    DR5.reset(new BSButton(driverRight, 5));
    DR6.reset(new BSButton(driverRight, 6));
    DR7.reset(new BSButton(driverRight, 7));
    DR8.reset(new BSButton(driverRight, 8));
    DR9.reset(new BSButton(driverRight, 9));
    DR10.reset(new BSButton(driverRight, 10));
    DR11.reset(new BSButton(driverRight, 11));
    DR12.reset(new BSButton(driverRight, 12));
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverLeft() {
   return driverLeft;
}

std::shared_ptr<Joystick> OI::getDriverRight() {
   return driverRight;
}

std::shared_ptr<Joystick> OI::getGamepad() {
   return gamepad;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

double OI::GetJoystickTwist() {
	const double threshold = 0.1;
	if (fabs(driverLeft->GetX()) < threshold) {
		return 0;
	} else {
		return driverLeft->GetX() / 2;
	}
}

double OI::GetJoystickX() {
	const double threshold = 0.1;
	if (fabs(driverRight->GetX()) < threshold) {
		return 0;
	} else {
		return driverRight->GetX() / 2;
	}
}

double OI::GetJoystickY() {
	const double threshold = 0.1;
	if (fabs(driverRight->GetY()) < threshold) {
		return 0;
	} else {
		return driverRight->GetY() / 2;
	}
}

double OI::GetGamepadLeftStick() {
	const double threshold = 0.1;
	if ((fabs(gamepad->GetRawAxis(1))) < threshold) {
		return 0;
	} else {
		return gamepad->GetRawAxis(1);
	}
}

double OI::GetGamepadRightStick() {
	const double threshold = 0.1;
	if ((fabs(gamepad->GetRawAxis(3))) < threshold) {
		return 0;
	} else {
		return gamepad->GetRawAxis(3);
	}
}
