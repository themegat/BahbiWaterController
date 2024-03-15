/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


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
    static char fireUserEmail[50];
    static char fireUserPassword[30];

private:
};