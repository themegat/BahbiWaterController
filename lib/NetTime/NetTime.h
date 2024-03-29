/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include <Arduino.h>
#include "time.h"
#include <string>

#ifndef NetTime_h
#define NetTime_h

class NetTime
{
public:
    NetTime(long timeZone, int dayLightOff, String ntpServer);
    void init();
    String getDayOfMonth();
    String getMonth();
    String getYear();
    String getHour();
    String getMinute();
    String getSecond();
    String getDateTimeString();
    String getDateString();
    String getTimeString();
    int toNumber(char *value);

private:
    long _gmtOffsetSec;
    int _dayLightOffsetSec;
    String _ntpServer;
    struct tm _timeinfo;
    String _getFomatted(char *format);
};

#endif