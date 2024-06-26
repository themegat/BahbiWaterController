/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */


#include "NetTime.h"
#include "ArduinoLog.h"

using namespace std;

NetTime::NetTime(long timeZone, int dayLightOffset, String ntpServer)
{
    _gmtOffsetSec = timeZone * 3600;
    _dayLightOffsetSec = dayLightOffset * 3600;
    _ntpServer = ntpServer;
}

void NetTime::init()
{
    configTime(_gmtOffsetSec, _dayLightOffsetSec, _ntpServer);
    Serial.print("Network Time: setting time infomation ");
    int count = 0;
    int retryDelay = 100;
    int countRetry = 30;
    bool timeInfoSet = false;
    do
    {
        if (!getLocalTime(&_timeinfo))
        {
            Serial.print(".");
            count++;
            delay(retryDelay);
        }
        else
        {
            count = countRetry;
            Serial.println();
            Serial.println("The time is - " + getDateTimeString());
            timeInfoSet = true;
        }
    } while (count < countRetry);

    if (!timeInfoSet)
    {
        Log.error("Failed to set time information");
    }
}

String NetTime::getDayOfMonth()
{
    return _getFomatted("%d");
}

String NetTime::getMonth()
{
    return _getFomatted("%m");
}

String NetTime::getYear()
{
    return _getFomatted("%Y");
}

String NetTime::getHour()
{
    return _getFomatted("%H");
}

String NetTime::getMinute()
{
    return _getFomatted("%M");
}

String NetTime::getSecond()
{
    return _getFomatted("%S");
}

int NetTime::toNumber(char *value)
{
    return stoi(value);
}

String NetTime::getDateTimeString()
{
    return getDayOfMonth() + "-" + getMonth() + "-" + getYear() +
           " " + getHour() + ":" + getMinute() + ":" + getSecond();
}

String NetTime::getDateString()
{
    return getDayOfMonth() + "-" + getMonth() + "-" + getYear();
}

String NetTime::getTimeString()
{
    return getHour() + ":" + getMinute() + ":" + getSecond();
}

String NetTime::_getFomatted(char *format)
{
    getLocalTime(&_timeinfo);
    char time[5];
    strftime(time, 5, format, &_timeinfo);
    return time;
}