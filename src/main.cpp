#include "brake_demo.hpp"

#include <iostream>

int main()
{
    WheelSpeed speed{50, 50};

    const int pressure = calculateBrakePressure(speed);
    std::cout << "Brake pressure: " << pressure << '\n';

    const int boost = estimateHydraulicBoost(false);
    std::cout << "Hydraulic boost: " << boost << '\n';

    const char* calibrationName = getCalibrationName();
    std::cout << "Calibration: " << calibrationName << '\n';

    const bool emergencyBrake = isEmergencyBrakeRequested(1);
    std::cout << "Emergency brake requested: " << emergencyBrake << '\n';

    return 0;
}
