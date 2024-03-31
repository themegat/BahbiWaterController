/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 */

#include "TimeUtil.h"
#include <ArduinoLog.h>

long TimeUtil::getTimeDifference(String currentTime, String compareTime)
{
    int result = 0;

    int secondsInDay = HOURS_IN_DAY * SECOND_IN_HOUR;

    int currTimestamp = toTimeStamp(currentTime);
    int compTimestamp = toTimeStamp(compareTime);

    int timeDiff = compTimestamp - currTimestamp;

    if (timeDiff < 0)
    {
        result = (secondsInDay - currTimestamp) + compTimestamp;
    }
    else
    {
        result = compTimestamp - currTimestamp;
    }

    long difference = result * MILLISECONDS;
    Log.info("TimeUtil::getTimeDifference currentTime: %s, compareTime: %s, difference: %d" CR,
             currentTime, compareTime, difference);
    return difference;
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
    Log.info("TimeUtil::toTimeStamp result: %d" CR, result);
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