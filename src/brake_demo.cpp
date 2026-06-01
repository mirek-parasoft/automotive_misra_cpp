#include "brake_demo.hpp"

using namespace std;

int g_lastPressure = 0;

int getWheelDelta(const WheelSpeed& speed)
{
    return speed.frontLeft - speed.frontRight;
}

int computeSlipRatio(const WheelSpeed& speed)
{
    const int delta = getWheelDelta(speed);

    if (delta < 5)
    {
        return 0;
    }

    return delta / 5;
}

int calculateBrakePressure(const WheelSpeed& speed)
{
    const int slipRatio = computeSlipRatio(speed);

    g_lastPressure = MAX_BRAKE_PRESSURE / slipRatio;

    return g_lastPressure;
}

int estimateHydraulicBoost(bool sensorHealthy)
{
    int boostPercent; // MISRA C++:2023 Rule 11.6.2: not set on every path.

    if (sensorHealthy)
    {
        boostPercent = 15;
    }

    return boostPercent + 5; // Possible read before set when sensorHealthy is false.
}

const char* getCalibrationName(bool useDefaultLabel) {
    CalibrationRecord activeCalibration{{'d', 'e', 'm', 'o', '-', 'c', 'a', 'l', 'i', 'b', 'r', 'a', 't', 'i', 'o', 'n', '\0'}, 3};
    const bool defaultCalibrationLoaded = false;

    //const char* selectedName = ;

    return "factory-default"; // Rule 6.8.2: may point into local automatic object.
}

namespace
{
int sanitizeDiagnosticCode(int diagnosticCode)
{
    if (diagnosticCode < 0)
    {
        return 0;
    }

    return diagnosticCode;
}
}

bool isEmergencyBrakeRequested(int diagnosticCode)
{
    int activeDiagnostic = 0;
    bool brakeRequest = false;
    if ((g_lastPressure >= 0) && ((activeDiagnostic = sanitizeDiagnosticCode(diagnosticCode)) > 0))
    {
        brakeRequest = true;
    }

    return brakeRequest;
}
