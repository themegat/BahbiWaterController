/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */


#include "Configuration.h"
#include <Arduino.h>
#include <string>

char Configuration::wifiSSID[30] = "";
char Configuration::wifiPassword[30] = "";
char Configuration::fireApiKey[50] = "";
char Configuration::fireDatabaseUrl[100] = "";
char Configuration::fireDeviceID[30] = "";
long Configuration::timeZone = 2;
char Configuration::ntpServer[30] = "pool.ntp.org";
char Configuration::fireUserEmail[50] = "";
char Configuration::fireUserPassword[30] = "";