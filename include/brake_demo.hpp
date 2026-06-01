#ifndef BRAKE_DEMO_HPP
#define BRAKE_DEMO_HPP

#define MAX_BRAKE_PRESSURE 1200

struct WheelSpeed
{
    int frontLeft;
    int frontRight;
};

struct CalibrationRecord
{
    char name[24];
    int version;
};

int calculateBrakePressure(const WheelSpeed& speed);
int computeSlipRatio(const WheelSpeed& speed);
int getWheelDelta(const WheelSpeed& speed);

int estimateHydraulicBoost(bool sensorHealthy);
const char* getCalibrationName(bool useDefaultLabel);
bool isEmergencyBrakeRequested(int diagnosticCode);

#endif
