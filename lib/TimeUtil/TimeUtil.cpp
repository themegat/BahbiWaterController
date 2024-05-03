/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include "TimeUtil.h"
#ifndef TEST_FLAG
#include <ArduinoLog.h>
#endif

long TimeUtil::getTimeBetween(String fromTime, String toTime)
{
    long fT = toTimeStamp(fromTime);
    long tT = toTimeStamp(toTime);
    int secondsInDay = HOURS_IN_DAY * SECOND_IN_HOUR;

    if (tT < fT)
    {
        tT = tT + secondsInDay;
    }

    long difference = tT - fT;
#ifndef TEST_FLAG
    Log.info("TimeUtil::getTimeBetween fromTime: %s, toTime: %s, difference: %d" CR,
             fromTime, toTime, difference);
#endif
    return difference;
}

bool TimeUtil::isBetween(String fromTime, String toTime, String currentTime)
{
    long fT = toTimeStamp(fromTime);
    long tT = toTimeStamp(toTime);
    long cT = toTimeStamp(currentTime);
    int secondsInDay = HOURS_IN_DAY * SECOND_IN_HOUR;

    if (cT < fT && cT < tT)
    {
        cT = cT + secondsInDay;
    }

    if (tT < fT)
    {
        tT = tT + secondsInDay;
    }

    return cT > fT && cT < tT;
}

long TimeUtil::toTimeStamp(String time)
{
    String timeH = time.substring(0, time.indexOf(":"));
    time.replace(timeH + ":", " ");
    time.trim();
    String timeM = time.substring(0, time.indexOf(":"));
    time.replace(timeM + ":", " ");
    time.trim();
    int timeS = time.toInt();

    long result = (timeH.toInt() * SECOND_IN_HOUR) + (timeM.toInt() * SECONDS) + timeS;
#ifndef TEST_FLAG
    Log.info("TimeUtil::toTimeStamp result: %d" CR, result);
#endif
    return result;
}

int TimeUtil::extractSeconds(long timeStamp)
{
    long seconds = timeStamp / MILLISECONDS;
    int result = seconds % SECONDS;
    return result;
}

int TimeUtil::extractMinutes(long timeStamp)
{
    long seconds = timeStamp / MILLISECONDS;
    int result = (seconds % SECOND_IN_HOUR) / SECONDS;
    return result;
}

int TimeUtil::extractHours(long timeStamp)
{
    long seconds = timeStamp / MILLISECONDS;
    int result = seconds / SECOND_IN_HOUR;
    return result;
}

String TimeUtil::toTimeString(long timeStamp)
{
    int hours = extractHours(timeStamp);
    int minutes = extractMinutes(timeStamp);
    int seconds = extractSeconds(timeStamp);
    String result = String(hours) + ":" + String(minutes) + ":" + String(seconds);
    return result;
}