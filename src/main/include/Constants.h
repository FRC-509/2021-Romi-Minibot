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
    constexpr auto ksVolts = 0.929_V;
    constexpr auto kvVoltSecondsPerMeter = 6.33 * 1_V * 1_s / 1_m;
    constexpr auto kaVoltSecondsSquaredPerMeter = 0.0389 * 1_V * 1_s * 1_s / 1_m;

    double kPDriveVel = 0.085;

    constexpr auto kTrackwidthMeters = 0.142072613_m;
    frc::DifferentialDriveKinematics kDriveKinematics(kTrackwidthMeters);
  }

  namespace AutoConstants {
    double kMaxSpeedMetersPerSecond = 0.8;
    double kMaxAccelerationMetersPerSecondSquared = 0.8;

    // Reasonable baseline values for a RAMSETE follower in units of meters and seconds
    double kRamseteB = 2;
    double kRamseteZeta = 0.7;
  }
}