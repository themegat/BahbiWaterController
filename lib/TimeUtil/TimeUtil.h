/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include <Arduino.h>

#ifndef TimeUtil_h
#define TimeUtil_h

class TimeUtil {
    public:
    static int getTimeDifference(String currentTime, String compareTime);
    static int toTimeStamp(String time);
};

#endif