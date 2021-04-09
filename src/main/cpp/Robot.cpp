// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Timer.h>

#include "subsystems/Drivetrain.h"
#include "PID.h"
#include "frc2/command/RamseteCommand.h"
#include "wpi/SmallString.h"
#include <frc/Filesystem.h>
#include "wpi/Path.h"
#include "frc/trajectory/TrajectoryUtil.h"
Drivetrain driver;
frc::Trajectory trajectory;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  wpi::SmallString<64> deployDir;
  frc::filesystem::GetDeployDirectory(deployDir);
  wpi::sys::path::append(deployDir, "paths");
  wpi::sys::path::append(deployDir, "ThePath01.wpilib.json");
  trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDir);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}



void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  driver.ResetEncoders();
  // frc2::RamseteCommand ramseteCommand(
  //   trajectory,
  //   [this](){ return driver.GetPose(); },

  // );
}


void Robot::TeleopInit() {
  driver.ArcadeDrive(0.0, 0.0);
  driver.ResetEncoders();
}

void Robot::TeleopPeriodic() {
  driver.ArcadeDrive(0.5, 0.0);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
