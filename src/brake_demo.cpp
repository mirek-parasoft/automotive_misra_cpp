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
    int boostPercent;
    if (sensorHealthy)
    {
        boostPercent = 15;
    }
    return boostPercent + 5;
}

const char* selectCalibrationLabel(const CalibrationRecord& record, bool useDefaultLabel)
{
    if (useDefaultLabel)
    {
        return "factory-default";
    }

    return record.name;
}

const char* getCalibrationName()
{
    CalibrationRecord activeCalibration{{'d', 'e', 'm', 'o', '-', 'c', 'a', 'l', 'i', 'b', 'r', 'a', 't', 'i', 'o', 'n', '\0'}, 3};
    const bool defaultCalibrationLoaded = false;

    const char* selectedName = selectCalibrationLabel(activeCalibration, defaultCalibrationLoaded);

    return selectedName;
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
    if ((g_lastPressure >= 0) && (activeDiagnostic = sanitizeDiagnosticCode(diagnosticCode)))
    {
        brakeRequest = true;
    }

    return brakeRequest;
}
