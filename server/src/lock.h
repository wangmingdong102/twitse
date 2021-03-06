#pragma once
#include "globals.h"

#include <string>
#include <QObject>


class Lock : public QObject
{
    Q_OBJECT

    const double UNLOCK_THRESHOLD = 50.0;
    const double HILOCK_THRESHOLD = 20.0;
    const double STDLOCK_THRESHOLD = 30.0;

    const int QUALITY_ACCEPT = 8;
    const int MAX_QUALITY = 20;
    const double SPAN_QUALITY = MAX_QUALITY - QUALITY_ACCEPT;

#ifdef VCTCXO
    const int MIN_SAMPLE_INTERVAL_ms = 10;
    const int MIN_NOF_SAMPLES = 200;
    const int MAX_NOF_SAMPLES = 1000;
    const int MAX_MEAS_PERIOD_sec = 60;
#else
    const int MIN_SAMPLE_INTERVAL_ms = 10;
    const int MIN_NOF_SAMPLES = 100;
    const int MAX_NOF_SAMPLES = 1000;
    const int MAX_MEAS_PERIOD_sec = 30;
#endif


public:
    enum LockState
    {
        UNLOCKED,
        LOCKED,
        HILOCK
    };

    enum Distribution
    {
        BURST_SILENCE,
        EVENLY_DISTRIBUTED
    };

    Lock(const std::string& clientname);

    bool isHiLock() const;
    bool isLock() const;
    LockState getLockState() const;
    int getInterMeasurementDelaySecs() const;
    int getPeriodMSecs() const;
    int getMeasurementPeriodsecs() const;
    int getNofSamples() const;
    static std::string toColorString(LockState state);
    static std::string toString(LockState state);
    static void setClientPeriod(int period);
    static void setClientSamples(int samples);
    LockState errorOffset(double offset);
    void panic();

signals:
    void signalNewLockState(LockState m_lockState);

private:
    LockState m_lockState = UNLOCKED;
    std::string m_clientName;
    int m_counter = 0;
    int m_quality = 0;
    int m_maxSamples = MAX_NOF_SAMPLES;
    Distribution m_distribution = BURST_SILENCE;
    static int s_clientPeriod;
    static int s_clientSamples;

};
