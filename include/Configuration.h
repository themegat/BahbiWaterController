#pragma once
#include <string>

// using namespace std

class Configuration
{
public:
    static char wifiSSID[30];
    static char wifiPassword[30];
    static char fireApiKey[50];
    static char fireDatabaseUrl[100];
    static char fireDeviceID[30];
    static long timeZone;
    static char ntpServer[30];

private:
};