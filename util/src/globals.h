#pragma once

#include <stdint.h>

#define ISUSED __attribute__((__unused__))

ISUSED static const char* g_multicastIp = "225.168.1.102";
const uint16_t g_multicastPort = 45654;

const int g_serverPingPeriod = 5000;
const int g_serverPingTimeout = 6000;

const int g_clientPingPeriod = 5000;
const int g_clientPingTimeout = 6000;

const int g_clientReconnectPeriod = 1000;

const int g_statusReport = 120000;

const int g_minSampleInterval_ms = 10;
const int g_minNofSamples = 100;
const int g_maxNofSamples = 1000;
const int g_maxMeasurementPeriod_sec = 30;

static const int TIMEROFF = -1;

enum DevelopmentMask
{
    None                        = 0x00,
    OnBailingOut                = 0x02,
    AnalysisAppendToSummary     = 0x04,
    SaveMeasurements            = 0x08,
    SaveClientSummaryLines      = 0x10
};

// #define TRACE_TCP_COMMANDS