// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include "Constants.h"
#include "frc2/command/RamseteCommand.h"
#include "wpi/SmallString.h"
#include <frc/Filesystem.h>
#include "wpi/Path.h"
#include "frc/trajectory/TrajectoryUtil.h"
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/trajectory/TrajectoryConfig.h>

#include <iostream>

RobotContainer::RobotContainer(){
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous

  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
    frc::SimpleMotorFeedforward<units::meter>(
      AutoConstants::DriveConstants::ksVolts,
      AutoConstants::DriveConstants::kvVoltSecondsPerMeter,
      AutoConstants::DriveConstants::kaVoltSecondsSquaredPerMeter
    ),
    AutoConstants::DriveConstants::kDriveKinematics, 10_V
  );

  frc::TrajectoryConfig config(
    AutoConstants::AutoConstants::kMaxSpeedMetersPerSecond,
    AutoConstants::AutoConstants::kMaxAccelerationMetersPerSecondSquared);
  config.SetKinematics(AutoConstants::DriveConstants::kDriveKinematics);
  config.AddConstraint(autoVoltageConstraint);

  frc::Trajectory trajectory;

  trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
    // Pass through these two interior waypoints, making an 's' curve path
    {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
    // End 3 meters straight ahead of where we started, facing forward
    frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
    config
  );
  
  wpi::SmallString<64> deployDir;
  frc::filesystem::GetDeployDirectory(deployDir);
  wpi::sys::path::append(deployDir, "paths");
  wpi::sys::path::append(deployDir, "path22.wpilib.json");
  //trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDir);

  frc2::RamseteCommand ramseteCommand(
    trajectory,
    [this]() { return m_drive.GetPose(); },
    frc::RamseteController(AutoConstants::AutoConstants::kRamseteB, AutoConstants::AutoConstants::kRamseteZeta),
    frc::SimpleMotorFeedforward<units::meters>(
      AutoConstants::DriveConstants::ksVolts,
      AutoConstants::DriveConstants::kvVoltSecondsPerMeter,
      AutoConstants::DriveConstants::kaVoltSecondsSquaredPerMeter),
    AutoConstants::DriveConstants::kDriveKinematics,
    [this]{ return m_drive.GetWheelSpeeds(); },
    frc2::PIDController(AutoConstants::DriveConstants::kPDriveVel, 0, 0),
    frc2::PIDController(AutoConstants::DriveConstants::kPDriveVel, 0, 0),
    [this](auto left, auto right){ m_drive.TankDriveVolts(left, -right); },
    {&m_drive}
  );

  m_drive.ResetOdometry(trajectory.InitialPose());
  return new frc2::SequentialCommandGroup(
    std::move(ramseteCommand),
    frc2::InstantCommand([this] { m_drive.TankDriveVolts(0_V, 0_V); }, {}));
}
