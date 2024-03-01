#include "Configuration.h"
#include <Arduino.h>
#include <string>

char Configuration::wifiSSID[30] = "";
char Configuration::wifiPassword[30] = "";
char Configuration::fireApiKey[50] = "";
char Configuration::fireDatabaseUrl[100] = "";