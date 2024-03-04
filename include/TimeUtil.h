#include <Arduino.h>

#ifndef TimeUtil_h
#define TimeUtil_h

class TimeUtil {
    public:
    static int getTimeDifference(String currentTime, String compareTime);
    static int toTimeStamp(String time);
};

#endif