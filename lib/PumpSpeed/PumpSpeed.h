/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include <Arduino.h>

#ifndef PumpSpeed_h
#define PumpSpeed_h

enum PumpSpeed
{
    SLOW = 1,
    SMEDIUM = 2,
    SHIGH = 3
};

static String pumpSpeedStr(PumpSpeed speed)
{
    switch (speed)
    {
    case SLOW:
        return "SLOW";
    case SMEDIUM:
        return "MEDIUM";
    case SHIGH:
        return "HIGH";
    default:
        return "";
    }
};

#endif