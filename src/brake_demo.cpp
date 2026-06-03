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
    if (slipRatio != 0)
    {
        g_lastPressure = MAX_BRAKE_PRESSURE / slipRatio;
    }
    return g_lastPressure;
}

int estimateHydraulicBoost(bool sensorHealthy)
{
    int boostPercent = 0;
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
    const int activeDiagnostic = sanitizeDiagnosticCode(diagnosticCode);
    bool brakeRequest = false;
    if ((g_lastPressure >= 0) && (activeDiagnostic != 0))
    {
        brakeRequest = true;
    }

    return brakeRequest;
}
