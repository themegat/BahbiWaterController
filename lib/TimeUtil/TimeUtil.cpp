/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include "TimeUtil.h"

int TimeUtil::getTimeDifference(String currentTime, String compareTime)
{
    int result = 0;

    int secondsInDay = 24 * 3600;

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

    return result * 1000;
}

int TimeUtil::toTimeStamp(String time)
{
    String timeH = time.substring(0, time.indexOf(":"));
    time.replace(timeH + ":", " ");
    time.trim();
    String timeM = time.substring(0, time.indexOf(":"));
    time.replace(timeM + ":", " ");
    time.trim();
    int timeS = time.toInt();

    return (timeH.toInt() * 360) + (timeM.toInt() * 60) + timeS;
}