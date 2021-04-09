// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or bool constants.  This should not be used for any other purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace DriveConstants {
constexpr double kCountsPerRevolution = 1440.0;
constexpr double kWheelDiameterInch = 2.75;
}  // namespace DriveConstants

namespace AutoConstants {
  namespace DriveConstants {
    double ksVolts = 0.929;
    double kvVoltSecondsPerMeter = 6.33;
    double kaVoltSecondsSquaredPerMeter = 0.0389;

    double kPDriveVel = 0.085;

    double kTrackwidthMeters = 0.142072613;
    frc::DifferentialDriveKinematics kDriveKinematics (units::meter_t(kTrackwidthMeters));
  }

  namespace AutoConstants {
    double kMaxSpeedMetersPerSecond = 0.8;
    double kMaxAccelerationMetersPerSecondSquared = 0.8;

    // Reasonable baseline values for a RAMSETE follower in units of meters and seconds
    double kRamseteB = 2;
    double kRamseteZeta = 0.7;
  }
}